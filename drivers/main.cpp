#include "PipeNetwork.hpp"
#include <iostream>

int main()
{
	std::cout << "CiE1 Pipe Network Assignment\n" << "Spencer Sharp\n" << "23.01.2019\n" << std::endl;
	
	//create instance of "PipeNetwork" class and initialize with name of .txt file
	//constructor will read in contents of .txt file and store to variables
	cie::pipenetwork::PipeNetwork provided_pipe_system("pipedata.txt");
	
	//call function inside PipeNetwork class that prints out data read in from .txt file
	provided_pipe_system.print_input_data();

	//call function inside PipeNetwork class that prints out solution to console
	provided_pipe_system.print_solution();
		
	return 0;
}
