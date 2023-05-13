/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/2023 03:54:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>

#include <iostream>
#include <memory>

#include "robot.h"

#include "screen.h"

#include "CoordinateSystem.h"


void Robot::update( )   {
	//auto s = reinterpret_cast<Screen *>(screen);
	
	//CoordinateSystem cs(s, 150,150,300,300);

	calc_grdient_decent(phi,links, des_xyz,0.001);
	//jacobian_pseudoinverse_optimization(phi,links, des_xyz,3,0.001);

	
	double *alpha=0;
	double *beta=0;
	//double gamma[] =  {0, 0.401455, 0.666982};
//	float x0 = 100;
//	float y0 = 100;



	forward_kinematic(links,alpha, beta , phi, xyz, 3) ;
	des_xyz[0] = xyz[2].x;
	des_xyz[1] = xyz[2].y;
	des_xyz[2] = xyz[2].z;
#if 0
	

//	for (int i = 0; i < 3; i++) {
//		xyz[i].x = xyz[i].x*20 + x0;
//		xyz[i].y = xyz[i].y*20 + y0;
//	}

//	printf("%lf %lf %lf\n",xyz[2].x,xyz[2].y,xyz[2].z);
	cs.pixel(0,0);	
	cs.pixel(xyz[0].x,xyz[0].y);
	cs.pixel(xyz[1].x,xyz[1].y);
	cs.pixel(xyz[2].x,xyz[2].y);

	cs.line(0,0, xyz[0].x,xyz[0].y);
	cs.line(xyz[0].x,xyz[0].y, xyz[1].x,xyz[1].y);
	cs.line(xyz[1].x,xyz[1].y, xyz[2].x,xyz[2].y);

	cs.grid();
#endif
}




