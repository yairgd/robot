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

#include "optim.h"

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

//#include "matrix.h"


float parameter_get(struct parameter  *p) {
	if (p->val != 0)
		return *p->val * p->coefficient;
	return 0;
}

void parameter_set_conststant(struct parameter *p, float *v, float coeff) {
	p->coefficient = coeff;
	p->val = v;
}





/**
 * Created  05/02/2023
 * @brief  auto generated function - calclautes the end effector position 
 * @param   
 * @return  
 */
void endeffector_location(double *links,double *phi,double *xyz) {
	double phi0 = phi[0];
	double phi1 = phi[1];
	double phi2 = phi[2];
	double l0=links[0];
	double l1=links[1];
	double l2=links[2];

	xyz[0] = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	xyz[1] = 1.0*l0*sin(phi0) + 1.0*l1*sin(phi0)*cos(phi1) + 1.0*l1*sin(phi1)*cos(phi0) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	xyz[2] = 0;



}

#if 0
/**
 * Created  05/02/2023
 * @brief   auto generated function - it calculates the jacobian
 * @param   
 * @return  
 */
void ik_jacobian_func_analytic(double *links,double *phi, struct matrix *jacobian) { // double J[3][3]) {
	double phi0 = phi[0];
	double phi1 = phi[1];
	double phi2 = phi[2];
	double l0=links[0];
	double l1=links[1];
	double l2=links[2];


	*MAT(jacobian,0,0) = -1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	*MAT(jacobian,0,1) = -1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) + l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	*MAT(jacobian,0,2) = -l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2);
	*MAT(jacobian,1,0) = 1.0*l0*cos(phi0) - 1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	*MAT(jacobian,1,1) = -1.0*l1*sin(phi0)*sin(phi1) + 1.0*l1*cos(phi0)*cos(phi1) + l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	*MAT(jacobian,1,2) = l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*sin(phi2);
	*MAT(jacobian,2,0) = 1;
	*MAT(jacobian,2,1) = 1;
	*MAT(jacobian,2,2) = 1;

}
#endif









#define pi 3.141592653589793

double rad2deg(double radians) {

	radians = radians - 2*pi*floor(radians/(2*pi));


	//radians = radians/2*3.141592653589793 - (int)(radians/2*3.141592653589793);
	//double deg = radians * (180/3.141592653589793);
	//return ((int)deg) %360;
	return radians;
}


void ik_cost_gradient_func_analytic(double *phi,double *links, double *des_xyz,double *grad) {
	double phi0 = phi[0];
	double phi1 = phi[1];
	double phi2 = phi[2];
	double l0=links[0];
	double l1=links[1];
	double l2=links[2];
	double x = des_xyz[0];
	double y = des_xyz[1];
	double z = des_xyz[2];

	grad[0] =  (2.0*l0*sin(phi0) + 2.0*l1*sin(phi0)*cos(phi1) + 2.0*l1*sin(phi1)*cos(phi0) - 2*l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x) + (-2.0*l0*cos(phi0) + 2.0*l1*sin(phi0)*sin(phi1) - 2.0*l1*cos(phi0)*cos(phi1) - 2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y);
	grad[1] = (2.0*l1*sin(phi0)*sin(phi1) - 2.0*l1*cos(phi0)*cos(phi1) - 2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y) + (2.0*l1*sin(phi0)*cos(phi1) + 2.0*l1*sin(phi1)*cos(phi0) - 2*l2*(1.0*sin(phi0)*sin(phi1) - 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x);
	grad[2] = (2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - 2*l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*cos(phi2))*(-1.0*l0*cos(phi0) + 1.0*l1*sin(phi0)*sin(phi1) - 1.0*l1*cos(phi0)*cos(phi1) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) - l2*(-1.0*sin(phi0)*cos(phi1) - 1.0*sin(phi1)*cos(phi0))*sin(phi2) + x) + (-2*l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*cos(phi2) + 2*l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*sin(phi2))*(-1.0*l0*sin(phi0) - 1.0*l1*sin(phi0)*cos(phi1) - 1.0*l1*sin(phi1)*cos(phi0) - l2*(-1.0*sin(phi0)*sin(phi1) + 1.0*cos(phi0)*cos(phi1))*sin(phi2) - l2*(1.0*sin(phi0)*cos(phi1) + 1.0*sin(phi1)*cos(phi0))*cos(phi2) + y);

}






void calc_grdient_decent(double *phi,double *links, double *des_xyz,double alpha) {

	double grad[3]; // will be taken from autogenerated frnction
	double norm;
	double xyz_new[3] = {0,0,0};
	int k = 1000;
	while (k>0) {
		ik_cost_gradient_func_analytic(phi,links, des_xyz,grad);
		norm = 0;
		for (int i=0;i<3;i++) {
			phi[i] = phi[i] - grad[i]*alpha;
			if (phi[i] <0.0 || phi[i]>1.5707963267948966)
				phi[i] = phi[i] + grad[i]*alpha;
			norm += (des_xyz[i]-xyz_new[i])*(des_xyz[i]-xyz_new[i]);
		}
		norm = sqrtf(norm);
		if (norm < 0.001)
			break;
		endeffector_location(links,phi,xyz_new);
		k--;

		//printf ("%lf %lf %lf %lf %lf %lf %lf\n", xyz_new[0], xyz_new[1], xyz_new[2], rad2deg(phi[0]), rad2deg(phi[1]), rad2deg(phi[2]), (xyz_new[0]-des_xyz[0]) * (xyz_new[0]-des_xyz[0])  + (xyz_new[1]-des_xyz[1]) * (xyz_new[1]-des_xyz[1]) );		
	}
}


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




/**
 * Created  05/07/2023
 * @brief   returns the location of the endeffecor in relate to world
 * @param   links vectors of links
 * @param   rpy vector of angle bewteen the links
 * @param   num_of_links the length of the links vector
 * @param   xyz gets  the final resuls in form of 2d shape -> dim[m][3] , m is the number of links, each row is xyz of the m'th links
 * @return  
 *for k in  range(0,len(ll)):
 H=np.identity(4);
 print("calc H")
 for i in range(0,k+1):
 print(i)
 m = roate_z(phi[i],ll[i]);
 H=H@m; 
 xy = [0,0,0]
 xy.append(1)
 x.append((H@xy)[0,0])
 y.append((H@xy)[0,1])
 fig,ax = plt.subplots()
 ax.plot(x, y, marker='*',linewidth=2.0)
 plt.show()

 *
 *
 */
void forward_kinematic(double *links,double *alpha, double *beta , double *gamma, struct vec3 *xyz, int num_of_links) {
	int i,k;

	struct matrix  * G = matrix_diag(4);	
	struct matrix  * O = matrix_init(4,1); // the end effector location
	for (i = 0; i < num_of_links; i++) {
		struct matrix  * t = matrix_translation_z(gamma[i],  links[i]);
		struct matrix  * m  = matrix_mul(G, t);
		//		struct matrix  * ef = matrix_mul(m,O);

		matrix_free(G);
		G = matrix_copy(m);

		/* multpy with point 0,0,0,1 to take the end effector position (at the origin of the axis*/
		O->data[0] = 0;O->data[1] = 0;O->data[2] = 0;O->data[3] = 1;
		struct matrix  * mo = matrix_mul (G,O);
		xyz[i].x = *MAT(mo,0,0);
		xyz[i].y = *MAT(mo,1,0);
		xyz[i].z = *MAT(mo,2,0);

		matrix_free(t);
		matrix_free(m);
		//		matrix_free(ef);
		matrix_free(mo);

	}
	matrix_free(O);
	matrix_free(G);
}


void rotate(struct vec3 * point,float Rx, float Ry, float Rz) {
	float cx = cos(Rx);
	float sx = sin(Rx);
	float cy = cos(Ry);
	float sy = sin(Ry);
	float cz = cos(Rz);
	float sz = sin(Rz);

	// rotate around x-axis
	float py = point->y * cx - point->z * sx;
	float pz = point->y * sx + point->z * cx;

	// rotate around y-axis
	float px = point->x * cy + pz * sy;
	pz = -point->x * sy + pz * cy;

	// rotate around z-axis
	float px2 = px * cz - py * sz;
	float py2 = px * sz + py * cz;

	point->x = px2;
	point->y = py2;
	point->z = pz;
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
	model->variables =(float*) malloc(sizeof(float)*n);
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
	float * p1 = &model->variables[0];
	float * p2 = &model->variables[1];
	float * p3 = &model->variables[2];
	float * g1 = &model->variables[3];

	*p1 = 0.100000;
	*p2 = 0.401455;
	*p3 = 0.666982;
	*g1 = 0;
	struct joint *  j1 = ( struct joint *) malloc (sizeof(struct joint));
	*j1 = (struct joint) {
		.name = (char*)"joint1",
			.type = JOINT_FIXED,
			.rpy = {PI,PI/2,0} , /*{PI,0,PI/2}, 		*/
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
	float cx = cos(parameter_get(&j->axis.x));
	float cy = cos(parameter_get(&j->axis.y));
	float cz = cos(parameter_get(&j->axis.z));
	float sx = sin(parameter_get(&j->axis.x));
	float sy = sin(parameter_get(&j->axis.y));
	float sz = sin(parameter_get(&j->axis.z));
	float cx0 = cos(j->rpy.x);
	float cy0 = cos(j->rpy.y);
	float cz0 = cos(j->rpy.z);
	float sx0 = sin(j->rpy.x);
	float sy0 = sin(j->rpy.y);
	float sz0 = sin(j->rpy.z);


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



void vec3_list_free(struct vec3_list *list) {
	struct vec3_list *next;
	while (list) {
		next=list->next;
		free(list);
		list = next;
	}
}

void endeffector_cost_function_numeric_gradient(struct model *model, double *des_xyz,double *grad) {
	float h=0.0001;
	struct vec3_list *list;
	float dx, dy, dz;

	for (int  i = 0; i < model->num_of_variable;i++) {
		list = forward_kinetic_for_chain (model->endeffector, model->base_link);
		dx = (list->p.x - des_xyz[0]);
		dy = (list->p.y - des_xyz[1]);
		dz = (list->p.z - des_xyz[2]);
		float f = dx*dx + dy*dy + dz*dz;
		vec3_list_free(list);


		model->variables[i] += h;
		list = forward_kinetic_for_chain (model->endeffector, model->base_link);
		dx = (list->p.x - des_xyz[0]);
		dy = (list->p.y - des_xyz[1]);
		dz = (list->p.z - des_xyz[2]);
		float fh = dx*dx + dy*dy + dz*dz;
		vec3_list_free(list);
		model->variables[i] -= h;

		grad[i] = (fh-f)/h;

	}







}
/**
 * Created  06/01/2023
 * @brief   minimize the endeffector location using minimzation of mean squre of the disstance between the current endeffector location and the target
 * @param   
 * @return  
 */
void endeffector_grdient_decent(struct model *model, double *des_xyz,double alpha) {
	double grad[4]; // will be taken from autogenerated frnction
	double norm;
	double xyz_new[3] = {0,0,0};
	int k = 100000;
	struct vec3_list *list;

	float * phi = model->variables;
	while (k>0) {
	
		endeffector_cost_function_numeric_gradient(model, des_xyz, grad);
		//ik_cost_gradient_func_analytic(phi,links, des_xyz,grad);
		for (int i=0;i<model->num_of_variable;i++) {
			phi[i] = phi[i] - grad[i]*alpha;
			if (phi[i] <0.0 || phi[i]>1.5707963267948966)
				phi[i] = phi[i] + grad[i]*alpha;
		}
		
		// calc norm
		norm = 0;		
		for (int j=0;j < 3;j++) {
			norm += (des_xyz[j]-xyz_new[j])*(des_xyz[j]-xyz_new[j]);
		}

		//norm = sqrtf(norm);
		double err = 0.001;
		if (norm < err*err)
			break;
		list = forward_kinetic_for_chain (model->endeffector, model->base_link);
		xyz_new[0] =  list->p.x;
		xyz_new[1] =  list->p.y;
		xyz_new[2] =  list->p.z;

		vec3_list_free(list);
		k--;

		//printf ("%d %lf %lf %lf %lf %lf %lf %lf %lf\n", 100000- k,norm,xyz_new[0], xyz_new[1], xyz_new[2], rad2deg(phi[0]), rad2deg(phi[1]), rad2deg(phi[2]), (xyz_new[0]-des_xyz[0]) * (xyz_new[0]-des_xyz[0])  + (xyz_new[1]-des_xyz[1]) * (xyz_new[1]-des_xyz[1]) );		
	}
}



void inverse_kinetic_calc(struct model * model, double des_xyz[3]) {
	struct vec3_list *list,*next;

	endeffector_grdient_decent (model, des_xyz, 0.001);
	
	list = forward_kinetic_for_chain (model->endeffector, model->base_link);
	des_xyz[0] = list->p.x;
	des_xyz[1] = list->p.y;
	des_xyz[2] = list->p.x;


	while (list) {
		//printf ("xyz: %lf, %lf,  %lf\n", list->p.x, list->p.y , list->p.z);
		next=list->next;
		free(list);
		list = next;
	}
}



void forward_calc() {
	struct vec3_list *list,*next;
	double des_xyz [3]= {9.411929, 7.603243, 1.539922};
	struct model * model =  init_robot();

	endeffector_grdient_decent (model, des_xyz, 0.001);
	
	list = forward_kinetic_for_chain (model->endeffector, model->base_link);
	while (list) {
		printf ("xyz: %lf, %lf,  %lf\n", list->p.x, list->p.y , list->p.z);
		next=list->next;
		free(list);
		list = next;
	}


	
}




