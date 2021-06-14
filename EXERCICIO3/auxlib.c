#include "auxlib.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// SistLinear_t*
// alocaSistLinear (int n)
// {
// 	SistLinear_t *SL;
// 	double **A, *b;

// 	SL = malloc(sizeof(SistLinear_t));

// 	A = (float**) malloc(sizeof(float*) * n);
// 	for (int i = 0; i < n; i++)
// 		A[i] = (float*) malloc (sizeof(float)*n);

// 	b = (float*) malloc (sizeof(float) * n);

// 	SL->A = A;
// 	SL->b = b;
// 	SL->n = n;
// 	SL->erro = 0.0;

// 	return SL;
// }

void
liberaSistLinear (SistLinear_t *SL)
{
	for (int i = 0; i < SL->n; i++)
		free(SL->A[i]);

	free(SL->A);
	free(SL->b);
	free(SL);
}
/************************************/
SL_Tridiag*
alocaSLTridiag(int n)
{
    SL_Tridiag* SL;

    SL     = malloc(sizeof(SL_Tridiag));
    SL->Ds = malloc(sizeof(double)*n);
    SL->D  = malloc(sizeof(double)*n);
    SL->Di = malloc(sizeof(double)*n);
    SL->B  = malloc(sizeof(double)*n);
    SL->n  = n;

    return SL;
}

void
liberaSLTridiag(SL_Tridiag* SLT)
{
    free (SLT->B);
    free (SLT->D);
    free (SLT->Di);
    free (SLT->Ds);
    free (SLT);
}

/************************************/

void
printTridiag(SL_Tridiag SLT)
{
    int n = SLT.n;

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if      (i ==   j) printf("% 1.1lf ", SLT.D[i]);
            else if (i == j+1) printf("% 1.1lf ", SLT.Ds[i]);
            else if (j == i+1) printf("% 1.1lf ", SLT.Di[i]);
            else               printf(" 0.0 ");
        }
        printf(" | %1.8lf\n", SLT.B[i]);
    }
}

/************************************/

double*
residuoSLTridiag(SL_Tridiag *SLT, double *Y)
{
    int n = SLT->n;

    double *res = malloc (sizeof(double) * n);

    for (int i = 0; i < n; i++){
        res[i] = SLT->B[i];
        for (int j = 0; j < n; j++){
            if      (i ==   j) res[i] -= Y[j] * SLT->D[i];
            else if (i == j+1) res[i] -= Y[j] * SLT->Ds[i];
            else if (j == i+1) res[i] -= Y[j] * SLT->Di[i];
            else               res[i] -= 0;
        }
    }
    return res;
}

void
normaL2Tridiag(SL_Tridiag *SLT, double *Y)
{
    double *residuo;
    double norma = 0;

    residuo = residuoSLTridiag(SLT, Y);

    for (int i = 0; i < SLT->n; i++)
        norma += residuo[i]*residuo[i];

    printf("Norma L2: % 1.8e\n", sqrt(norma));

    free(residuo);
}

/************************************/

void
gaussSeidelEDO (EDO *edo, double *Y)
{
    double h, xi, bi, yi, d, di, ds;
    int iteracoes;
    double tempoTotal;

    SL_Tridiag *SLT = alocaSLTridiag(edo->n);

    /* Calcula o tamanho do passo */
    h = (edo->b - edo->a) / (edo->n + 1);

    iteracoes = 0;
    tempoTotal = timestamp();
    while(iteracoes < MAXIT)
    {
        for (int i = 0; i < edo->n; i++)
        {
            xi = edo->a + (i+1)*h;     /* Valor xi da malha  */
            bi = h*h*edo->r(xi);       /* Termo independente */

            di = 1 - h*edo->p(xi)/2.0; /* Diagonal Inferior  */
            d  =-2 + h*h*edo->q(xi);   /* Diagonal Principal */
            ds = 1 + h*edo->p(xi)/2.0; /* Diagonal Superior  */

            SLT->Di[i] = di;
            SLT->D[i]  = d;
            SLT->Ds[i] = ds;
            SLT->B[i]  = bi;

            if      (i == 0)
                bi -= ds*Y[i+1] + edo->ya * (1 - h*edo->p(edo->a+h)/2.0);
            else if (i == edo->n-1)
                bi -= ds*Y[i-1] + edo->yb * (1 - h*edo->p(edo->b-h)/2.0);
            else 
                bi -=  ds*Y[i+1] + ds*Y[i-1];

            Y[i] = bi / d;
        }
        iteracoes++;
    }

    tempoTotal = timestamp() - tempoTotal;

    printTridiag(*SLT);
    normaL2Tridiag(SLT, Y);
    printf("Tempo: %1.8lf ms\n", tempoTotal);

    printf("Y: ");
    for (int i = 0; i < SLT->n; i++)
    {
        printf("%lf ", Y[i]);
    }

    liberaSLTridiag(SLT);
}