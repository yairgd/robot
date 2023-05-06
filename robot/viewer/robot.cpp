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

#include "cube.h"

#include "screen.h"




void Robot::update(IShape   * screen )   {
	int k=0;
	for (auto &p : points) {
		p.x -= c.x;
		p.y -= c.y;
		p.z -= c.z;
		rotate(p,0.01,0.05,0.05);
		p.x += c.x;
		p.y += c.y;
		p.z += c.z;

	}

	auto s = reinterpret_cast<Screen *>(screen);
	for (auto & conn: connectios) {
		s->line(points[conn.a].x , points[conn.a].y, points[conn.b].x , points[conn.b].y);
	}
}




