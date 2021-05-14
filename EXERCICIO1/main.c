/*  Jorge Lucas Vicilli Jabczenski  */
/*            GRR20190372           */
/*             14/05/2021           */
/* Exercício 1 - Análise Intervalar */

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#pragma STDC FENV_ACCESS ON

/* Menor ou igual número representavel */


/* Maior ou igual número representavel */

/* Representar um número como IEE754   */

/* Tipo de estrutura para representar um intervalo */
typedef struct 
intervalo
{
    float min;
    float max;
} intervalo_t;

int
main()
{
    /* Variáveis */
    int nrInputs, nrOperacoes;
    float *inputs;
    intervalo_t *intervalos;



    scanf("%d\n%d", &nrInputs, &nrOperacoes);

    
    /* Aloca espaço necessário para os inputs e suas representações em intervalos */
    inputs = (float *) malloc (nrInputs * sizeof(float));
    intervalos = (intervalo_t*) malloc (nrInputs * sizeof(intervalo_t));

    for (int i = 0; i < nrInputs; i++)
        scanf("%f", &inputs[i]);

    intervalos[0].max = (float) nextafter(inputs[0],inputs[0]+1);
    
    
    for (int i = 0; i < nrInputs; i++) printf("%.100f ", inputs[i]);
    putchar('\n');
    printf("%.100f", intervalos[0].max);
    putchar('\n');
    printf("%.100f", nextafter(inputs[0], inputs[0]-1));
    putchar('\n');

    if (nextafter(inputs[0], inputs[0]-1) == (nextafter(inputs[0],inputs[0]+1)))
    {
        printf("iguais\n");
    } else {
        printf("nao\n");
    }

    printf("Inputs: %d | Operacoes: %d\n", nrInputs, nrOperacoes);


    return 0;
}

