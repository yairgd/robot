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



#include "IShapeObjectBase.h"

class ShapeObject:public IShapeObjectBase {
	public:
		ShapeObject() = default;
		ShapeObject(std::vector<std::shared_ptr<IShape>> shapes) :IShapeObjectBase() {
				m_shapes = shapes;
				findCentroid();
			};

		void draw(Screen *s) override;	
		void processEvent(SDL_Event  * event) override; 


		void findCentroid() override;
		void setPosition(double x,double y) {
			x0=x;
			y0=y;
		}
		void setScale(double s) {
			scale=s;
		}
		//void rotate(float x = 0, float y = 0, float z = 0);
		
	private:
		int prevX;
		int prevY;
		bool isDragging = false;
		double x0=0;//640/2;
		double y0=0;//480/2;
		double scale=1;


};
#endif

