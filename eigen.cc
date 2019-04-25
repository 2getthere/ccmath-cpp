/*  eigen.c    CCMATH mathematics library source code.
 *
 *  Copyright (C)  2000   Daniel A. Atkinson    All rights reserved.
 *  This code may be redistributed under the terms of the GNU library
 *  public license (LGPL). ( See the lgpl.license file for details.)
 * ------------------------------------------------------------------------
 * C++-ified by lab
 */
#include <stdlib.h>
#include "array_storage.hh"
extern void housev(double *a,double *d,double *dp,int n);
extern int qrevec(double *ev,double *evec,double *dp,int n);
extern void trnm(double *a,int n);
int eigen(double *a,double *ev,int n)
{
    if (n < 2) return -1;

    array_storage<double> dp_storage(n);
    double *dp = dp_storage.array();

    housev(a,ev,dp,n);
    if (qrevec(ev,a,dp,n) < 0) return -2;
    trnm(a,n);
    return 0;
}
