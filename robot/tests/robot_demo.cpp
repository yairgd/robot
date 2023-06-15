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
#include "cube.h"
#include "AxisShape.h"
#include "ShapeObject.h"

#include "screen.h"
#include "optim.h"


extern "C" {
void forward_calc() ;
void forward_calc2() ;
}
int main(int argc, char* argv[]) {


	
	//forward_calc();
	//forward_calc2();

	//return 0;
	Screen screen(640*2,480*2);
	SDL_Event event;
	

	std::shared_ptr<IShape> robot = std::make_shared<Robot>();	
	//std::shared_ptr<IShape> cube = std::make_shared<Cube>();
	std::shared_ptr<IShape> axisShape = std::make_shared<AxisShape>();

	auto shapes = std::vector<std::shared_ptr<IShape>>({axisShape, robot});
	auto shapeObject = std::make_shared<ShapeObject>(shapes);
	shapeObject->setCentroid({0,0,0});
	shapeObject->setPosition(320,240);
	shapeObject->setScale(10);

	//axisShape->setXRange(-100,100);
	//axisShape->setYRange(-100,100);
	//axisShape->setZRange(-100,100);
	//axisObject->rotate(0.1, 0.1, 0.1);
	screen.addShapeObject(shapeObject);

//	shapeObject->rotate(0.01, 0.01, 0.001);		
	shapeObject->rotate(0.1, 0.1, 0.00);	
	double x=0,y=0,z=0;
	while (true) {
		screen.show();
		screen.clear();
		screen.processEvent(&event);
		screen.draw();
		//shapeObject->rotate(-0.1, 0.5, 0.5);		
		//	shapeObject->rotate(0.0, 0.0, 0.00);	

		shapeObject->rotate(0.0, 0.0, 0.000);		

//		shapeObject->rotate(0.0, 0.01, x+=0.001);		
		SDL_Delay(30);
	}	
}

