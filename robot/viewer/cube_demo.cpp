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




int main(int argc, char* argv[]) {
	Screen screen;
	SDL_Event event;
	
	auto cube = std::make_shared<Cube>();
	auto cube1 = std::make_shared<Cube>();
	auto cube2 = std::make_shared<Cube>();

	screen.addShape(cube);
	screen.addShape(cube1);
	screen.addShape(cube2);

	while (true) {
		screen.show();
		screen.clear();
		screen.processEvent(&event);
		screen.update();
		SDL_Delay(30);
	}	
}

