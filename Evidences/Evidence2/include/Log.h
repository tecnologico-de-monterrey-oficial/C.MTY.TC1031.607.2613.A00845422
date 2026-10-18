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

    // valida la fecha y hora y genera la clave cronológica
    long long createKey() const;

    // valida la dirección IP y la descripción del evento
    void validateRecord() const;

    // reconstruye el registro en el formato del archivo
    std::string toString() const;

    // comparamos los registros por fecha y hora
    bool operator<(const Log& other) const;
    bool operator>(const Log& other) const;
    bool operator==(const Log& other) const;
    bool operator!=(const Log& other) const;
    bool operator<=(const Log& other) const;
    bool operator>=(const Log& other) const;
};

#endif /* LOG_H */