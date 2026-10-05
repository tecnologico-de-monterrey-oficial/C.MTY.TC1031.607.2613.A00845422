#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "Node.h"

template <typename T>
class Stack {
private:
    Node<T>* head;
    int size;

public:
    Stack() : head(nullptr), size(0) {}

    ~Stack();

    T pop();
    void push(const T& data);
    T& top();
    const T& top() const;
    bool isEmpty() const;
    int getSize() const;
};

// elimina el último elemento agregado al stack y regresa su valor
template <typename T>
T Stack<T>::pop() {
    // validamos que el stack no esté vacío
    if (isEmpty()) {
        throw std::out_of_range("El historial esta vacio");
    }

    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;

    // guardamos el dato de la página que se cerrará
    T data = aux->data;

    // actualizamos head al siguiente nodo
    head = head->next;

    // liberamos la memoria del nodo eliminado
    delete aux;

    size--;

    return data;
}

// agrega un elemento al inicio del stack
template <typename T>
void Stack<T>::push(const T& data) {
    // creamos un nodo nuevo
    Node<T>* node = new Node<T>(data);

    // el nodo nuevo apunta al head actual
    node->next = head;

    // actualizamos head
    head = node;

    size++;
}

// obtiene el último elemento agregado al stack
template <typename T>
T& Stack<T>::top() {
    // validamos que el stack no esté vacío
    if (isEmpty()) {
        throw std::out_of_range("El historial esta vacio");
    }

    return head->data;
}

// obtiene el último elemento de un stack constante
template <typename T>
const T& Stack<T>::top() const {
    // validamos que el stack no esté vacío
    if (isEmpty()) {
        throw std::out_of_range("El historial esta vacio");
    }

    return head->data;
}

// verifica si el stack está vacío
template <typename T>
bool Stack<T>::isEmpty() const {
    return head == nullptr;
}

// obtiene la cantidad de elementos del stack
template <typename T>
int Stack<T>::getSize() const {
    return size;
}

// libera la memoria de todos los nodos
template <typename T>
Stack<T>::~Stack() {
    // eliminamos nodos mientras el stack no esté vacío
    while (!isEmpty()) {
        pop();
    }
}

#endif