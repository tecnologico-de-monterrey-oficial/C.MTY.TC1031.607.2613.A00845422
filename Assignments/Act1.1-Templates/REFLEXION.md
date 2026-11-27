# Reflexión

## 1. ¿Qué ventaja concreta notaste al usar templates en tu clase `Lista`, comparado con haberla hecho solo para un tipo de dato?

La ventaja que noté es que puedo utilizar la misma clase `List` para diferentes tipos de datos sin tener que hacer una clase diferente para cada uno. Por ejemplo, en mi código utilicé `List<int>` para guardar números enteros y `List<string>` para guardar palabras. En ambos casos utilizo los mismos métodos como `insert`, `print` y `getData`, solamente cambia el tipo de dato que se guarda.

Esto hace que el código sea más fácil de reutilizar y evita tener que escribir varias veces prácticamente la misma clase.

## 2. ¿Qué parte de la actividad —ya sea el uso de templates o el reto de `insertAt`/`removeAt`— te costó más trabajo entender o depurar? ¿Qué hiciste para resolverlo?

Lo que más trabajo me costó fue entender `insertAt` y `removeAt`, porque al insertar o eliminar un elemento los demás elementos tienen que cambiar de posición. También tuve que tener cuidado con las posiciones válidas, ya que no se puede insertar o eliminar en cualquier posición.

Para resolverlo revisé cómo funcionaban las operaciones de `vector` y fui probando los métodos con diferentes posiciones en el `main`. También probé casos como intentar insertar en una posición inválida y eliminar elementos de una lista vacía para comprobar que los mensajes y las condiciones funcionaran correctamente.

## 3. Si tuvieras que explicarle a un compañero qué es un template en C++ usando tus propias palabras, sin tecnicismos, ¿qué le dirías?

Yo diría que un template es como una plantilla que permite utilizar el mismo código con diferentes tipos de datos. Por ejemplo, en lugar de hacer una lista solamente para guardar enteros y después crear otra lista para guardar `string`, podemos hacer una sola clase y elegir qué tipo de dato queremos utilizar cuando creemos la lista.

Así podemos reutilizar el mismo código sin tener que volver a escribir toda la clase para cada tipo de dato.
