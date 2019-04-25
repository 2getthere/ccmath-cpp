/*  rmmult.c    CCMATH mathematics library source code.
 *
 *  Copyright (C)  2000   Daniel A. Atkinson    All rights reserved.
 *  This code may be redistributed under the terms of the GNU library
 *  public license (LGPL). ( See the lgpl.license file for details.)
 * ------------------------------------------------------------------------
 *	C++-ified by renej
 */
#include <stdlib.h>
#include "array_storage.hh"
void rmmult(double *rm,const double *a,const double *b,int n,int m,int l)
{ double z,*q; const double *p; int i,j,k;
  array_storage<double> q0_storage(m);
  double *q0 = q0_storage.array();
  for(i=0; i<l ;++i,++rm){
    for(k=0,p=b+i; k<m ;p+=l) q0[k++]= *p;
    for(j=0,p=a,q=rm; j<n ;++j,q+=l){
      for(k=0,z=0.; k<m ;) z+= *p++ * q0[k++];
      *q=z;
     }
   }
}
