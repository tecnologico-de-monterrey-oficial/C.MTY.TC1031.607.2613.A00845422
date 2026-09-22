#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

std::vector<Log> readLogs(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error(
            "No se pudo abrir el archivo: " + fileName
        );
    }

    std::vector<Log> logs;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        lineNumber++;

        if (line.empty()) {
            continue;
        }

        std::istringstream lineStream(line);

        std::string month;
        int day;
        int year;
        std::string time;
        std::string ip;
        std::string message;

        if (!(lineStream >> month >> day >> year >> time >> ip)) {
            std::cerr
                << "Advertencia: formato invalido en la linea "
                << lineNumber << '\n';

            continue;
        }

        std::getline(lineStream >> std::ws, message);

        if (message.empty()) {
            std::cerr
                << "Advertencia: mensaje vacio en la linea "
                << lineNumber << '\n';

            continue;
        }

        try {
            logs.emplace_back(
                year,
                month,
                day,
                time,
                ip,
                message
            );
        }
        catch (const std::exception& error) {
            std::cerr
                << "Advertencia en la linea "
                << lineNumber << ": "
                << error.what() << '\n';
        }
    }

    return logs;
}

void writeLogs(
    const std::string& fileName,
    const std::vector<Log>& logs
) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error(
            "No se pudo crear el archivo: " + fileName
        );
    }

    for (const Log& log : logs) {
        file << log.toString() << '\n';
    }

    if (!file.good()) {
        throw std::runtime_error(
            "Ocurrio un error al escribir: " + fileName
        );
    }
}