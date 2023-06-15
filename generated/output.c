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
#include <math.h>
#include <stdlib.h>
#include <strings.h>
#include "matrix.h"
#include "optim.h"


/**
 * Created  06/13/2023
 * @brief   returns the location of the joints by givven motor angels
 * @param   
 * @return  
 */
struct vec3_list * forward_kinetic(double *var_value)
{
	struct vec3_list * list_4 = 0;
	double Ry_0 = var_value[0];
	double Rz_1 = var_value[1];
	double Rz_2 = var_value[2];
	double Rz_3 = var_value[3];
	

    	
	// points for joint 1
	struct vec3_list * list_3 = (struct vec3_list*)malloc(sizeof (struct vec3_list));	
	list_3->next = list_4;	
	list_3->p.x = 0;
	list_3->p.y = 0;
	list_3->p.z = 0;
        
	// points for joint 2
	struct vec3_list * list_2 = (struct vec3_list*)malloc(sizeof (struct vec3_list));	
	list_2->next = list_3;	
	list_2->p.x = -4.0*sin(Ry_0)*cos(Rz_1);
	list_2->p.y = -4.0*sin(Rz_1);
	list_2->p.z = 4.0*cos(Ry_0)*cos(Rz_1);
        
	// points for joint 3
	struct vec3_list * list_1 = (struct vec3_list*)malloc(sizeof (struct vec3_list));	
	list_1->next = list_2;	
	list_1->p.x = 6.0*sin(Ry_0)*sin(Rz_1)*sin(Rz_2) - 6.0*sin(Ry_0)*cos(Rz_1)*cos(Rz_2) - 4.0*sin(Ry_0)*cos(Rz_1);
	list_1->p.y = -6.0*sin(Rz_1)*cos(Rz_2) - 4.0*sin(Rz_1) - 6.0*sin(Rz_2)*cos(Rz_1);
	list_1->p.z = -6.0*sin(Rz_1)*sin(Rz_2)*cos(Ry_0) + 6.0*cos(Ry_0)*cos(Rz_1)*cos(Rz_2) + 4.0*cos(Ry_0)*cos(Rz_1);
        
	// points for joint 4
	struct vec3_list * list_0 = (struct vec3_list*)malloc(sizeof (struct vec3_list));	
	list_0->next = list_1;	
	list_0->p.x = 6.0*(1.0*sin(Ry_0)*sin(Rz_1)*sin(Rz_2) - 1.0*sin(Ry_0)*cos(Rz_1)*cos(Rz_2))*cos(Rz_3) + 6.0*(1.0*sin(Ry_0)*sin(Rz_1)*cos(Rz_2) + 1.0*sin(Ry_0)*sin(Rz_2)*cos(Rz_1))*sin(Rz_3) + 6.0*sin(Ry_0)*sin(Rz_1)*sin(Rz_2) - 6.0*sin(Ry_0)*cos(Rz_1)*cos(Rz_2) - 4.0*sin(Ry_0)*cos(Rz_1);
	list_0->p.y = 6.0*(1.0*sin(Rz_1)*sin(Rz_2) - 1.0*cos(Rz_1)*cos(Rz_2))*sin(Rz_3) + 6.0*(-1.0*sin(Rz_1)*cos(Rz_2) - 1.0*sin(Rz_2)*cos(Rz_1))*cos(Rz_3) - 6.0*sin(Rz_1)*cos(Rz_2) - 4.0*sin(Rz_1) - 6.0*sin(Rz_2)*cos(Rz_1);
	list_0->p.z = 6.0*(-1.0*sin(Rz_1)*sin(Rz_2)*cos(Ry_0) + 1.0*cos(Ry_0)*cos(Rz_1)*cos(Rz_2))*cos(Rz_3) + 6.0*(-1.0*sin(Rz_1)*cos(Ry_0)*cos(Rz_2) - 1.0*sin(Rz_2)*cos(Ry_0)*cos(Rz_1))*sin(Rz_3) - 6.0*sin(Rz_1)*sin(Rz_2)*cos(Ry_0) + 6.0*cos(Ry_0)*cos(Rz_1)*cos(Rz_2) + 4.0*cos(Ry_0)*cos(Rz_1);
        
	return list_0;
 }




/**
 * Created  06/13/2023
 * @brief   claclaue the gradient for mean squre error (MSE) cost function between current location to destanation.
 * @param   
 * @return  
 */
void endeffector_cost_function_gradient(double *des_xyz, double *var_value,  double *grad, int n) 
{
	double x = des_xyz[0];
	double y = des_xyz[1];
	double z = des_xyz[2];
	double Ry_0 = var_value[0]  ;
	double Rz_1 = var_value[1]  ;
	double Rz_2 = var_value[2]  ;
	double Rz_3 = var_value[3]  ;
	
	
	grad[0] = -2*(-x - (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*sin(Ry_0))*(4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*cos(Ry_0) - 2*(-z + (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*cos(Ry_0))*(4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*sin(Ry_0);
        
	grad[1] = -2*(-x - (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*sin(Ry_0))*(-4.0*sin(Rz_1) - 6.0*sin(Rz_1 + Rz_2) - 6.0*sin(Rz_1 + Rz_2 + Rz_3))*sin(Ry_0) + 2*(-z + (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*cos(Ry_0))*(-4.0*sin(Rz_1) - 6.0*sin(Rz_1 + Rz_2) - 6.0*sin(Rz_1 + Rz_2 + Rz_3))*cos(Ry_0) + 36.0*(-1.33333333333333*cos(Rz_1) - 2*cos(Rz_1 + Rz_2) - 2*cos(Rz_1 + Rz_2 + Rz_3))*(-0.166666666666667*y - 0.666666666666667*sin(Rz_1) - sin(Rz_1 + Rz_2) - sin(Rz_1 + Rz_2 + Rz_3));
        
	grad[2] = -2*(-x - (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*sin(Ry_0))*(-6.0*sin(Rz_1 + Rz_2) - 6.0*sin(Rz_1 + Rz_2 + Rz_3))*sin(Ry_0) + 2*(-z + (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*cos(Ry_0))*(-6.0*sin(Rz_1 + Rz_2) - 6.0*sin(Rz_1 + Rz_2 + Rz_3))*cos(Ry_0) + 36.0*(-2*cos(Rz_1 + Rz_2) - 2*cos(Rz_1 + Rz_2 + Rz_3))*(-0.166666666666667*y - 0.666666666666667*sin(Rz_1) - sin(Rz_1 + Rz_2) - sin(Rz_1 + Rz_2 + Rz_3));
        
	grad[3] = 12.0*(-x - (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*sin(Ry_0))*sin(Ry_0)*sin(Rz_1 + Rz_2 + Rz_3) - 12.0*(-z + (4.0*cos(Rz_1) + 6.0*cos(Rz_1 + Rz_2) + 6.0*cos(Rz_1 + Rz_2 + Rz_3))*cos(Ry_0))*sin(Rz_1 + Rz_2 + Rz_3)*cos(Ry_0) - 72.0*(-0.166666666666667*y - 0.666666666666667*sin(Rz_1) - sin(Rz_1 + Rz_2) - sin(Rz_1 + Rz_2 + Rz_3))*cos(Rz_1 + Rz_2 + Rz_3);
        
}
