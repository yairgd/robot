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
#include "optimization.h"
#include "template.h"

#include  <thread>
#include  <chrono>
using namespace std::chrono_literals;

class Robot: public IShape {

	private:
		int prevX;
		int prevY;
		bool isDragging;


		std::vector<point> points; 
		std::vector<connection> connectios;

		//double des_xyz[3] = { 12.411930818340064, 7.603239324984113,0};
		struct gradient_info * info = get_endeffector_cost_function_gradient_info((double [3]){-2.437466, -4.519042,  11.326713});


//		double links[3]={4.0,6.0,6.0};
//		vec3 xyz[4]={0};

		//double phi[] = {0.000000, 0.401455, 0.666982};

//		double phi[3] = {0.000000, 0.401455, 0.666982};
		//struct model * model =  init_robot();
		bool has_change = true;	


	public:
		Robot () {

			points.clear();
			points = std::vector<point> {
				{{ 0,0,0 },{0,0,0}},
					{{ 0,0,0 },{0,0,0}},
					{{ 0,0,0 },{0,0,0}},
					{{ 0,0,0 },{0,0,0}},
					{{ 0,0,0 },{0,0,0}},
					
			};


			connectios = std::vector<connection> {
				{ 0, 1 },
					{ 1, 2 },
					{ 2, 3 },
					{ 3, 4 },

			};


			//	points.push_back({{0,0,0},{0,0,0}});
			//	points.push_back({{0,0,0},{0,0,0}});
			//	points.push_back({{0,0,0},{0,0,0}});
			//	points.push_back({{0,0,0},{0,0,0}});

			// Calaculate centroid
			//findCentroid();
		}
		virtual std::vector< point > &  getPoints() override {
			struct vec3_list *list,*next;
			if (!has_change)
				return points;
			has_change = false;

			//static int cnt = 0;
			//double grad[4];

//			if (cnt++ % 100 != 0)
//				return points;

			//endeffector_grdient_decent (model, des_xyz, 0.001); TODO CHANGE

			gradient_decent (info , 0.001,10000);
			
			//list = forward_kinetic_for_chain (model->endeffector, model->base_link);
			list =  forward_kinetic(info->variables);
			
	

			int k = 0;
			while (list) {
				points[k++].src = list->p;
				//printf ("xyz: %lf, %lf,  %lf\n", list->p.x, list->p.y , list->p.z);
				next=list->next;
				free(list);
				list = next;
			}


			//inverse_kinetic_calc(model,  des_xyz) ;

			//			calc_grdient_decent(phi,links, des_xyz,0.001);
			//jacobian_pseudoinverse_optimization(phi,links, des_xyz,3,0.001);

			double *alpha=0;
			double *beta=0;

			//forward_kinematic(links,alpha, beta , phi, xyz, 3) ;
			info->des_xyz[0] = points[0].src.x;
			info->des_xyz[1] = points[0].src.y;
			info->des_xyz[2] = points[0].src.z;
			//ints.clear();
			//ints.push_back({0,0,0},{0,0,0}};
			//for (int i =0; i < 4; i++) {
			//	points[i].src = xyz[i];
			//}
			//std::this_thread::sleep_for(100ms);
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
						info->des_xyz[1] +=0.1;
						has_change = true;

						//model->variables[1] +=0.1;	!!

						//	printf("inrease !!\n");
						break;
					case SDLK_DOWN:// keyText = loadText(255, 200, 50, "lazy.ttf", 50, "Down was pressed");
						       //printf("decrease !!\n");								       // 
						info->des_xyz[1] -=0.1;
						has_change = true;

						//model->variables[1] -=0.1;	 !!

						break;
					case SDLK_LEFT:// keyText = loadText(255, 200, 50, "lazy.ttf", 50, "Left was pressed");
						info->des_xyz[0] -=0.1;	
						has_change = true;

						//model->variables[3] -=0.1;	 !!
						break;
					case SDLK_RIGHT:// keyText = loadText(255, 200, 50, "lazy.ttf", 50, "Right was pressed");
						info->des_xyz[0] +=0.1;	
						has_change = true;

						//model->variables[3] +=0.1;	!!						 
						break;
					default:;
				}
				printf("%lf %lf %lf\n",points[0].dst.x,points[0].dst.y,points[0].dst.z);

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
