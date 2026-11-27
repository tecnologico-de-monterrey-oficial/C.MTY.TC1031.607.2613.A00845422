#include "SearchManager.h"
#include "Stack.h"

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {

// verifica que un texto contenga únicamente dígitos
bool containsOnlyDigits(const std::string& text) {
    if (text.empty()) {
        return false;
    }

    for (char character : text) {
        if (character < '0' || character > '9') {
            return false;
        }
    }

    return true;
}

} // namespace

// valida el día y obtiene sus límites de fecha y hora
SearchDay parseSearchDay(const std::string& text) {
    std::istringstream input(text);

    std::string month;
    std::string dayText;
    std::string yearText;
    std::string extra;

    // esperamos exactamente tres campos
    if (!(input >> month >> dayText >> yearText) ||
        (input >> extra)) {

        throw std::invalid_argument(
            "Usa el formato Mmm DD AAAA. Ejemplo: Sep 14 2024"
        );
    }

    if (!containsOnlyDigits(dayText) || dayText.size() > 2) {
        throw std::invalid_argument(
            "El dia debe contener uno o dos digitos"
        );
    }

    if (!containsOnlyDigits(yearText) || yearText.size() != 4) {
        throw std::invalid_argument(
            "El anio debe contener cuatro digitos"
        );
    }

    // usamos un Log vacío únicamente para validar fecha y hora
    // no llamamos al constructor de un evento completo
    Log limit;
    limit.month = month;
    limit.day = std::stoi(dayText);
    limit.year = std::stoi(yearText);
    limit.time = "00:00:00";

    SearchDay result;

    // createKey valida mes, día, año y hora
    result.startKey = limit.createKey();

    // obtenemos el último segundo del mismo día
    limit.time = "23:59:59";
    result.endKey = limit.createKey();

    // guardamos una presentación uniforme de la fecha
    std::ostringstream formatted;

    formatted << month << ' '
              << std::setfill('0') << std::setw(2)
              << limit.day << ' '
              << std::setw(4) << limit.year;

    result.text = formatted.str();

    return result;
}

// busca directamente sobre los nodos de la lista ordenada
int showLogsByDay(
    const DoublyLinkedList<Log>& logs,
    const SearchDay& day,
    bool descending
) {
    const NodeD<Log>* aux = logs.getHead();

    // la pila guarda apuntadores, sin copiar los registros
    Stack<const Log*> matches;

    int count = 0;

    std::cout << "\n========== LOGS DEL DIA ==========\n";
    std::cout << "Fecha: " << day.text << '\n';
    std::cout << "Orden: "
              << (descending ? "Descendente" : "Ascendente")
              << "\n\n";

    // saltamos los registros anteriores al día solicitado
    while (aux != nullptr && aux->data.key < day.startKey) {
        aux = aux->next;
    }

    // procesamos únicamente los registros del día
    // al pasar del límite superior termina el recorrido
    while (aux != nullptr && aux->data.key <= day.endKey) {
        if (descending) {
            // guardamos la dirección del registro en la pila
            matches.push(&aux->data);
        }
        else {
            std::cout << aux->data.toString() << '\n';
        }

        count++;
        aux = aux->next;
    }

    if (descending) {
        // el último registro encontrado sale primero
        while (!matches.isEmpty()) {
            const Log* record = matches.pop();
            std::cout << record->toString() << '\n';
        }
    }

    if (count == 0) {
        std::cout << "No existen registros para este dia.\n";
    }

    std::cout << "\nTotal encontrado: " << count << '\n';

    return count;
}