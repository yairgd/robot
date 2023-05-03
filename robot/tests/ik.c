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

#include "matrix.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>


/**
 * Created  05/02/2023
 * @brief  auto generated function - calclautes the end effector position 
 * @param   
 * @return  
 */
void endeffector_location(double *links,double *phi,double *xyz) {
	double phi0 = phi[0];
	double phi1 = phi[1];
	double phi2 = phi[2];
	double l0=links[0];
	double l1=links[1];
	double l2=links[2];

	xyz[0] = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	xyz[1] = 1.0*l0*sin(phi0) + 1.0*l1*sin(phi0)*cos(phi1) + 1.0*l1*sin(phi1)*cos(phi0) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	xyz[2] = 0;



}

/**
 * Created  05/02/2023
 * @brief   auto generated function - it calculates the jacobian
 * @param   
 * @return  
 */
void ik_jacobian_func_analytic(double *links,double *phi, struct matrix *jacobian) { // double J[3][3]) {
	double phi0 = phi[0];
	double phi1 = phi[1];
	double phi2 = phi[2];
	double l0=links[0];
	double l1=links[1];
	double l2=links[2];

	*MAT(jacobian,0,0) = -1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	*MAT(jacobian,0,1) = -1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	*MAT(jacobian,0,2) = -l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	*MAT(jacobian,1,0) = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	*MAT(jacobian,1,1) = -1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	*MAT(jacobian,1,2) = l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	*MAT(jacobian,2,0)= 1;
	*MAT(jacobian,2,1) = 1;
	*MAT(jacobian,2,2) = 1;

}







/**
 * Created  05/02/2023
 * @brief   sets initial value for phi for IK solver
 * @param   
 * @return  
 */
void set_inital_phi(double *phi, int len) {
	for (int i = 0;i < len;i++) 
		phi[i] = 0.0001;
}



/**
 * Created  05/02/2023
 * @brief   IK solver using Jacobian pseudoinverse
 * @param   
 * @return  
 */
void  jacobian_pseudoinverse_optimization(double *phi,double *links, double *des_xyz,int len) {
	set_inital_phi(phi, len);
	double xyz[] ={0,0,0};
	double delta[3];

	struct matrix *jacobian = matrix_init(3,3);
	struct matrix *jacobian_t = matrix_init(3,3);

	while (1) {
		endeffector_location(links,phi,xyz);
		ik_jacobian_func_analytic(links,phi, jacobian);
		//matrix_transpose(jacobian, jacobian_t);

		break;

	}


}




#define N 3

//gcc ik_optim.c matrix.c -o ik_optim -lm -O0 -g
int main() {

	double des_xy[] = { 8.411930818340064, 7.603239324984113,0};
	double links[]={7.0,4,2};
	double phi[] = {0,0,0};


	 double A[4*3] = {1, 2, 3, 4, 5, 6, 7, 8, 10,11,12,13}; // Matrix to be inverted
						      

	struct matrix  *matrix = matrix_init(4,3);
	
	memcpy (matrix->data, A, 4*3*sizeof(double));

	struct matrix * pseudo_inv  = matrix_pseudo_inv(matrix);

	matrix_dump (pseudo_inv);





    
	jacobian_pseudoinverse_optimization(phi, links, des_xy,3);


	return 0;
}

