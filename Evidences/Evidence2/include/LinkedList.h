#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdexcept>
#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // constructor copia
    LinkedList(const LinkedList<T>& other);

    // destructor
    ~LinkedList();

    void push_front(const T& data);
    void push_back(const T& data);
    T pop_front();

    void insert(int index, const T& data);

    bool deleteData(const T& data);
    bool deleteAt(int index);

    T& getData(int index);
    const T& getData(int index) const;

    bool updateData(const T& oldData, const T& newData);
    void updateAt(int index, const T& data);

    int findData(const T& data) const;

    T& operator[](int index);
    const T& operator[](int index) const;

    LinkedList<T>& operator=(const LinkedList<T>& other);

    void clear();
    void print() const;
    bool isEmpty() const;
    int getSize() const;
};

// agrega un nodo al principio
template <typename T>
void LinkedList<T>::push_front(const T& data) {
    // creamos un nodo nuevo que apunte al head actual
    Node<T>* node = new Node<T>(data, head);

    // si la lista estaba vacía, también será el último nodo
    if (head == nullptr) {
        tail = node;
    }

    // actualizamos head
    head = node;

    size++;
}

// agrega un nodo al final sin recorrer la lista
template <typename T>
void LinkedList<T>::push_back(const T& data) {
    // creamos un nodo nuevo
    Node<T>* node = new Node<T>(data);

    // validamos si la lista está vacía
    if (head == nullptr) {
        // el nuevo nodo será el primero y el último
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

// elimina el primer nodo y regresa su dato
template <typename T>
T LinkedList<T>::pop_front() {
    // validamos que la lista no esté vacía
    if (isEmpty()) {
        throw std::out_of_range("La lista esta vacia");
    }

    // guardamos el dato antes de eliminar el nodo
    T data = head->data;

    // guardamos el nodo que se eliminará
    Node<T>* aux = head;

    // actualizamos head al siguiente nodo
    head = head->next;

    // si eliminamos el único nodo, actualizamos tail
    if (head == nullptr) {
        tail = nullptr;
    }

    // liberamos la memoria del nodo eliminado
    delete aux;

    size--;

    return data;
}

// inserta un dato después del índice recibido
template <typename T>
void LinkedList<T>::insert(int index, const T& data) {
    // verificamos que el índice sea válido
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice fuera de rango");
    }

    // si insertamos después del último, usamos tail
    if (index == size - 1) {
        push_back(data);
        return;
    }

    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;

    // avanzamos hasta llegar al índice indicado
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    // el nuevo nodo apunta al siguiente del nodo auxiliar
    Node<T>* node = new Node<T>(data, aux->next);

    // conectamos el nodo auxiliar con el nodo nuevo
    aux->next = node;

    size++;
}

// borra la primera aparición de un dato
template <typename T>
bool LinkedList<T>::deleteData(const T& data) {
    // si la lista está vacía no se puede borrar
    if (isEmpty()) {
        return false;
    }

    // si el dato está en head
    if (head->data == data) {
        Node<T>* aux = head;
        head = head->next;

        // si la lista queda vacía, actualizamos tail
        if (head == nullptr) {
            tail = nullptr;
        }

        delete aux;
        size--;

        return true;
    }

    // buscamos el nodo anterior al que queremos borrar
    Node<T>* aux = head;

    while (aux->next != nullptr && aux->next->data != data) {
        aux = aux->next;
    }

    // si no se encontró el dato
    if (aux->next == nullptr) {
        return false;
    }

    // guardamos el nodo que se eliminará
    Node<T>* nodeToDelete = aux->next;

    // conectamos el nodo anterior con el siguiente
    aux->next = nodeToDelete->next;

    // si borramos el último nodo, actualizamos tail
    if (nodeToDelete == tail) {
        tail = aux;
    }

    // liberamos la memoria del nodo eliminado
    delete nodeToDelete;

    size--;

    return true;
}

// borra el elemento de una posición
template <typename T>
bool LinkedList<T>::deleteAt(int index) {
    // verificamos que el índice sea válido
    if (index < 0 || index >= size) {
        return false;
    }

    // si se quiere borrar head
    if (index == 0) {
        Node<T>* aux = head;
        head = head->next;

        // si la lista queda vacía, actualizamos tail
        if (head == nullptr) {
            tail = nullptr;
        }

        delete aux;
        size--;

        return true;
    }

    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;

    // avanzamos hasta el nodo anterior al que se eliminará
    for (int i = 0; i < index - 1; i++) {
        aux = aux->next;
    }

    // guardamos el nodo que se eliminará
    Node<T>* nodeToDelete = aux->next;

    // conectamos el nodo anterior con el siguiente
    aux->next = nodeToDelete->next;

    // si borramos el último nodo, actualizamos tail
    if (nodeToDelete == tail) {
        tail = aux;
    }

    // liberamos la memoria del nodo eliminado
    delete nodeToDelete;

    size--;

    return true;
}

// obtiene el dato de una posición
template <typename T>
T& LinkedList<T>::getData(int index) {
    // verificamos que el índice sea válido
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice fuera de rango");
    }

    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;

    // avanzamos hasta llegar al índice solicitado
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    return aux->data;
}

// obtiene el dato de una posición en una lista constante
template <typename T>
const T& LinkedList<T>::getData(int index) const {
    // verificamos que el índice sea válido
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice fuera de rango");
    }

    const Node<T>* aux = head;

    // avanzamos hasta llegar al índice solicitado
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    return aux->data;
}

// actualiza la primera aparición de un dato
template <typename T>
bool LinkedList<T>::updateData(
    const T& oldData,
    const T& newData
) {
    Node<T>* aux = head;

    // recorremos la lista buscando el dato anterior
    while (aux != nullptr) {
        if (aux->data == oldData) {
            aux->data = newData;
            return true;
        }

        aux = aux->next;
    }

    // si el dato no se encontró
    return false;
}

// actualiza un dato de una posición
template <typename T>
void LinkedList<T>::updateAt(int index, const T& data) {
    // obtenemos el dato y lo actualizamos
    getData(index) = data;
}

// busca un dato y regresa su posición
template <typename T>
int LinkedList<T>::findData(const T& data) const {
    const Node<T>* aux = head;
    int index = 0;

    // recorremos la lista buscando el dato
    while (aux != nullptr) {
        if (aux->data == data) {
            return index;
        }

        aux = aux->next;
        index++;
    }

    // si el dato no se encontró
    return -1;
}

// permite leer o actualizar usando corchetes
template <typename T>
T& LinkedList<T>::operator[](int index) {
    return getData(index);
}

// permite leer usando corchetes en una lista constante
template <typename T>
const T& LinkedList<T>::operator[](int index) const {
    return getData(index);
}

// limpia todos los nodos de la lista
template <typename T>
void LinkedList<T>::clear() {
    // liberamos los nodos desde el inicio
    while (head != nullptr) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
    }

    // la lista queda vacía
    tail = nullptr;
    size = 0;
}

// duplica una lista en otra usando =
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(
    const LinkedList<T>& other
) {
    // verificamos que una lista no se asigne a sí misma
    if (this != &other) {
        // creamos primero una copia independiente
        LinkedList<T> copy(other);

        // guardamos los apuntadores y tamaño actuales
        Node<T>* auxHead = head;
        Node<T>* auxTail = tail;
        int auxSize = size;

        // recibimos los nodos de la copia
        head = copy.head;
        tail = copy.tail;
        size = copy.size;

        // la copia recibe los nodos anteriores
        // su destructor los liberará al salir de la función
        copy.head = auxHead;
        copy.tail = auxTail;
        copy.size = auxSize;
    }

    return *this;
}

// constructor que copia otra lista
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other)
    : head(nullptr), tail(nullptr), size(0) {

    try {
        // recorremos la otra lista
        const Node<T>* aux = other.head;

        // copiamos sus datos en nodos nuevos
        while (aux != nullptr) {
            push_back(aux->data);
            aux = aux->next;
        }
    }
    catch (...) {
        // liberamos los nodos si la copia no pudo completarse
        clear();
        throw;
    }
}

// destructor de la lista
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// imprime los elementos de la lista
template <typename T>
void LinkedList<T>::print() const {
    const Node<T>* aux = head;

    std::cout << "[";

    // recorremos la lista mientras existan nodos
    while (aux != nullptr) {
        std::cout << aux->data;
        aux = aux->next;

        if (aux != nullptr) {
            std::cout << " - ";
        }
    }

    std::cout << "]" << std::endl;
}

// verifica si la lista está vacía
template <typename T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}

// obtiene el tamaño de la lista
template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

#endif /* LinkedList_h */