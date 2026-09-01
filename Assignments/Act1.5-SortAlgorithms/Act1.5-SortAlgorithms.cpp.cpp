#include <iostream>
#include <vector>
using namespace std;


// ==================== FUNCION SWAP ====================
// Funcion para intercambiar dos elementos
template <typename T>
void swap(vector<T> &list, int i, int j) {

    T aux = list[i];

    list[i] = list[j];

    list[j] = aux;
}


// ==================== SWAP SORT ====================
template <typename T>
void swapSort(vector<T> &list) {

    // Iteramos todos los elementos de la lista hasta el penultimo
    for (int i = 0; i < list.size() - 1; i++) {

        for (int j = i + 1; j < list.size(); j++) {

            // Comparacion para determinar si es menor
            if (list[i] > list[j]) {

                // Si es menor, intercambiar los valores
                swap(list, i, j);
            }
        }
    }
}


// ==================== SELECTION SORT ====================
template <typename T>
void SelectionSort(vector<T> &list) {

    for (int i = 0; i < list.size() - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < list.size(); j++) {

            if (list[j] < list[minIndex]) {
                minIndex = j;
            }
        }

        if (minIndex != i) {

            // Utilizamos nuestra funcion swap
            swap(list, i, minIndex);
        }
    }
}


// ==================== INSERTION SORT ====================
template <typename T>
void InsertionSort(vector<T> &list) {

    for (int i = 1; i < list.size(); i++) {

        T key = list[i];

        int j = i - 1;

        while (j >= 0 && list[j] > key) {

            list[j + 1] = list[j];

            j--;
        }

        list[j + 1] = key;
    }
}


// ==================== BUBBLE SORT ====================
template <typename T>
void bubbleSort(vector<T> &list) {

    // Repetimos el proceso varias veces
    for (int i = 0; i < list.size() - 1; i++) {

        // Comparamos elementos vecinos
        for (int j = 0; j < list.size() - 1 - i; j++) {

            // Si el de la izquierda es mayor,
            // los intercambiamos
            if (list[j] > list[j + 1]) {

                // Utilizamos nuestra funcion swap
                swap(list, j, j + 1);
            }
        }
    }
}


// ==================== FUNCION PRINT ====================
template <typename T>
void print(vector<T> &list) {

    for (int i = 0; i < list.size(); i++) {

        cout << list[i] << " ";
    }

    cout << endl;
}


// ==================== MAIN ====================
int main() {

    // Lista original
    vector<int> list = {15, 7, 3, 9, 12, 5, 1};

    cout << "Lista original: ";
    print(list);


    // --------------------------------
    // Ejercicio 1: Swap Sort
    // --------------------------------
    vector<int> listSwap = list;

    swapSort(listSwap);

    cout << "Lista ordenada (Swap Sort): ";
    print(listSwap);


    // --------------------------------
    // Ejercicio 2: Selection Sort
    // --------------------------------
    vector<int> listSelection = list;

    SelectionSort(listSelection);

    cout << "Lista ordenada (Selection Sort): ";
    print(listSelection);


    // --------------------------------
    // Ejercicio 3: Insertion Sort
    // --------------------------------
    vector<int> listInsertion = list;

    InsertionSort(listInsertion);

    cout << "Lista ordenada (Insertion Sort): ";
    print(listInsertion);


    // --------------------------------
    // Ejercicio 4: Bubble Sort
    // --------------------------------
    vector<int> listBubble = list;

    bubbleSort(listBubble);

    cout << "Lista ordenada (Bubble Sort): ";
    print(listBubble);


    return 0;
}