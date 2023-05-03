/*
 * =====================================================================================
 *
 *       Filename:  matrix.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/02/2023 06:52:00 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "clapack.h"

/**
 * Created  05/02/2023
 * @brief   initilize new matrix data structure
 * @param   
 * @return  
 */
struct matrix  * matrix_init(int m, int n) {
	struct matrix *mat = malloc(sizeof (struct matrix));
	mat->n = n;
	mat->m = m;
	mat->data = malloc(sizeof(double)*m*n);
	return mat;
}


/**
 * Created  05/02/2023
 * @brief   release memory of matrix
 * @param   
 * @return  
 */
void matrix_free(struct matrix  *matrix) {
	free(matrix->data);
	free(matrix);
}


/**
 * Created  05/02/2023
 * @brief   claclaues matrix multiplication  -> c = a*b 
 * It is reposisble of the caller of this function to verify 
 * the size of the data to prevent memory leaks
 * @param   
 * @return  
 */
struct matrix * matrix_mul(struct matrix  *a, struct matrix  *b) {
	struct matrix  *c = matrix_init(a->m,b->n);

	memset (c->data, 0 ,c->n * c->m);
	// multiply matrices
	for (int i = 0; i < a->m; i++) {
		for (int j = 0; j < b->n; j++) {
			for (int k = 0; k < a->n; k++) {
				*MAT(c, i,j)  += *MAT(a,i,k) * *MAT(b,k,j);
			}
		}
	}
	return c;

}

/**
 * Created  05/02/2023
 * @brief   claclaues transpose of matrix  -> mat_t = mat'
 * It is reposisble of the caller of this function to verify 
 * the size of the data to prevent memory leaks
 * @param  mat matrix to transpose
 * @param mat_t the tranposed matrix
 * @return  
 */
struct matrix  * matrix_transpose(struct matrix  *mat) {
	struct matrix  *mat_t = matrix_init(mat->n,mat->m);
	
	for (int m=0; m < mat->m; m++) 
		for (int n=0; n<mat->n; n++) 
			*MAT(mat_t,n,m) = *MAT(mat,m,n);
	return mat_t;

}


/**
 * Created  05/02/2023
 * @brief   print matrix contet to stdout
 * @param   
 * @return  
 */
void matrix_dump(struct matrix  *matrix)
{
	printf ("matix size: (%d, %d)\n----------\n",matrix->m, matrix->n); 

	for (int m =0; m< matrix->m;m++) {
		for (int n =0;n<matrix->n;n++) {
			printf ("%f",*MAT(matrix,m,n));
			if (n < matrix->n-1)
				printf (",");
		}
		printf("\n");
	}

}


/**
 * Created  05/03/2023
 * @brief   creates  diagonal and unit matrix
 * @param   
 * @return  
 */
void matrix_diag(struct matrix  *matrix)
{
#define MIN(a,b) ((a)<(b) ? (a) : (b))
	memset (matrix->data, 0, matrix->n * matrix->m);
	for (int i = 0; i < MIN(matrix->n,matrix->m) ; i++) {
		*MAT(matrix,i,i) = 1;
	}

}

/**
 * Created  05/03/2023
 * @brief   invers matrix using lapck functions
 * @param   
 * @return  
 */
struct matrix  * matrix_inv(struct matrix  *matrix) {
	struct matrix  *matrix_i =  matrix_init(matrix->n,matrix->m);
	doublereal *A = matrix->data ; // Matrix to be inverted
	doublereal *b = matrix_i->data; // Right-hand side of the linear system - It will be initilized as disangonal and unit matrix
	doublereal x[256]; // Solution to the linear system
	integer n = matrix->n; // Dimension of the matrix
	integer ipiv[256], info; // ipiv is pivot indices, info is to store status
	integer lda = n, ldb = n, nrhs = n; // Leading dimensions of A and b

	struct matrix  diag;
	diag.n = n;
	diag.m = n;
	diag.data = b;
	matrix_diag(&diag);

	// Solve the linear system of equations Ax=b
	// to resolve the inverse matix A we need to solve: A*B=I where B  should be the inverse of A
	// and I is a unit matrix
	dgesv_(&n, &nrhs, A, &lda, ipiv, b, &ldb, &info);

	if(info == 0) {
		// inversion on
	} else {
		// error
	}

	return matrix_i;
}


/**
 * Created  05/03/2023
 * @brief   calculate pseudo invers of a -> a=inv(a'*a)*a
 * @param   matrix to inverse 
 * @return  matrix_pseudo_inv pseudo inverse matrix
 */
struct matrix * matrix_pseudo_inv(struct matrix *matrix) {	
	struct matrix * matrix_t = matrix_transpose (matrix); // matrix_transpose = tranpose of matrix	
	struct matrix * matrix_m = matrix_mul(matrix_t,matrix);  // matrix_mul = matrix_transpose * matrix
	struct matrix  * matrix_i =  matrix_inv (matrix_m); // matrix_i = inv(matrix_mul)
	struct matrix * matrix_pseudo_inv =  matrix_mul (matrix_i,matrix_t); // matrix_i = inv(matrix_mul)

	matrix_free(matrix_i);
	matrix_free(matrix_t);
	matrix_free(matrix_m);

	return matrix_pseudo_inv;

}
