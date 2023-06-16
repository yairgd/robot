/*
 * =====================================================================================
 *
 *       Filename:  optimization.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/06/23 19:17:39
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H
#include "matrix.h"

#ifdef __cplusplus
extern "C" {
#endif

struct joint;
struct vec3_list {
	struct vec3 p;
	//struct joint *joint;
	struct vec3_list *next;
	struct joint *joint;
};
void vec3_list_free(struct vec3_list *list);

struct gradient_info {
	 void (*gradient)(double * des_xyz, double * var_value, double *  gradient, int n, void *data);
	 struct vec3_list * (*forward_kinetic)(double * variable, void *data);	 
	 double des_xyz[3];
	 double *variables;
	 int num_of_variable;
	 void *data;
} ;

void gradient_decent(struct  gradient_info *, double alpha,int max_iter);
struct vec3_list * forward_kinetic(struct  gradient_info * info);
void free_gradient_info(struct gradient_info * info) ;

void forward_calc(struct gradient_info *) ;


#define PI 3.141592653589793

#ifdef __cplusplus
}
#endif
#endif

