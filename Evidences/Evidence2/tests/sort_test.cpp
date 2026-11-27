#include <iostream>
#include <stdexcept>
#include "DoublyLinkedList.h"

using namespace std;

// permite comprobar el orden de llegada cuando hay empates
struct TestRecord {
    int key;
    char arrival;

    // ordenamos únicamente por la clave
    bool operator<(const TestRecord& other) const {
        return key < other.key;
    }
};

// permite imprimir los registros de prueba
ostream& operator<<(ostream& output, const TestRecord& record) {
    output << record.key << record.arrival;
    return output;
}

// comprueba una condición y detiene la prueba si falla
void check(bool condition, const char* message) {
    if (!condition) {
        throw runtime_error(message);
    }
}

// comprueba los enlaces y el número de nodos en ambas direcciones
template <typename T>
void checkLinks(const DoublyLinkedList<T>& list) {
    const NodeD<T>* previous = nullptr;
    const NodeD<T>* current = list.getHead();
    int count = 0;

    while (current != nullptr) {
        // limitamos el recorrido para detectar un posible ciclo
        check(count < list.getSize(), "Ciclo en recorrido hacia adelante");
        check(current->prev == previous, "Enlace prev incorrecto");

        previous = current;
        current = current->next;
        count++;
    }

    check(count == list.getSize(), "Cantidad de nodos incorrecta");
    check(previous == list.getTail(), "Tail incorrecto");

    const NodeD<T>* next = nullptr;
    current = list.getTail();
    count = 0;

    while (current != nullptr) {
        check(count < list.getSize(), "Ciclo en recorrido hacia atras");
        check(current->next == next, "Enlace next incorrecto");

        next = current;
        current = current->prev;
        count++;
    }

    check(count == list.getSize(), "Cantidad inversa incorrecta");
    check(next == list.getHead(), "Head incorrecto");
}

int main() {
    try {
        cout << "========== PRUEBA DE MERGE SORT ==========\n";

        // caso 1: lista vacía
        DoublyLinkedList<int> empty;
        SortStats emptyStats = empty.sort();

        check(empty.isSorted(), "Fallo en lista vacia");
        checkLinks(empty);

        cout << "\nLista vacia: ";
        empty.print();
        cout << "Comparaciones: " << emptyStats.comparisons << '\n';
        cout << "Profundidad: " << emptyStats.maxDepth << '\n';

        // caso 2: un solo elemento
        DoublyLinkedList<int> single;
        single.addLast(10);
        single.sort();

        check(single.isSorted(), "Fallo con un elemento");
        checkLinks(single);

        cout << "\nUn elemento: ";
        single.print();

        // caso 3: lista desordenada con valores repetidos
        DoublyLinkedList<int> list;
        list.addLast(40);
        list.addLast(10);
        list.addLast(30);
        list.addLast(20);
        list.addLast(10);

        cout << "\nAntes de ordenar: ";
        list.print();

        SortStats stats = list.sort();

        check(list.isSorted(), "Los datos no quedaron ordenados");
        checkLinks(list);

        // comprobamos también que se conservaron los valores
        int expected[] = {10, 10, 20, 30, 40};
        const NodeD<int>* current = list.getHead();

        for (int value : expected) {
            check(current != nullptr, "Faltan nodos");
            check(current->data == value, "Valor inesperado");
            current = current->next;
        }

        check(current == nullptr, "Sobran nodos");

        cout << "Orden ascendente: ";
        list.print();

        cout << "Orden descendente: ";
        list.printReverse();

        cout << "Comparaciones: " << stats.comparisons << '\n';
        cout << "Profundidad maxima: " << stats.maxDepth << '\n';

        // comprobamos una segunda llamada sobre datos ya ordenados
        list.sort();
        check(list.isSorted(), "Fallo al ordenar nuevamente");
        checkLinks(list);

        // caso 4: estabilidad ante claves iguales
        DoublyLinkedList<TestRecord> records;
        records.addLast(TestRecord{2, 'A'});
        records.addLast(TestRecord{1, 'B'});
        records.addLast(TestRecord{2, 'C'});
        records.addLast(TestRecord{1, 'D'});
        records.addLast(TestRecord{2, 'E'});

        cout << "\nAntes de ordenar los empates: ";
        records.print();

        records.sort();

        check(records.isSorted(), "Fallo al ordenar los registros");
        checkLinks(records);

        cout << "Esperado: [1B <-> 1D <-> 2A <-> 2C <-> 2E]\n";
        cout << "Obtenido: ";
        records.print();

        // las letras identifican el orden original de llegada
        const char expectedArrival[] = {'B', 'D', 'A', 'C', 'E'};
        const NodeD<TestRecord>* record = records.getHead();

        for (char arrival : expectedArrival) {
            check(record != nullptr, "Faltan registros");
            check(
                record->data.arrival == arrival,
                "No se conservo el orden de llegada"
            );

            record = record->next;
        }

        check(record == nullptr, "Sobran registros");

        cout << "\nTodas las pruebas pasaron correctamente.\n";
    }
    catch (const exception& error) {
        cerr << "\nPrueba fallida: " << error.what() << '\n';
        return 1;
    }

    return 0;
}