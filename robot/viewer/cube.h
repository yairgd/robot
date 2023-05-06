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

//class IShape;
#include "IShape.h"



class Cube: public IShape {

	private:
		int prevX;
		int prevY;
		bool isDragging;


		std::vector<connection> connectios{
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

		vec3 c{0,0,0};

	public:
		Cube () {
			float a = rand() % 200 ;
			float b = a +100;
			
			points.push_back({ a, a, a });
			points.push_back({ b, a, a });
			points.push_back({ b, b, a });
			points.push_back({ a, b, a });

			points.push_back({ a, a, b });
			points.push_back({ b, a, b });
			points.push_back({ b, b, b });
			points.push_back({ a, b, b });


#if 0
			points = std::vector {
				{ a, a, a },
					{ b, a, a },
					{ b, b, a },
					{ a, b, a },

					{ a, a, b },
					{ b, a, b },
					{ b, b, b },
					{ a, b, b }	
			};
#endif

			findCentroid();
		 }

		void processEvent(SDL_Event  * event) override {
			//while (SDL_PollEvent(event)) 
			//{
				switch (event->type)
				{
					case SDL_QUIT: 
						SDL_Quit();
						exit(0);
						break;
					case SDL_MOUSEBUTTONDOWN:
						if (event->button.button == SDL_BUTTON_LEFT)
						{
							isDragging = true;
							prevX = event->button.x;
							prevY = event->button.y;
							//if (x >= buttonRect.x && x <= buttonRect.x + buttonRect.w && y >= buttonRect.y && y <= buttonRect.y + buttonRect.h) {
							printf("Button clicked! %d %d\n",prevX,prevY);

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
							printf("Mouse drag! %d %d\n",dx,dy);

						}
						break;
						}
				//}


			}


			


			void update(IShape * shape ) override ;	
		};


#endif
