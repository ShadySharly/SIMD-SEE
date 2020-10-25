/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <getopt.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>

# include "../header/simdsort.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: 
// - OUTPUTS: 
// - DESCRIPTION:

void getParams (int argc, char** argv, char* cValue, char* mValue, char* nValue, char* bValue) {
/*
    int c;
    int int_n;
    strcpy(bValue, "0");

    // c: Cantidad de Imagenes (int)
    // m: Archivo con la mascara o kernel (string)
    // n: Umbral de negrura (nearly black) (porcentaje int)
    // b: Bandera (Mostrar resultados por pantalla (1) o no (0)) (binario)
    // Ejecutar como:
    //      ./pipeline -c (cValue) -m (mValue) -n (nValue) -b
    while ( (c = getopt (argc, argv, "c:m:n:b")) != -1) {

        switch (c) {
            case 'c':
                strcpy(cValue, optarg);
                // Verificacion de que se ingresa una cantidad de imagenes valida, osea un numero entero positivo
                if (!isInteger(cValue) || (strcmp(cValue, "0") == 0) ) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO MAYOR A 0.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                printf(" => Cantiad de imagenes (-c): %s\n", cValue);
                break;
            
            case 'm':
                strcpy(mValue, optarg);
                // Verificacion que el arcivo ingresado existe 
                if (!exist(mValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ARCHIVO EXISTENTE.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                printf(" => Ruta de la mascara (-m): %s\n", mValue);
                break;
            
            case 'n':
                strcpy(nValue, optarg);
                int_n = atoi(optarg);
                // Verificacion de que se ingresa una cantidad de imagenes valida, osea un numero entero positivo
                if (!isInteger(nValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

                // Verificacion de que se ingresa una cantidad de imagenes valida, osea un numero entero positivo entre 0 y 100
                if (!isPercentage(int_n)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO ENTRE 0 Y 100.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }
            
                printf(" => Umbral (-n): %s\n", nValue);
                break;
            
            case 'b':
                strcpy(bValue, "1");

                printf(" => Opcion b (-b): %s\n", bValue);
                break;
            
            case '?':
                // Verificacion de existencia de argumentos
                if ( (optopt == 'c') || (optopt == 'm') || (optopt == 'n') ) { 
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => La opcion -%c requiere un argumento.\n", optopt);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }
                // VErificacion de la validez de las banderas
                else if (isprint (optopt)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => Opcion -%c desconocida.\n", optopt);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    abort ();
                }

            default:
                break;
            }
    }
    */
}

void printHola() {

    printf("HOLA ME COMPILE XD\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////