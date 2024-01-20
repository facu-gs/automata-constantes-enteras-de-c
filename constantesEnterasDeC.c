#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define CENTINELA ','
#define ESTADOS 7
#define CARACTERES 6
#define ESTADO_INCIAL 0

int main() {
    FILE *archivoEntrada, *archivoSalida;
    char nombreArchivoEntrada[] = "entrada.txt";
    char nombreArchivoSalida[] = "salida.txt";
    char *traduccionEstados[ESTADOS] = {"NO RECONOCIDO", "OCTAL", "DECIMAL", "NO RECONOCIDO", "HEXADECIMAL", "OCTAL", "NO RECONOCIDO"};
    uint8_t tablaTransicion[ESTADOS][CARACTERES] = {
        {1,2,2,6,6,6},
        {5,5,6,6,3,6},
        {2,2,2,6,6,6},
        {4,4,4,4,6,6},
        {4,4,4,4,6,6},
        {5,5,6,6,6,6},
        {6,6,6,6,6,6},
    };

    archivoEntrada = fopen(nombreArchivoEntrada, "r");
    archivoSalida = fopen(nombreArchivoSalida, "w");

    if (archivoEntrada == NULL) {
        printf("No se pudo abrir el archivo de entrada\n");
        return 1;
    }

    if (archivoSalida == NULL) {
        printf("No se pudo abrir el archivo de salida\n");
        return 1;
    }

    char caracter;
    char estado = ESTADO_INCIAL;
    char *palabra = "";
    char *palabraAux;
    int largoPalabra = 0;
    int columna;

    while (fread(&caracter, 1, 1, archivoEntrada)) {
        if (caracter == CENTINELA) {
            fprintf(archivoSalida, "%-30s%s\n", palabra, traduccionEstados[estado]);
            estado = ESTADO_INCIAL;
            largoPalabra = 0;
            palabra = "";
            continue;
        }

        if (caracter == ' ') {
            continue;
        }

        switch(caracter){
            case '0':
                columna = 0;
                break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
                columna = 1;
                break;
            case '8':
            case '9':
                columna = 2;
                break;
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
                columna = 3;
                break;
            case 'x':
            case 'X':
                columna = 4;
                break;
            default:
                columna = 5;
        }

        largoPalabra = strlen(palabra);
        palabraAux = malloc(largoPalabra + 2);
        strcpy(palabraAux, palabra);
        palabraAux[largoPalabra] = caracter;
        palabraAux[largoPalabra + 1] = '\0';
        free(palabra);
        palabra = palabraAux;

        estado = tablaTransicion[estado][columna];
    }

    fprintf(archivoSalida, "%-30s%s", palabra, traduccionEstados[estado]);
    free(palabra);

    fclose(archivoEntrada);
    fclose(archivoSalida);
    return 0;
}