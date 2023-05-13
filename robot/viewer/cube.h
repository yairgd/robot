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


#ifndef CUBE_H
#define CUBE_H 
#include <vector>


#include "screen.h"
#include "IShape.h"



class Cube: public IShape {


	public:
		Cube () {
			float a = 50; //rand() % 200 ;
			float b = 100;// a +100;

			points = std::vector<point> {
				{{ a, a, a },{0,0,0}},
				{{ b, a, a },{0,0,0}},
				{{ b, b, a },{0,0,0}},
				{{ a, b, a },{0,0,0}},

				{{ a, a, b },{0,0,0}},
				{{ b, a, b },{0,0,0}},
				{{ b, b, b },{0,0,0}},
				{{ a, b, b },{0,0,0}},

			};

			connectios = std::vector<connection> {
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

		}

		virtual std::vector<point>  &  getPoints() override {
			return points;
		}		

		virtual std::vector< connection > &  getConnections() override{
			return connectios;
		}


		void processEvent(SDL_Event  * event) override {
		}



		void update( ) override ;	
		};


#endif
