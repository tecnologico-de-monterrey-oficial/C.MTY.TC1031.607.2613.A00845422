#include <iostream>
#include <vector>
using namespace std;

// Función iterativa
// O(n)
template <typename T>
T sumaImparesIterativa(vector<T> numeros) {
    T suma = 0;

    for (int i = 0; i < numeros.size(); i++) {
        if (numeros[i] % 2 != 0) {
            suma += numeros[i];
        }
    }

    return suma;
}

// Función recursiva
// O(n)
template <typename T>
T sumaImparesRecursiva(vector<T> numeros, int indice) {
    if (indice == numeros.size()) {
        return 0;
    }

    if (numeros[indice] % 2 != 0) {
        return numeros[indice] + sumaImparesRecursiva(numeros, indice + 1);
    }

    return sumaImparesRecursiva(numeros, indice + 1);
}

int main() {

    vector<int> numeros = {1, 2, 3, 4, 5, 6, 7};

    cout << "Suma iterativa: "
         << sumaImparesIterativa(numeros) << endl;

    cout << "Suma recursiva: "
         << sumaImparesRecursiva(numeros, 0) << endl;

    return 0;
}