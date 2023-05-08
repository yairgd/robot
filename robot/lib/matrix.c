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
#include <math.h>

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
	memset (mat->data, 0 ,sizeof(double)*m*n);
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
 * @return diagonal matix 
 */
struct matrix  *  matrix_diag(int m)
{
#define MIN(a,b) ((a)<(b) ? (a) : (b))
	struct matrix  *matrix = matrix_init(m,m);
	
	memset (matrix->data, 0, m * m);
	for (int i = 0; i < m ; i++) {
		*MAT(matrix,i,i) = 1;
	}
	return matrix;
}


/**
 * Created  05/07/2023
 * @brief   returns rotation matix around  z axis
 * @param   gama rotation angle around z
 * @return  
 */
struct matrix  *  matrix_rotation_z(double gama)
{
	struct matrix  *matrix = matrix_diag(3);
	*MAT(matrix,0,0) = cos(gama); *MAT(matrix,0,1) = -sin(gama);
	*MAT(matrix,1,0) = sin(gama); *MAT(matrix,1,1) =  cos(gama);	
	return matrix;
}


/**
 * Created  05/07/2023
 * @brief   returns rotation matix around y axis
 * @param   gama rotation angle around y
 * @return  
 */
struct matrix  *  matrix_rotation_y(double beta)
{
	struct matrix  *matrix = matrix_diag(3);
	*MAT(matrix,0,0) =  cos(beta); *MAT(matrix,0,2) =  sin(beta);
	*MAT(matrix,2,0) = -sin(beta); *MAT(matrix,2,2) =  cos(beta);	
	return matrix;
}


/**
 * Created  05/07/2023
 * @brief   returns rotation matix around y axis
 * @param   gama rotation angle around y
 * @return  
 */
struct matrix  *  matrix_rotation_x(double alpha)
{
	struct matrix  *matrix = matrix_diag(3);
	*MAT(matrix,1,1) = cos(alpha); *MAT(matrix,1,2) = -sin(alpha);
	*MAT(matrix,2,1) = sin(alpha); *MAT(matrix,2,2) =  cos(alpha);
	return matrix;
}


/**
 * Created  05/07/2023
 * @brief   roation and traslation matrix
 * @param   rpy - ray, yaw pitch angles
 * @return  
 */
struct matrix  *  matrix_translation_z(double gama, double link)
{
	int i,j;
	struct matrix  * h = matrix_diag(4);
	struct matrix  * rot_z = matrix_rotation_z(gama);

	/* copy the roation matirx */
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			*MAT(h,i,j) = *MAT(rot_z,i,j);
		}
	}

	/* copy translation vector */
	*MAT(h, 0,3) = link * cos(gama);
	*MAT(h, 1,3) = link * sin(gama);
	*MAT(h, 2,3) = 0;

	matrix_free(rot_z);
	return h;
}


#if 0
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

	//dgetri_(&n, &nrhs, A, &lda, ipiv, x, &ldb, &info);

	//dgetri_(&n, &A, &lda, &ipiv, x, &ldb, info);



	//	int dgetri_(integer *n, doublereal *a, integer *lda, integer 
	//	*ipiv, doublereal *work, integer *lwork, integer *info)

	if(info == 0) {
		// inversion on
	} else {
		// error
	}

	return matrix_i;
}

#else

int matrix_inv(struct matrix  *matrix) {
	struct matrix  *matrix_i =  matrix_init(matrix->n,matrix->m);
	integer N = matrix->n;
	integer * IPIV = malloc (sizeof (int) * N);
	integer LWORK = N*N;
	doublereal *WORK = malloc (sizeof (double) * LWORK);
	integer INFO;
	doublereal *WORK1 = malloc (sizeof (double) * LWORK);
	doublereal *A = matrix->data;

	dgetrf_(&N,&N,A,&N,IPIV,&INFO,WORK1);
	dgetri_(&N,A,&N,IPIV,WORK,&LWORK,&INFO);
	return INFO;
}

#endif


/**
 * Created  05/03/2023
 * @brief   calculate pseudo invers of a -> a=inv(a'*a)*a
 * @param   matrix to inverse 
 * @return  matrix_pseudo_inv pseudo inverse matrix
 */
struct matrix * matrix_pseudo_inv(struct matrix *matrix) {	
	struct matrix * matrix_t = matrix_transpose (matrix); // matrix_transpose = tranpose of matrix	
	struct matrix * matrix_m = matrix_mul(matrix_t,matrix);  // matrix_mul = matrix_transpose * matrix
								 //struct matrix  * matrix_i =  matrix_inv (matrix_m); // matrix_i = inv(matrix_mul)
	int ok = matrix_inv (matrix_m); // -> matrix_m = inv(matrix_m)
	struct matrix * matrix_pseudo_inv =  matrix_mul (matrix_m,matrix_t); // matrix_i = inv(matrix_mul)

	//matrix_free(matrix_i);
	matrix_free(matrix_t);
	matrix_free(matrix_m);

	return matrix_pseudo_inv;

}


struct matrix  *  matrix_copy(struct matrix *matrix)
{
	struct matrix  *new_matrix = matrix_init(matrix->n, matrix->m);
	for (int m = 0; m < matrix->m; m++) {
		for (int n = 0; n < matrix->n; n++) {
			*MAT(new_matrix, n, m) = *MAT(matrix, n,m);
		}
	}
	return new_matrix;
}


