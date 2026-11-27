#ifndef EVIDENCE3_FILE_MANAGER_H
#define EVIDENCE3_FILE_MANAGER_H

#include <cstddef>
#include <string>
#include <vector>

#include "BST.h"
#include "Log.h"

struct InvalidRecord {
    std::size_t position;
    std::size_t line;
    std::string reason;
};

struct LoadResult {
    std::size_t read = 0;
    std::size_t loaded = 0;
    std::vector<InvalidRecord> omitted;
};

// Carga los registros válidos y llena el BST de frecuencias.
LoadResult readLogs(
    const std::string& fileName,
    std::vector<Log>& logs,
    BST<std::uint32_t>& ips
);

#endif