#include <string>
#include <vector>
#include "Node.hpp"
#include "Tube.hpp"

#ifndef PIPENETWORK
#define PIPENETWORK

namespace cie
{
	namespace pipenetwork
	{
		class PipeNetwork
		{
		public:
			PipeNetwork(const std::string& filename);		//constructor
			~PipeNetwork();									//destructor
			std::vector<double> computeFluxes() const;		//function to compute fluxes through each tube (final solution)
			void print_input_data();						//function to print out input data to console
			void print_solution();							//function to print out computed solution to console
		private:
			int numberofNodes_;								//number of nodes present in system	
			int numberofTubes_;								//number of tubes present in system
			std::vector<Node*> nodeData_;					//vector storing pointers to all instances of nodes in system
			std::vector<Tube*> tubeData_;					//vector storing pointers to all instances of tubes in system
		};
	}
 }

#endif

