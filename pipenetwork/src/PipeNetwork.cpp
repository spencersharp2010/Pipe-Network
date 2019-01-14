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
			//filename_(filename)
		{
			std::ifstream filename1(filename);
			//std::ifstream filename1(filename);
			if (filename1.is_open())
			{
				filename1 >> numberofNodes_;
				filename1 >> numberofTubes_;

				double x;
				double y;
				double flux;

				for (int i = 0; i < numberofNodes_; ++i)
				{
					filename1 >> x;
					filename1 >> y;
					filename1 >> flux;
					nodeData_.push_back(new Node(x, y, flux, i));
				}

				int node_1;
				int node_2;
				double diameter;
				for (int i = 0; i < numberofTubes_; ++i)
				{
					filename1 >> node_1;
					filename1 >> node_2;
					filename1 >> diameter;
					tubeData_.push_back(new Tube(nodeData_[node_1], nodeData_[node_2], diameter));
				}
				filename1.close();
			}
			else
			{
				std::cout << "could not open file" << std::endl;
			}
		}
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
				std::cout << q[i] << std::endl;
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
				std::cout << "node1: " << tubeData_[i]->node1()->id() << ";  node 2: " << tubeData_[i]->node1()->id() << ";  diameter: " << tubeData_[i]->diameter() << std::endl;
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