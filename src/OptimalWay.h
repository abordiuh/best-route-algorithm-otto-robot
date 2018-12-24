#ifndef OPTIMALWAY_H
#define OPTIMALWAY_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <vector>
#include <algorithm>

/*Structure which represent a way point read from the file*/
typedef struct pointstruct {
	int id;
	int x;			//Meters
	int y;			//Meters
	int penalty;	//Seconds
} WayPoint;

using namespace std;

class OptimalWay
{

public:
	OptimalWay(int ottoSpeed, int loadingTimeAtWP);
	~OptimalWay();
	float getBestWayTime(vector<WayPoint> waypoints);

private:
	float getTimeDistBtwPoints(WayPoint currentPoint, WayPoint nextPoint);
	float getTimeToWayPoint(int currentStep, int desireStep, vector<WayPoint> waypoints);
	int ROBO_SPEED;		//Meters per second
	int LOADING_TIME;	//seconds

};

#endif /* OPTIMALWAY_H */