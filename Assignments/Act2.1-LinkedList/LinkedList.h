#ifndef LinkedList_h
#define LinkedList_h

#include "Node.h"

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    int size;
public:
    LinkedList() : head(nullptr), size(0) {}
    void push_front(T data);
    void push_back(T data);
    void print();
};

template <typename T>
void LinkedList<T>::push_front(T data) {
    // crear un nodo nuevo
    Node<T>* node = new Node<T>(data);
    // actualizo el next del nodo nuevo para que apunte a head
    node->next = head;
    // actualizo head
    head = node;
}

template <typename T>
void LinkedList<T>::print() {
    // creamos un apuntador auxiliar que apunte a head
    Node<T>* aux = head;
    // recorremos la lista mientras aux sea diferente de nullptr
    while (aux != nullptr) {
        cout << aux->data;
        aux = aux->next;
        if (aux != nullptr) {
            cout << "-";
        }
    }
    cout << endl;
}

template <typename T>
void LinkedList<T>::push_back(T data){
    Node<T>* node = new Node<T>(data);   
    if (head == nullptr) {              
        head = node;                    
    } else {
        Node<T>* aux = head;            
        while (aux->next != nullptr) {  
            aux = aux->next;            
        }
        aux->next = node;               
    }
    size++;
}

#endif /* LinkedList_h */