#ifndef NODE
#define NODE

namespace cie
{
	namespace pipenetwork
	{
		//node class
		class Node
		{
		public:
			Node(double x, double y, double flow, int id);		//constructor
			double x() const;		//returns x coordinate
			double y() const;		//returns y coordinate
			double flow() const;	//returns flux
			int id() const;			//returns node ID
		private:
			double x_;				//x coordinate of node
			double y_;				//y coordinate of node
			double flow_;			//flux through node
			int id_;				//ID of each node to identify it

		};
	}
}
#endif

