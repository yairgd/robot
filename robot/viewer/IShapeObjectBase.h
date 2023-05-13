/*
 * =====================================================================================
 *
 *       Filename:  IShapeObjectBase.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2023 08:57:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef SHAPE_OBJECT_BASE 
#define SHAPE_OBJECT_BASE 
#include <vector>
#include <cmath>
#include <memory>
#include "matrix.h"
#include "IShape.h"

class Screen;
class IShapeObjectBase {
	private:
		double Rx=0;
		double Ry=0;
		double Rz=0;
	public:
		virtual void findCentroid() = 0;
		virtual void draw(Screen *s) = 0;
		virtual void processEvent(SDL_Event  * event) = 0;	
		void setCentroid(vec3 centroid) {
			m_centroid = centroid;
		}
		void rotate(float x = 0, float y = 0, float z = 0) ;
	//	void setRotationAngle(double x,double y,double z) {
	//		Rx = x;
	//		Ry = y;
	//		Rz = z;
	//	}

	protected:
		std::vector<std::shared_ptr<IShape>> m_shapes;
		vec3 m_centroid;
		int x0,y0;

};
#endif
