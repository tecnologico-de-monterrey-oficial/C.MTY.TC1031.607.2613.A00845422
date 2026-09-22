#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "Log.h"

#include <string>
#include <vector>

std::vector<Log> readLogs(const std::string& fileName);

#endif