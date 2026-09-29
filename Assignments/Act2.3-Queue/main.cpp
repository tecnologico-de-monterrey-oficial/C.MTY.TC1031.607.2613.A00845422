#include <iostream>
#include <string>
#include <limits>
#include "Queue.h"

using namespace std;

struct Cliente {
    string nombre;
    int boletos;
};

int main() {
    Queue<Cliente> fila;
    int opcion;

    do {
        cout << "\n--- TAQUILLA DE BOLETOS ---" << endl;
        cout << "1. Llegada de un nuevo cliente" << endl;
        cout << "2. Atender al siguiente cliente" << endl;
        cout << "3. Ver al siguiente cliente" << endl;
        cout << "4. Mostrar personas en la fila" << endl;
        cout << "5. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                Cliente nuevoCliente;

                cout << "Nombre del cliente: ";
                getline(cin, nuevoCliente.nombre);

                cout << "Cantidad de boletos: ";
                cin >> nuevoCliente.boletos;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                fila.push(nuevoCliente);

                cout << nuevoCliente.nombre
                     << " fue agregado(a) a la fila." << endl;
                break;
            }

            case 2: {
                if (fila.isEmpty()) {
                    cout << "No hay clientes en la fila." << endl;
                } else {
                    Cliente atendido = fila.front();

                    cout << "Atendiendo a: " << atendido.nombre << endl;
                    cout << "Boletos solicitados: "
                         << atendido.boletos << endl;

                    fila.pop();
                }
                break;
            }

            case 3: {
                if (fila.isEmpty()) {
                    cout << "No hay clientes en la fila." << endl;
                } else {
                    Cliente siguiente = fila.front();

                    cout << "Siguiente cliente: "
                         << siguiente.nombre << endl;
                    cout << "Boletos solicitados: "
                         << siguiente.boletos << endl;
                }
                break;
            }

            case 4:
                cout << "Personas en la fila: "
                     << fila.getSize() << endl;
                break;

            case 5:
                cout << "Programa terminado." << endl;
                break;

            default:
                cout << "Opcion no valida." << endl;
        }

    } while (opcion != 5);

    return 0;
}