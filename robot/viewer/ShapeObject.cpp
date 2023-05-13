/*
 * =====================================================================================
 *
 *       Filename:  ShapeObject.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/12/2023 11:36:26 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include "ShapeObject.h"
#include "matrix.h"
#include "screen.h"
#include "CoordinateSystem.h"


void ShapeObject::draw(Screen *scr) {
	//rotate(0.1,0.1,0.1);
	CoordinateSystem cs(scr, x0,y0,640,480,scale);
	//CoordinateSystem cs(scr, 150,150,300,300);
	for ( auto s : m_shapes) {
		auto points = s->getPoints();
		for ( auto & p : points) {
			cs.pixel(p.dst.x, p.dst.y);
		}

	}
	for ( auto s : m_shapes) {
		auto conn = s->getConnections();
		auto points = s->getPoints();

		for ( auto & c : conn) {
			cs.line(points[c.a].dst.x, points[c.a].dst.y, points[c.b].dst.x, points[c.b].dst.y );
		}

	}

}

void ShapeObject::processEvent(SDL_Event  * event)  {
	//while (SDL_PollEvent(event)) 
	//{
	for ( auto s : m_shapes) {
		s->processEvent(event);
		
	}

	switch (event->type)
	{

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
				//rotate(-0.1*dx,0.1*dy,0.1*std::sqrt(dx*dx+dy*dy));


			}
			break;
			}
			//}


}






void ShapeObject::findCentroid() {
	int k = 0;

	for ( auto s : m_shapes) {
		auto points = s->getPoints();
		if (points.size()) {
			// Calaculate centroid
			m_centroid = vec3 {0,0,0};
			for (auto & p : points) {
				m_centroid.x += p.src.x;
				m_centroid.y += p.src.y;
				m_centroid.z += p.src.z;
			}
		}
		k += points.size();
	}
	m_centroid.x /= k;
	m_centroid.y /= k;
	m_centroid.z /= k;
}

