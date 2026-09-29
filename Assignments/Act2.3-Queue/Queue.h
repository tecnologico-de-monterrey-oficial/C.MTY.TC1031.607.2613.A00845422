#ifndef QUEUE_H
#define QUEUE_H

#include "Node.h"

template <typename T>
class Queue {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    void pop();
    void push(const T& value);
};

template <typename T>
void Queue<T>::pop() {
// validamos que no este vacio 
if (head != nullptr) {
    if (head == tail) {
       // creamos un apuntador auxiliar que apunte a head
        Node<T>* aux = head;
        // actualizamos head y tail a nullptr
        head = nullptr;
        tail = nullptr;
        // liberamos la memoria del nodo eliminado
        delete aux;
    } 
    else {
        // creamos un apuntador auxiliar que apunte a head
        Node<T>* aux = head;
        // actualizamos head al siguiente nodo
        head = head->next;
        // liberamos la memoria del nodo eliminado
        delete aux;
        }
    }
}

template <typename T>
void Queue<T>::push(T data) {
    //validamos que no este vacio
    if (head != nullptr) {
        //actualizamos el next del tail para que apunte al nuevo nodo
        tail->next = new Node<T>(data);
        //actualizamos tail al nuevo nodo
        tail = tail->next;
    } else {
        //actualizamos head y tail al nuevo nodo
        head = new Node<T>(data);
        tail = head;
    }


};
#endif   