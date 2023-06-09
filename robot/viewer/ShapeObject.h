/*
 * =====================================================================================
 *
 *       Filename:  ShapeObject.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/12/2023 11:36:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#ifndef SHAPEOBJECT_H
#define SHAPEOBJECT_H 


#include <vector>
#include <cmath>
#include <memory>
#include "matrix.h"
#include "IShape.h"

class Screen;


class ShapeObject {
	public:
		ShapeObject() = default;
		ShapeObject(std::vector<std::shared_ptr<IShape>> shapes)  {
				m_shapes = shapes;
				findCentroid();
			};

		void draw(Screen *s) ;	
		void processEvent(SDL_Event  * event) ; 


		void findCentroid();
		void setPosition(double x,double y) {
			x0=x;
			y0=y;
		}
		void setScale(double s) {
			scale=s;
		}
		
		void setCentroid(vec3 centroid) {
			m_centroid = centroid;
		}
		void rotate(float x = 0, float y = 0, float z = 0) ;
		void setRotationAngle(double x,double y,double z) {
			Rx = x;
			Ry = y;
			Rz = z;
		}

	private:
		int prevX;
		int prevY;
		bool isDragging = false;
		double x0=0;//640/2;
		double y0=0;//480/2;
		double scale=1;
		double Rx=0;
		double Ry=0;
		double Rz=0;
		std::vector<std::shared_ptr<IShape>> m_shapes;
		vec3 m_centroid;
		int rot_axis = 0;


};
#endif

