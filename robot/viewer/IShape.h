/*
 * =====================================================================================
 *
 *       Filename:  IShape.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2023 02:44:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>
#ifndef ISHAEPE
#define ISHAEPE 

#include <vector>
#include "matrix.h"


struct connection {
	int a,b;
};


struct point {
	vec3 src;
	vec3 dst;
};
class IShape {	

	public:
		std::vector<point> points; 
		std::vector<connection> connectios;

		virtual void processEvent(SDL_Event * event) = 0;
		virtual void update() = 0;
		virtual std::vector< point > &  getPoints() = 0;
		virtual std::vector< connection > &  getConnections() = 0;

		


};

#endif
