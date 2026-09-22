#include "SearchManager.h"


int findLowerBound(
    const std::vector<Log>& logs,
    long long targetKey
) {
    int left = 0;
    int right = static_cast<int>(logs.size());

    while (left < right) {
        int middle = left + (right - left) / 2;

        if (logs[middle].key < targetKey) {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }

    return left;
}


int findUpperBound(
    const std::vector<Log>& logs,
    long long targetKey
) {
    int left = 0;
    int right = static_cast<int>(logs.size());

    while (left < right) {
        int middle = left + (right - left) / 2;

        if (logs[middle].key <= targetKey) {
            left = middle + 1;
        }
        else {
            right = middle;
        }
    }

    return left;
}