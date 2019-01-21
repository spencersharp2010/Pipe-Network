#include "Node.hpp"

namespace cie
{
	namespace pipenetwork
	{
		//constructor
		Node::Node(double x, double y, double flow, int id) 
		{
			x_ = x;
			y_ = y;
			flow_ = flow;
			id_ = id;
		}
		//returns x coordinate
		double Node::x() const
		{
			return x_;
		}
		//returns y coordinate
		double Node::y() const
		{
			return y_;
		}
		//returns flux through node
		double Node::flow() const
		{
			return flow_;
		}
		//returns ID of node
		int Node::id() const
		{
			return id_;
		}
	}
}
