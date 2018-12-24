#include "WpFileHandler.h"

using namespace std;

WpFileHandler::WpFileHandler()
{
}

/*
* Function:  loadPoints 
* --------------------
*	@brief:		Will read the specified file data, parse waypoints and return it
*	@param:		File name to file with waypoints
*	@return:	The vector of vector of way points (since there are multiple paths in one input file)
*/
vector<vector<WayPoint>> WpFileHandler::loadPoints(string fileName)
{
	string line;
	vector<vector<WayPoint>> wpVectors;
	ifstream myfile(fileName);
	if (myfile.is_open())
	{
		int wayPointId = 0;
		vector<WayPoint> wpTempVector;
		int numberOfPoints = 0;
		/*Parsing the file*/
		while (getline(myfile, line))
		{	
			/*If it reach the number of points number*/
			if (line.length() <= MAX_HEAD_LINE_SIZE) {
				numberOfPoints = atoi(line.c_str());
				if (numberOfPoints > 0) 
					cout << "Retriving next " << numberOfPoints << " waypoints" << '\n';
					if (wpTempVector.size() != 0) {
						addEssentialWayPoints(&wpTempVector);	//Adding 0,0 and 100,100 begin and end points
						wpVectors.push_back(wpTempVector);
					}
					wpTempVector.clear();
					wayPointId = 0;
			}
			/*Loading all the points to array*/
			else {
				WayPoint wp;
				wp.id = ++wayPointId;
				std::string delimiter = " ";
				size_t pos = 0;
				std::string token;
				int wptempdata[3] = {0,0,0};
				int wptempdatacounter = 0;
				while ((pos = line.find(delimiter)) != std::string::npos) {
					token = line.substr(0, pos);
					wptempdata[wptempdatacounter] = atoi(token.c_str());
					line.erase(0, pos + delimiter.length());
					wptempdatacounter++;
				}
				wp.x = wptempdata[0];
				wp.y = wptempdata[1];
				wp.penalty = atoi(line.c_str());
				wpTempVector.push_back(wp);
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file";

	return wpVectors;
}

/*
* Function:  saveResultTime
* --------------------
*	@brief:		Add the total time needed to finish path to the specified file
*	@param:		File name where to store
*	@return:	The vector of vector of way points (since there are multiple paths in one input file)
*/
void WpFileHandler::saveResultTime(string filename, float time)
{
	ofstream myfile(filename, std::ios::out | std::ios::app);
	if (myfile.is_open())
	{
		myfile << std::fixed << std::setprecision(3) << time << endl;
		myfile.flush();
		myfile.close();
	}
	else cout << "Unable to open file to write";
}

/*
* Function:  saveResultTime
* --------------------
*	@brief:		Add the 0,0 point to the begining of the waypoint vector and 100,100 to the end
*	@param:		Pointer to vector with just parsed way points
*	@return:	None
*/
void WpFileHandler::addEssentialWayPoints(vector<WayPoint> * wpv)
{
	WayPoint wpBeginEnd;
	wpBeginEnd.id = 0;
	wpBeginEnd.x = 0;
	wpBeginEnd.y = 0;
	wpBeginEnd.penalty = 0;
	(*wpv).insert((*wpv).begin(), wpBeginEnd);
	wpBeginEnd.id = (*wpv).size();
	wpBeginEnd.x = 100;
	wpBeginEnd.y = 100;
	wpBeginEnd.penalty = 0;
	(*wpv).push_back(wpBeginEnd);
}

/*
* Function:  clearOutputFile
* --------------------
*	@brief:		Clear the output file
*	@param:		File name where to store
*	@return:	None
*/
void WpFileHandler::clearOutputFile(string filename)
{
	std::ofstream ofs;
	ofs.open(filename, std::ofstream::out | std::ofstream::trunc);
	ofs << "";
	ofs.flush();
	ofs.close();
}

WpFileHandler::~WpFileHandler()
{
}
