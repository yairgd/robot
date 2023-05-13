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
#ifndef SCREEN_H
#define SCREEN_H 

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <iostream>
#include <memory>


#include "ShapeObject.h"


//class IShape;
class Screen  {
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<SDL_FPoint> points;
	std::vector<std::shared_ptr<ShapeObject>> m_shapeObjects;

	int prevX = 0, prevY = 0;
	bool isDragging = false;


	public:
	Screen(int width, int height) {
		SDL_Init(SDL_INIT_VIDEO);
		SDL_CreateWindowAndRenderer(width,height,0,&window, &renderer);
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

	//std::vector< vec3 > getPoints() override {
	//		return points;
	//	}	
	
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

// draw x axis
 //   SDL_RenderDrawLine(renderer, 0, 240, 640, 240);

    // draw y axis
   // SDL_RenderDrawLine(renderer, 340, 0, 340, 480);

    
		SDL_RenderPresent(renderer);	
	}

	void clear() {
		points.clear();
	}

	void line(float x1, float y1, float x2, float y2){
#if 1
		float dx = x2 - x1;
		float dy = y2 - y1;

		float length = std::sqrt(dx * dx + dy*dy);
		float angle = std::atan2(dy,dx);

		for (float i = 0; i < length; i++) {
			pixel(x1+std::cos(angle) * i,y1+std::sin(angle) * i);
		}
#endif
		//SDL_RenderDrawLine(renderer, x1, y1, x2, y2);

	}

	void addShapeObject(std::shared_ptr<ShapeObject> shapeObject ) {
		m_shapeObjects.push_back(shapeObject);
	}

	void draw()  ;


	void processEvent(SDL_Event  * event = nullptr  ) ;
};


#endif
