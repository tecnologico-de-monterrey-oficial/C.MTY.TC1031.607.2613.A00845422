#ifndef Heap_h
#define Heap_h

#include <vector>

template <typename T>
class Heap {
private:
    vector<T> heap;
    void swap(int a, int b);
    void shiftDown(int aux);
public:
    Heap() {};
    Heap(std::vector<T> list);
    void push(T data);
    T pop();
    void print();
    void printTree(int index, int space);
};

// shiftdown
template <typename T>
void Heap<T>::shiftDown(int aux) {
    // obtenemos el ultimo parent
    int lastParent = heap.size() / 2 - 1;
    // iteramos mientras los hijos de aux sean padres
    while (aux <= lastParent) {
        // calculamos el índice de primer hijo
        int first = aux * 2 + 1;
        // validar si aux tiene 2 hijos o 1 hijo
        // definimos una varibale para determinar cual hijo es mayor
        int elder;
        if (first == heap.size()-1) {
            // tiene un hijo
            elder = first;
        } else {
            // tiene dos hijos
            // calculamos el 2do hijo
            int second = aux * 2 + 2;
            // validamos cual es que tiene mayor prioridad
            elder = (heap[first] > heap[second]) ? first : second;
        }
        // comparamos si el más grande de los hijos es mayor a aux
        if (heap[elder] > heap[aux]) {
            // el mayor de los hijos es de mayor priodidad que el padre
            swap(aux, elder);
            // cambiamos el valor de aux igual a elder
            aux = elder;
        } else {
            aux = lastParent+1;
        }
    }
}

// constructor en base a una lista
template <typename T>
Heap<T>::Heap(std::vector<T> list) {
    // actualizamos heap con el valor de list
    heap = list;
    // determinar cual es el último de los padres
    int lastParent = heap.size() / 2 - 1;
    // iteramos desde el último de los padres hasta el primero
    int parent = lastParent;
    while (parent >= 0) {
        shiftDown(parent);
        // decrementamos el valor del indice del padre actual
        parent--;
    }
}

// swap function to swap two elements in the heap
template <typename T>
void Heap<T>::swap(int a, int b) {
    T temp = heap[a];
    heap[a] = heap[b];
    heap[b] = temp;
}

template <typename T>
T Heap<T>::pop() {
    if (heap.size() > 0) {
        T data = heap[0];
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        shiftDown(0);
        return data;
    }
    throw std::out_of_range("Heap is empty");
}

template <typename T>
void Heap<T>::push(T data) {
    // agrego el elemento al final de lista
    heap.push_back(data);
    // determino el índice del elemento agregado
    int index = heap.size()-1;
    // encuentro el indice del padre
    int father = (index - 1) / 2;
    // itero mientras el índice del padre sea mayor o igual a 0
    while (father >= 0) {
        // comparo si el valor del indice es mayor al valor del padre
        if (heap[index] > heap[father]) {
            // si es mayor
            // intercambio los valores
            swap(index, father);
            // hago que el indice sea igual al padre
            index = father;
            // calculo el nuevo padre
            father = (index - 1) / 2;
        } else {
            // no es mayor
            // me salgo de la función
            return;
        }
    }
}

// print function to print the elements of the heap
template <typename T>
void Heap<T>::print() {
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}

// print del tree
template <typename T>
void Heap<T>::printTree(int index, int space) {
    if (index >= heap.size()) {
        return;
    }
    space += 5;
    printTree(2 * index + 2, space);
    cout << endl;
    for (int i = 5; i < space; i++) {
        cout << " ";
    }
    cout << heap[index] << "\n";
    printTree(2 * index + 1, space);
}



#endif /* Heap_h */