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
			PipeNetwork(const std::string& filename);
			~PipeNetwork();
			std::vector<double> computeFluxes() const;
			void print_input_data();
			//void print_solution();
			int numberofTubes();
			//std::vector<double> return_flux();
			//double diameter() const;
		private:
			//const std::string& filename_;
			int numberofNodes_;
			int numberofTubes_;
			std::vector<Node*> nodeData_;
			std::vector<Tube*> tubeData_;
			std::vector<double> q_;
		};
	}
 }

#endif

