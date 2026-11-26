#include <iostream>
#include "GraphM.h"
using namespace std;

// Como GraphM es dirigido, para un grafo no dirigido
// agregamos la arista en ambos sentidos
void addUndirectedEdge(GraphM &graph, string a, string b, int weight) {
    graph.addEdge(a, b, weight);
    graph.addEdge(b, a, weight);
}

int main() {
    GraphM graph;

    // Vertices
    graph.addVertex("Aeropuerto");
    graph.addVertex("Valle");
    graph.addVertex("Centro");
    graph.addVertex("Tec");
    graph.addVertex("Cumbres");
    graph.addVertex("San Pedro");
    graph.addVertex("Escobedo");
    graph.addVertex("Fundidora");

    // Aristas
    addUndirectedEdge(graph, "Aeropuerto", "Centro", 32);
    addUndirectedEdge(graph, "Aeropuerto", "Fundidora", 25);
    addUndirectedEdge(graph, "Aeropuerto", "Escobedo", 30);
    addUndirectedEdge(graph, "Valle", "Centro", 17);
    addUndirectedEdge(graph, "Valle", "Tec", 14);
    addUndirectedEdge(graph, "Valle", "San Pedro", 6);
    addUndirectedEdge(graph, "Centro", "Tec", 38);
    addUndirectedEdge(graph, "Centro", "Fundidora", 10);
    addUndirectedEdge(graph, "Centro", "Escobedo", 25);
    addUndirectedEdge(graph, "Centro", "Cumbres", 22);
    addUndirectedEdge(graph, "Cumbres", "Escobedo", 20);
    addUndirectedEdge(graph, "Cumbres", "San Pedro", 25);
    addUndirectedEdge(graph, "Tec", "Fundidora", 15);

    graph.print();

    return 0;
}