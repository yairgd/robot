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



#include <cmath>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <iostream>

#include "screen.h"


// screen dimensions
void rotate_nice_bug (vec3 & point, float x = 1, float y = 1, float z = 1)
{
	point.y = std::cos(x) * point.y - std::sin(x) * point.z;
	point.z = std::sin(x) * point.y + std::cos(x) * point.z;

	point.x = std::cos(y) * point.x + std::sin(y) * point.z;
	point.z = -std::sin(y) * point.x + std::cos(y) * point.z;

	point.x = std::cos(z) * point.x - std::sin(z) * point.y;
	point.y = std::sin(z) * point.x + std::cos(z) * point.y;
}

void rotate(vec3& point, float x = 0, float y = 0, float z = 0) {
	float cx = std::cos(x);
	float sx = std::sin(x);
	float cy = std::cos(y);
	float sy = std::sin(y);
	float cz = std::cos(z);
	float sz = std::sin(z);

	// rotate around x-axis
	float py = point.y * cx - point.z * sx;
	float pz = point.y * sx + point.z * cx;

	// rotate around y-axis
	float px = point.x * cy + pz * sy;
	pz = -point.x * sy + pz * cy;

	// rotate around z-axis
	float px2 = px * cz - py * sz;
	float py2 = px * sz + py * cz;

	point.x = px2;
	point.y = py2;
	point.z = pz;
}



SDL_Event event;

void input() 
{
	static int prevX;
	static int prevY;
	static bool isDragging;

	while (SDL_PollEvent(&event)) 
	{
		switch (event.type)
		{
			case SDL_QUIT: 
				SDL_Quit();
				exit(0);
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					isDragging = true;
					prevX = event.button.x;
					prevY = event.button.y;
					//if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
					printf("Button clicked! %d %d\n",prevX,prevY);

				}
				break;
					case SDL_MOUSEBUTTONUP:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					isDragging = false;
				}
				break;
					case SDL_MOUSEMOTION:
				if (isDragging)
				{
					int currX = event.motion.x;
					int currY = event.motion.y;
					int dx = currX - prevX;
					int dy = currY - prevY;
					// do something with dx and dy
					prevX = currX;
					prevY = currY;
					printf("Mouse drag! %d %d\n",dx,dy);

				}
				break;
				}
		}


	}


	int main(int argc, char* argv[]) {
		Screen screen;
		std::vector<vec3> points {
			{ 100., 100., 100. },
				{ 200., 100., 100. },
				{ 200., 200., 100. },
				{ 100., 200., 100. },

				{ 100., 100., 200. },
				{ 200., 100., 200. },
				{ 200., 200., 200. },
				{ 100., 200., 200. },	
		};
		std::vector<connection> connectios{
			{ 0, 1 },
				{ 1, 2 },
				{ 2, 3 },
				{ 3, 0 },
				{ 4, 5 },
				{ 5, 6 },
				{ 6, 7 },
				{ 7, 4 },
				{ 0, 4 },
				{ 1, 5 },
				{ 2, 6 },
				{ 3, 7 },
		};
		for (int i = 0; i < 100; i++) {
			screen.pixel(rand()%640, rand()%480);
		}

		// Calaculate centroid
		vec3 c{0,0,0};
		for (auto & p : points) {
			c.x += p.x;
			c.y += p.y;
			c.z += p.z;
		}
		c.x /= points.size();
		c.y /= points.size();
		c.z /= points.size();
		while (true) {
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

			for (auto & conn: connectios) {
				screen.line(points[conn.a].x , points[conn.a].y, points[conn.b].x , points[conn.b].y);
			}

			screen.show();
			screen.clear();
			SDL_Delay(30);
			input();
		}	
	}

