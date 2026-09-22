#ifndef LinkedList_h
#define LinkedList_h
#include "Node.h"


template <typename T>
class LinkedList {
    private:
        std::unique_ptr< Node<T> > head;
        int size;
    public:
        LinkedList() : head(nullptr), size(0) {}
        void push_front (T data);
        void push_back (T data);
        void print();
};


template <typename T>
void LinkedList<T>::push_front(T data) {
    // crear un nodo nuevo
    std::unique_ptr<Node<T>> node = std::make_unique<Node<T>>(data);
    //Actualizo el next del nodo nuevo para que apunte al head actual
    node->next = std::move(head);
    //Actualizo el head para que apunte al nodo nuevo
    head = std::move(node);
    
}
#endif /* LinkedList_h */   

template <typename T>
void LinkedList<T>::print() {
    // creamos un puntero auxiliar que apunte al head
    Node<T>* aux = head;
    // recorremos la lista mientras aux sea diferente de nullptr
    while (aux != nullptr) {
        std::cout << aux->data << "-";
        aux = aux->next;
    }
    std::cout << std::endl;
}