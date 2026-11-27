#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include <iostream>
#include <stdexcept>
#include "NodeD.h"

// guarda las mediciones del ordenamiento
struct SortStats {
    long long comparisons = 0;
    int maxDepth = 0;
};

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size;

    // divide una cadena en dos mitades
    NodeD<T>* split(NodeD<T>* first);

    // une dos cadenas ordenadas
    NodeD<T>* merge(
        NodeD<T>* left,
        NodeD<T>* right,
        SortStats& stats
    );

    // ordena una cadena mediante recursión
    NodeD<T>* mergeSort(
        NodeD<T>* first,
        SortStats& stats,
        int depth
    );

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    DoublyLinkedList(const DoublyLinkedList<T>& other);

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

    bool isSorted() const;
    SortStats sort();
};

// agrega un nodo al principio
template <typename T>
void DoublyLinkedList<T>::addFirst(const T& data) {
    // creamos un nodo nuevo
    NodeD<T>* node = new NodeD<T>(data);

    // el nuevo nodo apunta al primero actual
    node->next = head;

    if (head == nullptr) {
        // el nuevo nodo también será el último
        tail = node;
    }
    else {
        // conectamos el primero actual con el nuevo
        head->prev = node;
    }

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

    if (tail == nullptr) {
        // el nuevo nodo también será el primero
        head = node;
    }
    else {
        // conectamos el último actual con el nuevo
        tail->next = node;
    }

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

    if (node->next != nullptr) {
        // el siguiente debe apuntar hacia el nuevo
        node->next->prev = newNode;
    }
    else {
        // insertamos después del último nodo
        tail = newNode;
    }

    node->next = newNode;
    size++;

    return newNode;
}

// elimina un nodo dado
// debe pertenecer a esta lista y no haber sido eliminado
template <typename T>
bool DoublyLinkedList<T>::deleteNode(NodeD<T>* node) {
    if (node == nullptr) {
        return false;
    }

    if (node->prev != nullptr) {
        // conectamos el anterior con el siguiente
        node->prev->next = node->next;
    }
    else {
        // estamos eliminando el primer nodo
        head = node->next;
    }

    if (node->next != nullptr) {
        // conectamos el siguiente con el anterior
        node->next->prev = node->prev;
    }
    else {
        // estamos eliminando el último nodo
        tail = node->prev;
    }

    delete node;
    size--;

    return true;
}

// obtiene el primer nodo
template <typename T>
NodeD<T>* DoublyLinkedList<T>::getHead() {
    return head;
}

// obtiene el primer nodo de una lista constante
template <typename T>
const NodeD<T>* DoublyLinkedList<T>::getHead() const {
    return head;
}

// obtiene el último nodo
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
    while (head != nullptr) {
        NodeD<T>* aux = head;
        head = head->next;
        delete aux;
    }

    tail = nullptr;
    size = 0;
}

// constructor que copia otra lista
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(
    const DoublyLinkedList<T>& other
) : head(nullptr), tail(nullptr), size(0) {
    try {
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
    if (this != &other) {
        // primero creamos una copia independiente
        DoublyLinkedList<T> copy(other);

        NodeD<T>* auxHead = head;
        NodeD<T>* auxTail = tail;
        int auxSize = size;

        // recibimos los nodos de la copia
        head = copy.head;
        tail = copy.tail;
        size = copy.size;

        // la copia liberará los nodos anteriores al salir
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

// imprime desde head hasta tail
template <typename T>
void DoublyLinkedList<T>::print() const {
    const NodeD<T>* aux = head;

    std::cout << "[";

    while (aux != nullptr) {
        std::cout << aux->data;

        if (aux->next != nullptr) {
            std::cout << " <-> ";
        }

        aux = aux->next;
    }

    std::cout << "] (" << size << " elementos)\n";
}

// imprime desde tail hasta head
template <typename T>
void DoublyLinkedList<T>::printReverse() const {
    const NodeD<T>* aux = tail;

    std::cout << "[";

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

// verifica si los datos están en orden ascendente
template <typename T>
bool DoublyLinkedList<T>::isSorted() const {
    const NodeD<T>* aux = head;

    // comparamos cada nodo con su siguiente
    while (aux != nullptr && aux->next != nullptr) {
        if (aux->next->data < aux->data) {
            return false;
        }

        aux = aux->next;
    }

    // una lista vacía o de un elemento también está ordenada
    return true;
}

// divide una cadena en dos mitades
// recibe una cadena con al menos dos nodos
template <typename T>
NodeD<T>* DoublyLinkedList<T>::split(NodeD<T>* first) {
    NodeD<T>* slow = first;
    NodeD<T>* fast = first->next;

    // slow avanza uno y fast avanza dos
    // cuando fast llega al final, slow está al final de la primera mitad
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // guardamos el inicio de la segunda mitad
    NodeD<T>* second = slow->next;

    // separamos ambas mitades en las dos direcciones
    slow->next = nullptr;
    second->prev = nullptr;

    return second;
}

// une dos cadenas ordenadas sin copiar los datos
template <typename T>
NodeD<T>* DoublyLinkedList<T>::merge(
    NodeD<T>* left,
    NodeD<T>* right,
    SortStats& stats
) {
    NodeD<T>* mergedHead = nullptr;
    NodeD<T>* mergedTail = nullptr;

    // vamos tomando un nodo de alguna de las dos mitades
    while (left != nullptr || right != nullptr) {
        NodeD<T>* selected;

        if (left == nullptr) {
            // ya no quedan nodos en la mitad izquierda
            selected = right;
            right = right->next;
        }
        else if (right == nullptr) {
            // ya no quedan nodos en la mitad derecha
            selected = left;
            left = left->next;
        }
        else {
            // contamos únicamente comparaciones entre datos
            stats.comparisons++;

            if (right->data < left->data) {
                selected = right;
                right = right->next;
            }
            else {
                // en caso de empate elegimos el de la izquierda
                // así conservamos el orden de llegada
                selected = left;
                left = left->next;
            }
        }

        // conectamos el nodo seleccionado al final de la unión
        selected->prev = mergedTail;
        selected->next = nullptr;

        if (mergedTail == nullptr) {
            // es el primer nodo de la unión
            mergedHead = selected;
        }
        else {
            mergedTail->next = selected;
        }

        mergedTail = selected;
    }

    return mergedHead;
}

// ordena una cadena mediante Merge Sort
template <typename T>
NodeD<T>* DoublyLinkedList<T>::mergeSort(
    NodeD<T>* first,
    SortStats& stats,
    int depth
) {
    // registramos el nivel más profundo alcanzado
    if (depth > stats.maxDepth) {
        stats.maxDepth = depth;
    }

    // caso base: cero o un nodo
    if (first == nullptr || first->next == nullptr) {
        return first;
    }

    // dividimos la cadena en dos mitades
    NodeD<T>* second = split(first);

    // ordenamos cada mitad
    NodeD<T>* left = mergeSort(first, stats, depth + 1);
    NodeD<T>* right = mergeSort(second, stats, depth + 1);

    // unimos las dos mitades ordenadas
    return merge(left, right, stats);
}

// ordena la lista y regresa las mediciones
template <typename T>
SortStats DoublyLinkedList<T>::sort() {
    SortStats stats;

    // no necesitamos ordenar una lista vacía o de un elemento
    if (size < 2) {
        return stats;
    }

    // el primer nivel de recursión se cuenta como 1
    head = mergeSort(head, stats, 1);

    // localizamos el nuevo último nodo
    tail = head;

    while (tail->next != nullptr) {
        tail = tail->next;
    }

    // aseguramos que los extremos apunten hacia afuera a nullptr
    head->prev = nullptr;
    tail->next = nullptr;

    return stats;
}

#endif /* DoublyLinkedList_h */