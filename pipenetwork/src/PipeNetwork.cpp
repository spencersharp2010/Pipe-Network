#include "PipeNetwork.hpp"
#include "linalg.hpp"
#include <fstream>
#include <iostream>
#include <cmath>

namespace cie
{
	namespace pipenetwork 
	{
		PipeNetwork::PipeNetwork(const std::string& filename)

		{
			std::ifstream filename1(filename);

			if (filename1.is_open())
			{
				//read in first and second values of .txt file. these provide
				//# of nodes and # of tubes in pipe network
				filename1 >> numberofNodes_;
				filename1 >> numberofTubes_;

				//declare variables to store nodal values provided in .txt file
				double x;
				double y;
				double flux;

				//initializes nodeData and tubeData vector to size declared in .txt file
				nodeData_.reserve(numberofNodes_);
				tubeData_.reserve(numberofTubes_);

				//read in node data from .txt file
				for (int i = 0; i < numberofNodes_; ++i)
				{
					filename1 >> x;			//x coordinate
					filename1 >> y;			//y coordinate
					filename1 >> flux;		//flux through node

					//declare a new instance of "node" class and provide x & y coordinate, flux, and an id for this node
					//nodeData stores this in a vector of pointers
					nodeData_.push_back(new Node(x, y, flux, i));																	
				}

				//declare variables to store tube values provided in .txt file
				int node_1;					//which node defines one end of the tube
				int node_2;					//which node defines other end of the tube
				double diameter;			//diameter of tube

				//read in tube data from .txt file
				for (int i = 0; i < numberofTubes_; ++i)
				{
					filename1 >> node_1;	//read in first node associated with current tube
					filename1 >> node_2;	//read in second node associated with current tube
					filename1 >> diameter;	//read in diameter of tube

					//declare a new pointer to "tube" class and provide first node, second node, and diameter
					//tubeData stores this in a vector of pointers
					tubeData_.push_back(new Tube(nodeData_[node_1], nodeData_[node_2], diameter));
				}
				filename1.close();
			}
			else
			{
				std::cout << "error: could not open file" << std::endl;
			}
		}

		//destructor for PipeNetwork. Deletes instances of nodeData and tubeData by iterating across the vectors
		PipeNetwork::~PipeNetwork()
		{
			for (int i = 0; i < numberofNodes_; ++i)
			{
				delete nodeData_[i];
			}
			for (int i = 0; i < numberofTubes_; ++i)
			{
				delete tubeData_[i];
			}
		}

		std::vector<double> PipeNetwork::computeFluxes() const
		{
			cie::linalg::Matrix B(numberofNodes_, 0);

			for (int i = 0; i < numberofTubes_; ++i) 
			{
				double B_i = tubeData_[i]->permeability();
				int nodeID1 = tubeData_[i]->node1()->id();
				int nodeID2 = tubeData_[i]->node2()->id();
				B(nodeID1, nodeID1) += B_i;
				B(nodeID2, nodeID2) += B_i;
				B(nodeID1, nodeID2) -= B_i;
				B(nodeID2, nodeID1) -= B_i;
			}

			std::vector<double> Q(numberofNodes_);

			for (int i = 0; i < numberofNodes_; ++i)
			{
				Q[i] = -1 * nodeData_[i]->flow();
			}

			for (int i = 0; i < numberofNodes_; ++i)
			{
				B(i, 0) = 0;
				B(0, i) = 0;
			}

			B(0, 0) = 1;
			Q[0] = 0;

			std::vector<double> head(numberofNodes_);
			head = cie::linalg::solve(B, Q);
			std::vector<double> q(numberofTubes_);

			for (int i = 0; i < numberofTubes_; ++i)
			{
				int nodeID1 = tubeData_[i]->node1()->id();
				int nodeID2 = tubeData_[i]->node2()->id();
				double B_i = tubeData_[i]->permeability();
				q[i] = B_i * (head[nodeID1] - head[nodeID2]);
				//std::cout << q[i] << std::endl;
			}

			return q;
		}

		void PipeNetwork::print_input_data()
		{
			std::cout << "number of nodes: " << numberofNodes_ << std::endl;
			std::cout << "number of tubes: " << numberofTubes_ << std::endl;

			for (int i = 0; i < numberofNodes_; ++i)
			{
				std::cout << "x: " << nodeData_[i]->x() << ";  y: " << nodeData_[i]->y() << ";  flux: " << nodeData_[i]->flow() << std::endl;
			}
			
			for (int i = 0; i < numberofTubes_; ++i)
			{
				std::cout << "node1: " << tubeData_[i]->node1()->id() << ";  node 2: " << tubeData_[i]->node2()->id() << ";  diameter: " << tubeData_[i]->diameter() << std::endl;
			}
		}

		//void PipeNetwork::print_solution()
		//{
		//	std::cout << " " << std::endl;
		//	std::cout << "----------------SOLUTION BELOW--------------------" << std::endl;

		//	for (int i = 0; i < numberofTubes_; ++i)
		//	{
		//		std::cout << "flux[" << i << "] = " <<  << std::endl;
		//	}

		//}

		int PipeNetwork::numberofTubes()
		{
			return numberofTubes_;
		}

	}

}