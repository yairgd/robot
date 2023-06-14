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
#ifdef __cplusplus
extern "C" {
#endif
#include "matrix.h"
#include <stdlib.h>
#define PI 3.141592653589793


struct parameter {
	float coefficient;
	float *val;
};

float parameter_get(struct parameter  *p);
void parameter_set_conststant(struct parameter *p, float *v, float coeff);
int parameter_is_constant(struct parameter *p) ;


enum joint_type {
	JOINT_REVOLUTE, JOINT_FIXED, prismatic
};

struct model {
	struct link *base_link;
	struct joint *endeffector;
	int num_of_variable;
	float *variables;
};
struct model  * model_new(int n);
void model_free(struct model *);




struct joint ;
struct link {
	// name
	const char *name;

	// pointer to joint - the parent link in the joint is pointer to that joint
	struct joint *child;

	struct joint *parent;
	
};

struct joint {
	// name
	char *name;

	// type
	enum joint_type type;

	// wehere to locate the axis in relate to parent
	// and what is rotation of the axis if the joint
	// from boath we can define for example the DH matrix
	struct vec3 rpy;
	struct vec3 origin;
	
	// the childs links
	struct child {
		struct link link;
		struct child *next;
	} child;

	// the parent link
	struct link *parent;

	// the limit of the motion
	struct limit {
		double lower;
		double upper;
		double velocity;
		double efforts;
	} limit;


	struct  {
		struct parameter x;
		struct parameter y;
		struct parameter z;
	} axis;

	struct matrix *translation_matrix;
};


struct vec3_list {
	struct vec3 p;
	struct joint *joint;
	struct vec3_list *next;
};


void joint_set_parent_link(struct joint *j, struct link *l) ;
struct link * joint_get_child_link(struct joint *j, int child_idx) ;
void joint_add_child(struct joint *j , const char *name, struct joint *child);


//void joint 

void  jacobian_pseudoinverse_optimization(double *phi,double *links, double *des_xyz,int len,double alpha);
void calc_grdient_decent(double *phi,double *links, double *des_xyz,double alpha) ;
void forward_kinematic(double *links,double *alpha, double *beta , double *gamma, struct vec3 *xyz, int num_of_links);
void inverse_kinetic_calc(struct model * model, double des_xyz[3]) ;
 struct vec3_list * forward_kinetic_for_chain(struct joint *current, struct link *first_joint_in_chain);
void endeffector_grdient_decent(struct model *model, double *des_xyz,double alpha) ;
//void forward_calc(struct joint *j1, struct joint *j2) ;
struct model * init_robot() ;


void forward_calc1();
#ifdef __cplusplus
}
#endif

#endif
