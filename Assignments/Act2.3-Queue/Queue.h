#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "Node.h"

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Queue() : head(nullptr), tail(nullptr), size(0) {}

    ~Queue();

    T pop();
    void push(const T& data);
    T& front();
    const T& front() const;
    bool isEmpty() const;
    int getSize() const;
};

// elimina el primer elemento de la fila y regresa su valor
template <typename T>
T Queue<T>::pop() {
    // validamos que la fila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La fila esta vacia");
    }

    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;

    // guardamos el dato del cliente atendido
    T data = aux->data;

    // actualizamos head al siguiente nodo
    head = head->next;

    // si se eliminó el único nodo, tail también debe ser nullptr
    if (head == nullptr) {
        tail = nullptr;
    }

    // liberamos la memoria del nodo eliminado
    delete aux;

    size--;

    return data;
}

// agrega un elemento al final de la fila
template <typename T>
void Queue<T>::push(const T& data) {
    // creamos un nodo nuevo
    Node<T>* node = new Node<T>(data);

    // validamos si la fila está vacía
    if (isEmpty()) {
        // actualizamos head y tail al nodo nuevo
        head = node;
        tail = node;
    }
    else {
        // conectamos el último nodo con el nodo nuevo
        tail->next = node;

        // actualizamos tail
        tail = node;
    }

    size++;
}

// obtiene el primer elemento de la fila
template <typename T>
T& Queue<T>::front() {
    // validamos que la fila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La fila esta vacia");
    }

    return head->data;
}

// obtiene el primer elemento de una fila constante
template <typename T>
const T& Queue<T>::front() const {
    // validamos que la fila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La fila esta vacia");
    }

    return head->data;
}

// verifica si la fila está vacía
template <typename T>
bool Queue<T>::isEmpty() const {
    return head == nullptr;
}

// obtiene la cantidad de elementos en la fila
template <typename T>
int Queue<T>::getSize() const {
    return size;
}

// libera la memoria de todos los nodos
template <typename T>
Queue<T>::~Queue() {
    // eliminamos nodos mientras la fila no esté vacía
    while (!isEmpty()) {
        pop();
    }
}

#endif