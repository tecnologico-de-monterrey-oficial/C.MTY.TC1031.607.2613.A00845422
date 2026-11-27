#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Log.h"

#include <string>
#include <vector>

std::vector<Log> readLogs(
    const std::string& fileName
);

void writeLogs(
    const std::string& fileName,
    const std::vector<Log>& logs
);

void appendRunResult(
    const std::string& fileName,
    const std::string& inputFile,
    int recordCount,
    const std::string& algorithm,
    long long elapsedTime,
    const std::string& prediction,
    const std::string& bestCase,
    const std::string& worstCase,
    bool predictionMatched
);

#endif