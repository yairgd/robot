/*
 * =====================================================================================
 *
 *       Filename:  AxisShape.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/13/2023 11:19:18 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Yair Gadelov (yg), yair.gadelov@gmail.com
 *        Company:  Israel
 *
 * =====================================================================================
 */

#ifndef AXIS_SHAPE
#define AXIS_SHAPE 
class AxisShape: public IShape {
	public:
		AxisShape () {
			connectios = std::vector<connection> {
				{ 0, 1 },
					{ 2, 3 },
					{ 4, 5 },
			};


		}

		virtual std::vector<point>  &  getPoints() override {
			if (points.size() == 0) {
				points.push_back({{x_min,0,0},{0}});
				points.push_back({{x_max,0,0},{0}});
				points.push_back({{0,y_min,0},{0}});				
				points.push_back({{0,y_max,0},{0}});
				points.push_back({{0,0,z_min},{0}});				
				points.push_back({{0,0,z_max},{0}});

			};
			return points;
		}		

		virtual std::vector< connection > &  getConnections() override{
			return connectios;
		}


		void processEvent(SDL_Event  * event) override {
		}



		void update( ) override {
		}


		void setXRange(double xmin, double xmax) {
			x_min = xmin;
			x_max = xmax;
			points.clear();
		}
		void setYRange(double ymin, double ymax) {
			y_min = ymin;
			y_max = ymax;
			points.clear();
		}
		void setZRange(double zmin, double zmax) {
			z_min = zmin;
			z_max = zmax;
			points.clear();			
		}



	private:
		double x_min=-100;
		double x_max=100;
		double y_min=-100; 
		double y_max=100;
		double z_min=-100; 
		double z_max=100;

};

#endif
