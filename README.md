This program reads in a file called `input.txt`, which contains the following information about some hypothetical pipe network:
* number of nodes
* number of tubes
* node data: x-coordinate, y-coordinate, and inflow/outflow
* tube data: node 1, node 2, diameter

Based on the input data, the program computes the resulting fluxes through each tube in the network.

The program relies on the concept of aggregation to define the relationship between tubes and nodes. Specifically, three classes are implemented:
* PipeNetwork: consists of nodes and tubes
* Tube: consists of two nodes
* Node

**Note:** you must clone using the --recursive flag. This ensures the linear algebra libraries are properly cloned as well. Also, note that the `input.txt` file should be located in the build folder.
