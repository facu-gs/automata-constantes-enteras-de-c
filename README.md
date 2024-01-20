# Autómata Finito Determinístico para Constantes Enteras de C

El siguiente programa capaz de reconocer y **clasificar las distintas constantes enteras de C (Decimal, Octal, Hexadecimal)**. El mismo lee palabras separadas por “,” **(carácter centinela)** de un **archivo de entrada** (entrada.txt) y generar un **archivo de salida** (salida.txt) donde indica qué tipo de constante entera es cada palabra leída o si no fue reconocida. **El programa contempla la implementación de un autómata finito determinístico (AFD)** para el reconocimiento y clasificación de palabras según estado final. 

Se construye la **tabla de transición** qué define el automata de constantes enteras de c como una matriz en las que las filas corresponden a los **estados del autómata** y las columnas corresponden a cada uno de los 256 posibles códigos en **ASCII**. 

Para procesar los datos, se parte del estado inicial, luego se recorre el archivo caracter por caracter utilizando la función `fread`, obteniendo el nuevo estado del autómata accediendo a la celda de la matriz correspondiente a la fila del estado actual y a la columna del caracter leído. Se repite el proceso hasta llegar a una coma, nuestro carácter centinela. Al encontrarlo, imprime en el archivo `salida.txt` la palabra previamente almacenada junto con el estado que obtuvo, reinicia el estado y continúa con el siguiente caracter, así hasta terminar con todos los caracteres del archivo `entrada.txt`.

> Nota: Los espacios son ignorados por el programa. 