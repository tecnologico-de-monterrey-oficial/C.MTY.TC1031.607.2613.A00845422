#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include "LinkedList.h"

template <typename T>
class Queue {
private:
    // usamos nuestra lista ligada para almacenar los elementos
    LinkedList<T> list;

public:
    void enqueue(const T& data);
    T dequeue();

    T& front();
    const T& front() const;

    bool isEmpty() const;
    int getSize() const;
};

// agrega un elemento al final de la fila
template <typename T>
void Queue<T>::enqueue(const T& data) {
    // insertamos al final para conservar el orden de llegada
    list.push_back(data);
}

// elimina el primer elemento de la fila y regresa su valor
template <typename T>
T Queue<T>::dequeue() {
    // validamos que la fila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La fila esta vacia");
    }

    // eliminamos y regresamos el primer dato de la lista
    return list.pop_front();
}

// obtiene el primer elemento sin eliminarlo
template <typename T>
T& Queue<T>::front() {
    // validamos que la fila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La fila esta vacia");
    }

    // la posición 0 corresponde al primer elemento
    return list.getData(0);
}

// obtiene el primer elemento de una fila constante
template <typename T>
const T& Queue<T>::front() const {
    // validamos que la fila no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La fila esta vacia");
    }

    return list.getData(0);
}

// verifica si la fila está vacía
template <typename T>
bool Queue<T>::isEmpty() const {
    return list.isEmpty();
}

// obtiene la cantidad de elementos en la fila
template <typename T>
int Queue<T>::getSize() const {
    return list.getSize();
}

#endif /* QUEUE_H */