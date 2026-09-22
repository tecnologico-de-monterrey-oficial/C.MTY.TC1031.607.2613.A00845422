#include "Log.h"

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
    if (year <= 0) {
        throw std::invalid_argument("Anio invalido");
    }

    if (day < 1 || day > 31) {
        throw std::invalid_argument(
            "Dia fuera de rango: " + std::to_string(day)
        );
    }

    if (time.size() != 8 || time[2] != ':' || time[5] != ':') {
        throw std::invalid_argument("Hora invalida: " + time);
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

    int monthNumber = monthToNumber(month);

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