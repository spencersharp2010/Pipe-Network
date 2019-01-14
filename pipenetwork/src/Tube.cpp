#include "Tube.hpp"
#include <cmath>

namespace cie
{
	namespace pipenetwork
	{
		Tube::Tube(Node* node1, Node* node2, double diameter)
		{
			node1_ = node1;
			node2_ = node2;
			diameter_ = diameter;
		}

		double Tube::length() const
		{
			double xdistance = node1_->x() - node2_->x();
			double ydistance = node1_->y() - node2_->y();
			double length = sqrt(xdistance*xdistance + ydistance*ydistance);
			return length;

		}

		double Tube::permeability() const
		{
			const double pi = 3.141592653588979323846;
			const double g = 9.81;
			const double nu = pow(10, -6);

			//double diameter = diameter();
			double length = Tube::length();
			double B_i = (pi * g * pow(diameter_, 4)) / (128 * nu * length);
			return B_i;

		}

		const Node* Tube::node1() const
		{
			return node1_;

		}

		const Node* Tube::node2() const
		{
			return node2_;
		}

		double Tube::diameter() const
		{
			return diameter_;
		}
	}

}
