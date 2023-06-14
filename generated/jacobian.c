/*
 * =====================================================================================
 *
 *       Filename:  jacobian_template.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/17/2023 08:32:05 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "matrix.h"
void ik_jacobian_func_analytic_1(double *links,double *phi, struct matrix *jacobian) { // double J[3][3]) {
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
void ik_jacobian_func_analytic(double *links,double *phi, struct matrix *jacobian) { 
	
	double Rz1 = phi[0];
	double Rz2 = phi[1];
	double Rz3 = phi[2];
	
	double l1 = links[0];
	double l2 = links[1];
	double l3 = links[2];

#if 1
	*MAT(jacobian,0,0)=-1.0*l1*sin(Rz1);
	*MAT(jacobian,0,1)=0;
	*MAT(jacobian,0,2)=0;
	*MAT(jacobian,1,0)=1.0*l1*cos(Rz1);
	*MAT(jacobian,1,1)=0;
	*MAT(jacobian,1,2)=0;
	*MAT(jacobian,2,0)=-1.0*l1*sin(Rz1) - 1.0*l2*sin(Rz1)*cos(Rz2) - 1.0*l2*sin(Rz2)*cos(Rz1);
	*MAT(jacobian,2,1)=-1.0*l2*sin(Rz1)*cos(Rz2) - 1.0*l2*sin(Rz2)*cos(Rz1);
	*MAT(jacobian,2,2)=0;
	*MAT(jacobian,3,0)=1.0*l1*cos(Rz1) - 1.0*l2*sin(Rz1)*sin(Rz2) + 1.0*l2*cos(Rz1)*cos(Rz2);
	*MAT(jacobian,3,1)=-1.0*l2*sin(Rz1)*sin(Rz2) + 1.0*l2*cos(Rz1)*cos(Rz2);
	*MAT(jacobian,3,2)=0;
	*MAT(jacobian,4,0)=-1.0*l1*sin(Rz1) - 1.0*l2*sin(Rz1)*cos(Rz2) - 1.0*l2*sin(Rz2)*cos(Rz1) + l3*(1.0*sin(Rz1)*sin(Rz2) - 1.0*cos(Rz1)*cos(Rz2))*sin(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*cos(Rz3);
	*MAT(jacobian,4,1)=-1.0*l2*sin(Rz1)*cos(Rz2) - 1.0*l2*sin(Rz2)*cos(Rz1) + l3*(1.0*sin(Rz1)*sin(Rz2) - 1.0*cos(Rz1)*cos(Rz2))*sin(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*cos(Rz3);
	*MAT(jacobian,4,2)=-l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*sin(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*cos(Rz3);
	*MAT(jacobian,5,0)=1.0*l1*cos(Rz1) - 1.0*l2*sin(Rz1)*sin(Rz2) + 1.0*l2*cos(Rz1)*cos(Rz2) + l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*cos(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*sin(Rz3);
	*MAT(jacobian,5,1)=-1.0*l2*sin(Rz1)*sin(Rz2) + 1.0*l2*cos(Rz1)*cos(Rz2) + l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*cos(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*sin(Rz3);
	*MAT(jacobian,5,2)=l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*cos(Rz3) - l3*(1.0*sin(Rz1)*cos(Rz2) + 1.0*sin(Rz2)*cos(Rz1))*sin(Rz3);
	*MAT(jacobian,6,0)=1;
	*MAT(jacobian,6,1)=1;
	*MAT(jacobian,6,2)=1; 

#else
	*MAT(jacobian,0,0)=-1.0*l1*sin(Rz1) - 1.0*l2*sin(Rz1)*cos(Rz2) - 1.0*l2*sin(Rz2)*cos(Rz1) + l3*(1.0*sin(Rz1)*sin(Rz2) - 1.0*cos(Rz1)*cos(Rz2))*sin(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*cos(Rz3);
	*MAT(jacobian,0,1)=-1.0*l2*sin(Rz1)*cos(Rz2) - 1.0*l2*sin(Rz2)*cos(Rz1) + l3*(1.0*sin(Rz1)*sin(Rz2) - 1.0*cos(Rz1)*cos(Rz2))*sin(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*cos(Rz3);
	*MAT(jacobian,0,2)=-l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*sin(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*cos(Rz3);
	*MAT(jacobian,1,0)=1.0*l1*cos(Rz1) - 1.0*l2*sin(Rz1)*sin(Rz2) + 1.0*l2*cos(Rz1)*cos(Rz2) + l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*cos(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*sin(Rz3);
	*MAT(jacobian,1,1)=-1.0*l2*sin(Rz1)*sin(Rz2) + 1.0*l2*cos(Rz1)*cos(Rz2) + l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*cos(Rz3) + l3*(-1.0*sin(Rz1)*cos(Rz2) - 1.0*sin(Rz2)*cos(Rz1))*sin(Rz3);
	*MAT(jacobian,1,2)=l3*(-1.0*sin(Rz1)*sin(Rz2) + 1.0*cos(Rz1)*cos(Rz2))*cos(Rz3) - l3*(1.0*sin(Rz1)*cos(Rz2) + 1.0*sin(Rz2)*cos(Rz1))*sin(Rz3);
	*MAT(jacobian,2,0)=1;
	*MAT(jacobian,2,1)=1;
	*MAT(jacobian,2,2)=1;
#endif
}



int main11() {
    

    return 0;
}
