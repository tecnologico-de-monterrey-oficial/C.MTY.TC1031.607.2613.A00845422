#ifndef STATISTICS_MANAGER_H
#define STATISTICS_MANAGER_H

#include <map>
#include <string>

#include "Log.h"
#include "DoublyLinkedList.h"

// guarda el total y las frecuencias de los registros
struct FileStatistics {
    int total = 0;

    // la clave del día tiene el formato AAAAMMDD
    std::map<long long, int> days;

    std::map<std::string, int> events;
    std::map<std::string, int> ips;
};

// cuenta las apariciones recorriendo la lista
FileStatistics calculateStatistics(
    const DoublyLinkedList<Log>& logs
);

// muestra los máximos y todos los empates
void showStatistics(const FileStatistics& statistics);

#endif /* STATISTICS_MANAGER_H */