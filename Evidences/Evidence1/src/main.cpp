#include "FileManager.h"

#include <chrono>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


// ==================== ESTADISTICAS ====================

struct Stats {
    long long comparisons = 0;
    long long swaps = 0;
};


// ==================== INTERCAMBIO ====================

template <typename T>
void swapElements(vector<T>& list, int first, int second) {
    T auxiliar = list[first];
    list[first] = list[second];
    list[second] = auxiliar;
}


// ==================== SWAP SORT ====================

template <typename T>
void swapSort(vector<T>& list, Stats& stats) {
    for (int i = 0; i < static_cast<int>(list.size()) - 1; i++) {
        for (int j = i + 1; j < static_cast<int>(list.size()); j++) {
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
    cout << log.month << ' '
         << log.day << ' '
         << log.year << ' '
         << log.time << ' '
         << log.ip << ' '
         << log.message << '\n';
}


// ==================== MAIN ====================

int main() {
    try {
        vector<Log> logs = readLogs("../data/log607-1.txt");

        cout << "Registros leidos: "
             << logs.size() << '\n';

        auto start = chrono::high_resolution_clock::now();

        if (!logs.empty()) {
            mergeSort(
                logs,
                0,
                static_cast<int>(logs.size()) - 1
            );
        }

        auto end = chrono::high_resolution_clock::now();

        long long time =
            chrono::duration_cast<chrono::microseconds>(
                end - start
            ).count();

        cout << "Algoritmo: Merge Sort\n";
        cout << "Tiempo: " << time << " microsegundos\n";

        if (isSorted(logs)) {
            cout << "Resultado: registros ordenados correctamente\n";
        }
        else {
            cout << "Resultado: error en el ordenamiento\n";
        }

        if (!logs.empty()) {
            cout << "\nPrimer registro:\n";
            printLog(logs.front());

            cout << "\nUltimo registro:\n";
            printLog(logs.back());
        }
    }
    catch (const exception& error) {
        cerr << "Error: " << error.what() << '\n';
        return 1;
    }

    return 0;
}