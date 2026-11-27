#include <iostream>
#include <vector>
using namespace std;
#include "Heap.h"

int main() {

    vector<int> list{30, 50, 20, 90, 40, 80, 70};
    Heap<int> heap(list);

    heap.print();
    heap.printTree(0, 0);
    cout << heap.pop() << endl;

    return 0;
}