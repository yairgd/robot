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


#include "IShape.h"

// screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//class IShape;
class Screen : public IShape {
	SDL_Window *window;
	SDL_Renderer *renderer;
	std::vector<SDL_FPoint> points;
	std::vector<std::shared_ptr<IShape>> shapes;

	int prevX = 0, prevY = 0;
	bool isDragging = false;


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

	void clear() {
		points.clear();
	}

	void line(float x1, float y1, float x2, float y2){
		float dx = x2 - x1;
		float dy = y2 - y1;

		float length = std::sqrt(dx * dx + dy*dy);
		float angle = std::atan2(dy,dx);

		for (float i = 0; i < length; i++) {
			pixel(x1+std::cos(angle) * i,y1+std::sin(angle) * i);
		}
	}

	void addShape(std::shared_ptr<IShape> shape ) {
		shapes.push_back(shape);
	}

	void update(IShape * shape = nullptr) override ;


	void processEvent(SDL_Event  * event = nullptr  ) override;
};


#endif
