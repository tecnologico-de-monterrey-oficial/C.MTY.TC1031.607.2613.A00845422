# Actividad 2.1 - Listas Encadenadas

## Descripción

Este programa implementa una estructura de datos lineal de tipo lista encadenada utilizando templates en C++. La lista puede trabajar con datos de tipo `int` y `string`.

El programa permite crear listas con datos capturados por el usuario o con datos aleatorios. Posteriormente, se muestra un menú para realizar diferentes operaciones sobre la lista.

## Archivos del proyecto

- `Node.h`: contiene la estructura de cada nodo de la lista.
- `LinkedList.h`: contiene la clase template `LinkedList` y la implementación de sus métodos.
- `main.cpp`: contiene el menú principal y las funciones para interactuar con el usuario.
- `tests.pdf`: contiene las evidencias de las pruebas realizadas a cada opción del programa.

## Funciones implementadas

- Agregar un elemento al principio de la lista.
- Agregar un elemento al final de la lista.
- Insertar un elemento después de un índice dado.
- Borrar un elemento por su valor.
- Borrar un elemento por su posición.
- Obtener un elemento por su posición.
- Actualizar un elemento por su valor.
- Actualizar un elemento por su posición.
- Buscar un elemento y obtener su posición.
- Obtener y actualizar elementos mediante la sobrecarga del operador `[]`.
- Duplicar una lista mediante la sobrecarga del operador `=`.
- Liberar correctamente la memoria utilizada por los nodos mediante el destructor.

## Compilación y ejecución

Ubicarse en la carpeta de la actividad y ejecutar los siguientes comandos en PowerShell:

```powershell
g++ -std=c++20 main.cpp -o main.exe
if ($?) { .\main.exe }
```

## Uso del programa

Al iniciar el programa se debe seleccionar el tipo de lista:

1. Lista de enteros.
2. Lista de palabras.

Después, se debe elegir si los datos de la lista serán capturados manualmente o generados aleatoriamente. Finalmente, se puede utilizar el menú para realizar las operaciones disponibles.

Las posiciones de los elementos comienzan desde el índice `0`.

## Prompts utilizados

- “Ayúdame a revisar la estructura de mi implementación de listas encadenadas y las operaciones que debe incluir.”

- “Explícame el funcionamiento de los apuntadores y nodos dentro de una lista encadenada.”

- “Ayúdame a interpretar y corregir este error de compilación.”

- “Dame una guía de pruebas para verificar cada opción del menú.”

## Reflexión sobre el uso de herramientas de IA

Durante la actividad utilicé Copilot principalmente para detectar y corregir detalles menores de sintaxis y compilación. También consulté ChatGPT para resolver dudas puntuales sobre listas encadenadas, apuntadores, sobrecarga de operadores y mensajes de error.

Las herramientas me sirvieron como apoyo para entender errores y revisar la lógica de las operaciones. Después de cada ajuste realicé pruebas en el programa para verificar que las funciones trabajaran correctamente.

Lo que más reforcé durante la actividad fue el uso de nodos conectados mediante apuntadores, el manejo de memoria dinámica y la importancia de validar índices antes de acceder o modificar elementos de una lista.

Si no hubiera contado con estas herramientas, habría consultado mis apuntes, la documentación de C++, videos de YouTube y realizado pruebas más pequeñas para detectar errores paso a paso.