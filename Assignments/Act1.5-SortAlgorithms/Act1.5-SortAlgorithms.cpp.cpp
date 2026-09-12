#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>

using namespace std;


// ==================== ESTADISTICAS ====================
// Estructura para guardar las comparaciones e intercambios
struct Stats {

    long long comparaciones = 0;

    long long intercambios = 0;
};


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
void swapSort(vector<T> &list, Stats &stats) {

    // Iteramos todos los elementos de la lista hasta el penultimo
    for (int i = 0; i < list.size() - 1; i++) {

        for (int j = i + 1; j < list.size(); j++) {

            stats.comparaciones++;

            // Comparacion para determinar si es menor
            if (list[i] > list[j]) {

                // Si es menor, intercambiar los valores
                swap(list, i, j);

                stats.intercambios++;
            }
        }
    }
}


// ==================== SELECTION SORT ====================
template <typename T>
void SelectionSort(vector<T> &list, Stats &stats) {

    for (int i = 0; i < list.size() - 1; i++) {

        int minIndex = i;

        for (int j = i + 1; j < list.size(); j++) {

            stats.comparaciones++;

            if (list[j] < list[minIndex]) {

                minIndex = j;
            }
        }

        if (minIndex != i) {

            // Utilizamos nuestra funcion swap
            swap(list, i, minIndex);

            stats.intercambios++;
        }
    }
}


// ==================== INSERTION SORT ====================
template <typename T>
void InsertionSort(vector<T> &list, Stats &stats) {

    for (int i = 1; i < list.size(); i++) {

        int j = i;

        while (j > 0) {

            stats.comparaciones++;

            if (list[j] < list[j - 1]) {

                // Utilizamos nuestra funcion swap
                swap(list, j, j - 1);

                stats.intercambios++;

                j--;

            } else {

                break;
            }
        }
    }
}


// ==================== BUBBLE SORT ====================
template <typename T>
void bubbleSort(vector<T> &list, Stats &stats) {

    // Repetimos el proceso varias veces
    for (int i = 0; i < list.size() - 1; i++) {

        // Comparamos elementos vecinos
        for (int j = 0; j < list.size() - 1 - i; j++) {

            stats.comparaciones++;

            // Si el de la izquierda es mayor,
            // los intercambiamos
            if (list[j] > list[j + 1]) {

                // Utilizamos nuestra funcion swap
                swap(list, j, j + 1);

                stats.intercambios++;
            }
        }
    }
}


// ==================== QUICK SORT =======================
template <typename T>
void quickSort(vector<T> &list, int left, int right) {

    int i = left;

    int j = right;

    // Tomamos como pivote el elemento de en medio
    T pivot = list[(left + right) / 2];


    while (i <= j) {

        // Buscamos un elemento mayor al pivote
        while (list[i] < pivot) {

            i++;
        }

        // Buscamos un elemento menor al pivote
        while (list[j] > pivot) {

            j--;
        }

        // Intercambiamos los elementos
        if (i <= j) {

            if (i != j) {

                swap(list, i, j);
            }

            i++;

            j--;
        }
    }


    // Ordenamos la parte izquierda
    if (left < j) {

        quickSort(list, left, j);
    }


    // Ordenamos la parte derecha
    if (i < right) {

        quickSort(list, i, right);
    }
}


// ==================== MERGE SORT =======================
template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {

    // Generamos una lista para los valores de la izquierda
    vector<T> leftList;

    // Generamos una lista para los valores de la derecha
    vector<T> rightList;


    // Iteramos desde left hasta mid
    for (int i = left; i <= mid; i++) {

        leftList.push_back(list[i]);
    }


    // Iteramos desde mid + 1 hasta right
    for (int j = mid + 1; j <= right; j++) {

        rightList.push_back(list[j]);
    }


    // Creamos una variable index que contenga
    // el indice a actualizar en la lista original
    int index = left;

    // Inicializamos el indice del lado izquierdo
    int i = 0;

    // Inicializamos el indice del lado derecho
    int j = 0;


    // Iteramos mientras no se acaben las listas
    while (i < leftList.size() && j < rightList.size()) {

        // Comparamos los valores de las listas
        if (leftList[i] <= rightList[j]) {

            // Si el valor de la lista izquierda es menor,
            // lo agregamos a la lista original
            list[index] = leftList[i];

            i++;

        } else {

            // Si el valor de la lista derecha es menor,
            // lo agregamos a la lista original
            list[index] = rightList[j];

            j++;
        }

        index++;
    }


    // Agregamos los elementos que hayan quedado
    // en la lista izquierda
    while (i < leftList.size()) {

        list[index] = leftList[i];

        i++;

        index++;
    }


    // Agregamos los elementos que hayan quedado
    // en la lista derecha
    while (j < rightList.size()) {

        list[index] = rightList[j];

        j++;

        index++;
    }
}


template <typename T>
void mergeSort(vector<T> &list, int left, int right) {

    // La condicion de control es que left < right
    if (left < right) {

        // Calculamos mid
        int mid = (left + right) / 2;


        // Ordenamos la primera mitad
        mergeSort(list, left, mid);


        // Ordenamos la segunda mitad
        mergeSort(list, mid + 1, right);


        // Fusionamos las dos mitades
        merge(list, left, mid, right);
    }
}


// ==================== SHELL SORT =======================
// Algoritmo adicional no visto en clase
template <typename T>
void shellSort(vector<T> &list) {

    int n = list.size();


    // El gap comienza siendo la mitad del tamaño de la lista
    for (int gap = n / 2; gap > 0; gap /= 2) {

        for (int i = gap; i < n; i++) {

            T temp = list[i];

            int j = i;


            // Movemos los elementos hasta encontrar
            // la posicion correcta
            while (j >= gap && list[j - gap] > temp) {

                list[j] = list[j - gap];

                j -= gap;
            }


            list[j] = temp;
        }
    }
}


// ==================== FUNCION PRINT ====================
template <typename T>
void print(const vector<T> &list) {

    for (int i = 0; i < list.size(); i++) {

        cout << list[i] << " ";
    }

    cout << endl;
}


// ==================== CREAR LISTA INT ====================
vector<int> crearListaInt(int cantidad, mt19937 &generator) {

    vector<int> list;

    uniform_int_distribution<int> distribution(0, 100000);


    for (int i = 0; i < cantidad; i++) {

        list.push_back(distribution(generator));
    }


    return list;
}


// ==================== CREAR LISTA DOUBLE ====================
vector<double> crearListaDouble(int cantidad, mt19937 &generator) {

    vector<double> list;

    uniform_real_distribution<double> distribution(0.0, 100000.0);


    for (int i = 0; i < cantidad; i++) {

        list.push_back(distribution(generator));
    }


    return list;
}


// ==================== CREAR LISTA CHAR ====================
vector<char> crearListaChar(int cantidad, mt19937 &generator) {

    vector<char> list;

    // Generamos letras entre A y Z
    uniform_int_distribution<int> distribution('A', 'Z');


    for (int i = 0; i < cantidad; i++) {

        list.push_back((char)distribution(generator));
    }


    return list;
}


// ==================== NOMBRE DEL ALGORITMO ====================
string nombreAlgoritmo(int algoritmo) {

    if (algoritmo == 1) {

        return "Swap Sort";
    }

    if (algoritmo == 2) {

        return "Bubble Sort";
    }

    if (algoritmo == 3) {

        return "Selection Sort";
    }

    if (algoritmo == 4) {

        return "Insertion Sort";
    }

    if (algoritmo == 5) {

        return "Merge Sort";
    }

    if (algoritmo == 6) {

        return "Quick Sort";
    }

    if (algoritmo == 7) {

        return "Shell Sort";
    }


    return "";
}


// ==================== ORDENAR ====================
// Funcion que ejecuta el algoritmo seleccionado
template <typename T>
void ordenar(vector<T> &list, int algoritmo, Stats &stats) {

    if (algoritmo == 1) {

        swapSort(list, stats);
    }

    else if (algoritmo == 2) {

        bubbleSort(list, stats);
    }

    else if (algoritmo == 3) {

        SelectionSort(list, stats);
    }

    else if (algoritmo == 4) {

        InsertionSort(list, stats);
    }

    else if (algoritmo == 5) {

        mergeSort(list, 0, list.size() - 1);
    }

    else if (algoritmo == 6) {

        quickSort(list, 0, list.size() - 1);
    }

    else if (algoritmo == 7) {

        shellSort(list);
    }
}


// ==================== EJECUTAR ALGORITMO ====================
template <typename T>
void ejecutarAlgoritmo(vector<T> list, int algoritmo) {

    Stats stats;


    // Comenzamos a medir el tiempo
    auto inicio = chrono::high_resolution_clock::now();


    ordenar(list, algoritmo, stats);


    // Terminamos de medir el tiempo
    auto fin = chrono::high_resolution_clock::now();


    // Calculamos el tiempo en nanosegundos
    long long tiempo =
        chrono::duration_cast<chrono::nanoseconds>(fin - inicio).count();


    cout << endl;

    cout << "Lista ordenada:" << endl;

    print(list);


    cout << endl;

    cout << "Tiempo: "
         << tiempo
         << " nanosegundos"
         << endl;


    // Para los primeros cuatro algoritmos
    // mostramos comparaciones e intercambios
    if (algoritmo >= 1 && algoritmo <= 4) {

        cout << "Comparaciones: "
             << stats.comparaciones
             << endl;

        cout << "Intercambios: "
             << stats.intercambios
             << endl;
    }
}


// ==================== MEDIR TIEMPO ====================
// Esta funcion sirve para el analisis comparativo
template <typename T>
long long medirTiempo(vector<T> list, int algoritmo) {

    Stats stats;


    auto inicio = chrono::high_resolution_clock::now();


    ordenar(list, algoritmo, stats);


    auto fin = chrono::high_resolution_clock::now();


    return chrono::duration_cast<chrono::nanoseconds>(
        fin - inicio
    ).count();
}


// ==================== ANALISIS COMPARATIVO ====================
template <typename T>
void analizarTipo(
    string tipo,
    vector<vector<T>> &listas
) {

    // Probamos los 7 algoritmos
    for (int algoritmo = 1; algoritmo <= 7; algoritmo++) {

        long long tiempo1000 =
            medirTiempo(listas[0], algoritmo);


        long long tiempo10000 =
            medirTiempo(listas[1], algoritmo);


        long long tiempo100000 =
            medirTiempo(listas[2], algoritmo);


        cout << nombreAlgoritmo(algoritmo)
             << ", "
             << tipo
             << ", "
             << tiempo1000
             << ", "
             << tiempo10000
             << ", "
             << tiempo100000
             << endl;
    }
}


// ==================== MAIN ====================
int main() {

    // Generador de numeros aleatorios
    random_device rd;

    mt19937 generator(rd());


    // Los tres tamaños requeridos
    vector<int> tamanos = {
        1000,
        10000,
        100000
    };


    // Listas de los tres tipos de datos
    // Cada posicion contiene un tamaño diferente
    vector<vector<int>> listasInt(3);

    vector<vector<double>> listasDouble(3);

    vector<vector<char>> listasChar(3);


    bool listasCreadas = false;

    int opcion;


    do {

        cout << endl;

        cout << "==============================" << endl;

        cout << "       SORT ALGORITHMS" << endl;

        cout << "==============================" << endl;

        cout << "1. Crear listas aleatorias" << endl;

        cout << "2. Ejecutar algoritmo" << endl;

        cout << "3. Analisis comparativo" << endl;

        cout << "0. Salir" << endl;

        cout << endl;

        cout << "Selecciona una opcion: ";

        cin >> opcion;


        // ==================== CREAR LISTAS ====================
        if (opcion == 1) {

            cout << endl;

            cout << "Creando listas..." << endl;


            for (int i = 0; i < 3; i++) {

                listasInt[i] =
                    crearListaInt(tamanos[i], generator);


                listasDouble[i] =
                    crearListaDouble(tamanos[i], generator);


                listasChar[i] =
                    crearListaChar(tamanos[i], generator);
            }


            listasCreadas = true;


            cout << "Listas creadas correctamente." << endl;

            cout << endl;

            cout << "Se crearon listas de:" << endl;

            cout << "int: 1000, 10000 y 100000" << endl;

            cout << "double: 1000, 10000 y 100000" << endl;

            cout << "char: 1000, 10000 y 100000" << endl;
        }


        // ==================== EJECUTAR ALGORITMO ====================
        else if (opcion == 2) {

            // Verificamos que primero se hayan creado las listas
            if (!listasCreadas) {

                cout << endl;

                cout << "Primero debes crear las listas." << endl;

                continue;
            }


            int algoritmo;

            int tipo;

            int tamano;


            // --------------------------------
            // Seleccion del algoritmo
            // --------------------------------
            cout << endl;

            cout << "Algoritmo:" << endl;

            cout << "1. Swap Sort" << endl;

            cout << "2. Bubble Sort" << endl;

            cout << "3. Selection Sort" << endl;

            cout << "4. Insertion Sort" << endl;

            cout << "5. Merge Sort" << endl;

            cout << "6. Quick Sort" << endl;

            cout << "7. Shell Sort" << endl;

            cout << "Selecciona: ";

            cin >> algoritmo;


            // --------------------------------
            // Seleccion del tipo de dato
            // --------------------------------
            cout << endl;

            cout << "Tipo de dato:" << endl;

            cout << "1. int" << endl;

            cout << "2. double" << endl;

            cout << "3. char" << endl;

            cout << "Selecciona: ";

            cin >> tipo;


            // --------------------------------
            // Seleccion del tamaño
            // --------------------------------
            cout << endl;

            cout << "Cantidad de datos:" << endl;

            cout << "1. 1000" << endl;

            cout << "2. 10000" << endl;

            cout << "3. 100000" << endl;

            cout << "Selecciona: ";

            cin >> tamano;


            // Convertimos la opcion en un indice
            int index = tamano - 1;


            // Verificamos las opciones
            if (algoritmo < 1 || algoritmo > 7 ||
                tipo < 1 || tipo > 3 ||
                tamano < 1 || tamano > 3) {

                cout << endl;

                cout << "Opcion invalida." << endl;

                continue;
            }


            cout << endl;

            cout << "Algoritmo: "
                 << nombreAlgoritmo(algoritmo)
                 << endl;


            // --------------------------------
            // INT
            // --------------------------------
            if (tipo == 1) {

                ejecutarAlgoritmo(
                    listasInt[index],
                    algoritmo
                );
            }


            // --------------------------------
            // DOUBLE
            // --------------------------------
            else if (tipo == 2) {

                ejecutarAlgoritmo(
                    listasDouble[index],
                    algoritmo
                );
            }


            // --------------------------------
            // CHAR
            // --------------------------------
            else if (tipo == 3) {

                ejecutarAlgoritmo(
                    listasChar[index],
                    algoritmo
                );
            }
        }


        // ==================== ANALISIS COMPARATIVO ====================
        else if (opcion == 3) {

            // Verificamos que primero se hayan creado las listas
            if (!listasCreadas) {

                cout << endl;

                cout << "Primero debes crear las listas." << endl;

                continue;
            }


            cout << endl;

            cout << "ANALISIS COMPARATIVO" << endl;

            cout << endl;

            cout << "algoritmo, tipo de dato, "
                 << "tiempo1000, tiempo10000, tiempo100000"
                 << endl;


            // Analisis para int
            analizarTipo(
                "int",
                listasInt
            );


            // Analisis para double
            analizarTipo(
                "double",
                listasDouble
            );


            // Analisis para char
            analizarTipo(
                "char",
                listasChar
            );
        }


        else if (opcion != 0) {

            cout << endl;

            cout << "Opcion invalida." << endl;
        }


    } while (opcion != 0);


    cout << endl;

    cout << "Programa terminado." << endl;


    return 0;
}