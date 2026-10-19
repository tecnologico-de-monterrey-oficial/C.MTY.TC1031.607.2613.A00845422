#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "StatisticsManager.h"

using namespace std;

// detiene la prueba si una condición no se cumple
void check(bool condition, const string& message) {
    if (!condition) {
        throw runtime_error(message);
    }
}

// captura la salida para comprobar los máximos y empates
string captureOutput(const FileStatistics& statistics) {
    ostringstream output;
    streambuf* previous = cout.rdbuf(output.rdbuf());

    try {
        showStatistics(statistics);
    }
    catch (...) {
        // restauramos cout incluso si ocurre un error
        cout.rdbuf(previous);
        throw;
    }

    cout.rdbuf(previous);
    return output.str();
}

int main() {
    try {
        cout << "========== PRUEBAS DE ESTADISTICAS ==========\n";

        DoublyLinkedList<Log> logs;

        // caso 1: lista vacía
        FileStatistics empty = calculateStatistics(logs);

        check(empty.total == 0, "Total incorrecto en lista vacia");
        check(empty.days.empty(), "Hay dias en lista vacia");
        check(empty.events.empty(), "Hay eventos en lista vacia");
        check(empty.ips.empty(), "Hay IPs en lista vacia");

        string emptyOutput = captureOutput(empty);

        check(
            emptyOutput.find("No hay registros") != string::npos,
            "Falta el mensaje de lista vacia"
        );

        cout << "\nLista vacia: prueba correcta.\n";

        // caso 2: un solo registro
        logs.addLast(Log(
            2024, "Sep", 29, "10:00:00",
            "10.0.0.1", "Evento A"
        ));

        FileStatistics single = calculateStatistics(logs);

        check(single.total == 1, "Total incorrecto con un registro");
        check(single.days.at(20240929LL) == 1, "Dia incorrecto");
        check(single.events.at("Evento A") == 1, "Evento incorrecto");
        check(single.ips.at("10.0.0.1") == 1, "IP incorrecta");

        cout << "Un registro: prueba correcta.\n";

        // caso 3: datos desordenados con empates
        logs.clear();

        logs.addLast(Log(
            2024, "Sep", 30, "12:00:00",
            "10.0.0.2", "Evento B"
        ));

        logs.addLast(Log(
            2024, "Sep", 29, "10:00:00",
            "10.0.0.1", "Evento A"
        ));

        logs.addLast(Log(
            2024, "Sep", 30, "09:00:00",
            "10.0.0.1", "Evento A"
        ));

        logs.addLast(Log(
            2024, "Sep", 29, "11:00:00",
            "10.0.0.2", "Evento B"
        ));

        // tiene menor frecuencia y no debe aparecer entre los máximos
        logs.addLast(Log(
            2024, "Oct", 1, "08:00:00",
            "10.0.0.3", "Evento C"
        ));

        FileStatistics tied = calculateStatistics(logs);

        check(tied.total == 5, "El total debe ser 5");

        // comprobamos cada contador de días
        check(tied.days.size() == 3, "Deben existir tres dias");
        check(tied.days.at(20240929LL) == 2, "Conteo del dia 29 incorrecto");
        check(tied.days.at(20240930LL) == 2, "Conteo del dia 30 incorrecto");
        check(tied.days.at(20241001LL) == 1, "Conteo de octubre incorrecto");

        // comprobamos cada contador de eventos
        check(tied.events.size() == 3, "Deben existir tres eventos");
        check(tied.events.at("Evento A") == 2, "Conteo de A incorrecto");
        check(tied.events.at("Evento B") == 2, "Conteo de B incorrecto");
        check(tied.events.at("Evento C") == 1, "Conteo de C incorrecto");

        // comprobamos cada contador de IPs
        check(tied.ips.size() == 3, "Deben existir tres IPs");
        check(tied.ips.at("10.0.0.1") == 2, "Conteo de IP 1 incorrecto");
        check(tied.ips.at("10.0.0.2") == 2, "Conteo de IP 2 incorrecto");
        check(tied.ips.at("10.0.0.3") == 1, "Conteo de IP 3 incorrecto");

        string output = captureOutput(tied);

        // comprobamos que aparecen ambos días empatados
        check(
            output.find("Sep 29 2024: 2 incidentes") != string::npos,
            "Falta el primer dia empatado"
        );

        check(
            output.find("Sep 30 2024: 2 incidentes") != string::npos,
            "Falta el segundo dia empatado"
        );

        // comprobamos los empates de eventos
        check(
            output.find("Evento A: 2 apariciones") != string::npos &&
            output.find("Evento B: 2 apariciones") != string::npos,
            "Falta algun evento empatado"
        );

        // comprobamos los empates de IPs
        check(
            output.find("10.0.0.1: 2 apariciones") != string::npos &&
            output.find("10.0.0.2: 2 apariciones") != string::npos,
            "Falta alguna IP empatada"
        );

        // los elementos con menor frecuencia no deben aparecer
        check(
            output.find("Oct 01 2024") == string::npos &&
            output.find("Evento C") == string::npos &&
            output.find("10.0.0.3") == string::npos,
            "Se mostro un elemento que no es maximo"
        );

        cout << "\nDatos desordenados con empates:\n";
        cout << output;

        // ordenar no debe cambiar ninguna frecuencia
        logs.sort();

        FileStatistics sorted = calculateStatistics(logs);

        check(
            sorted.total == tied.total &&
            sorted.days == tied.days &&
            sorted.events == tied.events &&
            sorted.ips == tied.ips,
            "Las frecuencias cambiaron al ordenar"
        );

        cout << "\nEstadisticas antes y despues de ordenar: iguales.\n";
        cout << "Todas las pruebas pasaron correctamente.\n";
    }
    catch (const exception& error) {
        cerr << "\nPrueba fallida: " << error.what() << '\n';
        return 1;
    }

    return 0;
}