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

#include "optimization.h"
#include "template.h"
#include "optim.h"  //TODO depricated to remove

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



/**
 * Created  06/01/2023
 * @brief   minimize the endeffector location using minimzation of mean squre of the disstance between the current endeffector location and the target
 * @param   
 * @return  
 */
void  gradient_decent(struct gradient_info *info, double alpha, int max_iter) 
{
	double norm;
	double  xyz_new[3];
	int k = max_iter;
	struct vec3_list *list;
	double * vars = info->variables;	
	double * grad = malloc(sizeof (double) * info->num_of_variable);
	
	while (k>0) {
		info->gradient (info->des_xyz, info->variables,  grad, info->num_of_variable);
		k--;
		for (int i=0;i<info->num_of_variable;i++) {
			vars[i] = vars[i] - grad[i]*alpha;
			//if (vars[i] <0.0 || vars[i]>1.5707963267948966)
			//	vars[i] = vars[i] + grad[i]*alpha;
		}
		
		
		// calc norm
		norm = 0;		
		for (int j=0;j < 3;j++) {
			norm += (info->des_xyz[j]-xyz_new[j])*(info->des_xyz[j]-xyz_new[j]);
		}

		//norm = sqrtf(norm);
		double err = 0.001;
		if (norm < err*err)
			break;
		list =  forward_kinetic(info->variables);

		xyz_new[0] =  list->p.x;
		xyz_new[1] =  list->p.y;
		xyz_new[2] =  list->p.z;

		vec3_list_free(list);

		//printf ("%d %lf %lf %lf %lf %lf %lf %lf %lf\n", max_iter- k,norm,xyz_new[0], xyz_new[1], xyz_new[2], rad2deg(vars[0]), rad2deg(vars[1]), rad2deg(vars[2]), (xyz_new[0]-info->des_xyz[0]) * (xyz_new[0]-info->des_xyz[0])  + (xyz_new[1]-info->des_xyz[1]) * (xyz_new[1]-info->des_xyz[1]) );		
	}
	free(grad);
}



void forward_calc2() {
	struct vec3_list *next;
	double des_xyz [3]= {-2.437466, -4.519042,  11.326713};
	double grad[4];
	double variables[4];

	struct gradient_info * info = get_endeffector_cost_function_gradient_info((double [3]){-2.437466, -4.519042,  11.326713});
	for (int i=0;i<3;i++)
		info->des_xyz[i] = des_xyz[i];

	/*
	info->des_xyz = des_xyz;
	info->num_of_variable = 4;
	info->des_xyz = des_xyz;
	info->variables = variables;
	info->gradient = endeffector_cost_function_gradient;
	*/

	gradient_decent (info , 0.001,10000);
	struct vec3_list * list =  forward_kinetic(info->variables);
	while (list) {
		printf ("xyz: %lf, %lf,  %lf\n", list->p.x, list->p.y , list->p.z);
		next=list->next;
		free(list);
		list = next;
	}	
}

