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


#ifndef ROBOT_H
#define ROBOT_H 
#include <vector>
#include "screen.h"
#include "IShape.h"
#include "optim.h"


class Robot: public IShape {

	private:
		int prevX;
		int prevY;
		bool isDragging;


		std::vector<point> points; 
		std::vector<connection> connectios;

		double des_xyz[3] = { 12.411930818340064, 7.603239324984113,0};
		double links[3]={4.0,6.0,6.0};
		vec3 xyz[3]={0};

		//double phi[] = {0.000000, 0.401455, 0.666982};

		double phi[3] = {0.000000, 0.401455, 0.666982};


	public:
		Robot () {

			points.clear();
			points = std::vector<point> {
				{{ 0,0,0 },{0,0,0}},
				{{ 0,0,0 },{0,0,0}},
				{{ 0,0,0 },{0,0,0}},
				{{ 0,0,0 },{0,0,0}},
			};

	
			connectios = std::vector<connection> {
				{ 0, 1 },
				{ 1, 2 },
				{ 2, 3 },
			};

		//	points.push_back({{0,0,0},{0,0,0}});
		//	points.push_back({{0,0,0},{0,0,0}});
		//	points.push_back({{0,0,0},{0,0,0}});
		//	points.push_back({{0,0,0},{0,0,0}});

			// Calaculate centroid
			//findCentroid();
		}
		virtual std::vector< point > &  getPoints() override {
			calc_grdient_decent(phi,links, des_xyz,0.001);
			//jacobian_pseudoinverse_optimization(phi,links, des_xyz,3,0.001);

			double *alpha=0;
			double *beta=0;

			forward_kinematic(links,alpha, beta , phi, xyz, 3) ;
			des_xyz[0] = xyz[2].x;
			des_xyz[1] = xyz[2].y;
			des_xyz[2] = xyz[2].z;
			//ints.clear();
			//ints.push_back({0,0,0},{0,0,0}};
			for (int i =0; i < 3; i++) {
				points[i+1].src = xyz[i];
			}
			return points;
		}		

		void processEvent(SDL_Event  * event) override {
			//while (SDL_PollEvent(event)) 
			//{
			switch (event->type)
			{
				case SDL_KEYDOWN:
					{
						switch(event->key.keysym.sym)
						{

							case SDLK_UP:// keyText = loadText(255, 200, 50, "lazy.ttf", 50, "Up was pressed");
								des_xyz[1] +=0.1;
								//	printf("inrease !!\n");
								break;
							case SDLK_DOWN:// keyText = loadText(255, 200, 50, "lazy.ttf", 50, "Down was pressed");
								       //printf("decrease !!\n");								       // 
								des_xyz[1] -=0.1;
								break;
							case SDLK_LEFT:// keyText = loadText(255, 200, 50, "lazy.ttf", 50, "Left was pressed");
								des_xyz[0] -=0.1;									
								break;
							case SDLK_RIGHT:// keyText = loadText(255, 200, 50, "lazy.ttf", 50, "Right was pressed");
								des_xyz[0] +=0.1;									
								break;
							default:;
						}
						printf("%lf %lf %lf\n",xyz[2].x,xyz[2].y,xyz[2].z);

						break;
					}

				case SDL_MOUSEBUTTONDOWN:
					if (event->button.button == SDL_BUTTON_LEFT)
					{
						isDragging = true;
						prevX = event->button.x;
						prevY = event->button.y;
						//if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
						//printf("Button clicked! %d %d\n",prevX,prevY);



					}
					break;
						case SDL_MOUSEBUTTONUP:
					if (event->button.button == SDL_BUTTON_LEFT)
					{
						isDragging = false;
					}
					break;
						case SDL_MOUSEMOTION:
					if (isDragging)
					{
						int currX = event->motion.x;
						int currY = event->motion.y;
						int dx = currX - prevX;
						int dy = currY - prevY;
						// do something with dx and dy
						prevX = currX;
						prevY = currY;
						//		printf("Mouse drag! %d %d\n",dx,dy);


					}
					break;
					}
					//}


		}


		virtual std::vector< connection > &  getConnections() override{
			return connectios;
		}
		void update() override ;	
		};


#endif