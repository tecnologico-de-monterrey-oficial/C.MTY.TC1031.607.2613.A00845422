// Diego Martínez
// A00845422
#include <iostream>
using namespace std;


int factorial(int n) {
    if (n<=1) {
        return 1;
    }
    return n * factorial(n-1);
    
}


    int sumIterative (int n) { 
        int suma = 0;
        for (int i=1; i <= n; i++){
            suma += i;
        }
        return suma;
    }


    int sumRecursive (int n){
        if (n == 1) {
            return 1;
        }
        return n + sumRecursive(n-1);
    }   


    int sumFormula (int n) {
        return (n * (n+1)) / 2;
    }

    int fibonacciIterative (int n){
        if (n <= 1) {
            return n;
        }
        int a = 0, b = 1, c;
        for (int i = 2; i <= n; i++) {
            c = a + b;
            a = b;
            b = c;
        }
        return b;
    }

    
    int fibonacciRecursive (int n){
        if (n <= 2) {
            return 1;
        }
        return fibonacciRecursive(n-1) + fibonacciRecursive(n-2);
    }
    
    int bacteriasIterative (int n){
        int bacterias = 1;
        for ( int dia = 1; dia <= n; dia++){
            int nacimientos = bacterias * 3.78;
            int fallecimientos = bacterias * 2.34;

            bacterias = bacterias + nacimientos - fallecimientos;
        }
        return bacterias;


    }


    int bacteriasRecursive (int n){
        if (n == 0) {
            return 1;
        }
        int nacimientos = bacteriasRecursive(n - 1) * 3.78;
        int fallecimientos = bacteriasRecursive(n - 1) * 2.34;
        return bacteriasRecursive(n - 1) + nacimientos - fallecimientos;
    }
    
    
double investmentIterative(double amount, int months){
    for (int i = 1; i <= months; i++){
        amount += amount * 0.1875;
    }
    return amount;
}

double investmentRecursive(double amount, int months){
    if (months == 0){
        return amount;
    }
    return investmentRecursive(amount + amount * 0.1875, months - 1);
}

double powIterative(double base, int exponent){
    double result = 1;
    for (int i = 0; i < exponent; i++){
        result *= base;
    }
    return result;
}

double powRecursive(double base, int exponent){
    if (exponent == 0){
        return 1;
    }
    return base * powRecursive(base, exponent - 1);
}

int main() {

  cout << "El factorial de 5 es: " << factorial(5) << endl;
 // suma Iterativa
  cout << "La suma iterativa de 5 es: " << sumIterative(5) << endl;
 // suma Recursiva
  cout << "La suma recursiva de 5 es: " << sumRecursive(5) << endl;
 // suma con Formula
  cout << "La suma con formula de 5 es: " << sumFormula(5) << endl;
 // Fibonacci Iterativa
  cout << "El Fibonacci iterativo de 5 es: " << fibonacciIterative(5) << endl;
 // Fibonacci Recursiva
  cout << "El Fibonacci recursivo de 5 es: " << fibonacciRecursive(5) << endl;
 // Bacterias Iterativa
  cout << "El numero de bacterias iterativo de 5 días es: " << bacteriasIterative(5) << endl;
// Bacterias Recursiva
 cout << "El numero de bacterias recursivo de 5 días es: " << bacteriasRecursive(5) << endl;
// Inversion Iterativa
 cout << "El numero de inversion iterativo de 5 es: " << investmentIterative(1000, 5) << endl;
// Inversion Recursiva
 cout << "El numero de inversion recursivo de 5 es: " << investmentRecursive(1000, 5) << endl;
// Potencia Iterativa
 cout << "El numero de potencia iterativo de 5 es: " << powIterative(2, 5) << endl;
// Potencia Recursiva
 cout << "El numero de potencia recursivo de 5 es: " << powRecursive(2, 5) << endl;
    return 0;
}