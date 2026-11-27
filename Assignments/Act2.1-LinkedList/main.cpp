#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

#include "LinkedList.h"

using namespace std;

// limpia el buffer cuando el usuario escribe una opción inválida
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// crea una lista de enteros con datos manuales o aleatorios
void createIntList(LinkedList<int>& list) {
    int option;
    int amount;
    int data;

    cout << "\n1. Capturar datos" << endl;
    cout << "2. Generar datos aleatorios" << endl;
    cout << "Elige una opcion: ";
    cin >> option;

    cout << "Cuantos elementos deseas agregar? ";
    cin >> amount;

    for (int i = 0; i < amount; i++) {
        if (option == 1) {
            cout << "Dato " << i + 1 << ": ";
            cin >> data;
            list.push_back(data);
        }
        else {
            data = rand() % 100 + 1;
            list.push_back(data);
        }
    }
}

// crea una lista de strings con datos manuales o aleatorios
void createStringList(LinkedList<string>& list) {
    int option;
    int amount;
    string data;

    string randomWords[] = {
        "rojo", "azul", "verde", "amarillo", "morado",
        "cafe", "blanco", "negro", "naranja", "rosa"
    };

    cout << "\n1. Capturar datos" << endl;
    cout << "2. Generar datos aleatorios" << endl;
    cout << "Elige una opcion: ";
    cin >> option;

    cout << "Cuantos elementos deseas agregar? ";
    cin >> amount;

    for (int i = 0; i < amount; i++) {
        if (option == 1) {
            cout << "Dato " << i + 1 << ": ";
            cin >> data;
            list.push_back(data);
        }
        else {
            data = randomWords[rand() % 10];
            list.push_back(data);
        }
    }
}

// muestra el menú de operaciones de una lista
template <typename T>
void listMenu(LinkedList<T>& list) {
    int option;
    int index;
    T data;
    T newData;

    do {
        cout << "\n---------- MENU DE LISTA ----------" << endl;
        cout << "1. Mostrar lista" << endl;
        cout << "2. Agregar al principio" << endl;
        cout << "3. Agregar al final" << endl;
        cout << "4. Insertar despues de un indice" << endl;
        cout << "5. Borrar un dato" << endl;
        cout << "6. Borrar un dato por posicion" << endl;
        cout << "7. Obtener dato por posicion" << endl;
        cout << "8. Actualizar un dato" << endl;
        cout << "9. Actualizar dato por posicion" << endl;
        cout << "10. Encontrar un dato" << endl;
        cout << "11. Obtener con operador [ ]" << endl;
        cout << "12. Actualizar con operador [ ]" << endl;
        cout << "13. Duplicar la lista con operador =" << endl;
        cout << "0. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> option;

        try {
            switch (option) {
                case 1:
                    cout << "Lista: ";
                    list.print();
                    cout << "Tamanio: " << list.getSize() << endl;
                    break;

                case 2:
                    cout << "Dato a agregar: ";
                    cin >> data;
                    list.push_front(data);
                    break;

                case 3:
                    cout << "Dato a agregar: ";
                    cin >> data;
                    list.push_back(data);
                    break;

                case 4:
                    cout << "Indice despues del cual insertar: ";
                    cin >> index;
                    cout << "Dato a insertar: ";
                    cin >> data;
                    list.insert(index, data);
                    break;

                case 5:
                    cout << "Dato a borrar: ";
                    cin >> data;

                    if (list.deleteData(data)) {
                        cout << "Dato borrado correctamente." << endl;
                    }
                    else {
                        cout << "El dato no fue encontrado." << endl;
                    }
                    break;

                case 6:
                    cout << "Posicion a borrar: ";
                    cin >> index;

                    if (list.deleteAt(index)) {
                        cout << "Dato borrado correctamente." << endl;
                    }
                    else {
                        cout << "Posicion invalida." << endl;
                    }
                    break;

                case 7:
                    cout << "Posicion a consultar: ";
                    cin >> index;
                    cout << "Dato: " << list.getData(index) << endl;
                    break;

                case 8:
                    cout << "Dato a buscar: ";
                    cin >> data;
                    cout << "Dato nuevo: ";
                    cin >> newData;

                    if (list.updateData(data, newData)) {
                        cout << "Dato actualizado correctamente." << endl;
                    }
                    else {
                        cout << "El dato no fue encontrado." << endl;
                    }
                    break;

                case 9:
                    cout << "Posicion a actualizar: ";
                    cin >> index;
                    cout << "Dato nuevo: ";
                    cin >> data;
                    list.updateAt(index, data);
                    cout << "Dato actualizado correctamente." << endl;
                    break;

                case 10:
                    cout << "Dato a buscar: ";
                    cin >> data;
                    index = list.findData(data);

                    if (index == -1) {
                        cout << "El dato no fue encontrado." << endl;
                    }
                    else {
                        cout << "El dato se encuentra en la posicion " << index << endl;
                    }
                    break;

                case 11:
                    cout << "Posicion a consultar: ";
                    cin >> index;
                    cout << "Dato: " << list[index] << endl;
                    break;

                case 12:
                    cout << "Posicion a actualizar: ";
                    cin >> index;
                    cout << "Dato nuevo: ";
                    cin >> data;
                    list[index] = data;
                    cout << "Dato actualizado correctamente." << endl;
                    break;

                case 13: {
                    LinkedList<T> copiedList;
                    copiedList = list;

                    cout << "Lista original: ";
                    list.print();

                    cout << "Lista duplicada: ";
                    copiedList.print();
                    break;
                }

                case 0:
                    cout << "Saliendo del menu." << endl;
                    break;

                default:
                    cout << "Opcion invalida." << endl;
                    break;
            }
        }
        catch (const out_of_range& error) {
            cout << "Error: " << error.what() << endl;
        }

    } while (option != 0);
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int option;

    do {
        cout << "\n====== LISTAS ENCADENADAS ======" << endl;
        cout << "1. Crear lista de enteros" << endl;
        cout << "2. Crear lista de palabras" << endl;
        cout << "0. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> option;

        switch (option) {
            case 1: {
                LinkedList<int> list;
                createIntList(list);
                listMenu(list);
                break;
            }

            case 2: {
                LinkedList<string> list;
                createStringList(list);
                listMenu(list);
                break;
            }

            case 0:
                cout << "Programa terminado." << endl;
                break;

            default:
                cout << "Opcion invalida." << endl;
                break;
        }

    } while (option != 0);

    return 0;
}