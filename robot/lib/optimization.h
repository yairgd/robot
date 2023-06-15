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
//typedef void (*gradient_func)(double * des_xyz, double * var_value, double *  gradient, int n);

#ifdef __cplusplus
extern "C" {
#endif
struct gradient_info {
	 void (*gradient)(double * des_xyz, double * var_value, double *  gradient, int n);
	 double des_xyz[3];
	 double *variables;
	 int num_of_variable;
} ;

void gradient_decent(struct  gradient_info *, double alpha,int max_iter);
void forward_calc2() ;

#ifdef __cplusplus
}
#endif
#endif

