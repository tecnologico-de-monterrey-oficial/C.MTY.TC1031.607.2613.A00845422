#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "FileManager.h"
#include "Heap.h"
#include "HeapSort.h"

namespace {

bool readChoice(int min, int max, int& option) {
    std::string line;

    while (std::getline(std::cin, line)) {
        std::istringstream input(line);
        char extra;

        if ((input >> option) && !(input >> extra) &&
            option >= min && option <= max) {
            return true;
        }

        std::cout << "Entrada invalida. Ingresa un numero del "
                  << min << " al " << max << ": ";
    }

    return false;
}

void writeLogs(const std::string& fileName, const std::vector<Log>& logs) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("No se pudo crear el archivo: " + fileName);
    }

    for (const Log& record : logs) {
        file << record.toString() << '\n';
    }

    file.close();
    if (file.fail()) {
        throw std::runtime_error("Ocurrio un error al escribir: " + fileName);
    }
}

template <typename Compare>
void runSort(
    const std::vector<Log>& logs,
    Compare compare,
    const std::string& fileName
) {
    const std::string predictions[] = {
        "Aproximadamente igual",
        "Aproximadamente el doble",
        "Un poco mas del doble",
        "Aproximadamente cuatro veces"
    };

    std::cout << "\nSi el archivo tuviera el doble de registros,\n"
              << "como cambiarian las comparaciones?\n";

    for (int i = 0; i < 4; ++i) {
        std::cout << i + 1 << ". " << predictions[i] << '\n';
    }

    std::cout << "Tu prediccion: ";
    int prediction = 0;
    if (!readChoice(1, 4, prediction)) {
        return;
    }

    // Medimos el ordenamiento con los registros originales.
    const auto start = std::chrono::steady_clock::now();
    const auto result = heapSort(logs, compare);
    const auto end = std::chrono::steady_clock::now();
    const std::chrono::duration<double, std::milli> elapsed = end - start;

    std::filesystem::create_directories("out");
    writeLogs(fileName, result.values);

    std::cout << "\n========== RESULTADO DEL ORDENAMIENTO ==========\n"
              << "Archivo generado: " << fileName << '\n'
              << "Registros ordenados: " << result.values.size() << '\n'
              << "Tiempo de ordenamiento: " << elapsed.count() << " ms\n"
              << "Comparaciones: " << result.comparisons << '\n'
              << "Altura del heap lleno: " << result.height << '\n'
              << "Prediccion: " << predictions[prediction - 1] << '\n';

    if (result.comparisons == 0) {
        std::cout << "La corrida base no hizo comparaciones. "
                  << "No se puede calcular el factor de crecimiento.\n";
        return;
    }

    // Repetimos la bitácora en el mismo orden para obtener el doble de registros.
    std::vector<Log> doubled = logs;
    doubled.insert(doubled.end(), logs.begin(), logs.end());

    const auto experiment = heapSort(doubled, compare);
    const double ratio = static_cast<double>(experiment.comparisons)
                       / result.comparisons;

    // Clasificamos el factor medido con los cortes 1.50, 2.02 y 3.00.
    int observed = 4;
    if (ratio < 1.50) {
        observed = 1;
    } else if (ratio <= 2.02) {
        observed = 2;
    } else if (ratio < 3.00) {
        observed = 3;
    }

    std::cout << "Comparaciones con el doble: " << experiment.comparisons << '\n'
              << "Factor observado: " << ratio << "x\n"
              << "Resultado observado: " << predictions[observed - 1] << '\n'
              << "Coincidio con la prediccion: "
              << (prediction == observed ? "Si" : "No") << '\n';
}

struct IpFrequency {
    std::uint32_t ipKey;
    std::size_t count;
};

struct CompareIpFrequency {
    bool operator()(const IpFrequency& a, const IpFrequency& b) const {
        if (a.count != b.count) {
            return a.count > b.count;
        }

        return a.ipKey < b.ipKey;
    }
};

// Recuperamos los cuatro octetos de la llave numérica.
std::string formatIP(std::uint32_t ipKey) {
    return std::to_string((ipKey >> 24) & 255u) + "." +
           std::to_string((ipKey >> 16) & 255u) + "." +
           std::to_string((ipKey >> 8) & 255u) + "." +
           std::to_string(ipKey & 255u);
}

void showTopIPs(const BST<std::uint32_t>& ips) {
    Heap<IpFrequency, CompareIpFrequency> heap(CompareIpFrequency{});

    // Cada nodo del BST aporta una IP con su conteo acumulado.
    ips.inOrder([&heap](std::uint32_t ipKey, std::size_t count) {
        heap.push({ipKey, count});
    });

    std::cout << "\n========== TOP 10 DE IPs ==========\n";

    if (heap.empty()) {
        std::cout << "No hay IPs registradas.\n";
        return;
    }

    std::cout << "Lugar\tIP\t\tRegistros\n";
    std::size_t cutoffCount = 0;

    for (int place = 1; place <= 10 && !heap.empty(); ++place) {
        const IpFrequency entry = heap.pop();
        cutoffCount = entry.count;

        std::cout << place << '\t' << formatIP(entry.ipKey)
                  << "\t\t" << entry.count << '\n';
    }

    // Las IPs empatadas en el corte quedan al frente del Heap.
    std::size_t tiedOutside = 0;
    while (!heap.empty() && heap.top().count == cutoffCount) {
        heap.pop();
        ++tiedOutside;
    }

    if (tiedOutside == 1) {
        std::cout << "Hay 1 IP mas con " << cutoffCount
                  << " registros fuera del top 10.\n";
    } else if (tiedOutside > 1) {
        std::cout << "Hay " << tiedOutside << " IPs mas con " << cutoffCount
                  << " registros fuera del top 10.\n";
    }
}

void searchIP(const BST<std::uint32_t>& ips) {
    std::cout << "\nIngresa la direccion IPv4: ";
    std::string ip;

    if (!std::getline(std::cin, ip)) {
        return;
    }

    std::uint32_t ipKey = 0;
    if (!Log::parseIP(ip, ipKey)) {
        std::cout << "Direccion IPv4 invalida. Ejemplo: 10.14.9.200\n";
        return;
    }

    const auto result = ips.search(ipKey);

    if (result.count == 0) {
        std::cout << "No hay registros para " << ip << ".\n";
    } else {
        std::cout << ip << " aparece " << result.count << " veces.\n";
    }

    const int height = ips.height();
    const std::size_t distinctIPs = ips.size();

    std::cout << "Comparaciones de busqueda: " << result.comparisons << '\n'
              << "IPs distintas: " << distinctIPs << '\n'
              << "Altura del BST: " << height << '\n';

    if (distinctIPs == 0) {
        std::cout << "ceil(log2(n)) no se define para un BST vacio.\n";
        return;
    }

    // La cantidad de bits de n - 1 equivale a ceil(log2(n)).
    int reference = 0;
    for (std::size_t value = distinctIPs - 1; value > 0; value /= 2) {
        ++reference;
    }

    std::cout << "ceil(log2(n)): " << reference << '\n'
              << "Diferencia (altura - referencia): "
              << height - reference << '\n';
}

void showMenu(const std::vector<Log>& logs, const BST<std::uint32_t>& ips) {
    while (true) {
        std::cout << "\n========== EVIDENCIA 3 ==========\n"
                  << "1. Ordenar de mayor a menor (MaxHeap)\n"
                  << "2. Ordenar de menor a mayor (MinHeap)\n"
                  << "3. Mostrar las 10 IPs con mas registros\n"
                    << "4. Buscar una IP en el BST\n"
                  << "5. Salir\n"
                    << "Selecciona una opcion: ";

        int option = 0;
                if (!readChoice(1, 5, option) || option == 5) {
            return;
        }
    
        try {
            switch (option) {
                case 1:
                    runSort(logs, std::greater<Log>{}, "out/output608-1.out");
                    break;

                case 2:
                    runSort(logs, std::less<Log>{}, "out/output608-2.out");
                    break;

                case 3:
                    showTopIPs(ips);
                    break;
            
                case 4:
                    searchIP(ips);
                    break;
            }

        } catch (const std::runtime_error& error) {
            std::cerr << error.what() << '\n';
        }
    }
}

} // namespace

int main(int argc, char* argv[]) {
    const std::string fileName = argc > 1 ? argv[1] : "data/log608-3.json";
    std::vector<Log> logs;
    BST<std::uint32_t> ips;

    try {
        const LoadResult result = readLogs(fileName, logs, ips);

        std::cout << "========== REPORTE DE LECTURA ==========\n"
                  << "Archivo: " << fileName << '\n'
                  << "Registros leidos: " << result.read << '\n'
                  << "Registros validos: " << result.loaded << '\n'
                  << "Registros invalidos: " << result.omitted.size() << '\n'
                  << "IPs distintas: " << ips.size() << '\n';

        for (const InvalidRecord& record : result.omitted) {
            std::cout << "Registro " << record.position
                      << " (linea " << record.line << ") omitido: "
                      << record.reason << '\n';
        }

        showMenu(logs, ips);
    } catch (const std::runtime_error& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }

    return 0;
}