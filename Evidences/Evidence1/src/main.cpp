#include <iostream>
#include "FileManager.h"
using namespace std;

int main() {

    try {
    std::vector<Log> testLogs =
       readLogs("../data/log607-1.txt");

    std::cout
        << "Registros leidos: "
        << testLogs.size()
        << '\n';
}
catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
}


    return 0;
}