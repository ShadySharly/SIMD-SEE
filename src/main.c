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

    int N, L;
    __m128 A, B, C, D, W_IR, X_IR, Y_IR, Z_IR, W_BMN, X_BMN, Y_BMN, Z_BMN, W_MSIMD, X_MSIMD, Y_MSIMD, Z_MSIMD;
    char* iValue = (char*)malloc(sizeof(char)); // Archivo binario con la lista de entrada desordenados
    char* oValue = (char*)malloc(sizeof(char)); // Archivo binario de salida con la lista ordenada
    char* nValue = (char*)malloc(sizeof(char)); // Largo de la lista
    char* dValue = (char*)malloc(sizeof(char)); // Bandera para mostrar por consola los resultados
    
    if ( (iValue != NULL) && (oValue != NULL) && (nValue != NULL) && (dValue != NULL) ) {
        getParams (argc, argv, iValue, oValue, nValue, dValue);
        N = atoi(nValue);
        L = N / 16;
    }

    float** sequence = chargeSequence (iValue, N);
    float** sorted16Sequence = sequenceMalloc (N);

    for (int i = 0; i < L; i++) {
        print16Sequence (sequence[i]);
        //////////////////////////////////
        //         FASE SIMD            //
        //////////////////////////////////
        loadSequence (sequence[i], &A, &B, &C, &D);
        inRegister (A, B, C, D, &W_IR, &X_IR, &Y_IR, &Z_IR);
        BMN (W_IR, X_IR, &W_BMN, &X_BMN);
        BMN (Y_IR, Z_IR, &Y_BMN, &Z_BMN);
        mergeSIMD (W_BMN, X_BMN, Y_BMN, Z_BMN, &W_MSIMD, &X_MSIMD, &Y_MSIMD, &Z_MSIMD);
        storeSequence (sorted16Sequence[i], W_MSIMD, X_MSIMD, Y_MSIMD, Z_MSIMD);
        //print16Sequence (sorted16Sequence[i]);
    }
        //////////////////////////////////
        //        FASE NO SIMD          //
        //////////////////////////////////
    float* sortedSequence = MWMS (sorted16Sequence, N, L);
    writeSequence (sortedSequence, oValue, N);

    if (strcmp(dValue, "1") == 0)
        printSequence (sortedSequence, N);
        
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


