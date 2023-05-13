/*
 * =====================================================================================
 *
 *       Filename:  CoordinateSystem.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/09/2023 10:10:25 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */
#ifndef	CoordinateSystem_H
#define CoordinateSystem_H 

#include "screen.h"
class CoordinateSystem {
	public:
	CoordinateSystem(Screen * screen, int x, int y, int width, int height,double scale):
		m_screen(screen),m_x(x), m_y(y), m_width(width), m_height(height), m_scale(scale){};

	void pixel(float x, float y) {
		y=-y;
		x = x * m_scale  + m_x;
		y = y * m_scale + m_y;

		m_screen->pixel(x,y);
	}
	void line(float x1, float y1, float x2,float y2) {
		y1=-y1;
		y2=-y2;
		x1 = x1 * m_scale + m_x ;
		y1 = y1 * m_scale + m_y ;
		x2 = x2 * m_scale + m_x ;
		y2 = y2 * m_scale + m_y ;
		
		m_screen->line(x1,y1,x2,y2);
	}
	void grid() {
	    m_screen->line(m_x + m_width/2, m_y , m_x + m_width/2,m_y + m_height);
	    m_screen->line(m_x  , m_y + m_height/2 , m_x + m_width ,m_y + m_height/2);

	    // rectagne afround the axis
	    m_screen->line(m_x  , m_y , m_x + m_width ,m_y);
	    m_screen->line(m_x  , m_y+m_height , m_x + m_width ,m_y+m_height);
	    m_screen->line(m_x  , m_y , m_x ,m_y+m_height);
	    m_screen->line(m_x+m_width  , m_y , m_x+m_width ,m_y+m_height);

//	    SDL_RenderDrawLine(renderer, 340, 0, 340, 480);		
	}

	private:
		double m_x, m_y;
		int m_width, m_height;
		Screen *m_screen;
		double m_scale = 20;
};
#endif

