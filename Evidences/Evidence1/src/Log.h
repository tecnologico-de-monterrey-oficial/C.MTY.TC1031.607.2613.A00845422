#ifndef LOG_H
#define LOG_H

#include <string>

struct Log {
    int year = 0;
    std::string month;
    int day = 0;
    std::string time;
    std::string ip;
    std::string message;
    long long key = 0;

    Log();

    Log(
        int year,
        const std::string& month,
        int day,
        const std::string& time,
        const std::string& ip,
        const std::string& message
    );

    long long createKey() const;

    std::string toString() const;

    bool operator<(const Log& other) const;
    bool operator>(const Log& other) const;
    bool operator==(const Log& other) const;
    bool operator!=(const Log& other) const;
    bool operator<=(const Log& other) const;
    bool operator>=(const Log& other) const;
};

#endif