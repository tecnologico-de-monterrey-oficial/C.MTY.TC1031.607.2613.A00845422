# Evidencia 1 — Ordenamiento y búsqueda de registros

## Autor

* Diego Javier Martínez Sánchez
* A00845422
* TC1031 — Estructuras de Datos y Algoritmos

## Descripción

Esta aplicación procesa archivos de logs, ordena sus registros cronológicamente y permite buscar registros dentro de un rango inclusivo de fechas y horas.

Cada registro contiene:
Mes Día Año Hora DirecciónIP Mensaje

Ejemplo:
Sep 08 2024 00:22:43 10.14.168.155 Unencrypted communication

La aplicación permite elegir entre un archivo desordenado y otro casi ordenado para comparar el comportamiento de distintos algoritmos.

## Algoritmos implementados

1. Swap Sort
2. Bubble Sort
3. Selection Sort
4. Insertion Sort
5. Merge Sort
6. Quick Sort
7. Shell Sort

Bubble Sort utiliza una parada anticipada cuando una pasada no realiza intercambios, lo que le permite aprovechar datos ordenados o casi ordenados.

## Estructura del proyecto

Evidence1/
├── data/
│   ├── log607-1.txt
│   └── log607-2.txt
├── src/
│   ├── main.cpp
│   ├── Log.h
│   ├── Log.cpp
│   ├── FileManager.h
│   ├── FileManager.cpp
│   ├── SearchManager.h
│   └── SearchManager.cpp
├── out/
│   ├── output607.txt
│   ├── range607.txt
│   └── results607.txt
├── docs/
│   ├── EvidenciasPruebas.pdf
│   └── ReflexEvidencia1.pdf
└── README.md

## Compilación

Desde la carpeta `Evidence1/src`, ejecutar:

```powershell
g++ -std=c++20 main.cpp Log.cpp FileManager.cpp SearchManager.cpp -o main.exe
```

Después ejecutar:

```powershell
.\main.exe
```

También se puede compilar y ejecutar con una sola instrucción:

```powershell
g++ -std=c++20 main.cpp Log.cpp FileManager.cpp SearchManager.cpp -o main.exe; if ($?) { .\main.exe }
```

## Uso

En cada corrida, el programa solicita:

1. Archivo de entrada.
2. Algoritmo de ordenamiento.
3. Predicción sobre su desempeño.
4. Evaluación de la predicción después de conocer el tiempo.
5. Fecha y hora inicial del rango.
6. Fecha y hora final del rango.
7. Confirmación para realizar otra corrida.

El formato para ingresar fechas es:
Mon DD YYYY HH:MM:SS


Ejemplo:
Oct 02 2024 23:04:24

Los meses deben escribirse con sus abreviaturas en inglés:
Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec

## Archivos generados

* `output607.txt`: registros ordenados de la corrida más reciente.
* `range607.txt`: registros encontrados en el último rango consultado.
* `results607.txt`: historial de algoritmos, archivos, tiempos, predicciones y complejidades.

## Búsqueda por rango

El programa utiliza dos búsquedas binarias:

* Límite inferior: primera posición cuya fecha-hora sea mayor o igual al inicio.
* Límite superior: primera posición cuya fecha-hora sea estrictamente mayor al final.

El rango es inclusivo. Si uno de los límites coincide con varios registros que tienen el mismo timestamp, todos se incluyen exactamente una vez.

Cada búsqueda tiene complejidad temporal `O(log n)`. La impresión y exportación del rango tiene complejidad `O(k)`, donde `k` es la cantidad de resultados encontrados.

## Validaciones

La aplicación valida:

* Opciones numéricas fuera de rango.
* Meses inexistentes.
* Días inválidos para cada mes.
* Años bisiestos.
* Horas, minutos y segundos fuera de rango.
* Formato incorrecto de fecha y hora.
* Fecha inicial posterior a la fecha final.
* Errores al abrir o escribir archivos.
* Rangos sin resultados.

## Uso de inteligencia artificial

La inteligencia artificial se utilizó de manera incremental para revisar funciones específicas, explicar errores de compilación y enlazado, verificar la construcción de la llave cronológica y analizar la búsqueda binaria.

Cada modificación fue incorporada y probada por separado mediante commits. No se utilizó un asistente para generar y entregar el proyecto completo en una sola ejecución.

Un caso concreto de revisión crítica fue Bubble Sort. La primera versión sugerida siempre ejecutaba todas las pasadas, por lo que su mejor caso permanecía en `O(n²)` y no aprovechaba el archivo casi ordenado. Después de identificar esta ineficiencia, se agregó una variable booleana que detiene el algoritmo cuando una pasada no realiza intercambios. Con esto, su mejor caso pasó a `O(n)`.

## Video explicativo

Enlace al video:

```
https://tecmx-my.sharepoint.com/:f:/g/personal/a00845422_tec_mx/IgBoEUx25uqHRaIWWyuKGy2sAfhgErQQBJWq-dtID0D_OXk?e=TilHYh
```

El video muestra dos combinaciones de algoritmo y archivo, la búsqueda binaria, el tratamiento de timestamps duplicados y la explicación de las decisiones principales.
