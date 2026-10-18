#include "FileManager.h"
#include "Queue.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

// estas funciones y tipos auxiliares se usan en este archivo
namespace {

// conserva el texto y su posición original dentro del archivo
struct PendingLine {
    int number = 0;
    std::string text;
};

// valida que un texto contenga únicamente dígitos
bool containsOnlyDigits(const std::string& text) {
    if (text.empty()) {
        return false;
    }

    for (char character : text) {
        if (character < '0' || character > '9') {
            return false;
        }
    }

    return true;
}

// convierte una línea del archivo en un registro
Log parseLog(const std::string& line) {
    // rechazamos líneas vacías o formadas únicamente por espacios
    if (line.find_first_not_of(" \t\r\n") == std::string::npos) {
        throw std::invalid_argument("Linea vacia");
    }

    std::istringstream input(line);

    std::string month;
    std::string dayText;
    std::string yearText;
    std::string time;
    std::string ip;
    std::string message;

    // leemos los campos iniciales como textos independientes
    if (!(input >> month >> dayText >> yearText >> time >> ip)) {
        throw std::invalid_argument(
            "Faltan campos. Se espera: "
            "Mmm DD AAAA HH:MM:SS IP descripcion"
        );
    }

    // validamos antes de convertir para evitar números incompletos
    if (!containsOnlyDigits(dayText) || dayText.size() > 2) {
        throw std::invalid_argument(
            "Formato de dia invalido: " + dayText
        );
    }

    if (!containsOnlyDigits(yearText) || yearText.size() != 4) {
        throw std::invalid_argument(
            "El anio debe contener cuatro digitos"
        );
    }

    int day = std::stoi(dayText);
    int year = std::stoi(yearText);

    // el resto de la línea corresponde a la descripción
    std::getline(input >> std::ws, message);

    // eliminamos el retorno de carro si el archivo lo conserva
    if (!message.empty() && message.back() == '\r') {
        message.pop_back();
    }

    // el constructor valida fecha, hora, IP y descripción
    return Log(year, month, day, time, ip, message);
}

} // namespace

// lee mediante una fila y carga los registros en la lista doble
LoadResult readLogs(
    const std::string& fileName,
    DoublyLinkedList<Log>& logs
) {
    std::ifstream file(fileName);

    // verificamos el archivo antes de modificar la lista
    if (!file.is_open()) {
        throw std::runtime_error(
            "No se pudo abrir el archivo: " + fileName
        );
    }

    Queue<PendingLine> pending;
    std::string line;
    int lineNumber = 0;

    // primera etapa: encolamos cada línea en orden de llegada
    while (std::getline(file, line)) {
        lineNumber++;

        PendingLine current;
        current.number = lineNumber;
        current.text = line;

        pending.enqueue(current);
    }

    // distinguimos el final normal del archivo de un error de lectura
    if (file.bad() || (file.fail() && !file.eof())) {
        throw std::runtime_error(
            "Ocurrio un error al leer el archivo: " + fileName
        );
    }

    // eliminamos registros anteriores antes de cargar los nuevos
    logs.clear();

    LoadResult result;

    // segunda etapa: procesamos las líneas en orden FIFO
    while (!pending.isEmpty()) {
        PendingLine current = pending.dequeue();

        // guardamos temporalmente el registro que se validará
        Log record;

        try {
            record = parseLog(current.text);
        }
        catch (const std::invalid_argument& error) {
            // reportamos la línea inválida sin detener la carga
            result.omitted++;

            std::cerr << "Linea " << current.number
                      << " omitida: " << error.what() << '\n';

            continue;
        }

        // agregamos al final para conservar el orden de llegada
        // esta operación se realiza fuera del manejo de errores de formato
        logs.addLast(record);
        result.loaded++;
    }

    return result;
}

// escribe los registros recorriendo directamente los nodos
void writeLogs(
    const std::string& fileName,
    const DoublyLinkedList<Log>& logs
) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error(
            "No se pudo crear el archivo: " + fileName
        );
    }

    // comenzamos en el primer nodo de la lista
    const NodeD<Log>* aux = logs.getHead();

    while (aux != nullptr) {
        file << aux->data.toString() << '\n';

        // avanzamos al siguiente registro
        aux = aux->next;
    }

    // cerramos y comprobamos posibles errores de escritura
    file.close();

    if (file.fail()) {
        throw std::runtime_error(
            "Ocurrio un error al escribir el archivo: " + fileName
        );
    }
}