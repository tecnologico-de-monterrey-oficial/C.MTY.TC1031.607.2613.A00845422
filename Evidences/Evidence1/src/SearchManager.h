#ifndef SEARCH_MANAGER_H
#define SEARCH_MANAGER_H

#include "Log.h"

#include <vector>

int findLowerBound(
    const std::vector<Log>& logs,
    long long targetKey
);

int findUpperBound(
    const std::vector<Log>& logs,
    long long targetKey
);

#endif