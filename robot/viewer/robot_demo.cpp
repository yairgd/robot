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




int main(int argc, char* argv[]) {
	Screen screen(640*2,480*2);
	SDL_Event event;
	
	auto robot = std::make_shared<Robot>();

	screen.addShape(robot);

	while (true) {
		screen.show();
		screen.clear();
		screen.processEvent(&event);
		screen.update();
		SDL_Delay(30);
	}	
}

