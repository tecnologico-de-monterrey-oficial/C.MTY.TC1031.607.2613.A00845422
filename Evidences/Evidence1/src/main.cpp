#include "FileManager.h"
#include "SearchManager.h"


#include <chrono>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include <sstream>

using namespace std;


// ==================== ESTADISTICAS ====================

struct Stats {
    long long comparisons = 0;
    long long swaps = 0;
};


// ==================== INTERCAMBIO ====================

template <typename T>
void swapElements(vector<T>& list, int first, int second) {
    T auxiliary = list[first];
    list[first] = list[second];
    list[second] = auxiliary;
}


// ==================== SWAP SORT ====================

template <typename T>
void swapSort(vector<T>& list, Stats& stats) {
    int size = static_cast<int>(list.size());

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            stats.comparisons++;

            if (list[i] > list[j]) {
                swapElements(list, i, j);
                stats.swaps++;
            }
        }
    }
}


// ==================== BUBBLE SORT ====================

template <typename T>
void bubbleSort(vector<T>& list, Stats& stats) {
    int size = static_cast<int>(list.size());

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            stats.comparisons++;

            if (list[j] > list[j + 1]) {
                swapElements(list, j, j + 1);
                stats.swaps++;
            }
        }
    }
}


// ==================== SELECTION SORT ====================

template <typename T>
void selectionSort(vector<T>& list, Stats& stats) {
    int size = static_cast<int>(list.size());

    for (int i = 0; i < size - 1; i++) {
        int minimumIndex = i;

        for (int j = i + 1; j < size; j++) {
            stats.comparisons++;

            if (list[j] < list[minimumIndex]) {
                minimumIndex = j;
            }
        }

        if (minimumIndex != i) {
            swapElements(list, i, minimumIndex);
            stats.swaps++;
        }
    }
}


// ==================== INSERTION SORT ====================

template <typename T>
void insertionSort(vector<T>& list, Stats& stats) {
    int size = static_cast<int>(list.size());

    for (int i = 1; i < size; i++) {
        int j = i;

        while (j > 0) {
            stats.comparisons++;

            if (list[j] < list[j - 1]) {
                swapElements(list, j, j - 1);
                stats.swaps++;
                j--;
            }
            else {
                break;
            }
        }
    }
}


// ==================== MERGE SORT ====================

template <typename T>
void merge(
    vector<T>& list,
    int left,
    int middle,
    int right
) {
    vector<T> leftList;
    vector<T> rightList;

    for (int i = left; i <= middle; i++) {
        leftList.push_back(list[i]);
    }

    for (int i = middle + 1; i <= right; i++) {
        rightList.push_back(list[i]);
    }

    int leftIndex = 0;
    int rightIndex = 0;
    int listIndex = left;

    while (
        leftIndex < static_cast<int>(leftList.size()) &&
        rightIndex < static_cast<int>(rightList.size())
    ) {
        if (leftList[leftIndex] <= rightList[rightIndex]) {
            list[listIndex] = leftList[leftIndex];
            leftIndex++;
        }
        else {
            list[listIndex] = rightList[rightIndex];
            rightIndex++;
        }

        listIndex++;
    }

    while (leftIndex < static_cast<int>(leftList.size())) {
        list[listIndex] = leftList[leftIndex];
        leftIndex++;
        listIndex++;
    }

    while (rightIndex < static_cast<int>(rightList.size())) {
        list[listIndex] = rightList[rightIndex];
        rightIndex++;
        listIndex++;
    }
}


template <typename T>
void mergeSort(vector<T>& list, int left, int right) {
    if (left >= right) {
        return;
    }

    int middle = left + (right - left) / 2;

    mergeSort(list, left, middle);
    mergeSort(list, middle + 1, right);
    merge(list, left, middle, right);
}


// ==================== QUICK SORT ====================

template <typename T>
void quickSort(vector<T>& list, int left, int right) {
    int i = left;
    int j = right;
    T pivot = list[left + (right - left) / 2];

    while (i <= j) {
        while (list[i] < pivot) {
            i++;
        }

        while (list[j] > pivot) {
            j--;
        }

        if (i <= j) {
            if (i != j) {
                swapElements(list, i, j);
            }

            i++;
            j--;
        }
    }

    if (left < j) {
        quickSort(list, left, j);
    }

    if (i < right) {
        quickSort(list, i, right);
    }
}


// ==================== SHELL SORT ====================

template <typename T>
void shellSort(vector<T>& list) {
    int size = static_cast<int>(list.size());

    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            T current = list[i];
            int j = i;

            while (j >= gap && list[j - gap] > current) {
                list[j] = list[j - gap];
                j -= gap;
            }

            list[j] = current;
        }
    }
}


// ==================== VERIFICACION ====================

bool isSorted(const vector<Log>& logs) {
    for (int i = 1; i < static_cast<int>(logs.size()); i++) {
        if (logs[i] < logs[i - 1]) {
            return false;
        }
    }

    return true;
}


// ==================== MOSTRAR REGISTRO ====================

void printLog(const Log& log) {
    cout << log.toString() << '\n';
}


// ==================== NOMBRE DEL ALGORITMO ====================

string algorithmName(int option) {
    switch (option) {
        case 1: return "Swap Sort";
        case 2: return "Bubble Sort";
        case 3: return "Selection Sort";
        case 4: return "Insertion Sort";
        case 5: return "Merge Sort";
        case 6: return "Quick Sort";
        case 7: return "Shell Sort";
        default: return "Desconocido";
    }
}


// ==================== EJECUTAR ORDENAMIENTO ====================

void sortLogs(
    vector<Log>& logs,
    int algorithm,
    Stats& stats
) {
    if (logs.empty()) {
        return;
    }

    switch (algorithm) {
        case 1:
            swapSort(logs, stats);
            break;

        case 2:
            bubbleSort(logs, stats);
            break;

        case 3:
            selectionSort(logs, stats);
            break;

        case 4:
            insertionSort(logs, stats);
            break;

        case 5:
            mergeSort(
                logs,
                0,
                static_cast<int>(logs.size()) - 1
            );
            break;

        case 6:
            quickSort(
                logs,
                0,
                static_cast<int>(logs.size()) - 1
            );
            break;

        case 7:
            shellSort(logs);
            break;
    }
}


// ==================== LEER OPCION ====================

int readOption(
    const string& message,
    int minimum,
    int maximum
) {
    int option;

    while (true) {
        cout << message;

        if (
            cin >> option &&
            option >= minimum &&
            option <= maximum
        ) {
            return option;
        }

        cout << "Opcion invalida. Intenta nuevamente.\n";

        cin.clear();
        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );
    }
}


// ==================== COMPLEJIDAD TEORICA ====================

void printComplexity(int algorithm) {
    cout << "Complejidad teorica:\n";

    switch (algorithm) {
        case 1:
            cout << "  Mejor caso: O(n^2)\n";
            cout << "  Peor caso: O(n^2)\n";
            break;

        case 2:
            cout << "  Mejor caso: O(n^2)\n";
            cout << "  Peor caso: O(n^2)\n";
            break;

        case 3:
            cout << "  Mejor caso: O(n^2)\n";
            cout << "  Peor caso: O(n^2)\n";
            break;

        case 4:
            cout << "  Mejor caso: O(n)\n";
            cout << "  Peor caso: O(n^2)\n";
            break;

        case 5:
            cout << "  Mejor caso: O(n log n)\n";
            cout << "  Peor caso: O(n log n)\n";
            break;

        case 6:
            cout << "  Mejor caso: O(n log n)\n";
            cout << "  Peor caso: O(n^2)\n";
            break;

        case 7:
            cout << "  Mejor caso: O(n log n)\n";
            cout << "  Peor caso: O(n^2)\n";
            break;
    }
}

// ==================== LEER FECHA Y HORA ====================

long long readDateTimeKey(const string& message) {
    while (true) {
        cout << message;
        cout << "Formato: Mon DD YYYY HH:MM:SS\n";
        cout << "Ejemplo: Oct 02 2024 23:04:24\n";
        cout << "> ";

        string inputLine;
        getline(cin >> ws, inputLine);

        istringstream input(inputLine);

        string month;
        int day;
        int year;
        string time;
        string extra;

        if (
            !(input >> month >> day >> year >> time) ||
            input >> extra
        ) {
            cout << "Formato invalido. Intenta nuevamente.\n\n";
            continue;
        }

        try {
            Log limit(
                year,
                month,
                day,
                time,
                "",
                ""
            );

            return limit.key;
        }
        catch (const exception& error) {
            cout << "Fecha u hora invalida: "
                 << error.what() << "\n\n";
        }
    }
}


// ==================== MAIN ====================

int main() {
    int repeat;

    do {
        cout << "\n====================================\n";
        cout << "     ORDENAMIENTO DE REGISTROS\n";
        cout << "====================================\n\n";

        cout << "Archivos disponibles:\n";
        cout << "1. log607-1.txt (desordenado)\n";
        cout << "2. log607-2.txt (casi ordenado)\n\n";

        int fileOption = readOption(
            "Selecciona un archivo: ",
            1,
            2
        );

        string fileName;
        string displayedFileName;

        if (fileOption == 1) {
            fileName = "../data/log607-1.txt";
            displayedFileName = "log607-1.txt";
        }
        else {
            fileName = "../data/log607-2.txt";
            displayedFileName = "log607-2.txt";
        }

        cout << "\nAlgoritmos disponibles:\n";
        cout << "1. Swap Sort\n";
        cout << "2. Bubble Sort\n";
        cout << "3. Selection Sort\n";
        cout << "4. Insertion Sort\n";
        cout << "5. Merge Sort\n";
        cout << "6. Quick Sort\n";
        cout << "7. Shell Sort\n\n";

        int algorithm = readOption(
            "Selecciona un algoritmo: ",
            1,
            7
        );

        cin.ignore(
            numeric_limits<streamsize>::max(),
            '\n'
        );

        string prediction;

        cout << "\nEscribe tu prediccion sobre el tiempo "
             << "de esta corrida y explica por que:\n";

        getline(cin, prediction);

        try {
            vector<Log> logs = readLogs(fileName);
            Stats stats;

            cout << "\nProcesando "
                 << logs.size()
                 << " registros...\n";

            auto start =
                chrono::high_resolution_clock::now();

            sortLogs(logs, algorithm, stats);

            auto end =
                chrono::high_resolution_clock::now();

            long long elapsedTime =
                chrono::duration_cast<chrono::microseconds>(
                    end - start
                ).count();

            bool ordered = isSorted(logs);

            cout << "\n============= RESULTADOS =============\n";
            cout << "Archivo: " << displayedFileName << '\n';

            cout << "Cantidad de registros: "
                 << logs.size() << '\n';

            cout << "Algoritmo: "
                 << algorithmName(algorithm) << '\n';

            cout << "Tiempo: "
                 << elapsedTime
                 << " microsegundos\n";

            cout << "Prediccion inicial: "
                 << prediction << '\n';

            printComplexity(algorithm);

            if (ordered) {
                cout << "Verificacion: "
                     << "ordenamiento correcto\n";
            }
            else {
                cout << "Verificacion: "
                     << "error en el ordenamiento\n";
            }

            if (algorithm >= 1 && algorithm <= 4) {
                cout << "Comparaciones: "
                     << stats.comparisons << '\n';

                cout << "Intercambios: "
                     << stats.swaps << '\n';
            }

            if (!logs.empty()) {
                cout << "\nPrimer registro:\n";
                printLog(logs.front());

                cout << "\nUltimo registro:\n";
                printLog(logs.back());
            }

            if (ordered) {
                writeLogs(
                    "../out/output607.txt",
                    logs
                );

                cout << "\nArchivo generado: "
                     << "../out/output607.txt\n";
            }

            cout << "\nEl tiempo obtenido coincidio "
                 << "con tu prediccion?\n";

            cout << "1. Si\n";
            cout << "2. No\n";

            int predictionResult = readOption(
                "Selecciona una opcion: ",
                1,
                2
            );

            if (predictionResult == 1) {
                cout << "Evaluacion: el resultado coincidio "
                     << "con la prediccion inicial.\n";
            }
            else {
                cout << "Evaluacion: el resultado no coincidio "
                     << "con la prediccion inicial.\n";
            }

            // ==========================================
            // BUSQUEDA POR RANGO
            // ==========================================

            cout << "\n====================================\n";
            cout << "        BUSQUEDA POR RANGO\n";
            cout << "====================================\n\n";

            long long startKey;
            long long endKey;

            do {
                startKey = readDateTimeKey(
                    "Ingresa la fecha y hora inicial.\n"
                );

                cout << '\n';

                endKey = readDateTimeKey(
                    "Ingresa la fecha y hora final.\n"
                );

                if (startKey > endKey) {
                    cout << "\nLa fecha inicial no puede ser "
                         << "posterior a la fecha final.\n";

                    cout << "Ingresa nuevamente el rango.\n\n";
                }

            } while (startKey > endKey);

            int rangeStart =
                findLowerBound(logs, startKey);

            int rangeEnd =
                findUpperBound(logs, endKey);

            vector<Log> range(
                logs.begin() + rangeStart,
                logs.begin() + rangeEnd
            );

            cout << "\nRegistros encontrados: "
                 << range.size() << '\n';

            if (range.empty()) {
                cout << "No existen registros dentro "
                     << "del rango indicado.\n";
            }
            else {
                cout << "\nResultados del rango:\n\n";

                for (const Log& log : range) {
                    printLog(log);
                }
            }

            writeLogs(
                "../out/range607.txt",
                range
            );

            cout << "\nArchivo generado: "
                 << "../out/range607.txt\n";
        }
        catch (const exception& error) {
            cerr << "\nError: "
                 << error.what()
                 << '\n';
        }

        cout << "\nDeseas realizar otra corrida?\n";
        cout << "1. Si\n";
        cout << "0. No\n";

        repeat = readOption(
            "Selecciona una opcion: ",
            0,
            1
        );

    } while (repeat == 1);

    cout << "\nPrograma terminado.\n";

    return 0;
}