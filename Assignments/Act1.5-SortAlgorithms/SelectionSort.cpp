#include <iostream>
using namespace std;

template <typename T>
void SelectionSort(T list[], int n) {
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

template <typename T>
void InsertionSort(T list[], int n) {
    for (int i = 1; i < n; i++) {
        T key = list[i];
        int j = i - 1;
        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j--;
        }
        list [j + 1] = key;
    }
}

int main() {

    int list[] = {15, 7, 3, 9, 12, 5, 2};

    SelectionSort(list, 7);
    InsertionSort(list, 7);

    cout <<  "Lista ordenada (Selection Sort): ";
    for (int i = 0; i < 7; i++) {
        cout << list[i] << " ";
    }

    cout << endl;

    cout <<  "Lista ordenada (Insertion Sort): ";
    for (int i = 0; i < 7; i++) {
        cout << list[i] << " ";
    }
    cout << endl;


    return 0;
}