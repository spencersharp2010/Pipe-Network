#ifndef TUBE
#define TUBE

#include "Node.hpp"

namespace cie
{
	namespace pipenetwork 
	{
		class Tube
		{
		public:
			Tube(Node* node1, Node* node2, double diameter);
			double length() const;
			double permeability() const;
			double diameter() const;
			const Node* node1() const;
			const Node* node2() const;
		private:
			Node* node1_;
			Node* node2_;
			double permeability_;
			double length_;
			double diameter_;

		};
	}
}
#endif
