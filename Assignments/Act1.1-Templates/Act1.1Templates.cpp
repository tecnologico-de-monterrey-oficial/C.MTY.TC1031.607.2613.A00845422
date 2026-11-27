#include <iostream>
using namespace std;

int sum(int a, int b) {
    return a + b;
}

double sum(double a, double b) {
    return a + b;
}

string sum(string a, string b) {
    return a + b;
}

template <typename T>
T sum(T a, T b) {
    return a + b;
}

int main() {

    string a = "Hello ";
    string b = "World!";
    cout << sum(a, b) << endl;

    int x = 5;
    int y = 10;
    cout << sum(x, y) << endl;

    double m = 5.5;
    double n = 10.5;
    cout << sum(m, n) << endl;

    return 0;
}