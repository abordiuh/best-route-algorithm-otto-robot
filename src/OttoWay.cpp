// OttoWay.cpp : Defines the entry point for the console application.
//
#include <vector>
#include <stdlib.h>
#include "OptimalWay.h"
#include "WpFileHandler.h"
#include <ctime>// include this header

int main(int argc, char* argv[])
{
	/*Checking of there are files specified
	* argv[1] - Input data file
	* argv[2] - Output data file
	*/
	if (argc == 3) {
		std::vector<std::vector<WayPoint>> wpvectors;
		WpFileHandler wpInOut;
		/*Loading points from file*/
		wpvectors = wpInOut.loadPoints(argv[1]);

		/*2 - robo speed m/s; 10 - delay time at each point (s)*/
		OptimalWay optimalWay(2, 10);

		/*Clearing the output file*/
		wpInOut.clearOutputFile(argv[2]);

		/*Looking for best path for each points vector*/
		for (auto vector : wpvectors) {
			puts("_________________________________________________________________________");
			puts("_________________________NEXT VECTOR OF POINTS___________________________");
			puts("_________________________________________________________________________");
			int start_s = clock();
			/*Looking for best path and saving result to output file*/
			wpInOut.saveResultTime(argv[2], optimalWay.getBestWayTime(vector));
			int stop_s = clock();
			cout << "Execution time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC) * 1000 << "(ms)" << endl;
		}
		puts("\n\r*********************************************");
		puts("Do not go where the path may lead, go instead\n\rwhere there is no path and leave a trail.\n\rRalph Waldo Emerson\n\r");
		puts("*************************************************");
	}
	else puts("Please specify the input and output files\n\r Example: OttoWay Input.txt Output.txt\n\r");
	return 0;
}

