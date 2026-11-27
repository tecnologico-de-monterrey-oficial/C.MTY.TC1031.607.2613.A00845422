#include "Log.h"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>

// estas funciones auxiliares se usan únicamente en este archivo
namespace {

// convierte la abreviatura del mes a su número
int monthToNumber(const std::string& month) {
    if (month == "Jan") return 1;
    if (month == "Feb") return 2;
    if (month == "Mar") return 3;
    if (month == "Apr") return 4;
    if (month == "May") return 5;
    if (month == "Jun") return 6;
    if (month == "Jul") return 7;
    if (month == "Aug") return 8;
    if (month == "Sep") return 9;
    if (month == "Oct") return 10;
    if (month == "Nov") return 11;
    if (month == "Dec") return 12;

    throw std::invalid_argument("Mes invalido: " + month);
}

// determina si el año es bisiesto
bool isLeapYear(int year) {
    return year % 400 == 0 ||
           (year % 4 == 0 && year % 100 != 0);
}

// obtiene la cantidad de días del mes
int daysInMonth(int month, int year) {
    switch (month) {
        case 2:
            return isLeapYear(year) ? 29 : 28;

        case 4:
        case 6:
        case 9:
        case 11:
            return 30;

        default:
            return 31;
    }
}

// valida que la hora tenga el formato HH:MM:SS
bool hasValidTimeCharacters(const std::string& time) {
    if (time.size() != 8) {
        return false;
    }

    // los dos puntos deben estar en estas posiciones
    if (time[2] != ':' || time[5] != ':') {
        return false;
    }

    // las demás posiciones deben contener dígitos
    for (int i = 0; i < static_cast<int>(time.size()); i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (!std::isdigit(static_cast<unsigned char>(time[i]))) {
            return false;
        }
    }

    return true;
}

// valida una dirección IPv4 con cuatro números de 0 a 255
bool isValidIP(const std::string& ip) {
    int parts = 0;
    int value = 0;
    int digits = 0;

    // recorremos la dirección carácter por carácter
    for (char character : ip) {
        if (character >= '0' && character <= '9') {
            digits++;

            // cada sección puede tener hasta tres dígitos
            if (digits > 3) {
                return false;
            }

            value = value * 10 + (character - '0');

            if (value > 255) {
                return false;
            }
        }
        else if (character == '.') {
            // no permitimos secciones vacías ni más de tres puntos
            if (digits == 0 || parts >= 3) {
                return false;
            }

            parts++;
            value = 0;
            digits = 0;
        }
        else {
            // no permitimos letras ni otros caracteres
            return false;
        }
    }

    // deben existir tres puntos y una última sección no vacía
    return parts == 3 && digits > 0;
}

} // namespace

// crea un registro vacío
Log::Log() = default;

// crea y valida un registro completo
Log::Log(
    int year,
    const std::string& month,
    int day,
    const std::string& time,
    const std::string& ip,
    const std::string& message
) : year(year),
    month(month),
    day(day),
    time(time),
    ip(ip),
    message(message) {

    // validamos fecha y hora antes de generar la clave
    key = createKey();

    // validamos los demás datos del evento
    validateRecord();
}

// valida la fecha y hora y genera la clave cronológica
long long Log::createKey() const {
    if (year < 1 || year > 9999) {
        throw std::invalid_argument(
            "Anio fuera de rango: " + std::to_string(year)
        );
    }

    int monthNumber = monthToNumber(month);
    int maximumDay = daysInMonth(monthNumber, year);

    // validamos el día considerando el mes y los años bisiestos
    if (day < 1 || day > maximumDay) {
        throw std::invalid_argument(
            "Dia invalido para el mes indicado: " +
            std::to_string(day)
        );
    }

    if (!hasValidTimeCharacters(time)) {
        throw std::invalid_argument(
            "Formato de hora invalido: " + time
        );
    }

    // extraemos las tres partes de la hora
    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(3, 2));
    int second = std::stoi(time.substr(6, 2));

    if (hour > 23 || minute > 59 || second > 59) {
        throw std::invalid_argument(
            "Hora fuera de rango: " + time
        );
    }

    // formamos una clave con el orden AAAAMMDDHHMMSS
    return static_cast<long long>(year) * 10000000000LL
         + static_cast<long long>(monthNumber) * 100000000LL
         + static_cast<long long>(day) * 1000000LL
         + static_cast<long long>(hour) * 10000LL
         + static_cast<long long>(minute) * 100LL
         + second;
}

// valida los datos adicionales del evento
void Log::validateRecord() const {
    if (!isValidIP(ip)) {
        throw std::invalid_argument(
            "Direccion IP invalida: " + ip
        );
    }

    // el mensaje debe incluir al menos un carácter no blanco
    if (message.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument(
            "La descripcion del evento esta vacia"
        );
    }
}

// reconstruye el registro en el formato original
std::string Log::toString() const {
    std::ostringstream output;

    output << month << ' '
           << std::setfill('0') << std::setw(2) << day << ' '
           << std::setw(4) << year << ' '
           << time << ' '
           << ip << ' '
           << message;

    return output.str();
}

// compara si este registro ocurrió antes que el otro
bool Log::operator<(const Log& other) const {
    return key < other.key;
}

// compara si este registro ocurrió después que el otro
bool Log::operator>(const Log& other) const {
    return key > other.key;
}

// indica si ambos tienen la misma fecha y hora
// esto no significa que sean el mismo evento
bool Log::operator==(const Log& other) const {
    return key == other.key;
}

bool Log::operator!=(const Log& other) const {
    return key != other.key;
}

bool Log::operator<=(const Log& other) const {
    return key <= other.key;
}

bool Log::operator>=(const Log& other) const {
    return key >= other.key;
}