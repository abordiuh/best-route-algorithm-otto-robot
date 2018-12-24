# best-route-algorithm-otto-robot

Idea:
***************************************************************************************
Robot Otto placed in a waypoint with coordinates (0,0) in a factory 100m x 100m environment. 
 
Environment: 
	Start at (0,0); 
	The robot is moving from the point to another point only in ascending order; 
	Delay time (loading robot with goods) at each point - 10s; 
	Time penalty for skipping point - depend on the point; 
	Finish at (100, 100); 
 
Otto characteristics: 
	Movement speed 2m/s (in the task "OTTO is very maneuverable, but a bit slow. It moves at 2 m/s, but can turn very quickly.". wow 2 m/s is not slow at all!) 
	Can always move in a straight line between target points. 
	During delay at the waypoint can turn. 
 
Challenge: 
	Find Otto's the lowest time to reach the end through waypoints. 
 
Input file with:  
	Number of points N (1 <= N <= 1000) 
	"X Y P" - where  ( 1 <= X, Y <= 99, X and Y in meters) and (1 <= P <= 100) 
 
Output file with: 
	For each test case single decimal number truncated to 3 decimal  places 
	No lines between answers

***************************************************************************************
Run on Windows:
__________________________

1. Open command prompt
2. Navigate to Windows X86 folder inside OttoWay-Clearpath
3. Run in cmd:
	OttoWay.exe Challenges/sample_input_small.txt sample_output_small.txt
4. A file will be created with the results and the messages of the calculating best 
	ways will be displayed in cmd.

***************************************************************************************

Run on Linux/Ubuntu AMD64:
__________________________

1. Open terminal
2. Navigate to Linux AMD64 folder inside OttoWay-Clearpath
3. Run in terminal:
	ottoway Challenges/sample_input_small.txt sample_output_small.txt
4. The file will be created with results and the messages of the calculating best ways will be displayed.

***************************************************************************************

Source files are located inside the "src" folder

