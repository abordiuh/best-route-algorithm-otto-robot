#include <vector>
#include <stdio.h>
#include "OptimalWay.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>
#include <stdint.h>


using namespace std;
const int MAX_HEAD_LINE_SIZE = 4;

class WpFileHandler
{
public:
	WpFileHandler();
	vector<vector<WayPoint>> loadPoints(string fileName);
	void saveResultTime(string filename, float time);
	void addEssentialWayPoints(vector<WayPoint> * wpv);
	void clearOutputFile(string filename);
	~WpFileHandler();
};
