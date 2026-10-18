#ifndef STACK_H
#define STACK_H

#include <stdexcept>
#include "LinkedList.h"

template <typename T>
class Stack {
private:
    // usamos nuestra lista ligada para almacenar los elementos
    LinkedList<T> list;

public:
    void push(const T& data);
    T pop();

    T& peek();
    const T& peek() const;

    bool isEmpty() const;
    int getSize() const;
};

// agrega un elemento a la cima de la pila
template <typename T>
void Stack<T>::push(const T& data) {
    // el inicio de la lista representa la cima de la pila
    list.push_front(data);
}

// elimina el elemento de la cima y regresa su valor
template <typename T>
T Stack<T>::pop() {
    // validamos que la pila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La pila esta vacia");
    }

    // eliminamos y regresamos el primer dato de la lista
    return list.pop_front();
}

// obtiene el elemento de la cima sin eliminarlo
template <typename T>
T& Stack<T>::peek() {
    // validamos que la pila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La pila esta vacia");
    }

    // la posición 0 corresponde a la cima
    return list.getData(0);
}

// obtiene el elemento de la cima de una pila constante
template <typename T>
const T& Stack<T>::peek() const {
    // validamos que la pila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La pila esta vacia");
    }

    return list.getData(0);
}

// verifica si la pila está vacía
template <typename T>
bool Stack<T>::isEmpty() const {
    return list.isEmpty();
}

// obtiene la cantidad de elementos en la pila
template <typename T>
int Stack<T>::getSize() const {
    return list.getSize();
}

#endif /* STACK_H */