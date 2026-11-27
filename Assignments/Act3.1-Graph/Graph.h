//A00844802
//Jared Aldana Palacios
#if !defined(Graph_H)
#define Graph_H

#include "Edge.H"
#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class Graph {
    private:
        vector<string> vertices;
        vector<vector <Edge>> adjList;
        int findVertex(string vertex);
    public:
        void addVertex(string vertex);
        void addEdge(Edge edge);
        void print();
        void BFS(string startVertex);
};

void Graph::addVertex(string vertex){
    vertices.push_back(vertex);
    adjList.push_back(vector<Edge>());
}

void Graph::addEdge(Edge edge){
    int sourceIndex = findVertex(edge.source);
    if(sourceIndex == -1){
        return; 
    }
    adjList[sourceIndex].push_back(edge);
}

int Graph::findVertex(string vertex){
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i] == vertex){
            return i;
        }
    }
    return -1;
}

void Graph::print(){
    for(int i =0; i < vertices.size(); i++){
        cout << vertices[i] << ": ";
        for(int j = 0; j < adjList[i].size(); j++){
            cout << "(" << adjList[i][j].target << ", " << adjList[i][j].weight << ") ";
        }
        cout << endl;
    }
}

void Graph::BFS(string startVertex) {
    int startIndex = findVertex(startVertex);
    if (startIndex == -1) {
        cout << "El vértice de inicio no existe en el grafo." << endl;
        return;
    }

    vector<bool> visited(vertices.size(), false);
    queue<int> q;

    visited[startIndex] = true;
    q.push(startIndex);

    while (!q.empty()) {
        int currentIndex = q.front();
        q.pop();
        cout << vertices[currentIndex] << " ";

        for (const Edge& edge : adjList[currentIndex]) {
            int neighborIndex = findVertex(edge.target);
            if (neighborIndex != -1 && !visited[neighborIndex]) {
                visited[neighborIndex] = true;
                q.push(neighborIndex);
            }
        }
    }
    cout << endl;
}

#endif // Graph_H   