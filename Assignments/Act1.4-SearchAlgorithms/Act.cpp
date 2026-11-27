#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int busquedaSecuencial(const vector<int>& data, int target) {
	for (int i = 0; i < data.size(); i++) {
		if (data[i] == target) {
			return i;
		}
	}
	return -1;
}

template <typename T>
int binarySearch (vector<T> &list, T data) {
    // obtenemos left
    int left = 0;
    // obtenemos right
    int right = list.size() - 1;
    //buscamos el elemento mientras left <= right
    while (left <= right) {
        //obtenemos el mid
        int mid = left + (right - left) / 2;
        //comparamos el valor buscado con el valor en mid
        if (list[mid] == data) {
            //regresamos mid que es el indice del elemento encontrado
            return mid;
        } else {
            // preguntamos si el valor buscado es menor que el valor de mid
            if (data < list[mid]) {
                // si es menor, actualizamos right
                right = mid - 1;
            } else {
                // si es mayor, actualizamos left
                left = mid + 1;
            }
        }
    }
    // si no se encuentra el elemento, retornamos -1
    throw std::invalid_argument("Elemento no encontrado");
}


int main() {

    vector<int> data = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};

    return 0;
}