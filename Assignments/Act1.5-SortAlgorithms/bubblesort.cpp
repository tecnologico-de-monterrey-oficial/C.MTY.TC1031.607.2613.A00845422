    #include <iostream>
#include <vector>
using namespace std;


// Funcion para intercambiar dos elementos
template <typename T>
void swap(vector<T> &list, int i, int j) {

    T aux = list[i];

    list[i] = list[j];

    list[j] = aux;
}


// Funcion Bubble Sort
template <typename T>
void bubbleSort(vector<T> &list) {

    // Repetimos el proceso varias veces
    for (int i = 0; i < list.size() - 1; i++) {

        // Comparamos elementos vecinos
        for (int j = 0; j < list.size() - 1 - i; j++) {

            // Si el de la izquierda es mayor,
            // los intercambiamos
            if (list[j] > list[j + 1]) {

                swap(list, j, j + 1);
            }
        }
    }
}


// Funcion para imprimir la lista
void print(vector<int> &list) {

    for (int i = 0; i < list.size(); i++) {

        cout << list[i] << " ";
    }

    cout << endl;
}


int main() {

    vector<int> list = {15, 7, 3, 9, 12, 5, 1};

    cout << "Lista original: ";
    print(list);

    cout << "Lista ordenada: ";

    bubbleSort(list);

    print(list);

    return 0;
}