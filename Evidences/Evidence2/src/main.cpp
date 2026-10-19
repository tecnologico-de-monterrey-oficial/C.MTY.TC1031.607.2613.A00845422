#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <filesystem>

#include "FileManager.h"

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

            // no permitimos caracteres adicionales
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

// presenta las opciones que iremos completando
void showMenu() {
    cout << "\n========== EVIDENCIA 2 ==========\n";
    cout << "1. Ordenar por fecha y hora\n";
    cout << "2. Buscar logs por dia\n";
    cout << "3. Mostrar logs por dia en orden descendente\n";
    cout << "4. Estadisticas del archivo\n";
    cout << "5. Salir\n";
}

// ordena los logs, muestra las mediciones y genera el archivo
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

        // también permitimos exportar un archivo que ya llegó ordenado
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
    // no incluimos entrada, verificación previa ni escritura del archivo
    auto start = chrono::steady_clock::now();

    SortStats stats = logs.sort();

    auto end = chrono::steady_clock::now();

    double elapsedTime =
        chrono::duration<double, micro>(end - start).count();

    bool ordered = logs.isSorted();

    cout << "\n========== RESULTADOS DEL ORDENAMIENTO ==========\n";
    cout << "Algoritmo: Merge Sort\n";
    cout << "Archivo: " << fileName << '\n';
    cout << "Registros: " << logs.getSize() << '\n';
    cout << "Prediccion: " << predictionText << '\n';
    cout << "Tiempo: " << elapsedTime << " microsegundos\n";
    cout << "Comparaciones entre datos: " << stats.comparisons << '\n';
    cout << "Profundidad maxima de recursion: "
         << stats.maxDepth << '\n';

    cout << "Verificacion del orden: "
         << (ordered ? "Correcto" : "Incorrecto") << '\n';

    // comparamos la predicción con el crecimiento teórico del algoritmo
    // una sola corrida no permite demostrar una tasa de crecimiento
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

        // escribimos recorriendo directamente la lista ordenada
        writeLogs("out/output608.out", logs);

        cout << "\nArchivo generado: out/output608.out\n";
    }
    catch (const exception& error) {
        cerr << "\nLa lista quedo ordenada, pero no se pudo "
             << "guardar la salida: " << error.what() << '\n';
    }

    return true;
}

int main() {
    DoublyLinkedList<Log> logs;
    LoadResult result;
    string fileName;

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

            // no permitimos una ruta vacía o formada por espacios
            if (fileName.find_first_not_of(" \t\r\n") == string::npos) {
                cout << "La ruta no puede estar vacia.\n";
                continue;
            }
        }

        try {
            result = readLogs(fileName, logs);

            printLoadSummary(fileName, result, logs);

            // la carga terminó y podemos entrar al menú principal
            break;
        }
        catch (const runtime_error& error) {
            cerr << "\nError: " << error.what() << '\n';
            cout << "Selecciona nuevamente el archivo.\n";
        }
        catch (const exception& error) {
            // otros errores inesperados terminan con un mensaje claro
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
                break;

            case 2:
                cout << "\nLa busqueda por dia se agregara "
                     << "en un avance posterior.\n";
                break;

            case 3:
                cout << "\nEl listado descendente con pila "
                     << "se agregara junto con la busqueda.\n";
                break;

            case 4:
                cout << "\nLas estadisticas se agregaran "
                     << "en un avance posterior.\n";
                break;

            case 5:
                cout << "\nPrograma terminado.\n";
                break;
        }
    } while (option != 5);

    return 0;
}