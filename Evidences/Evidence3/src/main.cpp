#include <iostream>
#include <stdexcept>

#include "FileManager.h"

int main(int argc, char* argv[]) {
    const std::string fileName = argc > 1 ? argv[1] : "data/log608-3.json";
    std::vector<Log> logs;
    BST<std::uint32_t> ips;

    try {
        const LoadResult result = readLogs(fileName, logs, ips);

        std::cout << "========== REPORTE DE LECTURA ==========\n"
                  << "Archivo: " << fileName << '\n'
                  << "Registros leidos: " << result.read << '\n'
                  << "Registros validos: " << result.loaded << '\n'
                  << "Registros invalidos: " << result.omitted.size() << '\n'
                  << "IPs distintas: " << ips.size() << '\n';

        for (const InvalidRecord& record : result.omitted) {
            std::cout << "Registro " << record.position
                      << " (linea " << record.line << ") omitido: "
                      << record.reason << '\n';
        }
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}