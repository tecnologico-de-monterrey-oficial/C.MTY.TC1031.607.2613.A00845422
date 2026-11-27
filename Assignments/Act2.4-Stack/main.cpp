#include <iostream>
#include <string>
#include <limits>
#include "Stack.h"

using namespace std;

// representa una página visitada en el navegador
struct PaginaWeb {
    string titulo;
    string url;
};

int main() {
    Stack<PaginaWeb> historial;
    int opcion;

    do {
        cout << "\n--- HISTORIAL DEL NAVEGADOR ---" << endl;
        cout << "1. Visitar una nueva pagina" << endl;
        cout << "2. Retroceder a la pagina anterior" << endl;
        cout << "3. Ver la pagina actual" << endl;
        cout << "4. Mostrar paginas en el historial" << endl;
        cout << "5. Salir" << endl;
        cout << "Selecciona una opcion: ";
        cin >> opcion;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion) {
            case 1: {
                PaginaWeb nuevaPagina;

                cout << "Titulo de la pagina: ";
                getline(cin, nuevaPagina.titulo);

                cout << "URL de la pagina: ";
                getline(cin, nuevaPagina.url);

                historial.push(nuevaPagina);

                cout << "Pagina agregada al historial." << endl;
                break;
            }

            case 2: {
                if (historial.isEmpty()) {
                    cout << "No hay paginas en el historial." << endl;
                }
                else {
                    // pop elimina y regresa la página actual
                    PaginaWeb paginaCerrada = historial.pop();

                    cout << "Se cerro la pagina: "
                         << paginaCerrada.titulo << endl;
                    cout << "URL: " << paginaCerrada.url << endl;
                }
                break;
            }

            case 3: {
                if (historial.isEmpty()) {
                    cout << "No hay paginas en el historial." << endl;
                }
                else {
                    // top muestra la página actual sin eliminarla
                    PaginaWeb paginaActual = historial.top();

                    cout << "Pagina actual: "
                         << paginaActual.titulo << endl;
                    cout << "URL: " << paginaActual.url << endl;
                }
                break;
            }

            case 4:
                cout << "Paginas en el historial: "
                     << historial.getSize() << endl;
                break;

            case 5:
                cout << "Programa terminado." << endl;
                break;

            default:
                cout << "Opcion no valida." << endl;
                break;
        }

    } while (opcion != 5);

    return 0;
}