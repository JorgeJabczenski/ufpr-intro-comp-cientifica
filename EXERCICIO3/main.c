/****************************************/
/* Exercício 3 : EDO e EDP              */
/* Autor       : Jorge L. V. Jabczenski */
/*             : jlvj19                 */
/*             : GRR20190372            */
/* Data        : 08/06/2021             */
/****************************************/

#include <stdio.h>
#include "auxlib.h"

#define N1  5
#define N2 10

/* Item A */
double p_a(double x){ return 0; }
double q_a(double x){ return 0; }
double r_a(double x){ return ((6*x) - ((x*x)/2)); }

/* Item B */

/* Item C */
double p_c(double x){ return 0; }
double q_c(double x){ return 1; }
double r_c(double x){ return 0; }

/* Item D */



int
main()
{
    /***********************************************/
    /*                      A                      */
    /***********************************************/

    EDO edo_a;
    double Y1_a[N1], Y2_a[N2];
    
    edo_a.n  = N1;
    edo_a.a  =  0;
    edo_a.b  = 12;
    edo_a.ya =  0;
    edo_a.yb =  0;
    edo_a.p  = &p_a;
    edo_a.q  = &q_a;
    edo_a.r  = &r_a;

    printf("*************************\n");
    printf(">>  Item (A) : N = 5   <<\n");
    gaussSeidelEDO(&edo_a, Y1_a);
    printf("\n\n");

    printf(">>  Item (A) : N = 10  <<\n");
    edo_a.n  = N2;
    gaussSeidelEDO(&edo_a, Y2_a);
    printf("\n");

    printf(" ~~~ FIM DO ITEM (A) ~~~ \n\n\n");

    /***********************************************/
    /*                      B                      */
    /***********************************************/

    /***********************************************/
    /*                      C                      */
    /***********************************************/
    EDO edo_c;
    double Y1_c[N1], Y2_c[N2];
    
    edo_c.n  = N1;
    edo_c.a  =  0;
    edo_c.b  =  1;
    edo_c.ya =  0;
    edo_c.yb =  1;
    edo_c.p  = &p_c;
    edo_c.q  = &q_c;
    edo_c.r  = &r_c;

    printf("*************************\n");
    printf(">>  Item (C) : N = 5   <<\n");
    gaussSeidelEDO(&edo_c, Y1_c);
    printf("\n\n");

    printf(">>  Item (C) : N = 10  <<\n");
    edo_c.n  = N2;
    gaussSeidelEDO(&edo_c, Y2_c);
    printf("\n");

    printf(" ~~~ FIM DO ITEM (C) ~~~ \n\n\n");

    /***********************************************/
    /*                      D                      */
    /***********************************************/



    return 0;
}