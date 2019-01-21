#include "Tube.hpp"
#include <cmath>

namespace cie
{
	namespace pipenetwork
	{
		//constructor: aggregates node1 and node2 information via pointers and diameter data
		Tube::Tube(Node* node1, Node* node2, double diameter)
		{
			node1_ = node1;
			node2_ = node2;
			diameter_ = diameter;
		}

		//calculates and returns length of tube based on data aggregated from node instances
		double Tube::length() const
		{
			double xdistance = node1_->x() - node2_->x();		//calculates x distance between node1 and node2
			double ydistance = node1_->y() - node2_->y();		//calculates x distance between node1 and node2
			double length = sqrt(xdistance*xdistance + ydistance*ydistance);		//pythagorean theorem
			return length;

		}

		//calculates and returns permeability (B_i) of tube
		double Tube::permeability() const
		{
			const double pi = 3.141592653588979323846;	//value of pi
			const double g = 9.81;						//gravity
			const double nu = pow(10, -6);				//viscosity

			//double diameter = diameter();
			double length = Tube::length();				//find length via pre-defined length function above
			double B_i = (pi * g * pow(diameter_, 4)) / (128 * nu * length);	//given formula for permeability
			return B_i;

		}

		//return pointer to node1
		const Node* Tube::node1() const
		{
			return node1_;
		}

		//return pointer to node2
		const Node* Tube::node2() const
		{
			return node2_;
		}

		//return diameter of tube
		double Tube::diameter() const
		{
			return diameter_;
		}
	}

}
