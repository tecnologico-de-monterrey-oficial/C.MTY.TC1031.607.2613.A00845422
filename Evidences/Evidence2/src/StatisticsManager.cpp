#include "StatisticsManager.h"

#include <iomanip>
#include <iostream>
#include <sstream>

namespace {

// obtiene la mayor frecuencia de un mapa
template <typename K>
int maximumFrequency(const std::map<K, int>& frequencies) {
    int maximum = 0;

    // revisamos todas las frecuencias
    for (const auto& entry : frequencies) {
        if (entry.second > maximum) {
            maximum = entry.second;
        }
    }

    return maximum;
}

// convierte una clave AAAAMMDD al formato Mmm DD AAAA
std::string formatDay(long long dayKey) {
    int year = static_cast<int>(dayKey / 10000);
    int month = static_cast<int>((dayKey / 100) % 100);
    int day = static_cast<int>(dayKey % 100);

    std::string monthText;

    switch (month) {
        case 1: monthText = "Jan"; break;
        case 2: monthText = "Feb"; break;
        case 3: monthText = "Mar"; break;
        case 4: monthText = "Apr"; break;
        case 5: monthText = "May"; break;
        case 6: monthText = "Jun"; break;
        case 7: monthText = "Jul"; break;
        case 8: monthText = "Aug"; break;
        case 9: monthText = "Sep"; break;
        case 10: monthText = "Oct"; break;
        case 11: monthText = "Nov"; break;
        case 12: monthText = "Dec"; break;
    }

    std::ostringstream output;

    output << monthText << ' '
           << std::setfill('0') << std::setw(2) << day << ' '
           << std::setw(4) << year;

    return output.str();
}

// muestra todos los textos que comparten la frecuencia máxima
void showTextMaximums(
    const std::string& title,
    const std::map<std::string, int>& frequencies
) {
    int maximum = maximumFrequency(frequencies);

    std::cout << "\n" << title << '\n';

    // recorremos todo el mapa para incluir los empates
    for (const auto& entry : frequencies) {
        if (entry.second == maximum) {
            std::cout << "- " << entry.first
                      << ": " << entry.second
                      << " apariciones\n";
        }
    }
}

} // namespace

// calcula las estadísticas sin modificar la lista
FileStatistics calculateStatistics(
    const DoublyLinkedList<Log>& logs
) {
    FileStatistics statistics;

    const NodeD<Log>* aux = logs.getHead();

    // recorremos directamente los nodos
    while (aux != nullptr) {
        const Log& record = aux->data;

        statistics.total++;

        // quitamos HHMMSS para conservar AAAAMMDD
        long long dayKey = record.key / 1000000LL;

        // las claves nuevas comienzan con un contador de cero
        statistics.days[dayKey]++;
        statistics.events[record.message]++;
        statistics.ips[record.ip]++;

        aux = aux->next;
    }

    return statistics;
}

// muestra el resumen y todos los máximos empatados
void showStatistics(const FileStatistics& statistics) {
    std::cout << "\n========== ESTADISTICAS DEL ARCHIVO ==========\n";
    std::cout << "Total de registros: " << statistics.total << '\n';

    // evitamos buscar máximos si no existen registros
    if (statistics.total == 0) {
        std::cout << "No hay registros para calcular frecuencias.\n";
        return;
    }

    int maximumDay = maximumFrequency(statistics.days);

    std::cout << "\nDia(s) con mas incidentes:\n";

    // mostramos todos los días con la frecuencia máxima
    for (const auto& entry : statistics.days) {
        if (entry.second == maximumDay) {
            std::cout << "- " << formatDay(entry.first)
                      << ": " << entry.second
                      << " incidentes\n";
        }
    }

    showTextMaximums(
        "Tipo(s) de evento mas frecuente(s):",
        statistics.events
    );

    showTextMaximums(
        "Direccion(es) IP mas frecuente(s):",
        statistics.ips
    );
}