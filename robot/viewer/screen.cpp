/*
 * =====================================================================================
 *
 *       Filename:  screen.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2023 05:53:17 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#include "screen.h"

#include <SDL2/SDL.h>

void Screen::processEvent(SDL_Event  * event) 
{
	while (SDL_PollEvent(event)) {
		for ( auto s : shapes) {
			s->processEvent(event);
		}
	}

}


void Screen::update(IShape * shape) 
{
	for ( auto s : shapes) {
		s->update(this);
	}

}

