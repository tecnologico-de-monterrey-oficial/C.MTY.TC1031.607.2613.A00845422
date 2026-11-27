#include <iostream>
#include <stdexcept>

#include "LinkedList.h"
#include "DoublyLinkedList.h"
#include "Queue.h"
#include "Stack.h"

using namespace std;

// probamos la lista ligada simple
void testLinkedList() {
    cout << "\n========== LISTA LIGADA ==========\n";

    LinkedList<int> list;

    // caso 1: lista vacía
    cout << "\nLista vacia: ";
    list.print();
    cout << "Tamano esperado: 0. Obtenido: "
         << list.getSize() << '\n';

    // intentamos eliminar sin cerrar el programa
    try {
        list.pop_front();
    }
    catch (const out_of_range& error) {
        cout << "Mensaje: " << error.what() << '\n';
    }

    // caso 2: un solo elemento
    list.push_back(10);
    cout << "\nUn elemento: ";
    list.print();

    int removed = list.pop_front();
    cout << "Dato eliminado: " << removed << '\n';
    cout << "Lista vacia otra vez: "
         << (list.isEmpty() ? "Si" : "No") << '\n';

    // caso 3: inserciones en ambos extremos
    list.push_back(20);
    list.push_front(10);
    list.push_back(30);

    cout << "\nEsperado: [10 - 20 - 30]\n";
    cout << "Obtenido: ";
    list.print();

    // borramos tail y agregamos de nuevo al final
    // esto comprueba que tail se actualizó correctamente
    list.deleteAt(2);
    list.push_back(40);

    cout << "\nDespues de borrar el ultimo y agregar 40:\n";
    cout << "Esperado: [10 - 20 - 40]\n";
    cout << "Obtenido: ";
    list.print();

    // repetimos la comprobación borrando por dato
    list.deleteData(40);
    list.push_back(50);

    cout << "\nDespues de borrar 40 y agregar 50:\n";
    cout << "Esperado: [10 - 20 - 50]\n";
    cout << "Obtenido: ";
    list.print();

    // insertamos después del último nodo
    list.insert(list.getSize() - 1, 60);
    list.push_back(70);

    cout << "\nInsercion despues del ultimo y push_back:\n";
    cout << "Esperado: [10 - 20 - 50 - 60 - 70]\n";
    cout << "Obtenido: ";
    list.print();

    // comprobamos que clear permite reutilizar la lista
    list.clear();
    list.push_back(99);

    cout << "\nDespues de limpiar y agregar 99: ";
    list.print();
}

// probamos el comportamiento FIFO de la fila
void testQueue() {
    cout << "\n========== FILA ==========\n";

    Queue<int> fila;

    // caso 1: fila vacía
    cout << "\nTamano inicial: " << fila.getSize() << '\n';

    try {
        fila.dequeue();
    }
    catch (const out_of_range& error) {
        cout << "Mensaje: " << error.what() << '\n';
    }

    // caso 2: un solo elemento
    fila.enqueue(10);

    cout << "\nUn elemento. Frente: " << fila.front() << '\n';
    cout << "Dato eliminado: " << fila.dequeue() << '\n';
    cout << "Fila vacia: "
         << (fila.isEmpty() ? "Si" : "No") << '\n';

    // caso 3: varios elementos
    fila.enqueue(10);
    fila.enqueue(20);
    fila.enqueue(30);

    cout << "\nFrente esperado: 10. Obtenido: "
         << fila.front() << '\n';
    cout << "Tamano despues de consultar: "
         << fila.getSize() << '\n';

    cout << "Salida FIFO esperada: 10 20 30\n";
    cout << "Salida obtenida: ";

    // desencolamos hasta vaciar la fila
    while (!fila.isEmpty()) {
        cout << fila.dequeue() << ' ';
    }

    cout << "\nTamano final: " << fila.getSize() << '\n';

    // comprobamos que puede volver a utilizarse
    fila.enqueue(40);
    cout << "Frente al reutilizar la fila: "
         << fila.front() << '\n';
}

// probamos el comportamiento LIFO de la pila
void testStack() {
    cout << "\n========== PILA ==========\n";

    Stack<int> pila;

    // caso 1: pila vacía
    cout << "\nTamano inicial: " << pila.getSize() << '\n';

    try {
        pila.pop();
    }
    catch (const out_of_range& error) {
        cout << "Mensaje: " << error.what() << '\n';
    }

    // caso 2: un solo elemento
    pila.push(10);

    cout << "\nUn elemento. Cima: " << pila.peek() << '\n';
    cout << "Dato eliminado: " << pila.pop() << '\n';
    cout << "Pila vacia: "
         << (pila.isEmpty() ? "Si" : "No") << '\n';

    // caso 3: varios elementos
    pila.push(10);
    pila.push(20);
    pila.push(30);

    cout << "\nCima esperada: 30. Obtenida: "
         << pila.peek() << '\n';
    cout << "Tamano despues de consultar: "
         << pila.getSize() << '\n';

    cout << "Salida LIFO esperada: 30 20 10\n";
    cout << "Salida obtenida: ";

    // desapilamos hasta vaciar la pila
    while (!pila.isEmpty()) {
        cout << pila.pop() << ' ';
    }

    cout << "\nTamano final: " << pila.getSize() << '\n';

    // comprobamos que puede volver a utilizarse
    pila.push(40);
    cout << "Cima al reutilizar la pila: "
         << pila.peek() << '\n';
}

// probamos los enlaces en ambas direcciones
void testDoublyLinkedList() {
    cout << "\n========== LISTA DOBLEMENTE LIGADA ==========\n";

    DoublyLinkedList<int> list;

    // caso 1: lista vacía
    cout << "\nLista vacia: ";
    list.print();

    cout << "Recorrido inverso: ";
    list.printReverse();

    cout << "Eliminar nodo nulo: "
         << (list.deleteNode(nullptr) ? "Eliminado" : "Sin cambios")
         << '\n';

    // caso 2: un solo elemento
    list.addFirst(10);

    cout << "\nUn elemento: ";
    list.print();

    list.deleteNode(list.getHead());

    cout << "Despues de eliminar el unico nodo: ";
    list.print();

    cout << "Ambos extremos nulos: "
         << ((list.getHead() == nullptr &&
              list.getTail() == nullptr) ? "Si" : "No")
         << '\n';

    // caso 3: inserciones en los extremos y en medio
    list.addLast(20);
    list.addFirst(10);
    list.addLast(40);

    // guardamos el nodo nuevo para eliminarlo después
    NodeD<int>* middle = list.insertAfter(
        list.getHead()->next,
        30
    );

    cout << "\nAdelante esperado: [10 <-> 20 <-> 30 <-> 40]\n";
    cout << "Obtenido: ";
    list.print();

    cout << "Atras esperado: [40 <-> 30 <-> 20 <-> 10]\n";
    cout << "Obtenido: ";
    list.printReverse();

    // eliminamos un nodo intermedio
    list.deleteNode(middle);

    // el apuntador ya no debe utilizarse
    middle = nullptr;

    cout << "\nDespues de borrar 30:\n";
    list.print();
    list.printReverse();

    // eliminamos el primer nodo y el último
    list.deleteNode(list.getHead());
    list.deleteNode(list.getTail());

    cout << "\nDespues de borrar ambos extremos:\n";
    cout << "Esperado: [20]\n";
    list.print();
    list.printReverse();

    // insertamos después de tail para comprobar su actualización
    list.insertAfter(list.getTail(), 50);
    list.addLast(60);

    cout << "\nInsercion despues de tail y addLast:\n";
    cout << "Esperado: [20 <-> 50 <-> 60]\n";
    list.print();
    list.printReverse();

    // comprobamos que podemos limpiar y reutilizar
    list.clear();
    list.addLast(99);

    cout << "\nDespues de limpiar y agregar 99:\n";
    list.print();
    list.printReverse();
}

int main() {
    try {
        testLinkedList();
        testQueue();
        testStack();
        testDoublyLinkedList();

        cout << "\nPruebas terminadas. "
             << "Revisa los resultados esperados y obtenidos.\n";
    }
    catch (const exception& error) {
        cerr << "\nError inesperado: " << error.what() << '\n';
        return 1;
    }

    return 0;
}