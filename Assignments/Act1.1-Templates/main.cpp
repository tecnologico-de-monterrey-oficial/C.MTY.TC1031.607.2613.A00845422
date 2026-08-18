#include <iostream>
#include <string>
#include "List.h"

using namespace std;

int main() {

    cout << "--- LISTA DE ENTEROS ---" << endl;

    List<int> list;

    cout << "\nInsert:" << endl;
    list.insert(5);
    list.insert(10);
    list.insert(3);
    list.print();

    cout << "\ngetData(1): " << list.getData(1) << endl;

    cout << "getSize(): " << list.getSize() << endl;

    cout << "getMax(): " << list.getMax() << endl;


    cout << "\ninsertAt(1, 7):" << endl;
    list.insertAt(1, 7);
    list.print();

    cout << "\nremoveAt(2):" << endl;
    list.removeAt(2);
    list.print();

    cout << "\nremoveLast:" << endl;
    list.removeLast();
    list.print();


    cout << "\n--- PRUEBA DE POSICION INVALIDA ---" << endl;

    list.insertAt(20, 100);
    list.removeAt(20);


    cout << "\n--- LISTA DE STRINGS ---" << endl;

    List<string> stringList;

    stringList.insert("Hello");
    stringList.insert("World");
    stringList.insert("Templates");

    stringList.print();

    cout << "\ngetData(1): " << stringList.getData(1) << endl;

    cout << "getSize(): " << stringList.getSize() << endl;


    cout << "\n--- REMOVE LAST EN LISTA VACIA ---" << endl;

    List<int> emptyList;
    emptyList.removeLast();

    cout << "\n--- REMOVE AT EN LISTA VACIA ---" << endl;

    emptyList.removeAt(0);

    return 0;
}