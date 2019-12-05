#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 100000000

/*
*   Maquina KSI
*/

static char entrada[N] = "+(100)1";

//"=(1)(10)(1)(2)\0"
//String de teste:
//static char entrada[N] = "S(K(K))(KS)(SK)KK(SK)K\0";
static char saida[N];

//Procedimento que recebe duas vari·veis, uma que aponta para
//um array e outra que aponta para um inteiro com a posiÁ„o do
//array a ser usada. O procedimento termina quando atinge a
//primeira posiÁ„o depois dos parÍnteses.
void casa_parenteses(char *array1, int *p)
{
    int paren = 1;
    int c = *p;
    while (paren != 0)
    {
        switch (array1[c])
        {
        case '(':
            paren++;
            c++;
            break;
        case ')':
            paren--;
            c++;
            break;
        default:
            c++;
        }
    }
    *p = c;
}

//Procedimento que recebe duas vari·veis, uma que aponta para
//um array e outra que aponta para um inteiro com a posiÁ„o do
//array a ser usada. O procedimento termina quando atinge a
//primeira posiÁ„o depois do argumento.
void acha_argumento(char *array1, int *p)
{
    int c = *p;
    if (array1[c] == '(')
    {
        c++;
        casa_parenteses(array1, &c);
    }
    else
    {
        c++;
    }
    *p = c;
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador K: K a b => a,
//copiando os argumentos do array1 para o array2.
void reduzK(char *array1, char *array2)
{
    int A, nA;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    acha_argumento(array1, &n);

    //K a b => a
    int k = 0;
    int i;

    for (i = A; i <= nA; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador I: I a => a,
//copiando os argumentos do array1 para o array2.
void reduzI(char *array1, char *array2)
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

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador S: S a b c => a c ( b c ),
//copiando os argumentos do array1 para o array2.
void reduzS(char *array1, char *array2)
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
    for (i = C; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    array2[k] = '(';
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

    array2[k] = ')';
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador B: a b c => a(bc),
//copiando os argumentos do array1 para o array2.
void reduzB(char *array1, char *array2)
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

    array2[k] = '(';
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

    array2[k] = ')';
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador B: a b c => a c b,
//copiando os argumentos do array1 para o array2.
void reduzC(char *array1, char *array2)
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

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador B: a b c d => a (bd) (cd),
//copiando os argumentos do array1 para o array2.
void reduzD(char *array1, char *array2)
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

    array2[k] = '(';
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

    array2[k] = ')';
    k++;

    array2[k] = '(';
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

    array2[k] = ')';
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador B: a b c d => a b (cd),
//copiando os argumentos do array1 para o array2.
void reduzE(char *array1, char *array2)
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

    array2[k] = '(';
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

    array2[k] = ')';
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador B: a b c d => a (bd) c,
//copiando os argumentos do array1 para o array2.
void reduzF(char *array1, char *array2)
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

    array2[k] = '(';
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

    array2[k] = ')';
    k++;

    for (i = C; i <= nC; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

//Procedimento que recebe duas vari·veis que apontam para
//dois arrays e executa a regra do combinador +: + a b => a + b,
//copiando os argumentos do array1 para o array2.
void processaSoma(char *array1, char *array2)
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

    //+: + a b => a + b,
    int k = 0;
    int i;

    int num = 0;

    // Converte as 2 strings em strings separadas
    char first[100];
    char second[100];

    int stepper = 0;
    for (i = A; i <= nA; i++)
    {   
        if (array1[i] != '(' && array1[i] != ')') {
            first[stepper] = array1[i];
            stepper++;
        }
    }
    first[stepper] = '\0';

    stepper = 0;
    for (i = B; i <= nB; i++)
    {
        if (array1[i] != '(' && array1[i] != ')') {
            second[stepper] = array1[i];
            stepper++;
        }
    }
    second[stepper] = '\0';

    
    int val1 = atoi(first);
    int val2 = atoi(second);

    //printf("Valor = %d, %d\n", val1, val2);

    int resultado = val1 + val2;

    char res[1000];
    sprintf(res, "%d", resultado);

    array2[k] = '(';
    k++;

    for (stepper = 0; res[stepper] != '\0'; stepper++)
    {
        array2[k] = res[stepper];
        k++;
    }

    array2[k] = ')';
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';

    printf("Result %s\n", array2);
}

void processaMult(char *array1, char *array2)
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

    //+: + a b => a + b,
    int k = 0;
    int i;

    int num = 0;

    // Converte as 2 strings em strings separadas
    char first[100];
    char second[100];

    int stepper = 0;
    for (i = A; i <= nA; i++)
    {   
        if (array1[i] != '(' && array1[i] != ')') {
            first[stepper] = array1[i];
            stepper++;
        }
    }
    first[stepper] = '\0';

    stepper = 0;
    for (i = B; i <= nB; i++)
    {
        if (array1[i] != '(' && array1[i] != ')') {
            second[stepper] = array1[i];
            stepper++;
        }
    }
    second[stepper] = '\0';

    
    int val1 = atoi(first);
    int val2 = atoi(second);

    //printf("Valor = %d, %d\n", val1, val2);

    int resultado = val1 * val2;

    char res[1000];
    sprintf(res, "%d", resultado);

    array2[k] = '(';
    k++;

    for (stepper = 0; res[stepper] != '\0'; stepper++)
    {
        array2[k] = res[stepper];
        k++;
    }

    array2[k] = ')';
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';

    printf("Result %s\n", array2);
}


void processaSub(char *array1, char *array2)
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

    //+: + a b => a + b,
    int k = 0;
    int i;

    int num = 0;

    // Converte as 2 strings em strings separadas
    char first[100];
    char second[100];

    int stepper = 0;
    for (i = A; i <= nA; i++)
    {   
        if (array1[i] != '(' && array1[i] != ')') {
            first[stepper] = array1[i];
            stepper++;
        }
    }
    first[stepper] = '\0';

    stepper = 0;
    for (i = B; i <= nB; i++)
    {
        if (array1[i] != '(' && array1[i] != ')') {
            second[stepper] = array1[i];
            stepper++;
        }
    }
    second[stepper] = '\0';

    
    int val1 = atoi(first);
    int val2 = atoi(second);

    //printf("Valor = %d, %d\n", val1, val2);

    int resultado = val1 - val2;

    char res[1000];
    sprintf(res, "%d", resultado);

    array2[k] = '(';
    k++;

    for (stepper = 0; res[stepper] != '\0'; stepper++)
    {
        array2[k] = res[stepper];
        k++;
    }

    array2[k] = ')';
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';

    printf("Result %s\n", array2);
}


void testaIgualdade(char *array1, char *array2){
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

    int num = 0;

    // Converte as 2 strings em strings separadas
    char first[100];
    char second[100];

    int stepper = 0;
    for (i = A; i <= nA; i++)
    {   
        if (array1[i] != '(' && array1[i] != ')') {
            first[stepper] = array1[i];
            stepper++;
        }
    }
    first[stepper] = '\0';

    stepper = 0;
    for (i = B; i <= nB; i++)
    {
        if (array1[i] != '(' && array1[i] != ')') {
            second[stepper] = array1[i];
            stepper++;
        }
    }
    second[stepper] = '\0';

    
    int val1 = atoi(first);
    int val2 = atoi(second);

    printf("Valor = %d, %d\n", val1, val2);

    int resultado = (val1 == val2);

    if (resultado)
    {
        array2[k] = 'T';
    } else
    {
        array2[k] = 'F';
    }
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

void testaGT(char *array1, char *array2){
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

    int num = 0;

    // Converte as 2 strings em strings separadas
    char first[100];
    char second[100];

    int stepper = 0;
    for (i = A; i <= nA; i++)
    {   
        if (array1[i] != '(' && array1[i] != ')') {
            first[stepper] = array1[i];
            stepper++;
        }
    }
    first[stepper] = '\0';

    stepper = 0;
    for (i = B; i <= nB; i++)
    {
        if (array1[i] != '(' && array1[i] != ')') {
            second[stepper] = array1[i];
            stepper++;
        }
    }
    second[stepper] = '\0';

    
    int val1 = atoi(first);
    int val2 = atoi(second);

    printf("Valor = %d, %d\n", val1, val2);

    int resultado = (val1 > val2);

    if (resultado)
    {
        array2[k] = 'T';
    } else
    {
        array2[k] = 'F';
    }
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}

void testaLT(char *array1, char *array2){
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

    int num = 0;

    // Converte as 2 strings em strings separadas
    char first[100];
    char second[100];

    int stepper = 0;
    for (i = A; i <= nA; i++)
    {   
        if (array1[i] != '(' && array1[i] != ')') {
            first[stepper] = array1[i];
            stepper++;
        }
    }
    first[stepper] = '\0';

    stepper = 0;
    for (i = B; i <= nB; i++)
    {
        if (array1[i] != '(' && array1[i] != ')') {
            second[stepper] = array1[i];
            stepper++;
        }
    }
    second[stepper] = '\0';

    
    int val1 = atoi(first);
    int val2 = atoi(second);

    printf("Valor = %d, %d\n", val1, val2);

    int resultado = (val1 < val2);

    if (resultado)
    {
        array2[k] = 'T';
    } else
    {
        array2[k] = 'F';
    }
    k++;

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';
}


void processaT(char *array1, char *array2){
    reduzK(array1, array2);
}

void processaF(char *array1, char *array2){
    int A, nA;
    int B, nB;
    int n = 1;

    A = n;
    acha_argumento(array1, &n);
    nA = n - 1;
    B = n;
    acha_argumento(array1, &n);
    nB = n - 1;

    //K a b => a
    int k = 0;
    int i;

    for (i = B; i <= nB; i++)
    {
        array2[k] = array1[i];
        k++;
    }

    for (n = n; array1[n] != '\0'; n++)
    {
        array2[k] = array1[n];
        k++;
    }

    array2[k] = '\0';

}


//Procedimento que recebe uma vari·vel que aponta para
//um array e remove os parÍnteses da primeira posiÁ„o
//do array.
void recebeParenteses(char *array1)
{
    int c = 1;
    casa_parenteses(array1, &c);

    int i;
    for (i = 0; i < c - 2; i++)
    {
        array1[i] = array1[i + 1];
    }

    array1[i] = array1[i + 2];
    i++;
    while (array1[i + 2] != '\0')
    {
        array1[i] = array1[i + 2];
        i++;
    }
    array1[i] = '\0';
}

int main()
{

    char *array1 = entrada;
    char *array2 = saida;
    char *array3;
    while (array1[1] != '\0')
    {
        int i;

        for (i = 0; array1[i] != '\0'; i++)
        {
            printf("%c", array1[i]);
        }
        
        printf("\n");
    
        switch (array1[0])
        {
        case 'I':
            reduzI(array1, array2);
            break;
        case 'K':
            reduzK(array1, array2);
            break;
        case 'S':
            reduzS(array1, array2);
            break;
        case '+':
            processaSoma(array1, array2);
            break;
        case '*':
            processaMult(array1, array2);
            break;
        case '-':
            processaSub(array1, array2);
            break;
        case '=':
            testaIgualdade(array1, array2);
            break;
        case '>':
            testaGT(array1, array2);
            break;
        case '<':
            testaLT(array1, array2);
            break;
        case 'T':
            processaT(array1, array2);
            break;
        case 'F':
            processaF(array1, array2);
            break;
        case '(':
            recebeParenteses(array1);
            array2[0] = 'X';
            break;
        default:
            break;
        }
        array3 = array1;
        array1 = array2;
        array2 = array3;
    }

    int i;
    for (i = 0; array1[i] != '\0'; i++)
    {
        printf("%c", array1[i]);
    }
    printf("\n");

    printf("Tempo = %lf", (double)(clock() / CLOCKS_PER_SEC));

    return 0;
}
