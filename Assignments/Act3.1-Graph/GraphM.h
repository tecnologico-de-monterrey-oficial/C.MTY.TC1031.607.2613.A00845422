#ifndef GraphM_h
#define GraphM_h

#include <iostream>
#include <string>
using namespace std;

// Dirigido y Ponderado
class GraphM {
private:
    int matrix[8][8];
    string vertices[8];
    int size;
    int findVertex(string vertex);
public:
    GraphM();
    void addVertex(string vertex);
    void addEdge(string source, string target, int weight);
    void print();
};

// constructor
GraphM::GraphM() {
    for (int i = 0; i < 8; i++) {
        vertices[i] = "";
        for (int j = 0; j < 8; j++) {
            matrix[i][j] = 0;
        }
    }
    size = 0;
}

// encuentra el vertice sy regresa la posición
int GraphM::findVertex(string vertex) {
    for (int i=0; i<size; i++) {
        if (vertices[i] == vertex) {
            return i;
        }
    }
    return -1;
}

// agrega un vertice al grafo
void GraphM::addVertex(string vertex) {
    // validamos que no este llena la matrix
    if (size < 8) {
        // si se pueden agregar vertices
        // agrega al arerglo de vertices el vértice nuevo
        vertices[size] = vertex;
        // incrementar size
        size++;
    } else {
        throw out_of_range("La matriz ya esta llena");
    }
}

// agrega una arista
void GraphM::addEdge(string source, string target, int weight) {
    // valido que los vertices existan
    int sourceIndex = findVertex(source);
    int targetIndex = findVertex(target);
    if (sourceIndex != -1 && targetIndex != -1) {
        matrix[sourceIndex][targetIndex] = weight;
    } else {
        throw invalid_argument("La fuente o el destino no existen");
    }

}
// imprime la matriz de adyacencia
void GraphM::print() {
    cout << "\t";
    for (int i = 0; i < size; i++) {
        cout << vertices[i] << "\t";
    }
    cout << endl;

    for (int i = 0; i < size; i++) {
        cout << vertices[i] << "\t";
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}






#endif /* GraphM_h */