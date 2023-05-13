/*
 * =====================================================================================
 *
 *       Filename:  IShapeObjectBase.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2023 09:02:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#include "IShapeObjectBase.h"


static void _rotate(vec3& point, float x , float y, float z) {
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

void IShapeObjectBase::rotate(float x , float y, float z) {
	auto do_rotate = [&](point &p) -> void {
		p.dst = p.src;
		
		p.dst.x -= m_centroid.x;
		p.dst.y -= m_centroid.y;
		p.dst.z -= m_centroid.z;
		_rotate(p.dst,x,y,z);
		p.dst.x += m_centroid.x;
		p.dst.y += m_centroid.y;
		p.dst.z += m_centroid.z;
	};	
	for ( auto   s : m_shapes) {
		s->update();
		auto  & points = s->getPoints();
		for (auto &p : points) {
			do_rotate(p);
		}
	}
}
