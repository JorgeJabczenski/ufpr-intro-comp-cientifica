/*  Jorge Lucas Vicilli Jabczenski  */
/*              jlvj19              */
/*            GRR20190372           */
/*             14/5/2021            */
/* Exercício 1 - Análise Intervalar */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include <fenv.h>

#define DEBUG 

#pragma STDC FENV_ACCESS

/**************************************************/
/*                     STRUCS                     */
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

/**************************************************/
/*                    OPERAÇÕES                   */
/**************************************************/
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

/* MÍNIMO DE 4 */
float
min4(float n1, float n2, float n3, float n4)
{
    return fminf(fminf(n1,n2), fminf(n3,n4));
}

/* MÁXIMO DE 4 */
float
max4(float n1, float n2, float n3, float n4)
{
    return fmaxf(fmaxf(n1,n2), fmaxf(n3,n4));
}

/* SOMA */
intervalo_t
soma(intervalo_t i1, intervalo_t i2)
{
    intervalo_t resultado;
    float somaMin, somaMax;

    somaMin = i1.min + i2.min;
    somaMax = i1.max + i2.max;
    
    resultado.min = maiorAnterior(somaMin);
    resultado.max = menorPosterior(somaMax);

    return resultado;
}

/* SUBTRAÇÃO */
intervalo_t
subtacao(intervalo_t i1, intervalo_t i2)
{
    intervalo_t resultado;
    float subMin, subMax;

    subMin = i1.min - i2.max;
    subMax = i1.max - i2.min;

    resultado.min = maiorAnterior(subMin);
    resultado.max = menorPosterior(subMax);

    return resultado;
}

/* MULTIPLICAÇÃO */
intervalo_t
multiplicacao(intervalo_t i1, intervalo_t i2)
{
    intervalo_t resultado;
    float resMin, resMax;

    resMin = min4(i1.min*i2.min, i1.min*i2.max, i1.max*i2.min, i1.max*i2.max);
    resMax = max4(i1.min*i2.min, i1.min*i2.max, i1.max*i2.min, i1.max*i2.max);

    resultado.min = maiorAnterior(resMin);
    resultado.max = menorPosterior(resMax);
    
    return resultado;
}

/* DIVISÃO */
/* TO-DO */

/**************************************************/
/*                      MAIN                      */
/**************************************************/
int
main()
{
    /* Variáveis */
    int nrInputs, nrOperacoes;
    float *inputs;
    intervalo_t *intervalos;
    conta_t *contas;

    /**************************************/
    /* Le a quandiade de inputs e operações */
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

    /* Lê todas as operações */
    // for (int i = 0; i < nrOperacoes; i++)
    //     scanf("%f", &contas[i]);

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

