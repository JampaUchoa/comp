﻿#include <stdio.h>
#include <time.h>

#define N 100000000

#define fim_string -1
#define AP -2 //Abre Parenteses
#define FP -3 //Fecha Parenteses
#define K -4
#define S -5
#define I -6
#define lt -7
#define sub -8
#define mul -9
#define add -10
#define gt -11
#define eq -12
#define true -13
#define false -14
#define Bt -15
#define Ct -16
#define Dt -17
#define Et -18
#define Ft -19
#define Y -20

// YFib
static int entrada[N] = {Y, AP, Bt, AP, S, AP, S, AP, Ct, AP, Ct, I, 2, FP, lt, FP, I, FP, FP, AP, Ft, Ct, AP, S, AP, Ft, Dt, I, AP, Ct, AP, Ct, I, 2, FP, sub, FP, FP, AP, Ft, Bt, I, AP, Ct, AP, Ct, I, 1, FP, sub, FP, FP, FP, add, FP, FP, 10, fim_string};
//static int entrada[N] = {S, AP, K, AP, S, I, I, FP, FP, AP, S, AP, S, AP, K, S, FP, K, FP, AP, K, AP, S, I, I, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 2, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, lt, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, K, K, FP, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, sub, FP, FP, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, mul, FP, FP, FP, FP, 3, fim_string};
//static int entrada[N] = {add, 50, 40, 1, 0, fim_string};
//static int entrada[N] = {S, AP, K, AP, S, I, I, FP, FP, AP, S, AP, S, AP, K, S, FP, K, FP, AP, K, AP, S, I, I, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 2, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, lt, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, K, K, FP, I, FP, FP, AP, S, AP, S, AP, K, S, FP, AP, S, AP, S, AP, K, S, FP, AP, K, I, FP, FP, AP, S, AP, K, K, FP, AP, K, 1, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, sub, FP, FP, FP, FP, FP, FP, AP, S, AP, K, K, FP, AP, K, mul, FP, FP, FP, FP, 5, fim_string};
static int saida[N];

void printar_array(unsigned int *array1) {
   int i;
   unsigned int fimString = -1;
   //sleep(1);
   for(i = 0;array1[i] != fimString;i++){
       switch (array1[i]){
           case S:
               printf("S");
               break;
           case K:
               printf("K");
               break;
           case I:
               printf("I");
               break;
           case FP:
               printf(")");
               break;
           case AP:
               printf("(");
               break;
           case fim_string:
                break;
            case sub:
                printf("-");
                break;
            case mul:
                printf("*");
                break;
            case lt:
                printf("<");
                break;
           default:
               printf("%u ", array1[i]);
       }
   }
   printf("\n");
}

/*
 * Remove o parenteses da posição 0 e seu oposto
 */

void remove_parenteses(int *array1){
    int p = 0;
    int paren = 1;
    while (paren) {
        array1[p] = array1[p+1];
        p++;
        if(array1[p] == AP){
            paren++;
        }else if(array1[p] == FP){
            paren--;
        }
    }
    p--;
    while(array1[p+1] != fim_string && array1[p+2] != fim_string){
        array1[p] = array1[p+2];
        p++;
    }
    array1[p] = fim_string;
}

/*
 * Procura o fim do conjunto de inteiros
 */
void casa_parenteses(int* array1, int* p) {
    int paren = 1;
    int a = *p;
    while (paren) {
        unsigned int c  = array1[a];
        if(c == AP){
            paren++;
        }else if(c == FP){
            paren--;
        }
        a++;
    }
    *p = a;
}

/*
 * Verifica se a posicao do array é um inteiro ou um conjunto de inteiros
 */
void acha_argumento(int *array1, int *p){
    int c = (*p)++;
    if (array1[c] == AP) {
        casa_parenteses(array1,p);
    }
}

/*
 * Kab = a
 */

void reduz_K(int* array1, int* array2) {
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1,&n);

    nA = n-1;
    acha_argumento(array1,&n);

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

/*
 * Sabc = ac(bc)
 */
void reduz_S(int *array1, int *array2) {
    int A, nA;
    int B, nB;
    int C, nC;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    B = n;
    acha_argumento(array1,&n);
    nB = n-1;
    C = n;
    acha_argumento(array1,&n);
    nC = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = C; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = B; i <= nB; i++) {
        array2[k] = array1[i];
        k++;
    }
    for (i = C; i <= nC; i++) {
        array2[k] = array1[i];
        k++;
    }
    array2[k] = FP;
    k++;
    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

void reduz_I(int *array1, int *array2)
{
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;

    //I a => a
    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduz_B(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int C, nC;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;
    C = n;
    acha_argumento(array1, &n);
    nC = n - 1;

    //S a b c => a c ( b c )
    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = B; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }
    for (i = C; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador B: a b c => a c b,
//copiando os argumentos do array1 para o array2.
void reduz_C(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int C, nC;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;
    C = n;
    acha_argumento(array1, &n);
    nC = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = C; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = B; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduz_D(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int C, nC;
    int D, nD;

    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;
    C = n;
    acha_argumento(array1, &n);
    nC = n - 1;
    D = n;
    acha_argumento(array1, &n);
    nD = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = B; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }
    for (i = D; i <= nD; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    array2[k] = AP;
    k++;

    for (i = C; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = D; i <= nD; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}



void reduz_E(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int C, nC;
    int D, nD;

    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;
    C = n;
    acha_argumento(array1, &n);
    nC = n - 1;
    D = n;
    acha_argumento(array1, &n);
    nD = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = B; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = C; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (i = D; i <= nD; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduz_F(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int C, nC;
    int D, nD;

    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;
    C = n;
    acha_argumento(array1, &n);
    nC = n - 1;
    D = n;
    acha_argumento(array1, &n);
    nD = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    for (i = B; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }
    for (i = D; i <= nD; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (i = C; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}


void processaSoma(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    int val1 = array1[A];
    int val2 = array1[B];

    int resultado = val1 + val2;

    array2[k] = resultado;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

void processaMul(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    int val1 = array1[A];
    int val2 = array1[B];

    int resultado = val1 * val2;

    array2[k] = resultado;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}


void testaEq(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    int val1 = array1[A];
    int val2 = array1[B];

    int resultado = (val1 == val2);

    if (resultado)
    {
        array2[k] = true;
    } else
    {
        array2[k] = false;
    }

    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

void testaGt(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    int val1 = array1[A];
    int val2 = array1[B];

    int resultado = (val1 > val2);

    if (resultado)
    {
        array2[k] = true;
    } else
    {
        array2[k] = false;
    }

    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

void testaLt(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    int val1 = array1[A];
    int val2 = array1[B];

    int resultado = (val1 < val2);

    if (resultado)
    {
        array2[k] = true;
    } else
    {
        array2[k] = false;
    }

    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

void processaSub(int *array1, int *array2)
{
    int A, nA;
    int B, nB;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    int val1 = array1[A];
    int val2 = array1[B];

    int resultado = val1 - val2;

    array2[k] = resultado;
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }
    array2[k] = fim_string;
}

void reduz_true(int *array1, int *array2){
    reduz_K(array1, array2);
}

void reduz_false(int* array1, int* array2) {
    int A, nA;
    int B, nB;

    int n = 1;

    A = n;
    acha_argumento(array1,&n);
    nA = n-1;

    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    int k = 0;
    int i;

    for (i = B; i <= nB; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void trocaInteiro(int *array1, int *array2) {
   
    int A, nA;
    int B, nB;
    int n = 1;
    A = n;
    acha_argumento(array1,&n);
    nA = n-1;
    B = n;
    acha_argumento(array1,&n);
    nB = n-1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++) {
        array2[k] = array1[i];
        k++;
    }

    for (i = B; i <= nB; i++) {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = array1[0];
    k++;

    for (; array1[n] != fim_string; n++) {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}

void reduz_Y(int *array1, int *array2)
{
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;

    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = AP;
    k++;

    array2[k] = Y;
    k++;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = FP;
    k++;

    for (n = n; array1[n] != fim_string; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = fim_string;
}


int main(){
    int *array1, *array2, *array3;
    array1 = entrada;
    array2 = saida;
    while(array1[1] != fim_string){
        //printar_array(array1);
        switch (array1[0]){
            case AP:
                remove_parenteses(array1);
                array2[0] = fim_string;
                break;
            case K:
                reduz_K(array1, array2);
                break;
            case S:
                reduz_S(array1, array2);
                break;
            case I:
                reduz_I(array1, array2);
                break;
            case Bt:
                reduz_B(array1, array2);
                break;
            case Ct:
                reduz_C(array1, array2);
                break;                
            case Dt:
                reduz_D(array1, array2);
                break;
            case Et:
                reduz_E(array1, array2);
                break;
            case Ft:
                reduz_F(array1, array2);
                break;       
            case add:
                processaSoma(array1, array2);
                break;           
            case sub:
                processaSub(array1, array2);
                break;          
            case mul:
                processaMul(array1, array2);
                break;
            case eq:
                testaEq(array1, array2);
                break;
            case lt:
                testaLt(array1, array2);
                break;
            case gt:
                testaGt(array1, array2);
                break;
            case true:
                reduz_true(array1, array2);
                break;
            case false:
                reduz_false(array1, array2);
                break;
            case Y:
                reduz_Y(array1, array2);
            default:
                if (array1[0] >= 0){
                    trocaInteiro(array1, array2);
                }
                break;
        }
        array3 = array1;
        array1 = array2;
        array2 = array3;
    }
    printar_array(array1);
    float clks = CLOCKS_PER_SEC;
    printf("\nTempo = %f", (clock()/clks));
    return 0;
}
