# Evidencia 3 · Bitácora de incidentes

Programa en C++ que lee y valida una bitácora JSON. Usa un Heap para
ordenar los registros y un BST para contar las apariciones de cada IP.

## Compilar y ejecutar

Abre PowerShell en la carpeta `Evidences/Evidence3` y ejecuta:

```powershell
g++ -std=c++20 -Wall -Wextra -Wpedantic -I include src/main.cpp src/Log.cpp src/FileManager.cpp -o evidencia3.exe
if ($LASTEXITCODE -eq 0) { .\evidencia3.exe .\data\log607-3.json }
```

## Menú

1. Ordenar de mayor a menor con MaxHeap y generar `output608-1.out`.
2. Ordenar de menor a mayor con MinHeap y generar `output608-2.out`.
3. Mostrar las 10 IPs con más incidentes.
4. Buscar una IP y consultar sus apariciones.
5. Salir.

## Carpetas

- `include/` — Encabezados del Heap, Heap Sort, BST y manejo de registros.
- `src/` — Programa principal, lectura del JSON y validación.
- `tests/` — Pruebas de Heap, Heap Sort y BST.
- `data/` — Bitácora `log607-3.json`.
- `out/` — Archivos generados por las opciones 1 y 2.
- `docs/` — Informe `ReflexEvidencia3.pdf`.

## Video

[Ver video explicativo]
https://tecmx-my.sharepoint.com/:f:/r/personal/a00845422_tec_mx/_layouts/15/onedrive.aspx?id=%2Fpersonal%2Fa00845422%5Ftec%5Fmx%2FDocuments%2FVideos%20Estructura%20de%20datos&share=cgpoEUx25uqHRaIWWyuKGy2sEgUDghQ7rS5B%2DjIhSgSMshMX4A 