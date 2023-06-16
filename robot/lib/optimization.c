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

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



/**
 * Created  06/16/2023
 * @brief   release vec3_list linked list
 * @param   
 * @return  
 */
void vec3_list_free(struct vec3_list *list) {
	struct vec3_list *next;
	while (list) {
		next=list->next;
		free(list);
		list = next;
	}
}

/**
 * Created  06/01/2023
 * @brief   minimize the endeffector location using minimzation of mean squre of the disstance between the current endeffector location and the target
 * @param   
 * @return  
 */
void  gradient_decent(struct gradient_info *info, double alpha, int max_iter) 
{
	double norm;
	double  xyz_new[3] = {0};
	int k = max_iter;
	struct vec3_list *list;
	double * vars = info->variables;	
	double * grad = malloc(sizeof (double) * info->num_of_variable);
	
	while (k>0) {
		info->gradient (info->des_xyz, info->variables,  grad, info->num_of_variable, info->data);
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
		list =  info->forward_kinetic(info->variables, info->data);

		xyz_new[0] =  list->p.x;
		xyz_new[1] =  list->p.y;
		xyz_new[2] =  list->p.z;

		vec3_list_free(list);

		//printf ("%d %lf %lf %lf %lf %lf %lf %lf %lf\n", max_iter- k,norm,xyz_new[0], xyz_new[1], xyz_new[2], rad2deg(vars[0]), rad2deg(vars[1]), rad2deg(vars[2]), (xyz_new[0]-info->des_xyz[0]) * (xyz_new[0]-info->des_xyz[0])  + (xyz_new[1]-info->des_xyz[1]) * (xyz_new[1]-info->des_xyz[1]) );		
	}
	free(grad);
}


struct vec3_list *  forward_kinetic(struct gradient_info *info)
{
	return info->forward_kinetic(info->variables,info->data);
}


void forward_calc(struct gradient_info * info) {
	struct vec3_list *next;


	gradient_decent (info , 0.001,10000);
	struct vec3_list * list =  info->forward_kinetic(info->variables, info->data);
	while (list) {
		printf ("xyz: %lf, %lf,  %lf\n", list->p.x, list->p.y , list->p.z);
		next=list->next;
		free(list);
		list = next;
	}	
}



/**
 * Created  06/15/2023
 * @brief   release the memory of endeffector_cost_function_gradient_info
 * @param   
 * @return  
 */
void free_gradient_info(struct gradient_info * info) {
	free(info->variables);
	free(info);

}

