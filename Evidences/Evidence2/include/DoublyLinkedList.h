#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <iostream>
#include <stdexcept>
#include "NodeD.h"

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // constructor copia
    DoublyLinkedList(const DoublyLinkedList<T>& other);

    // destructor
    ~DoublyLinkedList();

    DoublyLinkedList<T>& operator=(
        const DoublyLinkedList<T>& other
    );

    void addFirst(const T& data);
    void addLast(const T& data);

    NodeD<T>* insertAfter(NodeD<T>* node, const T& data);
    bool deleteNode(NodeD<T>* node);

    NodeD<T>* getHead();
    const NodeD<T>* getHead() const;

    NodeD<T>* getTail();
    const NodeD<T>* getTail() const;

    void clear();
    void print() const;
    void printReverse() const;

    bool isEmpty() const;
    int getSize() const;
};

// agrega un nodo al principio
template <typename T>
void DoublyLinkedList<T>::addFirst(const T& data) {
    // creamos un nodo nuevo
    NodeD<T>* node = new NodeD<T>(data);

    // el nuevo nodo apunta al primero actual
    node->next = head;

    // validamos si la lista está vacía
    if (head == nullptr) {
        // el nuevo nodo también será el último
        tail = node;
    }
    else {
        // conectamos el primero actual con el nuevo
        head->prev = node;
    }

    // actualizamos head
    head = node;

    size++;
}

// agrega un nodo al final
template <typename T>
void DoublyLinkedList<T>::addLast(const T& data) {
    // creamos un nodo nuevo
    NodeD<T>* node = new NodeD<T>(data);

    // el nuevo nodo apunta hacia el último actual
    node->prev = tail;

    // validamos si la lista está vacía
    if (tail == nullptr) {
        // el nuevo nodo también será el primero
        head = node;
    }
    else {
        // conectamos el último actual con el nuevo
        tail->next = node;
    }

    // actualizamos tail
    tail = node;

    size++;
}

// inserta después de un nodo y regresa el nodo nuevo
// el nodo recibido debe pertenecer a esta lista
template <typename T>
NodeD<T>* DoublyLinkedList<T>::insertAfter(
    NodeD<T>* node,
    const T& data
) {
    // necesitamos un nodo válido para insertar después
    if (node == nullptr) {
        throw std::invalid_argument(
            "No se puede insertar despues de un nodo nulo"
        );
    }

    // conectamos el nuevo nodo con sus dos vecinos
    NodeD<T>* newNode = new NodeD<T>(
        data,
        node->next,
        node
    );

    // validamos si existe un nodo a la derecha
    if (node->next != nullptr) {
        // el siguiente debe apuntar hacia el nuevo
        node->next->prev = newNode;
    }
    else {
        // insertamos después del último nodo
        tail = newNode;
    }

    // conectamos el nodo recibido con el nuevo
    node->next = newNode;

    size++;

    return newNode;
}

// elimina un nodo dado
// debe pertenecer a esta lista y no haber sido eliminado
template <typename T>
bool DoublyLinkedList<T>::deleteNode(NodeD<T>* node) {
    // un apuntador nulo no representa un nodo para borrar
    if (node == nullptr) {
        return false;
    }

    // validamos si existe un nodo anterior
    if (node->prev != nullptr) {
        // conectamos el anterior con el siguiente
        node->prev->next = node->next;
    }
    else {
        // estamos eliminando el primer nodo
        head = node->next;
    }

    // validamos si existe un nodo siguiente
    if (node->next != nullptr) {
        // conectamos el siguiente con el anterior
        node->next->prev = node->prev;
    }
    else {
        // estamos eliminando el último nodo
        tail = node->prev;
    }

    // liberamos la memoria del nodo eliminado
    delete node;

    size--;

    return true;
}

// obtiene el primer nodo para recorrer la lista
template <typename T>
NodeD<T>* DoublyLinkedList<T>::getHead() {
    return head;
}

// obtiene el primer nodo de una lista constante
template <typename T>
const NodeD<T>* DoublyLinkedList<T>::getHead() const {
    return head;
}

// obtiene el último nodo para recorrer hacia atrás
template <typename T>
NodeD<T>* DoublyLinkedList<T>::getTail() {
    return tail;
}

// obtiene el último nodo de una lista constante
template <typename T>
const NodeD<T>* DoublyLinkedList<T>::getTail() const {
    return tail;
}

// libera todos los nodos de la lista
template <typename T>
void DoublyLinkedList<T>::clear() {
    // recorremos desde el primer nodo
    while (head != nullptr) {
        NodeD<T>* aux = head;
        head = head->next;
        delete aux;
    }

    // la lista queda vacía
    tail = nullptr;
    size = 0;
}

// constructor que copia otra lista
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(
    const DoublyLinkedList<T>& other
) : head(nullptr), tail(nullptr), size(0) {
    try {
        // recorremos los nodos de la otra lista
        const NodeD<T>* aux = other.head;

        while (aux != nullptr) {
            // copiamos los datos en nodos independientes
            addLast(aux->data);
            aux = aux->next;
        }
    }
    catch (...) {
        // liberamos los nodos si la copia no pudo completarse
        clear();
        throw;
    }
}

// copia una lista mediante el operador =
template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(
    const DoublyLinkedList<T>& other
) {
    // evitamos que una lista se copie a sí misma
    if (this != &other) {
        // primero creamos una copia independiente
        DoublyLinkedList<T> copy(other);

        // guardamos los extremos y el tamaño actuales
        NodeD<T>* auxHead = head;
        NodeD<T>* auxTail = tail;
        int auxSize = size;

        // recibimos los nodos de la copia
        head = copy.head;
        tail = copy.tail;
        size = copy.size;

        // la copia recibe los nodos anteriores
        // su destructor los liberará al salir
        copy.head = auxHead;
        copy.tail = auxTail;
        copy.size = auxSize;
    }

    return *this;
}

// destructor de la lista
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    clear();
}

// imprime los elementos desde head hasta tail
template <typename T>
void DoublyLinkedList<T>::print() const {
    const NodeD<T>* aux = head;

    std::cout << "[";

    // avanzamos mediante los apuntadores next
    while (aux != nullptr) {
        std::cout << aux->data;

        if (aux->next != nullptr) {
            std::cout << " <-> ";
        }

        aux = aux->next;
    }

    std::cout << "] (" << size << " elementos)\n";
}

// imprime los elementos desde tail hasta head
template <typename T>
void DoublyLinkedList<T>::printReverse() const {
    const NodeD<T>* aux = tail;

    std::cout << "[";

    // retrocedemos mediante los apuntadores prev
    while (aux != nullptr) {
        std::cout << aux->data;

        if (aux->prev != nullptr) {
            std::cout << " <-> ";
        }

        aux = aux->prev;
    }

    std::cout << "] (" << size << " elementos)\n";
}

// verifica si la lista está vacía
template <typename T>
bool DoublyLinkedList<T>::isEmpty() const {
    return head == nullptr;
}

// obtiene la cantidad de elementos
template <typename T>
int DoublyLinkedList<T>::getSize() const {
    return size;
}

#endif /* DoublyLinkedList_h */