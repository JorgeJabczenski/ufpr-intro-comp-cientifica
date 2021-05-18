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
#include <stdint.h>

#define DEBUG 

#pragma STDC FENV_ACCESS

/**************************************************/
/*                     STRUCS                     */
/**************************************************/

/* Representar um número como IEE754   */

/* Tipo de estrutura para representar um intervalo */
typedef struct 
{
    float min;
    float max;
} intervalo_t;

typedef union
{
    int32_t i;
    // int sinal = 0b10000000000000000000000000000000 | i;
    float f;
    struct
    {
        uint32_t mantissa : 23;
        uint32_t exponent : 8;
        uint32_t sign : 1;
    } parts;
} Float_t;


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
subtracao(intervalo_t i1, intervalo_t i2)
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
intervalo_t
divisao(intervalo_t i1, intervalo_t i2)
{
    intervalo_t resultado;

    if (i2.min != 0 && i1.max != 0){

        resultado.min = maiorAnterior (min4(i1.min/i2.min, i1.min/i2.max, i1.max/i2.min, i1.max/i2.max));
        resultado.max = menorPosterior(max4(i1.min/i2.min, i1.min/i2.max, i1.max/i2.min, i1.max/i2.max));
    }

    return resultado;

}

/* Confere se o intervalo é unitário (min == max) ou não (min < max) ou inválido (min > max)*/
int
isUnitario(intervalo_t intervalo)
{
    Float_t min, max;
    int sinalMin, sinalMax, ulps;

    min.f = intervalo.min;
    max.f = intervalo.max;

    // printf("sinais---- -> %d %d\n" ,sinalMin, sinalMin);

    // printf("min: %c | max: %c\n", (sinalMin)?'-':'+', (sinalMax)?'-':'+');
    if (min.parts.sign != max.parts.sign) return 0;
    
    switch (min.parts.sign){
        case 0:
            printf("%d | %d\n", min.i, max.i);
            if(min.i < max.i) return 0;
        break;

        case 1:
            printf("negativo: %d | %d\n", min.i, max.i);
            if (min.i > max.i) return 0;
        break;
    }

    return 1;
}

/**************************************************/
/*                      MAIN                      */
/**************************************************/
int
main()
{
    /* Variáveis */
    int nrInputs, nrOperacoes;
    intervalo_t *intervalos;

    /**************************************/
    /* Le a quantidade de inputs e operações */
    scanf("%d\n%d\n", &nrInputs, &nrOperacoes);

    /* 
    Aloca espaço necessário para os inputs, suas representações em intervalos,
    contas e resultados
    */
    intervalos = (intervalo_t*) malloc ((nrInputs + nrOperacoes) * sizeof(intervalo_t));

    /* Lê todas as entradas, já calculando os intervalos */
    for (int i = 0; i < nrInputs; i++)
    {
        int indice;
        float entrada;
        scanf("%*c %d %f\n",&indice, &entrada);

        //printf("---> %d | %1.8e\n", indice, entrada);

        intervalos[indice-1].min = maiorAnterior(entrada);
        intervalos[indice-1].max = menorPosterior(entrada);
    }

    /* Lê todas as operações */
    for (int i = 0; i < nrOperacoes; i++)
    {
        int indice1, indice2, destino;
        char op;
        //scanf("%s %*c %s %c %s", contas[i].dest, contas[i].rot1, &contas[i].op, contas[i].rot2);
        scanf("%*c %d %*c %*c %d %c %*c %d\n",&destino, &indice1, &op, &indice2);
        
        intervalo_t resultado;
        
        switch(op)
        {
            case '+':
                resultado = soma(intervalos[indice1-1], intervalos[indice2-1]);
            break;

            case '-':
                resultado = subtracao(intervalos[indice1-1], intervalos[indice2-1]);
            break;

            case '*':
            resultado = multiplicacao(intervalos[indice1-1], intervalos[indice2-1]);
            break;

            case '/':
            resultado = divisao(intervalos[indice1-1], intervalos[indice2-1]);
            break;
        }

        //printf("%d = %d %c %d\n",destino, indice1, op, indice2);        
        intervalos[destino-1] = resultado;


    }

    /* Imprime os intervalos */
    for(int i = 0; i < nrInputs + nrOperacoes; i++)
    {
        printf("X%d = [     % 1.8e,      % 1.8e]\n",i+1, intervalos[i].min, intervalos[i].max);
    }


    /* Confere se as contas resultaram em intervalos unitários ou não */
    printf("\nNão unitários:\n");
    for (int i = 0; i < nrOperacoes; i++)
    {
        if (!isUnitario(intervalos[nrInputs+i]))
        {
            printf("X%d = [     % 1.8e,      % 1.8e]\n",nrInputs+i+1, intervalos[nrInputs+i].min, intervalos[nrInputs+i].max);
        }
    }



    return 0;
}

