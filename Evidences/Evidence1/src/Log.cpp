#include "Log.h"

#include <cctype>
#include <iomanip>
#include <sstream>
#include <stdexcept>

namespace {

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


bool isLeapYear(int year) {
    return (
        year % 400 == 0 ||
        (year % 4 == 0 && year % 100 != 0)
    );
}


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


bool hasValidTimeCharacters(const std::string& time) {
    if (time.size() != 8) {
        return false;
    }

    if (time[2] != ':' || time[5] != ':') {
        return false;
    }

    for (int i = 0; i < static_cast<int>(time.size()); i++) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (!std::isdigit(
            static_cast<unsigned char>(time[i])
        )) {
            return false;
        }
    }

    return true;
}

} // namespace


Log::Log() = default;


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

    key = createKey();
}


long long Log::createKey() const {
    if (year < 1 || year > 9999) {
        throw std::invalid_argument(
            "Anio fuera de rango: " +
            std::to_string(year)
        );
    }

    int monthNumber = monthToNumber(month);
    int maximumDay = daysInMonth(monthNumber, year);

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

    int hour = std::stoi(time.substr(0, 2));
    int minute = std::stoi(time.substr(3, 2));
    int second = std::stoi(time.substr(6, 2));

    if (hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59) {

        throw std::invalid_argument(
            "Hora fuera de rango: " + time
        );
    }

    return static_cast<long long>(year) * 10000000000LL
         + static_cast<long long>(monthNumber) * 100000000LL
         + static_cast<long long>(day) * 1000000LL
         + static_cast<long long>(hour) * 10000LL
         + static_cast<long long>(minute) * 100LL
         + second;
}


std::string Log::toString() const {
    std::ostringstream output;

    output << month << ' '
           << std::setw(2)
           << std::setfill('0')
           << day << ' '
           << year << ' '
           << time << ' '
           << ip << ' '
           << message;

    return output.str();
}


bool Log::operator<(const Log& other) const {
    return key < other.key;
}


bool Log::operator>(const Log& other) const {
    return key > other.key;
}


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