#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include "Log.h"
#include "DoublyLinkedList.h"

// guarda el resumen de la lectura del archivo
struct LoadResult {
    int loaded = 0;
    int omitted = 0;
};

// carga los registros válidos conservando el orden de llegada
LoadResult readLogs(
    const std::string& fileName,
    DoublyLinkedList<Log>& logs
);

// escribe los registros en el orden actual de la lista
void writeLogs(
    const std::string& fileName,
    const DoublyLinkedList<Log>& logs
);

#endif /* FILE_MANAGER_H */