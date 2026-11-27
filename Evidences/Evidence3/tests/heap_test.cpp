#include <functional>
#include <iostream>

#include "Heap.h"

bool check(const char* name, int expected, int actual) {
    const bool passed = expected == actual;

    std::cout << name << " | Esperado: " << expected
              << " | Obtenido: " << actual
              << " | " << (passed ? "OK" : "FALLO") << '\n';

    return passed;
}

int main() {
    Heap<int, std::greater<int>> maxHeap(std::greater<int>{});
    Heap<int, std::less<int>> minHeap(std::less<int>{});
    bool passed = true;

    passed &= check("Altura del heap vacio", -1, maxHeap.height());

    bool rejectedEmptyPop = false;
    try {
        maxHeap.pop();
    } catch (const std::out_of_range&) {
        rejectedEmptyPop = true;
    }
    passed &= check("Pop vacio rechazado", 1, rejectedEmptyPop);

    maxHeap.push(4);
    passed &= check("Altura con un nodo", 0, maxHeap.height());
    passed &= check("Comparaciones con un nodo", 0, maxHeap.comparisons());

    maxHeap.push(9);
    maxHeap.push(6);
    passed &= check("MaxHeap top", 9, maxHeap.top());
    passed &= check("MaxHeap primer pop", 9, maxHeap.pop());
    passed &= check("MaxHeap top tras bajar", 6, maxHeap.top());

    minHeap.push(4);
    minHeap.push(9);
    minHeap.push(6);
    passed &= check("MinHeap top", 4, minHeap.top());
    passed &= check("MinHeap primer pop", 4, minHeap.pop());
    passed &= check("MinHeap segundo pop", 6, minHeap.pop());
    passed &= check("MinHeap ultimo pop", 9, minHeap.pop());
    passed &= check("MinHeap queda vacio", 1, minHeap.empty());

    return passed ? 0 : 1;
}