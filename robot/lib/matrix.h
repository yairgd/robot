/*
 * =====================================================================================
 *
 *       Filename:  matrix.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/02/2023 06:51:50 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef MATRIX_H
#define MATRIX_H
struct vec3 
{
	double  x,y,z;
};



struct matrix {
	double *data;
	int m,n;
};
struct matrix  * matrix_init(int m, int n) ;
struct matrix * matrix_transpose(struct matrix  *mat) ;
struct matrix  * matrix_transpose(struct matrix  *mat) ;
struct matrix * matrix_mul(struct matrix  *a, struct matrix  *b);
void matrix_free(struct matrix  *matrix);
void matrix_dump(struct matrix  *matrix);
//struct matrix  *  matrix_inv(struct matrix  *matrix);
int matrix_inv(struct matrix  *matrix);

struct matrix  *  matrix_rotation_z(double gama);
struct matrix  *  matrix_diag(int m);
struct matrix  *  matrix_translation_z(double gama, double link);
struct matrix  *  matrix_rotation_x(double gama);
struct matrix  *  matrix_rotation_y(double beta);
struct matrix  *  matrix_rotation_z(double alpha);
struct matrix  *  matrix_copy(struct matrix *matrix);

struct matrix * matrix_pseudo_inv(struct matrix *matrix) ;
#define MAT(mat,mm,nn) (&mat->data[(mm)*(mat->n) + (nn)])

#endif
