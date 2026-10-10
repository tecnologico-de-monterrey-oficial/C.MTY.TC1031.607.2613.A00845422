#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <stdexcept>
#include "DoublyLinkedList.h"
using namespace std;

// leemos una línea completa y validamos el tipo de dato
template <typename T>
T readData(const string& message) {
    while (true) {
        cout << message;
        string line;
        if (!getline(cin, line)) throw runtime_error("Entrada terminada");
        istringstream input(line);
        T data;
        if (input >> data) {
            input >> ws;
            if (input.eof()) return data;
        }
        cout << "Dato invalido. Intenta de nuevo.\n";
    }
}

// las palabras pueden incluir espacios
template <>
string readData<string>(const string& message) {
    while (true) {
        cout << message;
        string data;
        if (!getline(cin, data)) throw runtime_error("Entrada terminada");
        if (data.find_first_not_of(" \t\r") != string::npos) return data;
        cout << "Escribe un texto no vacio.\n";
    }
}

// generamos datos de acuerdo con el tipo de lista
template <typename T>
T randomData(mt19937& generator);

template <>
int randomData<int>(mt19937& generator) {
    return uniform_int_distribution<int>(1, 100)(generator);
}

template <>
double randomData<double>(mt19937& generator) {
    return uniform_int_distribution<int>(1, 1000)(generator) / 10.0;
}

template <>
string randomData<string>(mt19937& generator) {
    string words[] = {"casa", "robot", "lista", "nodo", "teclado", "pantalla", "motor", "cable"};
    return words[uniform_int_distribution<int>(0, 7)(generator)];
}

template <typename T>
void createList(DoublyLinkedList<T>& list, mt19937& generator) {
    int mode;
    do {
        mode = readData<int>("1. Datos capturados\n2. Datos aleatorios\nOpcion: ");
    } while (mode != 1 && mode != 2);
    int count;
    do {
        count = readData<int>("Cantidad de elementos (0 o mas): ");
    } while (count < 0);
    // limpiamos la lista antes de capturar los datos nuevos
    list.clear();
    for (int i = 0; i < count; i++) {
        if (mode == 1) list.addLast(readData<T>("Dato " + to_string(i) + ": "));
        else list.addLast(randomData<T>(generator));
    }
}

template <typename T>
void listMenu(mt19937& generator) {
    DoublyLinkedList<T> list;
    DoublyLinkedList<T> other;
    createList(list, generator);
    int option;
    do {
        cout << "\nLista actual: ";
        list.print();
        cout << "Indices desde 0.\n"
             << "1. Agregar al principio\n2. Agregar al final\n"
             << "3. Insertar a la derecha de un indice\n4. Borrar por dato\n"
             << "5. Borrar por posicion\n6. Obtener por posicion\n"
             << "7. Actualizar por dato\n8. Actualizar por posicion\n"
             << "9. Buscar dato\n10. Obtener con operador []\n"
             << "11. Actualizar con operador []\n12. Probar operador =\n"
             << "13. Limpiar\n14. Ordenar\n15. Duplicar cada elemento\n"
             << "16. Remover duplicados\n17. Mostrar al reves\n"
             << "18. Crear nuevamente la lista\n0. Volver\n";
        option = readData<int>("Opcion: ");
        try {
            switch (option) {
            case 1:
                list.addFirst(readData<T>("Dato: "));
                break;
            case 2:
                list.addLast(readData<T>("Dato: "));
                break;
            case 3: {
                int index = readData<int>("Indice: ");
                T data = readData<T>("Dato nuevo: ");
                list.insert(index, data);
                break;
            }
            case 4:
                cout << (list.deleteData(readData<T>("Dato a borrar: ")) ? "Dato borrado\n" : "Dato no encontrado\n");
                break;
            case 5:
                cout << (list.deleteAt(readData<int>("Posicion: ")) ? "Dato borrado\n" : "Posicion invalida\n");
                break;
            case 6: {
                int index = readData<int>("Posicion: ");
                cout << "Dato: " << list.getData(index) << '\n';
                break;
            }
            case 7: {
                T data = readData<T>("Dato a buscar: ");
                T newData = readData<T>("Dato nuevo: ");
                list.updateData(data, newData);
                break;
            }
            case 8: {
                int index = readData<int>("Posicion: ");
                T data = readData<T>("Dato nuevo: ");
                list.updateAt(index, data);
                break;
            }
            case 9: {
                T data = readData<T>("Dato a buscar: ");
                cout << "Posicion (-1 si no existe): " << list.findData(data) << '\n';
                break;
            }
            case 10: {
                int index = readData<int>("Posicion: ");
                cout << "Dato: " << list[index] << '\n';
                break;
            }
            case 11: {
                int index = readData<int>("Posicion: ");
                T data = readData<T>("Dato nuevo: ");
                list[index] = data;
                break;
            }
            case 12: {
                cout << "Crea la otra lista que se copiara a la actual.\n";
                createList(other, generator);
                // usamos la sobrecarga para copiar los datos
                list = other;
                cout << "Lista actual copiada: ";
                list.print();
                // modificamos la otra lista para comprobar la independencia
                other.clear();
                cout << "Otra lista despues de limpiarla: ";
                other.print();
                cout << "La lista actual conserva sus datos.\n";
                break;
            }
            case 13: list.clear(); break;
            case 14: list.sort(); break;
            case 15: list.duplicate(); break;
            case 16: list.removeDuplicates(); break;
            case 17: list.printReverse(); break;
            case 18: createList(list, generator); break;
            case 0: break;
            default: cout << "Opcion invalida\n";
            }
        } catch (const out_of_range& error) {
            cout << "Error: " << error.what() << '\n';
        }
    } while (option != 0);
}

int main() {
    mt19937 generator(random_device{}());
    try {
        int option;
        do {
            cout << "\nDOBLY LINKED LIST\n1. Lista de enteros\n"
                 << "2. Lista de decimales\n3. Lista de palabras\n0. Salir\n";
            option = readData<int>("Opcion: ");
            switch (option) {
            case 1: listMenu<int>(generator); break;
            case 2: listMenu<double>(generator); break;
            case 3: listMenu<string>(generator); break;
            case 0: break;
            default: cout << "Opcion invalida\n";
            }
        } while (option != 0);
    } catch (const exception& error) {
        cout << error.what() << '\n';
        return 1;
    }
    return 0;
}
