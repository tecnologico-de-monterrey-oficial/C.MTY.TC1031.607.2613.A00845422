#include <functional>
#include <iostream>
#include <vector>

#include "HeapSort.h"

void printValues(const std::vector<int>& values) {
    std::cout << '[';

    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            std::cout << ", ";
        }
        std::cout << values[i];
    }

    std::cout << ']';
}

bool check(const char* name, const std::vector<int>& expected,
           const HeapSortResult<int>& actual, int expectedHeight) {
    const bool passed = actual.values == expected &&
                        actual.height == expectedHeight &&
                        (expected.size() < 2 ? actual.comparisons == 0
                                             : actual.comparisons > 0);

    std::cout << name << " | Esperado: ";
    printValues(expected);
    std::cout << " | Obtenido: ";
    printValues(actual.values);
    std::cout << '\n'
              << "  Altura esperada: " << expectedHeight
              << " | Obtenida: " << actual.height
              << " | Comparaciones: " << actual.comparisons
              << " | " << (passed ? "OK" : "FALLO") << '\n';

    return passed;
}

int main() {
    const std::vector<int> input{4, -1, 8, 4, 2};
    const std::vector<int> empty;
    const std::vector<int> single{7};

    bool passed = true;
    passed &= check("Ascendente", {-1, 2, 4, 4, 8},
                    heapSort(input, std::less<int>{}), 2);
    passed &= check("Descendente", {8, 4, 4, 2, -1},
                    heapSort(input, std::greater<int>{}), 2);
    passed &= check("Entrada vacia", {},
                    heapSort(empty, std::less<int>{}), -1);
    passed &= check("Un solo valor", {7},
                    heapSort(single, std::less<int>{}), 0);

    return passed ? 0 : 1;
}