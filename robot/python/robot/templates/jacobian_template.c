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
#include "optimization.h"
#include <string.h>



/**
 * Created  06/13/2023
 * @brief   returns the location of the joints by givven motor angels
 * @param   
 * @return  
 */
static struct vec3_list * model_forward_kinetic(double *var_value, void *data)
{
	struct vec3_list * list_{{forwad_kinetic|length}} = 0;
	{% for var in var_list %}double {{ var }} = var_value[{{loop.index-1}}];
	{% endfor %}

	(void)data;	
	
    	{% for fk in forwad_kinetic %}
	// points for joint {{ loop.index }}
	struct vec3_list * list_{{forwad_kinetic|length - loop.index}} = (struct vec3_list*)malloc(sizeof (struct vec3_list));	
	list_{{forwad_kinetic|length - loop.index}}->next = list_{{forwad_kinetic|length - loop.index+1}};	
	list_{{forwad_kinetic|length - loop.index}}->p.x = {{ fk[0] }};
	list_{{forwad_kinetic|length - loop.index}}->p.y = {{ fk[1] }};
	list_{{forwad_kinetic|length - loop.index}}->p.z = {{ fk[2] }};
        {% endfor %}
	return list_0;
 }





/**
 * Created  06/13/2023
 * @brief   claclaue the gradient for mean squre error (MSE) cost function between current location to destanation.
 * @param   
 * @return  
 */
static void endeffector_cost_function_gradient(double *des_xyz, double *var_value,  double *grad, int n,void *data) 
{
	double x = des_xyz[0];
	double y = des_xyz[1];
	double z = des_xyz[2];

	(void)n;
	(void)data;	
	{% for var in var_list %}double {{ var }} = var_value[{{loop.index-1}}]  ;
	{% endfor %}
	{% for g in mse_grad %}
	grad[{{loop.index-1}}] = {{g}};
        {% endfor %}
}



/**
 * Created  06/15/2023
 * @brief   genrrates the gradient infor structure to use 
 * @param   
 * @return  
 */
struct gradient_info * gradient_info_init(double des_xyz[3]) {
	struct gradient_info  * info = 0;
	info = malloc(sizeof(struct gradient_info));
	info->num_of_variable = {{forwad_kinetic|length}};
	info->variables = malloc(sizeof(double) * {{forwad_kinetic|length}});
	memset (info->variables, 0 , {{forwad_kinetic|length}} * sizeof ( double));				
	info->gradient = endeffector_cost_function_gradient;
	info->forward_kinetic = model_forward_kinetic;
	for (int i =0;i<3;i++)
		info->des_xyz[i] = des_xyz[i];
	return info;
}






