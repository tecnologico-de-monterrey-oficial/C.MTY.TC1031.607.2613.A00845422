# pragma once
#include <string>

using namespace std;

struct Edge {
    string source;
    string target;
    int weight;
    Edge() : source(""), target(""), weight(0) {};
};