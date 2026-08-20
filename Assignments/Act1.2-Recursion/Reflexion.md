# Reflexión

### 1. ¿En qué casos notaste que la versión recursiva fue más lenta o usó más memoria que la iterativa? ¿A qué se debió?

La versión recursiva puede ser más lenta y utilizar más memoria porque cada llamada a la función se guarda en la memoria hasta llegar al caso base. Esto se nota especialmente en `fibonacciRecursive`, ya que realiza muchas llamadas y repite cálculos. En cambio, la versión iterativa utiliza ciclos y necesita menos memoria. 

### 2. Para la suma 1..n, `sumFormula` resuelve en un solo paso lo que a `sumIterative` y `sumRecursive` les toma n pasos. ¿Qué te dice esto sobre buscar una fórmula antes de escribir código?

Me enseñó que antes de programar es importante analizar el problema y buscar si existe una fórmula o una solución más eficiente. `sumFormula` obtiene el resultado directamente, mientras que las otras versiones tienen que recorrer los números. 

### 3. Si `bacteriasRecursive` tuviera que calcular n = 100,000 días, ¿qué problema esperarías encontrar y cómo lo resolverías?

Esperaría que el programa tardara demasiado y utilizara mucha memoria, ya que la función hace muchas llamadas recursivas y repite cálculos. Lo resolvería utilizando la versión iterativa, ya que consume menos memoria y evita tantas llamadas recursivas. 
