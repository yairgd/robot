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

#include "model.h"
#include "optimization.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>



int parameter_is_constant(struct parameter  *p) {
	return p->val == 0;
}
double parameter_get(struct parameter  *p) {
	if (p->val != 0)
		return *p->val * p->coefficient;
	return 0;
}

void parameter_set_conststant(struct parameter *p, double *v, double coeff) {
	p->coefficient = coeff;
	p->val = v;
}



#if 0

/**
 * Created  05/02/2023
 * @brief   IK solver using Jacobian pseudoinverse
 * @param   
 * @return  
 */
void  jacobian_pseudoinverse_optimization(double *phi,double *links, double *des_xyz,int len,double alpha) {
	//set_inital_phi(phi, len);
	double xyz_new[] ={0,0,0};

	struct matrix *jacobian = matrix_init(7,3);
	double norm;

	int k=10000;
	double phi_prev[3];
	memcpy (phi_prev, phi,24);
	endeffector_location(links,phi,xyz_new);

	do  {
		ik_jacobian_func_analytic(links,phi, jacobian);
		struct matrix * diff_xyz = matrix_init(3,1);
		diff_xyz->data[0] = des_xyz[0] - xyz_new[0];
		diff_xyz->data[1] = des_xyz[1] - xyz_new[1];
		diff_xyz->data[2] = des_xyz[2] - xyz_new[2];

		struct matrix * pseudo_inv  = matrix_pseudo_inv(jacobian);

		struct matrix * delta = matrix_mul(pseudo_inv, diff_xyz);

		norm = 0;
		for (int i=0;i<3;i++) {
			phi[i] = phi[i] + alpha * delta->data[i];
			//if (phi[i] <0.0 || phi[i]>1.5707963267948966)
			//	phi[i] = phi[i] - alpha * delta->data[i];
			norm += (des_xyz[i]-xyz_new[i])*(des_xyz[i]-xyz_new[i]);
		}
		norm = sqrtf(norm);

#if 0
		if ((phi[0] + alpha * delta->data[0])<0.7853981633974483 && (phi[0] + alpha * delta->data[0])>0 ) phi[0] = phi[0] + alpha * delta->data[0];
		if ((phi[1] + alpha * delta->data[1])<0.7853981633974483 && (phi[1] + alpha * delta->data[1])>0 ) phi[1] = phi[1] + alpha * delta->data[1];
		phi[2] = phi[2] + alpha * delta->data[2];
		//if ((phi[2] + alpha * delta->data[2])<0.7853981633974483 && (phi[2] + alpha * delta->data[2])>0 ) phi[2] = phi[2] + alpha * delta->data[2];

		//phi[0] =phi[0] + alpha * delta->data[0];
		//phi[1] =phi[1] + alpha * delta->data[1];
		printf ("%lf %lf %lf %lf %lf %lf %lf\n", xyz[0], xyz[1], xyz[2], rad2deg(phi[0]), rad2deg(phi[1]), rad2deg(phi[2]), (xyz[0]-des_xyz[0]) * (xyz[0]-des_xyz[0])  + (xyz[1]-des_xyz[1]) * (xyz[1]-des_xyz[1]) );
#endif
		matrix_free(diff_xyz);
		matrix_free(pseudo_inv);
#if 0
		if ( sqrtf( (xyz[0]-des_xyz[0]) * (xyz[0]-des_xyz[0])  + (xyz[1]-des_xyz[1]) * (xyz[1]-des_xyz[1]))  < 0.0000001)
			break;
#endif
		//printf ("%lf %lf %lf %lf %lf %lf %lf\n", xyz_new[0], xyz_new[1], xyz_new[2], rad2deg(phi[0]), rad2deg(phi[1]), rad2deg(phi[2]), norm );
		endeffector_location(links,phi,xyz_new);

		if (norm < 0.0001)
			break;
		k--;


	} while (k>0);
	//if (norm > 0.1) {
	//	memcpy (phi, phi_prev,24);
	//	printf ("%f %d\n", norm,k);
	//	}




}


#endif

void rotate(struct vec3 * point,double Rx, double Ry, double Rz) {
	// TODO move tot template
	double x = point->x;
	double y = point->y;
	double z = point->z;

	point->x = x*cos(Ry)*cos(Rz) - y*sin(Rz)*cos(Ry) + z*sin(Ry);
	point->y = x*(sin(Rx)*sin(Ry)*cos(Rz) + sin(Rz)*cos(Rx)) + y*(-sin(Rx)*sin(Ry)*sin(Rz) + cos(Rx)*cos(Rz)) - z*sin(Rx)*cos(Ry);	
	point->z = x*(sin(Rx)*sin(Rz) - sin(Ry)*cos(Rx)*cos(Rz)) + y*(sin(Rx)*cos(Rz) + sin(Ry)*sin(Rz)*cos(Rx)) + z*cos(Rx)*cos(Ry);
}

void joint_add_child(struct joint *parent , const char *name, struct joint *child) {
	parent->child.link.name = name;
	parent->child.link.child = child; 
	parent->child.link.parent = parent; 

}

void joint_set_parent_link(struct joint *j, struct link *l)  {
	j->parent = l;
};

struct link * joint_get_child_link(struct joint *j, int child_idx) {
	return &j->child.link;
}


struct model  * model_new(int n) {
	struct model *model = (struct model*)malloc(sizeof(struct model));
	model->num_of_variable = n;
	model->variables =(double*) malloc(sizeof(double)*n);
	return model;
}

void model_free(struct model *model) {
	if (model) {
		free(model->variables);
		free(model);
	}
}

struct model * init_robot() {


	struct model *model = model_new(4);
	double * p1 = &model->variables[0];
	double * p2 = &model->variables[1];
	double * p3 = &model->variables[2];
	double * g1 = &model->variables[3];

	*p1 = 0.000000;
	*p2 = 0.401455;
	*p3 = 0.666982;
	*g1 = 0;
	struct joint *  j1 = ( struct joint *) malloc (sizeof(struct joint));
	*j1 = (struct joint) {
		.name = (char*)"joint1",
			.type = JOINT_FIXED,
			.rpy =  {PI,PI/2,0} , /*{PI,0,PI/2}, 		*/
			.origin = {0,0,0},
			.child = {
				.link = {0},
				.next = 0,
			},
			.parent = 0,
			.limit = {0},
			.axis = { {0,0},{1,g1}, {0,0}}

	};
	joint_set_parent_link(j1, 0 ) ;




	struct joint *  j2 = ( struct joint *) malloc (sizeof(struct joint));
	*j2 = (struct joint) {
		.name = (char*)"joint2",
			.type = JOINT_FIXED,
			.rpy = {0,0,0}, 		
			.origin = {4,0,0},
			.child = {
				.link = {0},
				.next = 0,
			},
			.parent = 0,
			.limit = {0},
			.axis = { {0,0},{0,0},{1,p1}}

	};
	joint_set_parent_link(j2, joint_get_child_link(j1,0) ) ;


	struct joint *  j3 = ( struct joint *) malloc (sizeof(struct joint));	
	*j3 = (struct joint) {
		.name = (char*)"joint3",
			.type = JOINT_FIXED,
			.rpy = {0,0,0}, 		
			.origin = {6,0,0},
			.child = {
				.link = {0},
				.next = 0,
			},
			.parent = 0,
			.limit = {0},
			.axis = { {0,0},{0,0},{1,p2}}

	};
	joint_set_parent_link(j3, joint_get_child_link(j2,0) ) ;




	struct joint *  j4 = ( struct joint *) malloc (sizeof(struct joint));
	*j4 = (struct joint) {
		.name = (char*)"joint4",
			.type = JOINT_FIXED,
			.rpy = {0,0,0}, 		
			.origin = {6,0,0},
			.child = {
				.link = {0},
				.next = 0,
			},
			.parent = 0,
			.limit = {0},
			.axis = { {0,0},{0,0},{1,p3}}

	};
	joint_set_parent_link(j4, joint_get_child_link(j3,0) ) ;

	joint_add_child (j1, "l1",j2);
	joint_add_child (j2, "l2",j3);
	joint_add_child (j3, "l3",j4);
	joint_add_child (j4, "l4",0);

	model->endeffector = j4;
	model->base_link = 0;
	return model;
}





/**
 * Created  05/30/2023
 * @brief   create translation matrix
 * @param   j is the joint with the data of the matrix
 * @param   rot_angle the rotatuion angle
 * @param   vec3 is the location of the axis after translation. it is positioned in relate to the parent axis (joint)
 * @return  
 here is the python code to get the formula of the matrix
 import  sympy as sym
#import  pysym as ee
cx= sym.Symbol('cx');
sx= sym.Symbol('sx');
cy= sym.Symbol('cy');
sy= sym.Symbol('sy');
cz= sym.Symbol('cz');
sz= sym.Symbol('sz');
Rx=sym.Matrix([[1,0,0],[0,cx,sx],[0,-sx,cx]]);
Ry=sym.Matrix([[cy,0,-sy],[0,1,0],[sy,0,cy]]);
Rz=sym.Matrix([[cz,sz,0],[-sz,cz,0],[0,0,1]]);
R=Rx*Ry*Rz
cx0= sym.Symbol('cx0');
sx0= sym.Symbol('sx0');
cy0= sym.Symbol('cy0');
sy0= sym.Symbol('sy0');
cz0= sym.Symbol('cz0');
sz0= sym.Symbol('sz0');
Rx0=sym.Matrix([[1,0,0],[0,cx0,sx0],[0,-sx,cx0]]);
Ry0=sym.Matrix([[cy0,0,-sy0],[0,1,0],[sy0,0,cy0]]);
Rz0=sym.Matrix([[cz0,sz0,0],[-sz0,cz0,0],[0,0,1]]);
R=Rx*Ry*Rz*Rx0*Ry0*Rz0
R.simplify()
R[0,0]
R[0,1]
R[0,2]
R[1,0]
R[1,1]
R[1,2]
R[2,0]
R[2,1]
R[2,2]

*/

void joint_translation_matrix(struct joint *j) {
	double cx = cos(parameter_get(&j->axis.x));
	double cy = cos(parameter_get(&j->axis.y));
	double cz = cos(parameter_get(&j->axis.z));
	double sx = sin(parameter_get(&j->axis.x));
	double sy = sin(parameter_get(&j->axis.y));
	double sz = sin(parameter_get(&j->axis.z));
	double cx0 = cos(j->rpy.x);
	double cy0 = cos(j->rpy.y);
	double cz0 = cos(j->rpy.z);
	double sx0 = sin(j->rpy.x);
	double sy0 = sin(j->rpy.y);
	double sz0 = sin(j->rpy.z);


	// rotate the current location of the axis after rotation of the parent
	struct vec3 rot_vec =  j->origin;
	rotate (&rot_vec, parameter_get(&j->axis.x),parameter_get(&j->axis.y), parameter_get(&j->axis.z)  );
	rotate (&rot_vec, j->rpy.x,  j->rpy.y,  j->rpy.z);

	// initlize matirx if needed
	if (j->translation_matrix == 0)
		j->translation_matrix = matrix_init(4,4);

	// assign values to matrix
	*MAT(j->translation_matrix,0,0) = cz0*(cy*cy0*cz - sy0*(cx0*sy - cy*sx0*sz)) - sz0*(cx0*cy*sz + sx*sy);
	*MAT(j->translation_matrix,1,0) = cz0*(cx0*cy*sz + sx*sy) + sz0*(cy*cy0*cz - sy0*(cx0*sy - cy*sx0*sz));   /// TODO rever with (1,0) <->(0,1)
	*MAT(j->translation_matrix,0,2) = -cy*cz*sy0 - cy0*(cx0*sy - cy*sx0*sz);
	*MAT(j->translation_matrix,0,3) = rot_vec.x;

	*MAT(j->translation_matrix,0,1) = -cz0*(cy0*(cx*sz - cz*sx*sy) - sy0*(cx0*cy*sx + sx0*(cx*cz + sx*sy*sz))) - sz0*(cx0*(cx*cz + sx*sy*sz) - cy*sx*cy*sx); /// TODO rever with (1,0) <->(0,1)
	*MAT(j->translation_matrix,1,1) = cz0*(cx0*(cx*cz + sx*sy*sz) - cy*sx*cy*sx) - sz0*(cy0*(cx*sz - cz*sx*sy) - sy0*(cx0*cy*sx + sx0*(cx*cz + sx*sy*sz)));
	*MAT(j->translation_matrix,1,2) = cy0*(cx0*cy*sx + sx0*(cx*cz + sx*sy*sz)) + sy0*(cx*sz - cz*sx*sy);
	*MAT(j->translation_matrix,1,3) = rot_vec.y;

	*MAT(j->translation_matrix,2,0) = cz0*(cy0*(cx*cz*sy + sx*sz) + sy0*(cx*cx0*cy + sx0*(cx*sy*sz - cz*sx))) + sz0*(cx*cy*sx - cx0*(cx*sy*sz - cz*sx));
	*MAT(j->translation_matrix,2,1) = -cz0*(cx*cy*sx - cx0*(cx*sy*sz - cz*sx)) + sz0*(cy0*(cx*cz*sy + sx*sz) + sy0*(cx*cx0*cy + sx0*(cx*sy*sz - cz*sx)));
	*MAT(j->translation_matrix,2,2) = cy0*(cx*cx0*cy + sx0*(cx*sy*sz - cz*sx)) - sy0*(cx*cz*sy + sx*sz);
	*MAT(j->translation_matrix,2,3) = rot_vec.z;

	*MAT(j->translation_matrix,3,0) = 0;
	*MAT(j->translation_matrix,3,1) = 0;
	*MAT(j->translation_matrix,3,2) = 0;
	*MAT(j->translation_matrix,3,3) = 1;
}


/**
 * Created  06/01/2023
 * @brief   calculate forward kinetic for joint chain
 * this is revursive call from the last joint in the chain to ward the first link of a chain.  The recursive
 * starts to calclates the transation matrix right after the recursive get into stop condtion.
 * @param   current - the last joint in the chain
 * @param   first_joint_in_chain the first link in the chain
 * @return  linked list of each joint position
 */
struct vec3_list * forward_kinetic_for_chain(struct joint *current, struct link *first_joint_in_chain) {
	struct vec3_list *list_next = 0, *list;

	// recursive call to parenet joint - stop when getting to fist_joint_in_chain
	if (current->parent != 0 && current->parent != first_joint_in_chain)
		list_next = forward_kinetic_for_chain (current->parent->parent, first_joint_in_chain);

	// find traslation matrix for the current joint
	joint_translation_matrix(current);

	// multiply the current traslation matrix and the translation from nextious joint
	if (current->parent) {
		struct matrix * matrix_m = matrix_mul(current->parent->parent->translation_matrix, current->translation_matrix); 
		matrix_free(current->translation_matrix);
		current->translation_matrix = matrix_m;
	}


	// collect the location of the current join into a linkaged list
	list = (struct vec3_list*)malloc(sizeof (struct vec3_list));	
	list->next = list_next;	
	list->p.x = *MAT(current->translation_matrix,0,3);
	list->p.y = *MAT(current->translation_matrix,1,3);
	list->p.z = *MAT(current->translation_matrix,2,3);
	list->joint = current;
	/*
	   if we want forwad connection - not needed
	   if (list_next)
	   list_next->next = list;
	   */

	/* uncomment to dump
	   matrix_dump (current->translation_matrix);	
	   printf ("%s\n",joint_get_child_link(current,0)->name); 
	   printf ("%s\n",current->name); 
	   */
	return list;

}





void endeffector_cost_function_numeric_gradient(struct model *model, double *des_xyz,double *grad) {
	double h=0.0001;
	struct vec3_list *list;
	double dx, dy, dz;

	for (int  i = 0; i < model->num_of_variable;i++) {
		list = forward_kinetic_for_chain (model->endeffector, model->base_link);
		dx = (list->p.x - des_xyz[0]);
		dy = (list->p.y - des_xyz[1]);
		dz = (list->p.z - des_xyz[2]);
		double f = dx*dx + dy*dy + dz*dz;
		vec3_list_free(list);


		model->variables[i] += h;
		list = forward_kinetic_for_chain (model->endeffector, model->base_link);
		dx = (list->p.x - des_xyz[0]);
		dy = (list->p.y - des_xyz[1]);
		dz = (list->p.z - des_xyz[2]);
		double fh = dx*dx + dy*dy + dz*dz;
		vec3_list_free(list);
		model->variables[i] -= h;

		grad[i] = (fh-f)/h;

	}


}


/**
 * Created  06/16/2023
 * @brief   interface function to calculate numeric forwad kinetic, 
 * @param   var_value the values of the angles to assign in the model
 * @param   data numeric model data structure
 * @return  
 */
static struct vec3_list * model_forward_kinetic(double * var_value, void * data)
{
	struct model * model = data;
	struct vec3_list * list = forward_kinetic_for_chain (model->endeffector, model->base_link);

	return list;
}



static void endeffector_cost_function_gradient(double *des_xyz, double *var_value,  double *grad, int n,void *data) 
{
	struct model * model = data;
	(void)n;
	endeffector_cost_function_numeric_gradient(model, des_xyz, grad);	
	
}


		
/**
 * Created  06/15/2023
 * @brief   genrrates the gradient infor structure to use 
 * @param   
 * @return  
 */
struct gradient_info * numeric_model__get_gradient_info_init(struct model *model, double des_xyz[3]) {
	struct gradient_info  * info = 0;

	info = malloc(sizeof(struct gradient_info));
	info->num_of_variable = 4;
	info->gradient = endeffector_cost_function_gradient;
	info->forward_kinetic = model_forward_kinetic;
	info->data = model;

	info->variables = model->variables;
	for (int i =0;i<3;i++)
		info->des_xyz[i] = des_xyz[i];


	return info;


}




