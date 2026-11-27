#pragma once

#include <cstddef>

template <typename T>
struct NodeT {
    T data;
    NodeT<T>* left;
    NodeT<T>* right;
    std::size_t count;

    NodeT(const T& value)
        : data(value), left(nullptr), right(nullptr), count(1) {}
};