#ifndef __AUXLIB__
#define __AUXLIB__

/* Número máximo de iterações em métodos iterativos */
#define MAXIT   50  

typedef struct {
	int n;         /* Tamanho do SL        */
	double erro;   /* Critério de Parada   */
	double **A;    /* Coeficientes         */ 
	double *b;     /* Termos Independentes */
} SistLinear_t;


typedef struct {
    int n;
    double *D, *Di, *Ds, *B;
} SL_Tridiag;


typedef struct{
    int n;               /* Nr de pontos internos */
    double a, b;         /* Intervalo             */
    double ya, yb;       /* Contorno              */
    double (*p)(double); /**/
    double (*q)(double); /**/
    double (*r)(double); /**/
} EDO;

/* Alocação e desalocação de memória */
SistLinear_t* alocaSistLinear (int n);
void liberaSistLinear (SistLinear_t *SL);

SL_Tridiag *alocaSLTridiag(int n);
void liberaSLTridiag(SL_Tridiag *SL);



void gaussSeidelEDO (EDO *edo, double *Y);

#endif