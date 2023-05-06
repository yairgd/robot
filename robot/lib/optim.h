/*
 * =====================================================================================
 *
 *       Filename:  optim.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2023 02:38:22 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef OPTIM_H
#define OPTIM_H 

void  jacobian_pseudoinverse_optimization(double *phi,double *links, double *des_xyz,int len,double alpha);
void calc_grdient_decent(double *phi,double *links, double *des_xyz,double alpha) ;

#endif
