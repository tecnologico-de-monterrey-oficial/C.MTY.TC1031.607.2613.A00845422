#ifndef EVIDENCE3_LOG_H
#define EVIDENCE3_LOG_H

#include <cstdint>
#include <string>

struct Log {
    int year = 0;
    std::string month;
    int day = 0;
    std::string time;
    std::string ip;
    std::string message;
    long long key = 0;
    std::uint32_t ipKey = 0;

    Log();

    Log(
        int year,
        const std::string& month,
        int day,
        const std::string& time,
        const std::string& ip,
        const std::string& message
    );

    // Valida la fecha y hora y genera la clave cronológica.
    long long createKey() const;

    // Valida la IP y el mensaje, y guarda la llave numérica de la IP.
    void validateRecord();

    // Convierte los cuatro octetos de una IPv4 en una llave numérica.
    static bool parseIP(const std::string& ip, std::uint32_t& key);

    // Reconstruye el registro en el formato del archivo de salida.
    std::string toString() const;

    // Comparamos por IP numérica, fecha y hora, y mensaje.
    bool operator<(const Log& other) const;
    bool operator>(const Log& other) const;
    bool operator==(const Log& other) const;
    bool operator!=(const Log& other) const;
    bool operator<=(const Log& other) const;
    bool operator>=(const Log& other) const;
};

#endif