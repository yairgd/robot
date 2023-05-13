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
		switch (event->type) {
			{
				case SDL_QUIT: 
					SDL_Quit();
					exit(0);
					break;
			}
		}
		for ( auto s : m_shapeObjects) {
			s->processEvent(event);
		}

	}

}


void Screen::draw() 
{
	for ( auto s : m_shapeObjects) {
		s->draw(this);
	}

}

