/*
 * =====================================================================================
 *
 *       Filename:  ik.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/03/2023 10:44:47 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "matrix.h"
#include "optim.h"



#define N 3

//gcc ik_optim.c matrix.c -o ik_optim -lm -O0 -g
int main() {

	double des_xyz[] = { 12.411930818340064, 7.603239324984113,0};
	double links[]={4.0,6.0,6.0};
	//double phi[] = {0.000000, 0.401455, 0.666982};

double phi[] = {0.000000, 0.401455, 0.666982};

//	calc_grdient_decent(phi,links, des_xyz,0.001);

	jacobian_pseudoinverse_optimization(phi, links, des_xyz,3,0.001);



	return 0;
}

