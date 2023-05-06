/*
 * =====================================================================================
 *
 *       Filename:  IShape.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/06/2023 02:44:36 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#include <SDL2/SDL.h>
#ifndef ISHAEPE
#define ISHAEPE 

#include <vector>

struct vec3 
{
	double  x,y,z;
};

struct connection {
	int a,b;
};



class IShape {	
	
	public:
		std::vector<vec3> points; 
	vec3 centroid;
	
		virtual void processEvent(SDL_Event * event) = 0;
		virtual void update(IShape *) = 0;

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
		void findCentroid() {
			// Calaculate centroid
			centroid = vec3 {0,0,0};
			for (auto & p : points) {
				centroid.x += p.x;
				centroid.y += p.y;
				centroid.z += p.z;
			}
			centroid.x /= points.size();
			centroid.y /= points.size();
			centroid.z /= points.size();
		}



};

#endif
