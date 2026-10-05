#ifndef LinkedList_h
#define LinkedList_h

#include <iostream>
#include <stdexcept>
#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    // constructor copia
    LinkedList(const LinkedList<T>& other);

    // destructor
    ~LinkedList();

    void push_front(const T& data);
    void push_back(const T& data);
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
    int getSize() const;
};

// agrega un nodo al principio
template <typename T>
void LinkedList<T>::push_front(const T& data) {
    // crear un nodo nuevo
    Node<T>* node = new Node<T>(data);

    // actualizo el next del nodo nuevo para que apunte a head
    node->next = head;

    // actualizo head
    head = node;

    size++;
}

// agrega un nodo al final
template <typename T>
void LinkedList<T>::push_back(const T& data) {
    // crear un nodo nuevo
    Node<T>* node = new Node<T>(data);

    // si la lista está vacía, el nodo será head
    if (head == nullptr) {
        head = node;
    }
    else {
        // creamos un apuntador auxiliar que apunte a head
        Node<T>* aux = head;

        // recorremos hasta llegar al último nodo
        while (aux->next != nullptr) {
            aux = aux->next;
        }

        // conectamos el último nodo con el nodo nuevo
        aux->next = node;
    }

    size++;
}

// inserta un dato después del índice recibido
template <typename T>
void LinkedList<T>::insert(int index, const T& data) {
    // verificamos que el índice sea válido
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice fuera de rango");
    }

    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;

    // avanzamos hasta llegar al índice indicado
    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    // creamos un nodo nuevo
    Node<T>* node = new Node<T>(data);

    // el nuevo nodo apunta al siguiente del nodo auxiliar
    node->next = aux->next;

    // el nodo auxiliar apunta al nodo nuevo
    aux->next = node;

    size++;
}

// borra la primera aparición de un dato
template <typename T>
bool LinkedList<T>::deleteData(const T& data) {
    // si la lista está vacía no se puede borrar
    if (head == nullptr) {
        return false;
    }

    // si el dato está en head
    if (head->data == data) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
        size--;
        return true;
    }

    // recorremos la lista buscando el dato
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

    // conectamos el nodo anterior con el nodo siguiente
    aux->next = nodeToDelete->next;

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

    // regresamos el dato encontrado
    return aux->data;
}

// obtiene el dato de una posición en una lista constante
template <typename T>
const T& LinkedList<T>::getData(int index) const {
    // verificamos que el índice sea válido
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice fuera de rango");
    }

    Node<T>* aux = head;

    for (int i = 0; i < index; i++) {
        aux = aux->next;
    }

    return aux->data;
}

// actualiza la primera aparición de un dato
template <typename T>
bool LinkedList<T>::updateData(const T& oldData, const T& newData) {
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
    Node<T>* aux = head;
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
    // mientras haya nodos en la lista
    while (head != nullptr) {
        Node<T>* aux = head;
        head = head->next;
        delete aux;
    }

    size = 0;
}

// duplica una lista en otra usando =
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    // verificamos que una lista no se asigne a sí misma
    if (this != &other) {
        // eliminamos los datos actuales
        clear();

        // recorremos la otra lista
        Node<T>* aux = other.head;

        // agregamos sus datos a la lista actual
        while (aux != nullptr) {
            push_back(aux->data);
            aux = aux->next;
        }
    }

    return *this;
}

// constructor que copia otra lista
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), size(0) {
    // usamos la sobrecarga del operador =
    *this = other;
}

// destructor de la lista
template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// imprime los elementos de la lista
template <typename T>
void LinkedList<T>::print() const {
    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;

    std::cout << "[";

    // recorremos la lista mientras aux sea diferente de nullptr
    while (aux != nullptr) {
        std::cout << aux->data;
        aux = aux->next;

        if (aux != nullptr) {
            std::cout << " - ";
        }
    }

    std::cout << "]" << std::endl;
}

// obtiene el tamaño de la lista
template <typename T>
int LinkedList<T>::getSize() const {
    return size;
}

#endif /* LinkedList_h */