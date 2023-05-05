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
	*MAT(jacobian,2,0) = 1;
	*MAT(jacobian,2,1) = 1;
	*MAT(jacobian,2,2) = 1;

}









#define pi 3.141592653589793

double rad2deg(double radians) {

	radians = radians - 2*pi*floor(radians/(2*pi));


	//radians = radians/2*3.141592653589793 - (int)(radians/2*3.141592653589793);
	//double deg = radians * (180/3.141592653589793);
	//return ((int)deg) %360;
	return radians;
}


void ik_cost_gradient_func_analytic(double *phi,double *links, double *des_xyz,double *grad) {
	double phi0 = phi[0];
	double phi1 = phi[1];
	double phi2 = phi[2];
	double l0=links[0];
	double l1=links[1];
	double l2=links[2];
	double x = des_xyz[0];
	double y = des_xyz[1];
	double z = des_xyz[2];

	grad[0] =  (2.0*l0*sin(phi0) + 2.0*l1*sin(phi0)*cos(phi1) + 2.0*l1*sin(phi1)*cos(phi0) - 2*l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x) + (-2.0*l0*cos(phi0) + 2.0*l1*sin(phi0)*sin(phi1) - 2.0*l1*cos(phi0)*cos(phi1) - 2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y);
	grad[1] = (2.0*l1*sin(phi0)*sin(phi1) - 2.0*l1*cos(phi0)*cos(phi1) - 2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y) + (2.0*l1*sin(phi0)*cos(phi1) + 2.0*l1*sin(phi1)*cos(phi0) - 2*l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x);
	grad[2] = (2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x) + (-2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + 2*l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y);

}






void calc_grdient_decent(double *phi,double *links, double *des_xyz,double alpha) {

	double grad[3]; // will be taken from autogenerated frnction
	double norm;
	double xyz_new[3] = {0,0,0};
	while (1) {
		ik_cost_gradient_func_analytic(phi,links, des_xyz,grad);
		norm = 0;
		for (int i=0;i<3;i++) {
			phi[i] = phi[i] - grad[i]*alpha;
			if (phi[i] <0.0 || phi[i]>0.7853981633974483)
				phi[i] = phi[i] + grad[i]*alpha;
			norm += (des_xyz[i]-xyz_new[i])*(des_xyz[i]-xyz_new[i]);
		}
		norm = sqrtf(norm);
		if (norm < 0.001)
			break;
		endeffector_location(links,phi,xyz_new);

		printf ("%lf %lf %lf %lf %lf %lf %lf\n", xyz_new[0], xyz_new[1], xyz_new[2], rad2deg(phi[0]), rad2deg(phi[1]), rad2deg(phi[2]), (xyz_new[0]-des_xyz[0]) * (xyz_new[0]-des_xyz[0])  + (xyz_new[1]-des_xyz[1]) * (xyz_new[1]-des_xyz[1]) );		
	}
}


/**
 * Created  05/02/2023
 * @brief   IK solver using Jacobian pseudoinverse
 * @param   
 * @return  
 */
void  jacobian_pseudoinverse_optimization(double *phi,double *links, double *des_xyz,int len,double alpha) {
	//set_inital_phi(phi, len);
	double xyz_new[] ={0,0,0};

	struct matrix *jacobian = matrix_init(3,3);
	double norm;

	int k=10000;
	while (k>0) {
		endeffector_location(links,phi,xyz_new);
		ik_jacobian_func_analytic(links,phi, jacobian);
		struct matrix * diff_xyz = matrix_init(3,1);
		diff_xyz->data[0] = des_xyz[0] - xyz_new[0];
		diff_xyz->data[1] = des_xyz[1] - xyz_new[1];
		diff_xyz->data[2] = des_xyz[2] - xyz_new[2];

		struct matrix * pseudo_inv  = matrix_pseudo_inv(jacobian);

		struct matrix * delta = matrix_mul(pseudo_inv, diff_xyz);

		norm = 0;
		for (int i=0;i<3;i++) {
			phi[i] = phi[i] + alpha * delta->data[i];
			if (  phi[i]>0.7853981633974483)
				phi[i] = phi[i] - alpha * delta->data[i];
			norm += (des_xyz[i]-xyz_new[i])*(des_xyz[i]-xyz_new[i]);
		}
		norm = sqrtf(norm);

#if 0
		if ((phi[0] + alpha * delta->data[0])<0.7853981633974483 && (phi[0] + alpha * delta->data[0])>0 ) phi[0] = phi[0] + alpha * delta->data[0];
		if ((phi[1] + alpha * delta->data[1])<0.7853981633974483 && (phi[1] + alpha * delta->data[1])>0 ) phi[1] = phi[1] + alpha * delta->data[1];
		phi[2] = phi[2] + alpha * delta->data[2];
		//if ((phi[2] + alpha * delta->data[2])<0.7853981633974483 && (phi[2] + alpha * delta->data[2])>0 ) phi[2] = phi[2] + alpha * delta->data[2];

		//phi[0] =phi[0] + alpha * delta->data[0];
		//phi[1] =phi[1] + alpha * delta->data[1];
		printf ("%lf %lf %lf %lf %lf %lf %lf\n", xyz[0], xyz[1], xyz[2], rad2deg(phi[0]), rad2deg(phi[1]), rad2deg(phi[2]), (xyz[0]-des_xyz[0]) * (xyz[0]-des_xyz[0])  + (xyz[1]-des_xyz[1]) * (xyz[1]-des_xyz[1]) );
#endif
		matrix_free(diff_xyz);
		matrix_free(pseudo_inv);
#if 0
		if ( sqrtf( (xyz[0]-des_xyz[0]) * (xyz[0]-des_xyz[0])  + (xyz[1]-des_xyz[1]) * (xyz[1]-des_xyz[1]))  < 0.0000001)
			break;
#endif
		printf ("%lf %lf %lf %lf %lf %lf %lf\n", xyz_new[0], xyz_new[1], xyz_new[2], rad2deg(phi[0]), rad2deg(phi[1]), rad2deg(phi[2]), norm );

		if (norm < 0.0001)
			break;

	}


}




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

