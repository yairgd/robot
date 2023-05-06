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


class Robot: public IShape {

	private:
		int prevX;
		int prevY;
		bool isDragging;


		std::vector<vec3> points; 
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
		Robot () {
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

			// Calaculate centroid
			for (auto & p : points) {
				c.x += p.x;
				c.y += p.y;
				c.z += p.z;
			}
			c.x /= points.size();
			c.y /= points.size();
			c.z /= points.size();
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


			void rotate(vec3& point, float x = 0, float y = 0, float z = 0) {
				float cx = std::cos(x);
				float sx = std::sin(x);
				float cy = std::cos(y);
				float sy = std::sin(y);
				float cz = std::cos(z);
				float sz = std::sin(z);

				// rotate around x-axis
				float py = point.y * cx - point.z * sx;
				float pz = point.y * sx + point.z * cx;

				// rotate around y-axis
				float px = point.x * cy + pz * sy;
				pz = -point.x * sy + pz * cy;

				// rotate around z-axis
				float px2 = px * cz - py * sz;
				float py2 = px * sz + py * cz;

				point.x = px2;
				point.y = py2;
				point.z = pz;
			}


			void update(IShape * shape ) override ;	
		};


#endif
