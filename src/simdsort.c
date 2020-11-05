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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////// FUNCTIONS //////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: 
// - OUTPUTS: 
// - DESCRIPTION:

void getParams (int argc, char** argv, char* iValue, char* oValue, char* nValue, char* dValue) {

    int c;

    // i: Archivo binario con la lista de entrada desordenados (string)
    // o: Archivo binario de salida con la lista ordenada (string)
    // n: Largo de la lista (int)
    // d: Bandera (Mostrar resultados por pantalla (1) o no (0)) (binario)
    // Ejecutar como:
    //      ./simdsort -i desordenada.raw -o ordenada.raw -N num_elementos -d debug
    while ( (c = getopt (argc, argv, "i:o:N:d:")) != -1) {

        switch (c) {
            case 'i':
                strcpy(iValue, optarg);
                // Verificacion que el archivo de entrada existe 
                if (!exist(iValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ARCHIVO EXISTENTE.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    exit(EXIT_FAILURE);
                }       

                //printf(" => Ruta del archivo de entrada (-i): %s\n", iValue);
                break;
            
            case 'o':
                strcpy(oValue, optarg);
                //printf(" => Ruta del archivo de salida (-o): %s\n", oValue);
                break;
            
            case 'N':
                strcpy(nValue, optarg);
                // Verificacion de que se ingr#include <unistd.h>esa un numero entero positivo
                if (!isInteger(nValue)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un ENTERO POSITIVO.\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    exit(EXIT_FAILURE);
                }
            
                //printf(" => Largo de la lista (-N): %s\n", nValue);
                break;
            
            case 'd':
                strcpy(dValue, optarg);
                // Verificacion de que se ingresa un valor binario (1 o 0)
                if ( (strcmp(dValue, "0") != 0) && (strcmp(dValue, "1") != 0) ) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => El argumento de -%c debe ser un VALOR BINARIO (1 o 0).\n", c);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    exit(EXIT_FAILURE);
                }

                //printf(" => Opcion debug (-d): %s\n", dValue);
                break;
            
            case '?':
                // Verificacion de existencia de argumentos
                if ( (optopt == 'i') || (optopt == 'o') || (optopt == 'N') || (optopt == 'd')) { 
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => La opcion -%c requiere un argumento.\n", optopt);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    exit(EXIT_FAILURE);
                }
                // Verificacion de la validez de las banderas
                else if (isprint (optopt)) {
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    printf (" => Opcion -%c desconocida.\n", optopt);
                    printf (" => Programa abortado\n");
                    printf ("%s\n", "-------------------------------------------------------------------------");
                    exit(EXIT_FAILURE);
                }

            default:
                break;
            }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - fileName: Nombre del archivo a leer
// - OUTPUTS: Valor booleano 1 si el archivo existe, 0 en caso contrario
// - DESCRIPTION: Verifica que el archivo con el nombre "fileName" existe y devuelve la verificacion.

int exist (char* fileName) {

    FILE* f = fopen(fileName, "r");

    if (f != NULL) {
        fclose(f);
        return 1;
    }
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

int isInteger (char* input) {

    int c;

    for (c = 0; c < strlen(input); c++) {

        if (!isdigit(input[c]))
            return 0;
    }
    return 1;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

float** chargeSequence (char* inputName, int N) {

    int index = 0;
    FILE* inputFile = fopen(inputName, "rb");
    
    if (inputFile != NULL) {
        float** sequences = sequenceMalloc (N);

        while (!feof(inputFile)) {
            fread(sequences[index], sizeof(float), 16, inputFile);
            index++;
        }
        fclose(inputFile);
        return sequences;
    }

    else{
        printf("ERROR AL LEER ARCHIVO DE ENTRADA\n");
        printf (" => Programa abortado\n");
        exit(EXIT_FAILURE);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

void loadSequence (float* sequence, __m128* A, __m128* B, __m128* C, __m128* D) {

    float a[4] __attribute__((aligned(16))) = { sequence[0], sequence[1], sequence[2], sequence[3] };
    float b[4] __attribute__((aligned(16))) = { sequence[4], sequence[5], sequence[6], sequence[7] };
    float c[4] __attribute__((aligned(16))) = { sequence[8], sequence[9], sequence[10], sequence[11] };
    float d[4] __attribute__((aligned(16))) = { sequence[12], sequence[13], sequence[14], sequence[15] };

    *A = _mm_load_ps (a);
    *B = _mm_load_ps (b);
    *C = _mm_load_ps (c);
    *D = _mm_load_ps (d);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

void inRegister (__m128 A, __m128 B, __m128 C, __m128 D, __m128* W_F, __m128* X_F, __m128* Y_F, __m128* Z_F) {

    __m128 A_1, C_1, B_2, D_2, A_3, B_3, C_3, D_3, B_4, C_4;
    __m128 W_1, W_2, X_1, X_2;
    __m128 Y_1, Y_2, Z_1, Z_2;

    A_1 = _mm_min_ps (A, C);
    C_1 = _mm_max_ps (A, C);
    B_2 = _mm_min_ps (B, D);
    D_2 = _mm_max_ps (B, D);
    A_3 = _mm_min_ps (A_1, B_2);
    B_3 = _mm_max_ps (A_1, B_2);
    C_3 = _mm_min_ps (C_1, D_2);
    D_3 = _mm_max_ps (C_1, D_2);
    B_4 = _mm_min_ps (B_3, C_3);
    C_4 = _mm_max_ps (B_3, C_3);

    W_1 = _mm_shuffle_ps (A_3, B_4, _MM_SHUFFLE (1, 0, 1, 0));
    X_1 = _mm_shuffle_ps (C_4, D_3, _MM_SHUFFLE (1, 0, 1, 0));
    W_2 = _mm_shuffle_ps (W_1, W_1, _MM_SHUFFLE (3, 1, 2, 0));
    X_2 = _mm_shuffle_ps (X_1, X_1, _MM_SHUFFLE (3, 1, 2, 0));
    *W_F = _mm_shuffle_ps (W_2, X_2, _MM_SHUFFLE (1, 0, 1, 0));
    *X_F = _mm_shuffle_ps (W_2, X_2, _MM_SHUFFLE (3, 2, 3, 2));

    Y_1 = _mm_shuffle_ps (A_3, B_4, _MM_SHUFFLE (3, 2, 3, 2));
    Z_1 = _mm_shuffle_ps (C_4, D_3, _MM_SHUFFLE (3, 2, 3, 2));
    Y_2 = _mm_shuffle_ps (Y_1, Y_1, _MM_SHUFFLE (3, 1, 2, 0));
    Z_2 = _mm_shuffle_ps (Z_1, Z_1, _MM_SHUFFLE (3, 1, 2, 0));
    *Y_F = _mm_shuffle_ps (Y_2, Z_2, _MM_SHUFFLE (1, 0, 1, 0));
    *Z_F = _mm_shuffle_ps (Y_2, Z_2, _MM_SHUFFLE (3, 2, 3, 2));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: 4 registros desde inRegister
// - OUTPUTS: 4 arreglos ordenados
// - DESCRIPTION: BMN

void BMN (__m128 A, __m128 B, __m128* W, __m128* X) {
    
    __m128 A_1, A_2, A_3, A_4, A_5, A_6, A_7, A_8;
    __m128 BI_1, BI_2, BI_3, BI_4, BI_5, BI_6, BI_7, BI_8, BI;

    //Shuffle 1, se reordenan los registros X e Y en orden decreciente
    BI = _mm_shuffle_ps(B, B, _MM_SHUFFLE(0, 1, 2, 3));

    //min max paso 1
    A_1 = _mm_min_ps(A, BI);
    BI_1 = _mm_max_ps(A, BI);

    //Shuffle paso 2
    A_2 = _mm_shuffle_ps(A_1, BI_1, _MM_SHUFFLE(1, 0, 1, 0));
    BI_2 = _mm_shuffle_ps(A_1, BI_1 , _MM_SHUFFLE(3, 2, 3, 2));

    //Shufle paso 3
    A_3 = _mm_shuffle_ps(A_2, A_2, _MM_SHUFFLE(3, 1, 2, 0));
    BI_3 = _mm_shuffle_ps(BI_2, BI_2, _MM_SHUFFLE(3, 1, 2, 0));

    //min max paso 4 
    A_4 = _mm_min_ps(A_3, BI_3);
    BI_4 = _mm_max_ps(A_3, BI_3);

    //Shuffle paso 5 
    A_5 = _mm_shuffle_ps(A_4, BI_4, _MM_SHUFFLE(1, 0, 1, 0));
    BI_5 = _mm_shuffle_ps(A_4, BI_4, _MM_SHUFFLE(3, 2, 3, 2));

    //Shuffle paso 6 
    A_6 = _mm_shuffle_ps(A_5, A_5, _MM_SHUFFLE(3, 1, 2, 0));
    BI_6 = _mm_shuffle_ps(BI_5, BI_5, _MM_SHUFFLE(3, 1, 2, 0));

    //min max paso 7
    A_7 =  _mm_min_ps(A_6, BI_6);
    BI_7 = _mm_max_ps(A_6, BI_6);

    //Shuffle paso 8 
    A_8 = _mm_shuffle_ps(A_7, BI_7, _MM_SHUFFLE(1, 0, 1, 0));
    BI_8 = _mm_shuffle_ps(A_7, BI_7, _MM_SHUFFLE(3, 2, 3, 2));

    //Shuffle paso 9
    *W = _mm_shuffle_ps(A_8, A_8, _MM_SHUFFLE(3,1,2,0));
    *X = _mm_shuffle_ps(BI_8, BI_8, _MM_SHUFFLE(3,1,2,0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

void mergeSIMD (__m128 A, __m128 B, __m128 C, __m128 D, __m128* W, __m128* X, __m128* Y, __m128* Z) {

    __m128 O1, O2;
    float b[4] __attribute__((aligned(16))) = { 0.0, 0.0, 0.0, 0.0 };
    float d[4] __attribute__((aligned(16))) = { 0.0, 0.0, 0.0, 0.0 };

    _mm_store_ps(b, B);
    _mm_store_ps(d, D);

    // Se aplica la BMN con los primeros 4 elementos de cada secuencia de 8
    BMN (A, C, &O1, &O2);
    *W = O1;

    if (b[0] < d[0]) {
        BMN (O2, B, &O1, &O2);
        *X = O1;

        BMN (O2, D, &O1, &O2);
        *Y = O1;
        *Z = O2;
    }

    else if (b[0] > d[0]) {
        BMN (O2, D, &O1, &O2);
        *X = O1;

        BMN (O2, B, &O1, &O2);
        *Y = O1;
        *Z = O2;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

float* MWMS (float** sequence, int N, int L) {

    float min;
    int seqIndex, minIndex, firstIndex, outIndex;
    float* outSequence = (float*)malloc(N * sizeof(float));
    int* indexArray = initIndexArray (L);

    outIndex = 0;
    firstIndex = 1;
    
    while (outIndex < N) {
        
        for (seqIndex = 0; seqIndex < L; seqIndex++) {
            int numIndex = indexArray[seqIndex];

            if (numIndex < 16) {
                if (firstIndex == 1) {
                    minIndex = seqIndex;
                    min = sequence[seqIndex][numIndex];
                    firstIndex = 0;
                }

                //printf("%f < %f\n", sequence[seqIndex][numIndex], min);

                if (sequence[seqIndex][numIndex] < min) {
                    minIndex = seqIndex;
                    min = sequence[seqIndex][numIndex];
                }
            }
        }
        outSequence[outIndex] = min;
        indexArray[minIndex] = indexArray[minIndex] + 1;
        firstIndex = 1;
        outIndex++;
    }
    
    return outSequence;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

int* initIndexArray (int L) {

    int index;
    int* array = (int*)malloc(L * sizeof(int));

    for (index = 0; index < L; index++)
        array[index] = 0;

    return array;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

void storeSequence (float* sequence, __m128 WF, __m128 XF, __m128 YF, __m128 ZF) {

    float w[4] __attribute__((aligned(16))) = { 0.0, 0.0, 0.0, 0.0 };
    float x[4] __attribute__((aligned(16))) = { 0.0, 0.0, 0.0, 0.0 };
    float y[4] __attribute__((aligned(16))) = { 0.0, 0.0, 0.0, 0.0 };
    float z[4] __attribute__((aligned(16))) = { 0.0, 0.0, 0.0, 0.0 };

    _mm_store_ps(w, WF);
    _mm_store_ps(x, XF);
    _mm_store_ps(y, YF);
    _mm_store_ps(z, ZF);

    sequence[0] = w[0];
    sequence[1] = w[1];
    sequence[2] = w[2];
    sequence[3] = w[3];
    sequence[4] = x[0];
    sequence[5] = x[1];
    sequence[6] = x[2];
    sequence[7] = x[3];
    sequence[8] = y[0];
    sequence[9] = y[1];
    sequence[10] = y[2];
    sequence[11] = y[3];
    sequence[12] = z[0];
    sequence[13] = z[1];
    sequence[14] = z[2];
    sequence[15] = z[3];
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

void writeSequence (float* sequence, char* outputName, int N) {

    FILE* outputFile = fopen(outputName, "wb");
    
    if (outputFile != NULL) {
        fwrite(sequence, sizeof(float), N, outputFile);
        fclose(outputFile);
    }

    else{
        printf("ERROR AL CREAR ARCHIVO DE SALIDA\n");
        printf (" => Programa abortado\n");
        exit(EXIT_FAILURE);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

void print16Sequence (float* sequence) {

    for (int i = 0; i < 16; i = i + 4) {
        printf("%f %f %f %f\n", sequence[i], sequence[i + 1], sequence[i + 2], sequence[i + 3]);
    }
    printf("\n");
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

void printSequence (float* sequence, int N) {

    for (int i = 0; i < N; i++) {
        printf("%f\n", sequence[i]);
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// - INPUTS: - input: Cadena de caracteres a evaluar si corresponde a un numero entero positivo o no
// - OUTPUTS: Valor booleano 1 si es entero positivo, 0 en caso contrario
// - DESCRIPTION: Verifica si una cadena de caracteres de entrada posee en cada una de sus posiciones un caracter que es
//                digito y es positivo

float** sequenceMalloc (int N) {

    int L, index;
    L = N / 16;

    float** sequences = (float**)malloc(L * sizeof(float*));

    if (sequences != NULL) {
        for (index = 0; index < L; index++) {
            sequences[index] = (float*)malloc(16 * sizeof(float));

            if (sequences[index] == NULL) {
                printf("ERROR AL ALOJAR MEMORIA PARA LAS SECUENCIAS\n");
                printf (" => Programa abortado\n");
                exit(EXIT_FAILURE);
            }
        }
        return sequences;
    }

    else {
        printf("ERROR AL ALOJAR MEMORIA PARA LAS SECUENCIAS\n");
        printf (" => Programa abortado\n");
        exit(EXIT_FAILURE);
    }    
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////// END ////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////