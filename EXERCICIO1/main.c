/*  Jorge Lucas Vicilli Jabczenski  */
/*              jlvj19              */
/*            GRR20190372           */
/*             14/5/2021            */
/* Exercício 1 - Análise Intervalar */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define DEBUG 

/* Maior anterior ou igual número representavel */
float 
maiorAnterior(float n)
{
    return nextafterf(n, n-1);
}

/* Menos posterior ou igual número representavel */
float 
menorPosterior(float n)
{
    return nextafterf(n, n+1);
}

/**************************************************/
/*                    OPERAÇÕES                   */
/**************************************************/

/* MÁXIMO DE 2 */
/* MÁXIMO DE 4 */
/* MÍNIMO DE 2 */
/* MÍNIMO DE 4 */


/* SOMA */
intervalo_t
soma(intervalo_t i1, intervalo_t i2)
{
    intervalo_t resultado;
    resultado.min = i1.min + i2.min;
    resultado.max = i1.max + i2.max;
    return resultado;
}

/* SUBTRAÇÃO */
intervalo_t
subtacao(intervalo_t i1, intervalo_t i2)
{
    intervalo_t resultado;
    resultado.min = i1.min - i2.max;
    resultado.max = i1.max - i2.min;
    return resultado;
}

/* MULTIPLICAÇÃO */
/* DIVISÃO */

/**************************************************/

/* Representar um número como IEE754   */

/* Tipo de estrutura para representar um intervalo */
typedef struct 
intervalo
{
    char  rot[5];
    float min;
    float max;
} intervalo_t;

typedef struct
conta 
{
    char dest[5];
    char igual;
    char rot1[5];
    char op;
    char rot2[5];
} conta_t;

int
main()
{
    /* Variáveis */
    int nrInputs, nrOperacoes;
    float *inputs;
    intervalo_t *intervalos;
    conta_t *contas;

    /**************************************/
    /* Le as entradas */
    scanf("%d\n%d", &nrInputs, &nrOperacoes);

    #ifdef DEBUG
    printf("Inputs: %d | Operacoes: %d\n", nrInputs, nrOperacoes);
    #endif

    /* 
    Aloca espaço necessário para os inputs, suas representações em intervalos,
    contas e resultados
    */
    inputs = (float *) malloc (nrInputs * sizeof(float));
    intervalos = (intervalo_t*) malloc (nrInputs * sizeof(intervalo_t));
    contas = (conta_t *) malloc (nrOperacoes * sizeof(conta_t));

    /* Lê todas as entradas */
    for (int i = 0; i < nrInputs; i++)
        scanf("%f", &inputs[i]);

    /* Calcula os intervalos*/
    for (int i = 0; i < nrInputs; i++)
    {
        intervalos[i].min = maiorAnterior(inputs[i]);
        intervalos[i].max = menorPosterior(inputs[i]);
    }

    printf("-------------\n%.20g\n%.20g\n%.20g\n\n%.20g\n%.20g\n", inputs[0],intervalos[0].min, intervalos[0].max, nextafterf(inputs[0],inputs[0]-1),nextafterf(inputs[0],inputs[0]+1));

    printf("\n%.20g\n",maiorAnterior(intervalos[0].max));
    printf("\n%.20g\n",menorPosterior(intervalos[0].min));
    
    
    return 0;
}

