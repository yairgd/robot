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

				case 0000: //SDL_KEYDOWN:
				switch (event->key.keysym.sym) {
					case SDLK_x:
						rot_axis = 0;
						break;
					case SDLK_y:
						rot_axis = 1;
						break;
					case SDLK_z:
						rot_axis = 2;
						break;					
					case SDLK_UP:
						switch  (rot_axis) {
							case 0: Rz+=0.01;break;
							case 1: Rz+=0.01;break;
							case 2: Rx+=0.01;break;
						}
						rotate(Rx,Ry,Rz);
						break;
					case SDLK_DOWN:
						switch  (rot_axis) {
							case 0: Rz-=0.01;break;
							case 1: Rz-=0.01;break;
							case 2: Rx-=0.01;break;
						}
						rotate(Rx,Ry,Rz);						
						break;
					case SDLK_LEFT:
						switch  (rot_axis) {
							case 0: Ry+=0.01;break;
							case 1: Rx+=0.01;break;
							case 2: Ry+=0.01;break;
						}
						rotate(Rx,Ry,Rz);
						break;
					case SDLK_RIGHT:
						switch  (rot_axis) {
							case 0: Ry-=0.01;break;
							case 1: Rx-=0.01;break;
							case 2: Ry-=0.01;break;
						}
						rotate(Rx,Ry,Rz);						
						break;




				}
			break;
		}
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


void ShapeObject::rotate(float x , float y, float z) {
	auto do_3d_rotate = [&](vec3& point, float x , float y, float z) ->void {
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

	};
	auto do_rotate = [&](point &p) -> void {
		p.dst = p.src;

		p.dst.x -= m_centroid.x;
		p.dst.y -= m_centroid.y;
		p.dst.z -= m_centroid.z;
		do_3d_rotate(p.dst,Rx,Ry,Rz);
		p.dst.x += m_centroid.x;
		p.dst.y += m_centroid.y;
		p.dst.z += m_centroid.z;
	};	
	for ( auto   s : m_shapes) {
		//		s->update();
		auto  & points = s->getPoints();
		for (auto &p : points) {
			do_rotate(p);
		}
	}
	Rx = x;
	Ry = y;
	Rz = z;

}
