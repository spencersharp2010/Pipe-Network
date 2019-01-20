#include "PipeNetwork.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

int main()
{
	std::cout << "pipe network problem" << std::endl;

	cie::pipenetwork::PipeNetwork provided_pipe_system("input.txt");
	provided_pipe_system.print_input_data();
	std::vector<double> fluxes(provided_pipe_system.numberofTubes());
	fluxes = provided_pipe_system.computeFluxes();
	std::cout << "solution below" << std::endl;
	for (int i = 0; i < provided_pipe_system.numberofTubes(); ++i)
	{
		std::cout << fluxes[i] << std::endl;
	}
	//provided_pipe_system.print_solution();
	//solution = provided_pipe_system.computeFluxes();
	//for (int i = 0; i < provided_pipe_system.numberofTubes; ++i)
	//{
	//	std::cout << "---------------SOLUTION BELOW----------------" << std::endl;
	//	std::cout << solution[i] << std::endl;
	//}
	
	return 0;
}
