/*
 * =====================================================================================
 *
 *       Filename:  AxisObject.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2023 09:23:01 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef AXIX_OBJECT_H
#define AXIX_OBJECT_H 
#include "IShapeObjectBase.h"

class AxisObject:public IShapeObjectBase {
	public:
		AxisObject() = default;
		AxisObject(std::vector<std::shared_ptr<IShape>> shapes) :IShapeObjectBase() {
			m_shapes = shapes;
			setCentroid({0,0,0});
		};
		void draw(Screen *s) override;	
		void findCentroid() override;

		void addAxis() {

		}
		void processEvent(SDL_Event  * event) override {
		}
		void setXRange(int xmin, int xmax) {
			x_min = xmin;
			x_max = xmax;
		}
		void setYRange(int ymin, int ymax) {
			y_min = ymin;
			y_max = ymax;
		}
		void setZRange(int zmin, int zmax) {
			z_min = zmin;
			z_max = zmax;
		}

	private:
		int x_min, x_max;
		int y_min, y_max;
		int z_min, z_max;


};
#endif
