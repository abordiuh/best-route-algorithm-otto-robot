#include "OptimalWay.h"

using namespace std;

/*
* Function:  OptimalWay
* --------------------
*	@brief: Constructor. Setting up robot speed and time needed robot to wait at each way point
*	@param: int -	Robot speed (m/s)
*	@param: int -	Loading time (s)
*	@return: None
*/
OptimalWay::OptimalWay(int robotSpeed, int loadingTimeAtWP)
{
	ROBO_SPEED = robotSpeed;
	LOADING_TIME = loadingTimeAtWP;
}


OptimalWay::~OptimalWay()
{
}

/*
* Function:  getTimeDistBtwPoints
* --------------------
*	@brief: Calculating the time distance between 2 points based on robot speed
*	@param: WayPoint
*	@param: WayPoint
*	@return: Will return the time distance between 2 points in seconds
*/
float OptimalWay::getTimeDistBtwPoints(WayPoint currentPoint, WayPoint nextPoint) {
	return (float)sqrtf(powf(abs(currentPoint.x - nextPoint.x), 2)
		+ powf(abs(currentPoint.y - nextPoint.y), 2)) / ROBO_SPEED;
}

/*
* Function:  getTimeDistBtwPoints
* --------------------
*	@brief: Calculating the time distance between 2 points including loading time and penalties
*	@param: int					current way point ID
*	@param: int					desire way point ID
*	@param: vector<WayPoint> -	way points vector
*	@return: Will return the time distance between 2 chosen points in seconds
*/
float OptimalWay::getTimeToWayPoint(int currentStep, int desireStep, vector<WayPoint> waypoints) {
	float resultTime = getTimeDistBtwPoints(waypoints[currentStep], waypoints[desireStep]);
	if ((desireStep - currentStep) == 1)
		resultTime += (float)LOADING_TIME; //Waiting at the desireStep waypoint
	for (int i = currentStep + 1; i < desireStep; i++) {
		resultTime += (float)waypoints[i].penalty;
	}
	return resultTime;
}

/*
* Function:  getTimeDistBtwPoints
* --------------------
*	@brief: Optimising the best way to reach the final point by using Dijkstra's Algorithm
*	@param: vector<WayPoint> -	way points vector
*	@return: Will return the smallest time in seconds needed to go through necessary way points
*/
float OptimalWay::getBestWayTime(vector<WayPoint> waypoints) {
	const int MAX_TIME = 100000000;
	int numbOfVertices = waypoints.size();
	int startVertex = 0;
	int endVertex = waypoints.size() - 1;
	vector<vector< pair<int, float> >> graph(numbOfVertices);
	for (size_t vertex = 0; vertex < numbOfVertices; vertex++) {
		for (int connectedVertex = vertex + 1; connectedVertex < numbOfVertices; connectedVertex++) {
			graph[vertex].push_back(pair <int, float>(waypoints[connectedVertex].id, getTimeToWayPoint(vertex, connectedVertex, waypoints)));
		}
	}
	vector<int> dist(numbOfVertices, MAX_TIME), parent(numbOfVertices);
	dist[startVertex] = 0;
	vector<char> flag(numbOfVertices,false);
	for (int i = 0; i < numbOfVertices; ++i) {
		int v = -1;
		for (int j = 0; j < numbOfVertices; ++j)
			if (!flag[j] && (v == -1 || dist[j] < dist[v]))
				v = j;
		if (dist[v] == MAX_TIME)
			break;
		flag[v] = true;

		for (size_t j = 0; j < graph[v].size(); ++j) {
			int to = graph[v][j].first,
				len = graph[v][j].second;
			if (dist[v] + len < dist[to]) {
				dist[to] = dist[v] + len;
				parent[to] = v;
			}
		}
	}
	/*Restoring the shortest path from begining to the end*/
	float totalTime = 0;
	vector<WayPoint> path;
	for (int v = endVertex; v != startVertex; v = parent[v])
		path.push_back(waypoints[v]);
	path.push_back(waypoints[startVertex]);
	reverse(path.begin(), path.end());
	
	/*Calculating amount of time needed to finish the path through way points*/
	int currentStep = 0;
	int lastStep = 0;
	printf("Now at waypoint ID %d from %d (+2 points for begin and end of way)\n\rSkipping next points:", waypoints[currentStep].id, (int) waypoints.size());
	for (auto waypoint : path) {
		if (waypoint.id != 0)
			totalTime += getTimeToWayPoint(currentStep, waypoint.id, waypoints);
		if (currentStep != waypoint.id - 1) {
			for (int i = currentStep + 1; i < waypoint.id; i++)
			{
				printf(" %d", i);
			}
			lastStep = currentStep;
		}
		currentStep = waypoint.id;
	}
	printf("\n\rTotal time %.3f\n\r", totalTime);
	return totalTime;
}
