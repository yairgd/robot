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

#include "ShapeObject.h"
#include "cube.h"
#include "screen.h"




int main(int argc, char* argv[]) {
	Screen screen(640*2,480*2);;
	SDL_Event event;
	
	std::shared_ptr<IShape> cube = std::make_shared<Cube>();
	auto shapes = std::vector<std::shared_ptr<IShape>>({cube});
	auto shapeObject = std::make_shared<ShapeObject>(shapes);
	shapeObject->setPosition(320,240);
	shapeObject->setScale(1);

	screen.addShapeObject(shapeObject);
	
	double x=0,y=0,z=0;
	while (true) {
		screen.show();
		screen.clear();
		screen.processEvent(&event);
		screen.draw();
		//shapeObject->setRotationAngle(x+=0.001,y+=0.001,z+=0.001);
		shapeObject->rotate(0.1, 0.1, z+=0.001);		
		SDL_Delay(30);
	}	
}

