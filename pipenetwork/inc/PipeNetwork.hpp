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
			std::vector<double> computeFluxes() const;		//compute fluxes through each tube (final solution)
			void print_input_data();						//function to print out input data to console
			int numberofTubes();							//return number of tubes provided in input data
		private:
			int numberofNodes_;								//number of nodes present in system	
			int numberofTubes_;								//number of tubes present in system
			std::vector<Node*> nodeData_;					//vector storing pointers to all instances of nodes in system
			std::vector<Tube*> tubeData_;					//vector storing pointers to all instances of tubes in system
			std::vector<double> q_;							//vector storing fluxes of all tubes
		};
	}
 }

#endif

