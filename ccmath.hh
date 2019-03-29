#ifndef _ccmath_HH_
#define _ccmath_HH_

/*  ccmath.h    CCMATH mathematics library source code.
 *
 *  Copyright (C)  2000   Daniel A. Atkinson    All rights reserved.
 *  This code may be redistributed under the terms of the GNU library
 *  public license (LGPL). ( See the lgpl.license file for details.)
 * ------------------------------------------------------------------------
 *	C++-ified by renej
 *  C++-ified by lab
 *	Documentation copied by RKR from ccmath-2.2.1/manual/C01-matrix
 */


/**
     Invert (in place) a general real matrix A -> Inv(A).

     int minv(double a[],int n)
       a = array containing the input matrix A
           This is converted to the inverse matrix.
       n = dimension of the system (i.e. A is n x n )
      return: 0 -> normal exit
              1 -> singular input matrix
*/
int minv(double * a, int n);

/**
     Invert (in place) a symmetric real matrix, V -> Inv(V).

     int psinv(double v[],int n)
       v = array containing a symmetric input matrix
           This is converted to the inverse matrix.
       n = dimension of the system (dim(v)=n*n)
      return: 0 -> normal exit
              1 -> input matrix not positive definite

           The input matrix V is symmetric (V[i,j] = V[j,i]).
*/
int psinv(double *v,int n);

/**
     Compute the inner product of two real vectors, p = u~*v.

     double vnrm(double *u,double *v,int n)
       u = pointer to array of input vector u
       v = pointer to array of input vector v
       n = dimension (dim(u)=dim(v)=n)
      return value: p = u~*v (dot product of u and v)
*/
double vnrm(const double * u, const double * v, int n);

/**
     Multiply a vector by a matrix Vp = Mat*V.

     void vmul(double *vp,double *mat,double *v,int n)
       vp = pointer to array containing output vector
       mat = pointer to array containing input matrix in row order
       v = pointer to array containing input vector
       n = dimension of vectors (mat is n by n)
*/
void vmul(double *vp,const double *mat,const double *v,int n);

/**
     Transpose a real square matrix in place A -> A~.

     void trnm(double *a,int n)
       a = pointer to array of n by n input matrix A
           This is overloaded by the transpose of A.
       n = dimension (dim(a)=n*n)
*/
void trnm(double *a,int n);

/**
     Multiply two matrices Mat = A*B.

     void rmmult(double *mat,double *a,double *b,int m,int k,int n)
     double mat[],a[],b[]; int m,k,n;
       mat = array containing m by n product matrix at exit
       a = input array containing m by k matrix
       b = input array containing k by n matrix
            (all matrices stored in row order)
       m,k,n = dimension parameters of arrays
*/
void rmmult(double *rm,const double *a,const double *b,int n,int m,int l);

/**
     Transpose an m by n matrix A = B~.

     void mattr(double *a,double *b,int m,int n)
       a = pointer to array containing output n by m matrix 
       b = pointer to array containing input m by n matrix
            (matrices stored in row order)
       m,n = dimension parameters (dim(a)=dim(b)=n*m)
 */
void mattr(double *a,const double *b,int m,int n);

/**
     Compute the singular values of a real m by n matrix A.

     int svdval(double *d,double *a,int m,int n)
       d = pointer to double array of dimension n
           (output = singular values of A)
       a = pointer to store of the m by n input matrix A
           (A is altered by the computation)
       m = number of rows in A
       n = number of columns in A (m>=n required)
      return value: status flag with:
               0 -> success
              -1 -> input error m < n
 */
int svdval(double *d,double *a,int m,int n);

/**
    Compute the eigenvalues and eigenvectors of a real symmetric matrix A.

    void eigen(double *a,double *ev,int n)
       a = pointer to store for symmetric n by n input
           matrix A. The computation overloads this with an
           orthogonal matrix of eigenvectors E.
       ev = pointer to the array of the output eigenvalues
       n = dimension parameter (dim(a)= n*n, dim(ev)= n)

     The input and output matrices are related by

          A = E*D*E~ where D is the diagonal matrix of eigenvalues
          D[i,j] = ev[i] if i=j and 0 otherwise.

     The columns of E are the eigenvectors.

     return value: status flag with:
               0 -> success
              -1 -> input error n < 2
              -2 -> qr decomposition failed
 */
int eigen(double *a,double *ev,int n);

/*
    Compute the eigenvalues of a real symmetric matrix A.

     void eigval(double *a,double *ev,int n)
       a = pointer to array of symmetric n by n input
           matrix A. The computation alters these values.
       ev = pointer to array of the output eigenvalues
       n = dimension parameter (dim(a)= n*n, dim(ev)= n)
     return value: status flag with:
               0 -> success
              -1 -> input error n < 2
              -2 -> qr decomposition failed
*/
int eigval(double *a,double *ev,int n);

#endif /* _ccmath_HH_ */
