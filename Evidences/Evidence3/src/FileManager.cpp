#include "FileManager.h"

#include <charconv>
#include <fstream>
#include <regex>
#include <stdexcept>

namespace {

const std::string fields[] = {"month", "day", "year", "time", "ip", "message"};

// Campo JSON plano: nombre, dos puntos y un texto o entero.
const std::regex fieldPattern(
    R"json(\s*"([^"\\]+)"\s*:\s*("(?:[^"\\\x00-\x1f]|\\["\\/bfnrt])*"|-?(?:0|[1-9][0-9]*))\s*)json"
);

std::string trim(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }

    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

std::string readText(const std::string& token, const std::string& field) {
    if (token.front() != '"') {
        throw std::invalid_argument("Se esperaba texto en " + field);
    }

    const std::string escapes = "\"\\/bfnrt";
    const std::string decoded = "\"\\/\b\f\n\r\t";
    std::string value;

    // Quitamos las comillas y traducimos los escapes simples de JSON.
    for (std::size_t i = 1; i + 1 < token.size(); ++i) {
        if (token[i] == '\\') {
            ++i;
            value += decoded[escapes.find(token[i])];
        } else {
            value += token[i];
        }
    }

    return value;
}

int readInteger(const std::string& token, const std::string& field) {
    int value = 0;
    const char* end = token.data() + token.size();
    const auto result = std::from_chars(token.data(), end, value);

    if (result.ec != std::errc{} || result.ptr != end) {
        throw std::invalid_argument("Se esperaba un entero valido en " + field);
    }

    return value;
}

Log parseLog(const std::string& line) {
    if (line.size() < 2 || line.front() != '{' || line.back() != '}') {
        throw std::invalid_argument("Se esperaba un objeto JSON");
    }

    const std::string body = trim(line.substr(1, line.size() - 2));
    std::string tokens[6];

    auto position = body.cbegin();
    const auto end = body.cend();

    while (position != end) {
        std::smatch match;
        if (!std::regex_search(position, end, match, fieldPattern,
                               std::regex_constants::match_continuous)) {
            throw std::invalid_argument("Campo JSON mal formado o tipo no admitido");
        }

        for (int i = 0; i < 6; ++i) {
            if (match[1].str() == fields[i]) {
                if (!tokens[i].empty()) {
                    throw std::invalid_argument("Campo duplicado: " + fields[i]);
                }
                tokens[i] = match[2].str();
                break;
            }
        }

        position = match[0].second;
        if (position == end) {
            break;
        }

        if (*position != ',' || ++position == end) {
            throw std::invalid_argument("Separador de campos invalido");
        }
    }

    for (int i = 0; i < 6; ++i) {
        if (tokens[i].empty()) {
            throw std::invalid_argument("Falta el campo " + fields[i]);
        }
    }

    const std::string month = readText(tokens[0], "month");
    const int day = readInteger(tokens[1], "day");
    const int year = readInteger(tokens[2], "year");
    const std::string time = readText(tokens[3], "time");
    const std::string ip = readText(tokens[4], "ip");
    const std::string message = readText(tokens[5], "message");

    return Log(year, month, day, time, ip, message);
}

} // namespace

LoadResult readLogs(
    const std::string& fileName,
    std::vector<Log>& logs,
    BST<std::uint32_t>& ips
) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo: " + fileName);
    }

    LoadResult result;
    std::string line;
    std::size_t lineNumber = 0;
    bool opened = false;
    bool closed = false;
    bool previousHadComma = false;

    while (std::getline(file, line)) {
        ++lineNumber;
        line = trim(line);

        if (line.empty()) {
            continue;
        }

        if (!opened) {
            if (line != "[") {
                throw std::runtime_error("Se esperaba [ al inicio del archivo");
            }
            opened = true;
            continue;
        }

        if (closed) {
            throw std::runtime_error("Hay contenido despues del cierre del arreglo");
        }

        if (line == "]") {
            if (previousHadComma) {
                throw std::runtime_error("Hay una coma antes del cierre del arreglo");
            }
            closed = true;
            continue;
        }

        const bool missingComma = result.read > 0 && !previousHadComma;
        ++result.read;

        previousHadComma = line.back() == ',';
        if (previousHadComma) {
            line.pop_back();
            line = trim(line);
        }

        Log record;
        try {
            if (missingComma) {
                throw std::invalid_argument("Falta coma antes de este objeto");
            }

            record = parseLog(line);
        } catch (const std::invalid_argument& error) {
            result.omitted.push_back({result.read, lineNumber, error.what()});
            continue;
        }

        // Conservamos el orden de llegada y contamos la IP en el BST.
        logs.push_back(record);
        ips.insert(record.ipKey);
        ++result.loaded;
    }

    if (file.bad() || (file.fail() && !file.eof())) {
        throw std::runtime_error("Ocurrio un error al leer: " + fileName);
    }

    if (!closed) {
        throw std::runtime_error("Falta el cierre del arreglo JSON");
    }

    return result;
}