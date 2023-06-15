/*
 * =====================================================================================
 *
 *       Filename:  template.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/15/2023 01:26:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef TEMPLATE_H
#define TEMPLATE_H 

#ifdef __cplusplus
extern "C" {
#endif

struct gradient_info * get_endeffector_cost_function_gradient_info(double[3]);
void put_endeffector_cost_function_gradient_info() ;
struct vec3_list * forward_kinetic(double *var_value);
void  endeffector_cost_function_gradient( double *des_xyz, double *var_value,  double *grad, int n); 


#ifdef __cplusplus
}
#endif
#endif
