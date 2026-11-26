#ifndef EVIDENCE3_HEAP_H
#define EVIDENCE3_HEAP_H

#include <cstddef>
#include <stdexcept>
#include <utility>
#include <vector>

template <typename T, typename Compare>
class Heap {
private:
    std::vector<T> heap;
    Compare compare;
    std::size_t comparisonCount = 0;

    bool hasPriority(std::size_t a, std::size_t b) {
        ++comparisonCount;
        return compare(heap[a], heap[b]);
    }

    void siftUp(std::size_t child) {
        while (child > 0) {
            const std::size_t parent = (child - 1) / 2;

            if (!hasPriority(child, parent)) {
                break;
            }

            std::swap(heap[child], heap[parent]);
            child = parent;
        }
    }

    void siftDown(std::size_t parent) {
        // Los índices menores a size() / 2 tienen al menos un hijo.
        while (parent < size() / 2) {
            const std::size_t left = 2 * parent + 1;
            const std::size_t right = left + 1;
            std::size_t bestChild = left;

            if (right < size() && hasPriority(right, left)) {
                bestChild = right;
            }

            if (!hasPriority(bestChild, parent)) {
                break;
            }

            std::swap(heap[parent], heap[bestChild]);
            parent = bestChild;
        }
    }

public:
    explicit Heap(Compare compare) : compare(compare) {}

    std::size_t size() const {
        return heap.size();
    }

    bool empty() const {
        return heap.empty();
    }

    std::size_t comparisons() const {
        return comparisonCount;
    }

    // Altura en aristas. Vacío: -1. Solo la raíz: 0.
    int height() const {
        int result = -1;

        for (std::size_t nodes = size(); nodes > 0; nodes /= 2) {
            ++result;
        }

        return result;
    }

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("Heap vacio");
        }
        return heap.front();
    }

    void push(const T& data) {
        heap.push_back(data);
        siftUp(size() - 1);
    }

    T pop() {
        if (empty()) {
            throw std::out_of_range("Heap vacio");
        }

        T data = std::move(heap.front());

        if (size() > 1) {
            heap.front() = std::move(heap.back());
        }

        heap.pop_back();
        siftDown(0);
        return data;
    }
};

#endif