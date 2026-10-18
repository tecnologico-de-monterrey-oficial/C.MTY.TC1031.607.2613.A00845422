#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

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
                cout << "\nEl ordenamiento se agregara "
                     << "en el siguiente avance.\n";
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