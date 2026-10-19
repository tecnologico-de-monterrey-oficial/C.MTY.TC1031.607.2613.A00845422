#ifndef SEARCH_MANAGER_H
#define SEARCH_MANAGER_H

#include <string>
#include "Log.h"
#include "DoublyLinkedList.h"

// representa un día válido y sus límites cronológicos
struct SearchDay {
    std::string text;
    long long startKey = 0;
    long long endKey = 0;
};

// convierte y valida una fecha con formato Mmm DD AAAA
SearchDay parseSearchDay(const std::string& text);

// muestra los registros del día y regresa el total encontrado
// requiere que la lista esté ordenada
int showLogsByDay(
    const DoublyLinkedList<Log>& logs,
    const SearchDay& day,
    bool descending
);

#endif /* SEARCH_MANAGER_H */