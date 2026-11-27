#ifndef EVIDENCE3_HEAP_SORT_H
#define EVIDENCE3_HEAP_SORT_H

#include <cstddef>
#include <vector>

#include "Heap.h"

template <typename T>
struct HeapSortResult {
    std::vector<T> values;
    std::size_t comparisons;
    int height;
};

template <typename T, typename Compare>
HeapSortResult<T> heapSort(const std::vector<T>& input, Compare compare) {
    Heap<T, Compare> heap(compare);

    for (const T& value : input) {
        heap.push(value);
    }

    HeapSortResult<T> result{};
    result.height = heap.height();
    result.values.reserve(heap.size());

    while (!heap.empty()) {
        result.values.push_back(heap.pop());
    }

    result.comparisons = heap.comparisons();
    return result;
}

#endif