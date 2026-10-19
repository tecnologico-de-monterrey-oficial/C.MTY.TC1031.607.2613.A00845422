# Evidencia 2: Procesamiento de logs con estructuras de datos lineales

Aplicación en C++ que permite cargar, validar, ordenar y consultar registros de eventos de red mediante estructuras de datos implementadas con templates y apuntadores.

## Organización del proyecto

- `data/`: archivos de entrada y archivos de prueba.
- `include/`: cabeceras y estructuras de datos.
- `src/`: implementación de la aplicación.
- `tests/`: programas de pruebas.
- `out/`: archivo generado con los registros ordenados.
- `docs/`: documento de evidencia.

## Requisitos

- Compilador g++ con soporte para C++20.
- Ejecutar los comandos desde la carpeta `Evidences/Evidence2`.

## Compilación y ejecución

En PowerShell:

```powershell
g++ -std=c++20 -Wall -Wextra -I include src/main.cpp src/Log.cpp src/FileManager.cpp src/SearchManager.cpp src/StatisticsManager.cpp -o evidence2.exe
if ($?) { .\evidence2.exe }
```

Para ejecutar nuevamente:

```powershell
.\evidence2.exe
```

## Archivos de entrada

Al iniciar, el programa permite seleccionar:

1. `data/log607-1.txt`
2. `data/log607-2.txt`
3. Otro archivo mediante su nombre o ruta.
0. Salir.

Las rutas relativas se interpretan desde la carpeta donde se ejecuta el programa. Si se escribe una ruta con espacios dentro de la aplicación, debe introducirse sin comillas.

Cada línea debe tener el siguiente formato:

```text
Mmm DD AAAA HH:MM:SS IP descripcion
```

Ejemplo:

```text
Sep 29 2024 14:37:38 10.14.19.188 Unauthorized Access Attempts
```

Los meses aceptados son:

```text
Jan Feb Mar Apr May Jun Jul Aug Sep Oct Nov Dec
```

Se valida el día según el mes y los años bisiestos, el año de cuatro dígitos entre 0001 y 9999, la hora, la dirección IPv4 y que la descripción no esté vacía.

El día admite uno o dos dígitos. Las líneas inválidas, incluidas las vacías, se reportan con su número y motivo y se omiten sin detener la carga.

## Estructuras utilizadas

| Estructura | Uso |
|---|---|
| Lista ligada simple | Base de la fila y de la pila. Mantiene apuntadores a head y tail. |
| Fila | Almacena temporalmente las líneas y sus números originales para procesarlas en orden FIFO. |
| Lista doblemente ligada | Almacena los registros válidos y permite ordenarlos directamente sobre sus nodos. |
| Pila | Guarda apuntadores a los registros encontrados para mostrarlos en orden inverso. |
| std::map | Cuenta frecuencias exclusivamente para las estadísticas. |

Los registros completos permanecen en la lista doblemente ligada. La pila utiliza apuntadores temporales a esos registros y no los elimina.

## Opciones del menú

### 1. Ordenar por fecha y hora

Solicita una predicción del crecimiento del número de comparaciones y ejecuta Merge Sort directamente sobre los nodos.

Muestra:

- Algoritmo y archivo utilizado.
- Cantidad de registros.
- Predicción.
- Tiempo en microsegundos.
- Comparaciones entre datos.
- Profundidad máxima de recursión.
- Verificación del orden.
- Coincidencia de la predicción con el crecimiento teórico O(n log n).

La evaluación de la predicción utiliza la complejidad teórica. Una sola corrida no demuestra una tasa de crecimiento.

El tiempo incluye la llamada a `sort()`, pero excluye la entrada del usuario, las verificaciones previa y posterior y la escritura del archivo. Las comparaciones contabilizadas son las realizadas entre datos durante las uniones.

La llamada inicial de Merge Sort cuenta como profundidad 1. Para listas vacías o de un elemento, `sort()` no realiza recursión y reporta profundidad 0.

El ordenamiento es estable: los registros con la misma fecha y hora conservan su orden de llegada.

Si la lista ya está ordenada, el programa lo informa y evita repetir Merge Sort.

### 2. Buscar logs por día

Requiere completar primero la opción 1.

Formato de consulta:

```text
Sep 29 2024
```

Muestra los registros del día en orden ascendente y el total encontrado. El recorrido se detiene al pasar del día solicitado.

### 3. Mostrar logs por día en orden descendente

Utiliza el último día consultado. Si no existe una búsqueda previa, solicita la fecha.

Los registros encontrados se apilan y después se desapilan para mostrarlos de más reciente a más antiguo. Los empates también se muestran en orden inverso al listado ascendente.

### 4. Estadísticas del archivo

Puede utilizarse antes o después de ordenar.

Muestra:

- Total de registros.
- Día o días con más incidentes.
- Tipo o tipos de evento más frecuentes.
- Dirección o direcciones IP más frecuentes.
- Número de apariciones de cada máximo.

Se muestran todos los elementos empatados en la frecuencia máxima.

### 5. Salir

Termina el programa. Los destructores de las estructuras liberan sus nodos.

## Archivo de salida

La opción 1 genera:

```text
out/output608.out
```

Conserva el formato de los registros de entrada y contiene los datos ordenados cronológicamente. Cada exportación reemplaza su contenido anterior.

Los archivos de entrada conservan sus nombres `log607`, mientras que la salida utiliza `output608.out`, como solicita la evidencia.

## Pruebas

### Estructuras base

```powershell
g++ -std=c++20 -Wall -Wextra -I include tests/structures_test.cpp -o tests/structures_test.exe
if ($?) { .\tests\structures_test.exe }
```

Comprueba estructuras vacías, un elemento, operaciones en los extremos, FIFO, LIFO y recorridos de la lista doble en ambas direcciones. Los resultados se comparan visualmente con las salidas esperadas.

### Ordenamiento

```powershell
g++ -std=c++20 -Wall -Wextra -I include tests/sort_test.cpp -o tests/sort_test.exe
if ($?) { .\tests\sort_test.exe }
```

Comprueba el orden, la conservación de valores, los enlaces y la estabilidad ante claves iguales.

### Estadísticas

```powershell
g++ -std=c++20 -Wall -Wextra -I include tests/statistics_test.cpp src/Log.cpp src/StatisticsManager.cpp -o tests/statistics_test.exe
if ($?) { .\tests\statistics_test.exe }
```

Comprueba listas vacías, un registro, conteos conocidos, empates y que las frecuencias no cambien después de ordenar.

### Archivos de prueba manual

- `data/prueba_validacion.txt`: contiene un registro válido y tres líneas inválidas. Se espera un registro cargado y tres omitidos.
- `data/prueba_final.txt`: contiene cinco registros, incluidos dos con la misma fecha y hora y descripciones diferentes, para comprobar el orden de llegada después de ordenar.

También se probaron búsquedas por día, resultados descendentes, fechas inválidas, días sin registros, archivos inexistentes, búsqueda antes de ordenar y ordenamiento de una lista ya ordenada.


## Documento de evidencia

El documento se encuentra en:

```text
docs/Evidencia2.pdf
```

## Video explicativo

El enlace al video se encontrará dentro de la siguiente carpeta compartida:

https://tecmx-my.sharepoint.com/:f:/g/personal/a00845422_tec_mx/IgBoEUx25uqHRaIWWyuKGy2sAfhgErQQBJWq-dtID0D_OXk?e=EtKDa7