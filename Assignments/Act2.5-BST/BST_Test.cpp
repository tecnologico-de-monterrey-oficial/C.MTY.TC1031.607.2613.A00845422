#include <iostream>
#include <limits>

using namespace std;

#include "BST.h"

// leemos un entero y validamos la entrada
bool readInt(int& data) {
    while (!(cin >> data)) {
        // validamos si terminó la entrada
        if (cin.eof()) {
            return false;
        }

        // limpiamos el error y descartamos la entrada incorrecta
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Entrada invalida. Ingresa un numero entero: ";
    }

    // descartamos el resto de la línea
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

int main() {
    BST<int> bst;

    int option = 0;
    int data = 0;
    int level = 0;

    do {
        cout << "\n========== ARBOL BINARIO DE BUSQUEDA ==========" << endl;
        cout << "1. Insertar un valor" << endl;
        cout << "2. Mostrar el arbol" << endl;
        cout << "3. Mostrar recorrido inorder" << endl;
        cout << "4. Mostrar recorrido preorder" << endl;
        cout << "5. Mostrar recorrido postorder" << endl;
        cout << "6. Mostrar recorrido por niveles" << endl;
        cout << "7. Buscar un valor" << endl;
        cout << "8. Mostrar la altura del arbol" << endl;
        cout << "9. Mostrar los ancestros de un nodo" << endl;
        cout << "10. Consultar el nivel de un nodo" << endl;
        cout << "11. Eliminar un valor" << endl;
        cout << "12. Salir" << endl;
        cout << "Selecciona una opcion: ";

        if (!readInt(option)) {
            return 0;
        }

        switch (option) {
            case 1:
                cout << "\nIngresa el valor a insertar: ";

                if (!readInt(data)) {
                    return 0;
                }

                // validamos si el dato ya existe
                if (bst.find(data)) {
                    cout << "El valor ya existe en el arbol." << endl;
                } else {
                    bst.insert(data);
                    cout << "Valor insertado correctamente." << endl;
                }
                break;

            case 2:
                cout << "\n========== ARBOL ==========" << endl;
                cout << "El arbol se muestra acostado:" << endl;
                cout << "derecha arriba e izquierda abajo.\n" << endl;

                bst.print();
                break;

            case 3:
                cout << "\nInorder: ";
                bst.visit(2);
                break;

            case 4:
                cout << "\nPreorder: ";
                bst.visit(1);
                break;

            case 5:
                cout << "\nPostorder: ";
                bst.visit(3);
                break;

            case 6:
                cout << "\nPor niveles: ";
                bst.visit(4);
                break;

            case 7:
                cout << "\nIngresa el valor a buscar: ";

                if (!readInt(data)) {
                    return 0;
                }

                if (bst.find(data)) {
                    cout << "El valor existe en el arbol." << endl;
                } else {
                    cout << "El valor no existe en el arbol." << endl;
                }
                break;

            case 8:
                cout << "\nAltura del arbol: " << bst.height() << endl;
                cout << "Se mide en conexiones. Arbol vacio: -1." << endl;
                break;

            case 9:
                cout << "\nIngresa el valor del nodo: ";

                if (!readInt(data)) {
                    return 0;
                }

                cout << "Ancestros: ";
                bst.ancestors(data);
                break;

            case 10:
                cout << "\nIngresa el valor del nodo: ";

                if (!readInt(data)) {
                    return 0;
                }

                level = bst.whatLevelAmI(data);

                if (level == -1) {
                    cout << "El valor no existe en el arbol." << endl;
                } else {
                    cout << "Nivel del nodo: " << level << endl;
                    cout << "La raiz esta en el nivel 0." << endl;
                }
                break;

            case 11:
                cout << "\nIngresa el valor a eliminar: ";

                if (!readInt(data)) {
                    return 0;
                }

                try {
                    bst.remove(data);
                    cout << "Valor eliminado correctamente." << endl;
                } catch (const out_of_range& error) {
                    cout << error.what() << endl;
                }
                break;

            case 12:
                cout << "\nPrograma terminado." << endl;
                break;

            default:
                cout << "\nOpcion invalida. Intenta nuevamente." << endl;
                break;
        }

    } while (option != 12);

    return 0;
}