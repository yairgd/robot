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


#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <iostream>
// screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct vec3 
{
	double  x,y,z;
};

struct connection {
	int a,b;
};

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

class Screen {
	SDL_Event e;
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<SDL_FPoint> points;

	public:
	Screen() {
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(640*2,480*2,0,&window, &renderer);
		SDL_RenderSetScale(renderer,2,2);
#if 0
		// create window and renderer
		window = SDL_CreateWindow("SDL Line", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (!window) {
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!renderer) {
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		}
#endif

	}
	void pixel(float x, float y) {
		points.push_back({x,y});
	}

	void show() {
		SDL_SetRenderDrawColor(renderer, 0,0,0,255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor (renderer, 255, 255, 255, 255);
		for (auto & point: points) {
			SDL_RenderDrawPointF(renderer, point.x, point.y);
		}
		SDL_RenderPresent(renderer);	
	}
	void input() {
		while (SDL_PollEvent(&e)) 
		{
			if (e.type == SDL_QUIT) {
				SDL_Quit();
				exit(0);
			} else if (e.type == SDL_MOUSEBUTTONDOWN) {
				if (e.button.button == SDL_BUTTON_LEFT) {
					// check if button was clicked
					int x = e.button.x;
					int y = e.button.y;
					//if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
					printf("Button clicked! %d %d\n",x,y);
					//}
				}
			}
		}
	}

	void clear() {
		points.clear();
	}
};

void line(Screen &screen, float x1, float y1, float x2, float y2){
	float dx = x2 - x1;
	float dy = y2 - y1;

	float length = std::sqrt(dx * dx + dy*dy);
	float angle = std::atan2(dy,dx);

	for (float i = 0; i < length; i++) {
		screen.pixel(x1+std::cos(angle) * i,y1+std::sin(angle) * i);

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
			rotate(p,0.0,0.05,0.05);
			
			if (k==0)
				std::cout<<std::sqrt((p.x-c.x)*(p.x-c.x))<<" "<<std::sqrt((p.y-c.y)*(p.y-c.y))<<" "<<std::sqrt((p.z-c.z)*(p.z-c.z))<<std::endl;
			k++;

			p.x += c.x;
			p.y += c.y;
			p.z += c.z;


		}

		for (auto & conn: connectios) {
			line(screen, points[conn.a].x , points[conn.a].y, points[conn.b].x , points[conn.b].y);
		}

		screen.show();
		screen.clear();
		screen.input();
		SDL_Delay(30);
	}	
}

