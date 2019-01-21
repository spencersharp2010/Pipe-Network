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
				delete nodeData_[i];					//delete all pointers in nodeData vector
			}
			for (int i = 0; i < numberofTubes_; ++i)
			{
				delete tubeData_[i];					//delete all pointers in tubeData vector
			}
		}

		//function to compute fluxes through each pipe, based on node and tube data
		std::vector<double> PipeNetwork::computeFluxes() const
		{
			cie::linalg::Matrix B(numberofNodes_, 0);			//initialize square (#nodes x #nodes) matrix using linear algebra library function
																//all values initialized to 0

			for (int i = 0; i < numberofTubes_; ++i)			//loop over all tubes
			{
				double B_i = tubeData_[i]->permeability();		//store permeability from tubeData vector
				int nodeID1 = tubeData_[i]->node1()->id();		//retrieve id of node1
				int nodeID2 = tubeData_[i]->node2()->id();		//retrieve id of node2
				B(nodeID1, nodeID1) += B_i;						//add permeability to B matrix in position node1, node1
				B(nodeID2, nodeID2) += B_i;						//add permeability to B matrix in position node2, node2
				B(nodeID1, nodeID2) -= B_i;						//subtract permeability from B matrix in position node1, node2
				B(nodeID2, nodeID1) -= B_i;						//subtract permeability from B matrix in position node2, node1
			}

			std::vector<double> Q(numberofNodes_);				//initialize vector Q of size based on # of nodes
																//Q represents volumetric flow rate

			for (int i = 0; i < numberofNodes_; ++i)			//populate Q vector with flow stored in node data vector
			{
				Q[i] = -1 * nodeData_[i]->flow();
			}

			for (int i = 0; i < numberofNodes_; ++i)			//set boundary conditions
			{
				B(i, 0) = 0;
				B(0, i) = 0;
			}

			B(0, 0) = 1;										//more boundary conditions
			Q[0] = 0;											//more boundary conditions

			std::vector<double> head(numberofNodes_);			//initialize vector head (hydraulic head) of size based on # of nodes
			head = cie::linalg::solve(B, Q);					//use linalg function to perform linalg operate to compute head
			std::vector<double> q(numberofTubes_);				//initialize vector q. this is what we are wanting to compute			

			for (int i = 0; i < numberofTubes_; ++i)			//loop over number of tubes
			{
				int nodeID1 = tubeData_[i]->node1()->id();		//retrieve ID of node1 associated with current tube
				int nodeID2 = tubeData_[i]->node2()->id();		//retrieve ID of node2 associated with current tube
				double B_i = tubeData_[i]->permeability();		//retrieve permeability of current tube
				q[i] = B_i * (head[nodeID1] - head[nodeID2]);	//perform calculation to determine flux of current tube and store in vector
			}

			return q;
		}

		//program to output input data read from txt file
		void PipeNetwork::print_input_data()
		{
			std::cout << "number of nodes: " << numberofNodes_ << std::endl;
			std::cout << "number of tubes: " << numberofTubes_ << std::endl;

			//loop across all nodes and output data stored in nodeData vector
			for (int i = 0; i < numberofNodes_; ++i)
			{
				std::cout << "x: " << nodeData_[i]->x() << ";  y: " << nodeData_[i]->y() << ";  flux: " << nodeData_[i]->flow() << std::endl;
			}

			//loop across all tubes and output data stored in tubeData vector
			for (int i = 0; i < numberofTubes_; ++i)
			{
				std::cout << "node1: " << tubeData_[i]->node1()->id() << ";  node 2: " << tubeData_[i]->node2()->id() << ";  diameter: " << tubeData_[i]->diameter() << std::endl;
			}
		}

		void PipeNetwork::print_solution()
		{
			std::cout << " " << std::endl;
			std::cout << "----------------SOLUTION BELOW--------------------" << std::endl;

			std::vector<double> qprint(numberofTubes_);
			qprint = cie::pipenetwork::PipeNetwork::computeFluxes();
			for (int i = 0; i < numberofTubes_; ++i)
			{
				std::cout << "flux[" << i << "] = " << qprint[i] << std::endl;
			}

		}

		int PipeNetwork::numberofTubes()
		{
			return numberofTubes_;
		}

	}

}