#ifndef List_h
#define List_h

#include <vector>
#include <iostream>

template <typename T>
class List {
    private:
        std::vector<T> list;
        int size;

    public:
        List();
        void insert(T data);
        void removeLast();
        T getData(int pos);
        int getSize();
        T getMax();
        void print();
        void insertAt(int pos, T data);
        void removeAt(int pos);
};

template <typename T>
List<T>::List() {
    size = 0;
}

template <typename T>
void List<T>::insert(T data) {
    list.push_back(data);
    size++;
}

template <typename T>
void List<T>::removeLast() {
    if (size == 0) {
        std::cout << "NO HAY ELEMENTOS" << std::endl;
        return;
    }

    std::cout << list[size - 1] << std::endl;
    list.pop_back();
    size--;
}

template <typename T>
T List<T>::getData(int pos) {
    return list[pos];
}

template <typename T>
int List<T>::getSize() {
    return size;
}

template <typename T>
T List<T>::getMax() {
    T max = list[0];

    for (int i = 1; i < size; i++) {
        if (list[i] > max) {
            max = list[i];
        }
    }

    return max;
}

template <typename T>
void List<T>::print() {
    for (int i = 0; i < size; i++) {
        std::cout << "[" << i << "] - " << list[i] << std::endl;
    }
}

template <typename T>
void List<T>::insertAt(int pos, T data) {
    if (pos < 0 || pos > size) {
        std::cout << "POSICIÓN INVÁLIDA" << std::endl;
        return;
    }

    list.insert(list.begin() + pos, data);
    size++;
}

template <typename T>
void List<T>::removeAt(int pos) {
    if (size == 0) {
        std::cout << "NO HAY ELEMENTOS" << std::endl;
        return;
    }

    if (pos < 0 || pos >= size) {
        std::cout << "POSICIÓN INVÁLIDA" << std::endl;
        return;
    }

    std::cout << list[pos] << std::endl;
    list.erase(list.begin() + pos);
    size--;
}