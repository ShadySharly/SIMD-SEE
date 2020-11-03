/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// DIRECTIVES /////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
# include <getopt.h>
# include <ctype.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <pmmintrin.h>

# include "../header/simdsort.h"

int main(int argc, char** argv) {

    int N;
    __m128 A, B, C, D, W, X, Y, Z, W_BMN, X_BMN, Y_BMN, Z_BMN;
    char* iValue = (char*)malloc(sizeof(char)); // Archivo binario con la lista de entrada desordenados
    char* oValue = (char*)malloc(sizeof(char)); // Archivo binario de salida con la lista ordenada
    char* nValue = (char*)malloc(sizeof(char)); // Largo de la lista
    char* dValue = (char*)malloc(sizeof(char)); // Bandera para mostrar por consola los resultados
    
    if ( (iValue != NULL) && (oValue != NULL) && (nValue != NULL) && (dValue != NULL) ) {
        getParams (argc, argv, iValue, oValue, nValue, dValue);
        N = atoi(nValue);
    }

    float** sequence = chargeSequence (iValue, N);
    float** sorted16Sequence = sequenceMalloc (N);

    for (int i = 0; i < N / 16; i++) {
        loadSequence (sequence[i], &A, &B, &C, &D);
        inRegister (A, B, C, D, &W, &X, &Y, &Z);
        bmn (W, X, Y, Z, &W_BMN, &X_BMN, &Y_BMN, &Z_BMN);
        storeSequence (sorted16Sequence[i], W_BMN, X_BMN, Y_BMN, Z_BMN);
        print16Sequence (sorted16Sequence[i]);
    }

    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


