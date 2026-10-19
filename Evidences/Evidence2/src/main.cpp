#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "FileManager.h"
#include "SearchManager.h"
#include "StatisticsManager.h"

using namespace std;

// lee una opción completa y valida su rango
// regresa false si termina la entrada de la terminal
bool readOption(
    const string& message,
    int minimum,
    int maximum,
    int& option
) {
    while (true) {
        cout << message;

        string line;

        if (!getline(cin, line)) {
            return false;
        }

        istringstream input(line);
        int value;

        if (input >> value) {
            // descartamos espacios después del número
            input >> ws;

            // rechazamos caracteres adicionales y valores fuera del rango
            if (input.eof() &&
                value >= minimum &&
                value <= maximum) {

                option = value;
                return true;
            }
        }

        cout << "Opcion invalida. Escribe un numero entre "
             << minimum << " y " << maximum << ".\n";
    }
}

// muestra información para comprobar la carga
void printLoadSummary(
    const string& fileName,
    const LoadResult& result,
    const DoublyLinkedList<Log>& logs
) {
    cout << "\n========== RESUMEN DE CARGA ==========\n";
    cout << "Archivo: " << fileName << '\n';
    cout << "Registros cargados: " << result.loaded << '\n';
    cout << "Lineas omitidas: " << result.omitted << '\n';

    if (logs.isEmpty()) {
        cout << "El archivo no contiene registros validos.\n";
        return;
    }

    // consultamos los extremos sin modificar los registros
    cout << "\nPrimer registro recibido:\n";
    cout << logs.getHead()->data.toString() << '\n';

    cout << "\nUltimo registro recibido:\n";
    cout << logs.getTail()->data.toString() << '\n';

    cout << "\nLos registros conservan el orden de llegada.\n";
}

// presenta las opciones de la aplicación
void showMenu() {
    cout << "\n========== EVIDENCIA 2 ==========\n";
    cout << "1. Ordenar por fecha y hora\n";
    cout << "2. Buscar logs por dia\n";
    cout << "3. Mostrar logs por dia en orden descendente\n";
    cout << "4. Estadisticas del archivo\n";
    cout << "5. Salir\n";
}

// ordena los registros, muestra las mediciones y genera la salida
// regresa false si termina la entrada de la terminal
bool sortLogs(
    DoublyLinkedList<Log>& logs,
    const string& fileName
) {
    if (logs.isEmpty()) {
        cout << "\nNo hay registros para ordenar.\n";
        return true;
    }

    // verificamos el orden antes de ejecutar Merge Sort
    if (logs.isSorted()) {
        cout << "\nLa lista ya esta ordenada. "
             << "No se ejecutara nuevamente Merge Sort.\n";

        // exportamos también un archivo que ya llegó ordenado
        try {
            filesystem::create_directories("out");
            writeLogs("out/output608.out", logs);

            cout << "Archivo generado: out/output608.out\n";
        }
        catch (const exception& error) {
            cerr << "No se pudo guardar la salida: "
                 << error.what() << '\n';
        }

        return true;
    }

    cout << "\nAntes de ordenar, predice como crecera "
         << "el numero de comparaciones al aumentar los datos:\n";
    cout << "1. Aproximadamente n\n";
    cout << "2. Aproximadamente n * log2(n)\n";
    cout << "3. Aproximadamente n^2\n";

    int prediction;

    if (!readOption("Selecciona tu prediccion: ", 1, 3, prediction)) {
        return false;
    }

    string predictionText;

    switch (prediction) {
        case 1:
            predictionText = "n";
            break;

        case 2:
            predictionText = "n * log2(n)";
            break;

        case 3:
            predictionText = "n^2";
            break;
    }

    // medimos únicamente la llamada al ordenamiento
    auto start = chrono::steady_clock::now();

    SortStats stats = logs.sort();

    auto end = chrono::steady_clock::now();

    double elapsedTime =
        chrono::duration<double, micro>(end - start).count();

    // esta comprobación queda fuera de la medición
    bool ordered = logs.isSorted();

    cout << "\n========== RESULTADOS DEL ORDENAMIENTO ==========\n";
    cout << "Algoritmo: Merge Sort\n";
    cout << "Archivo: " << fileName << '\n';
    cout << "Registros: " << logs.getSize() << '\n';
    cout << "Prediccion: " << predictionText << '\n';
    cout << "Tiempo: " << elapsedTime << " microsegundos\n";
    cout << "Comparaciones entre datos: "
         << stats.comparisons << '\n';
    cout << "Profundidad maxima de recursion: "
         << stats.maxDepth << '\n';

    cout << "Verificacion del orden: "
         << (ordered ? "Correcto" : "Incorrecto") << '\n';

    // la evaluación de la predicción utiliza la complejidad teórica
    cout << "Crecimiento teorico de Merge Sort: O(n log n)\n";
    cout << "Coincidio la prediccion con el crecimiento teorico: "
         << (prediction == 2 ? "Si" : "No") << '\n';

    cout << "Esta evaluacion usa la complejidad teorica; "
         << "una sola corrida no demuestra el crecimiento.\n";

    if (!ordered) {
        cout << "No se guardara la salida porque fallo "
             << "la verificacion del orden.\n";
        return true;
    }

    cout << "\nPrimer registro ordenado:\n";
    cout << logs.getHead()->data.toString() << '\n';

    cout << "\nUltimo registro ordenado:\n";
    cout << logs.getTail()->data.toString() << '\n';

    try {
        // creamos la carpeta si todavía no existe
        filesystem::create_directories("out");

        // escribimos recorriendo directamente los nodos
        writeLogs("out/output608.out", logs);

        cout << "\nArchivo generado: out/output608.out\n";
    }
    catch (const exception& error) {
        cerr << "\nLa lista quedo ordenada, pero no se pudo "
             << "guardar la salida: " << error.what() << '\n';
    }

    return true;
}

// solicita un día y repite si la fecha es inválida
// regresa false si termina la entrada de la terminal
bool readSearchDay(SearchDay& day) {
    while (true) {
        cout << "\nIngresa el dia que deseas consultar.\n";
        cout << "Formato: Mmm DD AAAA\n";
        cout << "Ejemplo: Sep 14 2024\n";
        cout << "> ";

        string line;

        if (!getline(cin, line)) {
            return false;
        }

        try {
            day = parseSearchDay(line);
            return true;
        }
        catch (const invalid_argument& error) {
            cout << "Fecha invalida: " << error.what() << '\n';
        }
    }
}

int main() {
    DoublyLinkedList<Log> logs;
    LoadResult result;
    string fileName;

    // indica que la opción 1 confirmó el orden de los registros
    bool orderReady = false;

    // conservamos el último día consultado para la opción 3
    bool hasLastSearch = false;
    SearchDay lastSearch;

    // elegimos el archivo y permitimos reintentar si no existe
    while (true) {
        cout << "\n========== CARGA DE LOGS ==========\n";
        cout << "1. log607-1.txt\n";
        cout << "2. log607-2.txt\n";
        cout << "3. Escribir otro nombre o ruta\n";
        cout << "0. Salir\n";

        int fileOption;

        if (!readOption("Selecciona una opcion: ", 0, 3, fileOption)) {
            cout << "\nEntrada terminada.\n";
            return 0;
        }

        if (fileOption == 0) {
            cout << "Programa terminado.\n";
            return 0;
        }

        if (fileOption == 1) {
            fileName = "data/log607-1.txt";
        }
        else if (fileOption == 2) {
            fileName = "data/log607-2.txt";
        }
        else {
            cout << "Nombre o ruta del archivo: ";

            if (!getline(cin, fileName)) {
                cout << "\nEntrada terminada.\n";
                return 0;
            }

            // rechazamos una ruta vacía o formada por espacios
            if (fileName.find_first_not_of(" \t\r\n") == string::npos) {
                cout << "La ruta no puede estar vacia.\n";
                continue;
            }
        }

        try {
            result = readLogs(fileName, logs);

            printLoadSummary(fileName, result, logs);

            // terminamos la selección y pasamos al menú principal
            break;
        }
        catch (const runtime_error& error) {
            cerr << "\nError: " << error.what() << '\n';
            cout << "Selecciona nuevamente el archivo.\n";
        }
        catch (const exception& error) {
            cerr << "\nNo se pudo completar la carga: "
                 << error.what() << '\n';
            return 1;
        }
    }

    int option;

    do {
        showMenu();

        if (!readOption("Selecciona una opcion: ", 1, 5, option)) {
            cout << "\nEntrada terminada.\n";
            return 0;
        }

        switch (option) {
            case 1:
                if (!sortLogs(logs, fileName)) {
                    cout << "\nEntrada terminada.\n";
                    return 0;
                }

                // habilitamos búsquedas si hay datos ordenados
                orderReady = !logs.isEmpty() && logs.isSorted();
                break;

            case 2:
                if (!orderReady) {
                    cout << "\nPrimero debes ordenar los registros "
                         << "con la opcion 1.\n";
                    break;
                }

                if (!readSearchDay(lastSearch)) {
                    cout << "\nEntrada terminada.\n";
                    return 0;
                }

                hasLastSearch = true;

                showLogsByDay(logs, lastSearch, false);
                break;

            case 3:
                if (!orderReady) {
                    cout << "\nPrimero debes ordenar los registros "
                         << "con la opcion 1.\n";
                    break;
                }

                // solicitamos el día si no existe una búsqueda previa
                if (!hasLastSearch) {
                    if (!readSearchDay(lastSearch)) {
                        cout << "\nEntrada terminada.\n";
                        return 0;
                    }

                    hasLastSearch = true;
                }

                showLogsByDay(logs, lastSearch, true);
                break;

            case 4: {
                // las frecuencias no dependen del orden de los registros
                FileStatistics statistics = calculateStatistics(logs);

                showStatistics(statistics);
                break;
            }

            case 5:
                cout << "\nPrograma terminado.\n";
                break;
        }
    } while (option != 5);

    return 0;
}