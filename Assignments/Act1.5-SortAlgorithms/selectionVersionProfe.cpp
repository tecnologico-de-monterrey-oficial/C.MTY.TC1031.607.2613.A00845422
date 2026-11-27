#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void selectionSort(vector<T> &list) {
    int n = list.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (list[j] < list[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            T temp = list[i];
            list[i] = list[minIndex];
            list[minIndex] = temp;
        }
    }
}





int main() {

    


    return 0;
}