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
			Tube(Node* node1, Node* node2, double diameter);	//constructor
			double length() const;					//returns length of tube
			double permeability() const;			//returns permeability of tube
			double diameter() const;				//returns diameter of tube
			const Node* node1() const;				//returns pointer to instance of node1 associated with tube
			const Node* node2() const;				//returns pointer to instance of node2 associated with tube
		private:
			Node* node1_;							//pointer to node1 associated with tube (aggregation of node1)
			Node* node2_;							//pointer to node1 associated with tube (aggregation of node2)
			double permeability_;					//permeability of tube
			double length_;							//length of tube
			double diameter_;						//diameter of tube

		};
	}
}
#endif
