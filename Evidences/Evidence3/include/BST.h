#ifndef EVIDENCE3_BST_H
#define EVIDENCE3_BST_H

#include <cstddef>

#include "NodeT.h"

template <typename T>
class BST {
private:
    NodeT<T>* root;
    std::size_t nodeCount;

    int height(const NodeT<T>* node) const;
    void clear(NodeT<T>* node);

    template <typename Visitor>
    void inOrder(const NodeT<T>* node, Visitor& visit) const;

public:
    struct SearchResult {
        std::size_t count;
        std::size_t comparisons;
    };

    BST() : root(nullptr), nodeCount(0) {}
    ~BST();

    // Evitamos copiar los apuntadores del árbol.
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    void insert(const T& data);
    SearchResult search(const T& data) const;
    std::size_t size() const;
    int height() const;

    template <typename Visitor>
    void inOrder(Visitor visit) const;
};

template <typename T>
BST<T>::~BST() {
    clear(root);
}

template <typename T>
void BST<T>::clear(NodeT<T>* node) {
    if (node != nullptr) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

template <typename T>
void BST<T>::insert(const T& data) {
    if (root == nullptr) {
        root = new NodeT<T>(data);
        ++nodeCount;
        return;
    }

    NodeT<T>* aux = root;
    NodeT<T>* father = root;

    // Buscamos la llave o la posición donde se agrega el nodo.
    while (aux != nullptr) {
        if (aux->data == data) {
            ++aux->count;
            return;
        }

        father = aux;
        if (data < aux->data) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    if (data < father->data) {
        father->left = new NodeT<T>(data);
    } else {
        father->right = new NodeT<T>(data);
    }

    ++nodeCount;
}

template <typename T>
typename BST<T>::SearchResult BST<T>::search(const T& data) const {
    const NodeT<T>* aux = root;
    std::size_t comparisons = 0;

    while (aux != nullptr) {
        // Contamos una comparación de llave por nodo visitado.
        ++comparisons;
        if (aux->data == data) {
            return {aux->count, comparisons};
        }

        if (data < aux->data) {
            aux = aux->left;
        } else {
            aux = aux->right;
        }
    }

    return {0, comparisons};
}

template <typename T>
std::size_t BST<T>::size() const {
    return nodeCount;
}

template <typename T>
int BST<T>::height(const NodeT<T>* node) const {
    if (node == nullptr) {
        return -1;
    }

    const int leftHeight = height(node->left);
    const int rightHeight = height(node->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

template <typename T>
int BST<T>::height() const {
    return height(root);
}

template <typename T>
template <typename Visitor>
void BST<T>::inOrder(const NodeT<T>* node, Visitor& visit) const {
    if (node != nullptr) {
        inOrder(node->left, visit);
        visit(node->data, node->count);
        inOrder(node->right, visit);
    }
}

template <typename T>
template <typename Visitor>
void BST<T>::inOrder(Visitor visit) const {
    inOrder(root, visit);
}

#endif