#pragma once

template <typename T>
struct NodeT {
    T data;
    NodeT<T>* left;
    NodeT<T>* right;

    NodeT(const T& value) : data(value), left(nullptr), right(nullptr) {}
    NodeT(const T& value, NodeT<T>* leftNode, NodeT<T>* rightNode) : data(value), left(leftNode), right(rightNode) {} 
};