#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "NodeD.h"
#include <iostream>
#include <stdexcept>

template <typename T>
class DoublyLinkedList {
private:
    NodeD<T>* head;
    NodeD<T>* tail;
    int size = 0;
    NodeD<T>* getNode(int index) const;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    DoublyLinkedList(const DoublyLinkedList<T>& other);
    ~DoublyLinkedList();
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    T& operator[](int index);
    const T& operator[](int index) const;
    T getData(int index) const;
    void updateData(T data, T newData);
    void updateAt(int index, T data);
    void clear();
    void sort();
    void duplicate();
    void removeDuplicates();
    void print() const;
    void printReverse() const;
    int getSize() const { return size; }
    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteAt(int index);
    int findData(T data);
    bool deleteData(T data);
};

template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el next de aux a head
        aux->next = head;
        // apuntamos el prev de head a aux
        head->prev = aux;
        // apuntamos head a aux
        head = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // validamos si la lista está vacía
    if (head == nullptr) {
        // si está vacía la lista
        // apunto head a un nuevo nodo con data
        head = new NodeD<T>(data);
        // apunto tail a head
        tail = head;
        // incremento size
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        NodeD<T>* aux = new NodeD<T>(data);
        // apuntamos el prev de aux a tail
        aux->prev = tail;
        // apuntamos el next de tail a aux
        tail->next = aux;
        // apuntamos tail a aux
        tail = aux;
        // incrementamos size
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // validamos que él índice sea válido
    if (index >= 0 && index <= size-1) {
        // validamos que el indice sea desde 0 hasta el penúltimo
        if (index != size-1) {
            // el index es desde 0 hasta el penúltimo (en medio)
            // creamos un indice auxiliar igual a 0
            int auxIndex = 0;
            // creamos un apuntador auxiliar igual a head
            NodeD<T>* aux = head;
            // iteramos hasta encontrar el índice dato
            while (auxIndex < index) {
                // recorremos aux
                aux = aux->next;
                // incrementamos el indice auxiliar
                auxIndex++;
            }
            // creamos un nodo nuevo
            NodeD<T>* auxNew = new NodeD<T>(data);
            // el prev del nuevo lo apuntamos a aux
            auxNew->prev = aux;
            // el next del nuevo lo apuntamos a aux->next
            auxNew->next = aux->next;
            // el prev del siguiente de aux lo apuntamos al nuevo
            aux->next->prev = auxNew;
            // apuntamos aux next al nuevo
            aux->next = auxNew;
            // incrmenetamos size
            size++;
        } else {
            // el index es igual a size -1
            // hacemos como si fuera addLast
            // creamos un nuevo nodo
            NodeD<T>* aux = new NodeD<T>(data);
            // apuntamos el prev de aux a tail
            aux->prev = tail;
            // apuntamos el next de tail a aux
            tail->next = aux;
            // apuntamos tail a aux
            tail = aux;
            // incrementamos size
            size++;
        }
    } else {
        throw std::out_of_range("Índice inválido");
    }
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    // validamos si el índice es válido
    if (index >= 0 && index < size) {
        // índíce válido
        // validamos si solo hay un elemento
        if (head->next == nullptr) {
            // solo hay un elemento
            // creamos un nodo auxiliar que apunte a head
            NodeD<T>* aux = head;
            // apuntamos a nulos head y tail
            head = nullptr;
            tail = nullptr;
            // liberamos aux
            delete aux;
            // decrementamos size
            size--;
            // retornamos verdadero
            return true;
        } else {
            // hay más de un elemento
            // validamos si queremos borrar el primero
            if (index == 0) {
                // queremos borrar el primero
                // creamos un nodo auxiliar que apunte a head
                NodeD<T>* aux = head;  
                // apuntamos head al siguiente elemento
                head = head->next;
                // actualizamos el apuntador prev de head
                head->prev = nullptr;
                // liberamos aux
                delete aux;
                // decrementamos size
                size--;
                // retornamos verdadero
                return true; 
            } else {
                // validamos si queremos borrar el último elemento
                if (index == size -1) {
                    // borramos el último
                    // creamos un nodo auxiliar que apunte a tail
                    NodeD<T>* aux = tail;  
                    // apuntamos tail al elemento previo
                    tail = tail->prev;
                    // actualizamos el apuntador prev de head
                    tail->next = nullptr;
                    // liberamos aux
                    delete aux;
                    // decrementamos size
                    size--;
                    // retornamos verdadero
                    return true; 
                } else {
                    // borramos el de en medio
                    // revisamos por donde empezamos a recorrer la lista
                    if (index <= (size-1)/2) {
                        // recorremos por la izquierda
                        // creamos un indice auxliar = 1
                        int auxIndex = 1;
                        // creamos un apuntador auxiliar igual a head->next
                        NodeD<T>* aux = head->next;
                        // recorremos la lista mientras auxIndex < index
                        while (auxIndex < index) {
                            // recorremos aux
                            aux = aux->next;
                            // incrementamos auxIndex
                            auxIndex++;
                        }
                        // ya llegue al nodo deseado
                        // actualizamos el next de aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // actualizamos el prev de aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        // libero aux
                        delete aux;
                        // decremento size
                        size--;
                        // regreso true
                        return true;
                    } else {
                        // recorremos por la derecha
                        // creamos un indice auxliar = size -2
                        int auxIndex = size - 2;
                        // creamos un apuntador auxiliar igual a tail->prev
                        NodeD<T>* aux = tail->prev;
                        // recorremos la lista mientras indez < auxIndex
                        while (index < auxIndex) {
                            // recorremos aux
                            aux = aux->prev;
                            // decrementamos auxIndex
                            auxIndex--;
                        }
                        // ya llegue al nodo deseado
                        // actualizamos el next de aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // actualizamos el prev de aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        // libero aux
                        delete aux;
                        // decremento size
                        size--;
                        // regreso true
                        return true;
                    }
                }
            }
        }
    } else {
        // índice inválido
        return false;
    }
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) {
    // creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    // incializamos un indice auxialiar en 0
    int auxIndex = 0;
    // recorremos la lista mientras sea diferente
    while (auxIndex < size) {
        // validamos si lo encontramos
        if (aux->data == data) {
            // si lo encontramos
            return auxIndex;
        }
        // recorremos aux e incrmentamos auxIndex
        auxIndex++;
        aux = aux->next;
    }
    // data no se encuentra en la lista
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    // find Data
    // creamos un apuntador auxiliar
    NodeD<T>* aux = head;
    // incializamos un indice auxialiar en 0
    int auxIndex = 0;
    // recorremos la lista mientras sea diferente
    while (auxIndex < size) {
        // validamos si lo encontramos
        if (aux->data == data) {
            // si lo encontramos, hay que borrarlo
            // valiamos si es el único
            if (head == tail) {
                // apuntamos a nulos head y tail
                head = nullptr;
                tail = nullptr;
                // liberamos aux
                delete aux;
                // decrementamos size
                size--;
                // retornamos verdadero
                return true;
            } else {
                // validamos si vamos a borrar head
                if (aux == head) {
                    // si es el primer elemento
                    // apuntamos head al siguiente elemento
                    head = head->next;
                    // actualizamos el apuntador prev de head
                    head->prev = nullptr;
                    // liberamos aux
                    delete aux;
                    // decrementamos size
                    size--;
                    // retornamos verdadero
                    return true; 
                } else {
                    // validamos si el último elemento
                    if (aux == tail) {
                        // si es el último elemento
                        // apuntamos tail al elemento previo
                        tail = tail->prev;
                        // actualizamos el apuntador prev de head
                        tail->next = nullptr;
                        // liberamos aux
                        delete aux;
                        // decrementamos size
                        size--;
                        // retornamos verdadero
                        return true; 
                    } else {
                        // boramos el de en medio
                        // actualizamos el next de aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // actualizamos el prev de aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        // libero aux
                        delete aux;
                        // decremento size
                        size--;
                        // regreso true
                        return true;
                    }
                }
            }
        }
        // recorremos aux e incrmentamos auxIndex
        auxIndex++;
        aux = aux->next;
    }
    // data no se encuentra en la lista
    return false;

}

// buscamos el nodo desde el extremo más cercano
template <typename T>
NodeD<T>* DoublyLinkedList<T>::getNode(int index) const {
    // validamos que el índice sea válido
    if (index < 0 || index >= size) {
        throw std::out_of_range("Indice invalido");
    }
    NodeD<T>* aux;
    if (index <= (size - 1) / 2) {
        // recorremos por la izquierda
        aux = head;
        for (int auxIndex = 0; auxIndex < index; auxIndex++) {
            aux = aux->next;
        }
    } else {
        // recorremos por la derecha
        aux = tail;
        for (int auxIndex = size - 1; auxIndex > index; auxIndex--) {
            aux = aux->prev;
        }
    }
    return aux;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T>& other)
    : head(nullptr), tail(nullptr), size(0) {
    // copiamos los datos en nodos nuevos
    try {
        NodeD<T>* aux = other.head;
        while (aux != nullptr) {
            addLast(aux->data);
            aux = aux->next;
        }
    } catch (...) {
        // liberamos los nodos si no se pudo terminar la copia
        clear();
        throw;
    }
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    // liberamos todos los nodos al destruir la lista
    clear();
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    // validamos que no sea la misma lista
    if (this != &other) {
        // primero creamos una copia independiente
        DoublyLinkedList<T> copy(other);
        NodeD<T>* auxHead = head;
        NodeD<T>* auxTail = tail;
        int auxSize = size;
        head = copy.head;
        tail = copy.tail;
        size = copy.size;
        // la copia libera los nodos anteriores al salir
        copy.head = auxHead;
        copy.tail = auxTail;
        copy.size = auxSize;
    }
    return *this;
}

template <typename T>
T DoublyLinkedList<T>::getData(int index) const {
    return getNode(index)->data;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    // regresamos una referencia para leer o actualizar
    return getNode(index)->data;
}

template <typename T>
const T& DoublyLinkedList<T>::operator[](int index) const {
    return getNode(index)->data;
}

template <typename T>
void DoublyLinkedList<T>::updateData(T data, T newData) {
    // buscamos la primera coincidencia
    int index = findData(data);
    if (index == -1) {
        throw std::out_of_range("Dato no encontrado");
    }
    updateAt(index, newData);
}

template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T data) {
    // actualizamos el dato del nodo encontrado
    getNode(index)->data = data;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    // recorremos la lista liberando cada nodo
    while (head != nullptr) {
        NodeD<T>* aux = head;
        head = head->next;
        delete aux;
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
void DoublyLinkedList<T>::sort() {
    // usamos bubble sort intercambiando los datos
    if (size < 2) {
        return;
    }
    for (int i = 0; i < size - 1; i++) {
        NodeD<T>* aux = head;
        bool changed = false;
        for (int j = 0; j < size - 1 - i; j++) {
            if (aux->data > aux->next->data) {
                T auxData = aux->data;
                aux->data = aux->next->data;
                aux->next->data = auxData;
                changed = true;
            }
            aux = aux->next;
        }
        // terminamos si la lista ya está ordenada
        if (!changed) {
            break;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::duplicate() {
    NodeD<T>* aux = head;
    while (aux != nullptr) {
        // creamos la copia a la derecha del nodo original
        NodeD<T>* auxNew = new NodeD<T>(aux->data, aux->next, aux);
        if (aux->next != nullptr) {
            aux->next->prev = auxNew;
        } else {
            tail = auxNew;
        }
        aux->next = auxNew;
        size++;
        // avanzamos al siguiente original
        aux = auxNew->next;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    // ordenamos primero para juntar los datos iguales
    sort();
    NodeD<T>* aux = head;
    while (aux != nullptr && aux->next != nullptr) {
        if (aux->data == aux->next->data) {
            // eliminamos el siguiente nodo repetido
            NodeD<T>* auxDelete = aux->next;
            aux->next = auxDelete->next;
            if (aux->next != nullptr) {
                aux->next->prev = aux;
            } else {
                tail = aux;
            }
            delete auxDelete;
            size--;
        } else {
            aux = aux->next;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::print() const {
    NodeD<T>* aux = head;
    std::cout << "[";
    while (aux != nullptr) {
        std::cout << aux->data;
        if (aux->next != nullptr) std::cout << " <-> ";
        aux = aux->next;
    }
    std::cout << "] (" << size << " elementos)\n";
}

template <typename T>
void DoublyLinkedList<T>::printReverse() const {
    // recorremos desde tail para revisar los apuntadores prev
    NodeD<T>* aux = tail;
    std::cout << "[";
    while (aux != nullptr) {
        std::cout << aux->data;
        if (aux->prev != nullptr) std::cout << " <-> ";
        aux = aux->prev;
    }
    std::cout << "]\n";
}

#endif /* DoublyLinkedList_h */
