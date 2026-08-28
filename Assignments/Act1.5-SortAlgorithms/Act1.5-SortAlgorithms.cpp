#include <iostream>
#include <vector>
using namespace std;


template <typename T>
void swap(vector<T> &list, int i, int j) {
    // creamos una variable temporal

    T aux = list[i];
    // intercambiamos i por j
    list[i] = list[j];
    // intercambiamos j por aux
    list[j] = aux;
    }

template <typename T>
void swapSort(vector<T> &list) {
//iteramos todos los elementos de la lista hasta el penultimo
    for (int i = 0; i < list.size()-1; i++) {
        for (int j = i + 1; j < list.size(); j++) {
            // comparacion para determinar si es menor 
            if (list[i] > list[j]) {
                // si es menor, intercambiar los valores
                swap(list, i, j);
            }
        }
    }
}

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
swapSort(list);
print(list);

return 0;
}


