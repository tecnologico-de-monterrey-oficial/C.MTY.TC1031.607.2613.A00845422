#include <iostream>
using namespace std;
#include "Graph.H"

int main() {

    Graph graph;
    graph.addVertex("Ana");
    graph.addVertex("Beto");
    graph.addVertex("Carlos");
    graph.addEdge(Edge{"Ana", "Beto", 5});
    graph.addEdge(Edge{"Ana", "Carlos", 10});
    graph.print();
    graph.BFS("A");
    graph.BFS("Ana");

    
    return 0;
}