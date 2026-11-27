#include <iostream>
#include <string>

#include "BST.h"

template <typename T>
bool check(const char* name, const T& expected, const T& actual) {
    const bool passed = expected == actual;

    std::cout << name << " | Esperado: " << expected
              << " | Obtenido: " << actual
              << " | " << (passed ? "OK" : "FALLO") << '\n';

    return passed;
}

int main() {
    BST<int> bst;
    bool passed = true;

    passed &= check("Altura del BST vacio", -1, bst.height());
    passed &= check("Comparaciones en BST vacio",
                    std::size_t{0}, bst.search(5).comparisons);

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(3);

    passed &= check("Nodos distintos", std::size_t{3}, bst.size());
    passed &= check("Altura con tres nodos", 1, bst.height());

    const auto found = bst.search(3);
    passed &= check("Apariciones de 3", std::size_t{2}, found.count);
    passed &= check("Comparaciones al buscar 3",
                    std::size_t{2}, found.comparisons);

    const auto missing = bst.search(4);
    passed &= check("Apariciones de 4", std::size_t{0}, missing.count);
    passed &= check("Comparaciones al buscar 4",
                    std::size_t{2}, missing.comparisons);

    std::string order;
    bst.inOrder([&](int data, std::size_t count) {
        if (!order.empty()) {
            order += ", ";
        }
        order += std::to_string(data) + "(" + std::to_string(count) + ")";
    });
    passed &= check("Inorden", std::string("3(2), 5(1), 7(1)"), order);

    BST<int> sorted;
    for (int data = 1; data <= 4; ++data) {
        sorted.insert(data);
    }

    passed &= check("Altura al insertar 1, 2, 3, 4", 3, sorted.height());
    passed &= check("Comparaciones al buscar 4 en cadena",
                    std::size_t{4}, sorted.search(4).comparisons);

    return passed ? 0 : 1;
}