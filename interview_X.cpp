#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

  
using namespace std;

#define PI 3.1415926

// define step size as global parameter
#define STEP_SIZE 0.001 // using 1000 Hz as update frequency.

// define vehicle length as global parameter
#define VEHICLE_LENGTH 2.0

#define V0 1.0// 1m/s

// Car configuration
struct Configuration{
  double x;
  double y;
  double theta; // heading angle of the car; theta=0 if the car heads towards x axis and PI/2 if the car heads towards y axis.
};

Configuration dynamics(const Configuration init, double controlInput){
	double x_dot = V0*cos(init.theta);
	double y_dot = V0*sin(init.theta);
	double theta_dot = V0*tan(controlInput)/VEHICLE_LENGTH;

	Configuration nextConfig;
	nextConfig.x = init.x + x_dot*STEP_SIZE;
	nextConfig.y = init.y + y_dot*STEP_SIZE;
	nextConfig.theta = init.theta + theta_dot*STEP_SIZE;
	nextConfig.theta = (nextConfig.theta>=PI) ? (nextConfig.theta-2*PI) : nextConfig.theta;
	nextConfig.theta = (nextConfig.theta<-PI) ? (nextConfig.theta+2*PI) : nextConfig.theta;
	
	return nextConfig;
}

// Problem 1
// Input: an initial configuration of the car
// Input: total time
// Output: final configuration 
// Output: a path
vector<Configuration> GenPath(const Configuration init, double T, Configuration &final){
  	vector<Configuration> out;
  	int numSteps = T/STEP_SIZE; // assuming that output is integer as step_size is 0.001. But can use ceil() function otherwise.
	double controlInput = 0.2;
	cout<<init.x<<", "<<init.y<<", "<<init.theta<<", "<<controlInput<<endl;
	out.push_back(init);
    Configuration nextConfig = init;
	for (int i = 0; i < numSteps; ++i)
	{
		nextConfig = dynamics(nextConfig, controlInput);
		if(i%10==0){
			cout<<nextConfig.x<<", "<<nextConfig.y<<", "<<nextConfig.theta<<", "<<controlInput<<endl;
		}
		out.push_back(nextConfig);
	}
	final = nextConfig;
  return out;
}


double calculateInput(vector<double> error, double &errorSum){
	// double proportionalGain = 1.5;
	// double derivativeGain = 0.1;
	// double integralGain = 0.01;

	// double proportionalGain = 0.12;
	// double derivativeGain = 0.1;
	// double integralGain = 0.01;

	double proportionalGain = 0.05;
	double derivativeGain = 0.01;
	double integralGain = 0.0001;

	int bufferSize = error.size();
	double currError = error[bufferSize-1];

	double errorDot = 0.0;
	if(bufferSize>1){
		errorDot = (error[bufferSize-1] - error[bufferSize-2]);	
	}

	errorSum += error[bufferSize-1];
	if(bufferSize>100){
		errorSum -= error[0];
		error.erase(error.begin());
	}


	return min(max((proportionalGain*currError + derivativeGain*errorDot + integralGain*errorSum),-0.5),0.5);
	// return VEHICLE_LENGTH/V0*atan(proportionalGain*currError + derivativeGain*errorDot + integralGain*errorSum);

}

// Problem 2
// Input: reference path. To test your implementation, you can use problem #1's solution to generate reference paths
// Input: an initial configuration
// Output: u: a sequence of control 
void Tracking(const vector<Configuration> &reference_path, const Configuration &init_conf, vector<double> &u)
{
  	// I would be using PID controller over theta_error to find the input control.
  	// To calculate theta_error: I would use atan2(y_diff, x_diff) and theta_diff and would fine tune the weights. 
  	// For now, I would use 10:1 weight with lesser weight on theta_diff as I would like to track the vehicle more on (x,y) positions

	vector<double> error; // using the vector to find the integral and diffential

	Configuration nextConfig = init_conf;

	double errorSum = 0.0;

	for (int i = 0; i < reference_path.size()-1; ++i)
	{
		double x_diff = (reference_path[i+1]).x - nextConfig.x;
		double y_diff = (reference_path[i+1]).y - nextConfig.y;
		double theta_diff = (reference_path[i+1]).theta - nextConfig.theta;
		double nextError = ((0.1*theta_diff + atan2(y_diff, x_diff)));// /STEP_SIZE);
		error.push_back(nextError);
		double controlInput = calculateInput(error, errorSum);
		u.push_back(controlInput);
		nextConfig = dynamics(nextConfig, controlInput);
		if(i%10==0){
			cout<<"errors: "<<x_diff<<", "<<y_diff<<", "<<theta_diff<<", "<<nextError<<", "<<errorSum<<endl;
			cout<<nextConfig.x<<", "<<nextConfig.y<<", "<<nextConfig.theta<<", "<<controlInput<<endl;
		}
	}

}

// Problem 3
void ReachTarget(const double x, vector<double> &u)
{
	// Configuration A, B;
	// A.x = 0, A.y = 0, A.theta = PI/2;
	// B.x = x, B.y = 0, B.theta = PI/2;

	// Compute a sequence of control so that the car can move from A and reach target B as closely as possible
	vector<double> error; // using the vector to find the integral and diffential


	Configuration nextConfig;
	nextConfig.x = 0;
	nextConfig.y = 0;
	nextConfig.theta = PI/2;

	double errorSum = 0.0;
	double goalPositionError = pow(x,2);

	double threshold = 0.01;
	int i=0;
	while(goalPositionError>threshold)
	{
		double x_diff = x - nextConfig.x;
		double y_diff = 0 - nextConfig.y;
		double theta_diff = PI/2 - nextConfig.theta;
		double nextError = ((0.1*theta_diff + atan2(y_diff, x_diff)));// /STEP_SIZE);
		error.push_back(nextError);
		double controlInput = calculateInput(error, errorSum);
		u.push_back(controlInput);
		nextConfig = dynamics(nextConfig, controlInput);
		if(i%10==0){
			cout<<"errors: "<<x_diff<<", "<<y_diff<<", "<<theta_diff<<", "<<nextError<<", "<<errorSum<<endl;
			cout<<nextConfig.x<<", "<<nextConfig.y<<", "<<nextConfig.theta<<", "<<controlInput<<endl;
		}
		goalPositionError = pow((x-nextConfig.x),2) + pow(nextConfig.y,2) + pow((nextConfig.theta-PI/2),2);
		i++;
	}

}


// To execute C++, please define "int main()"
int main() {
  Configuration init, final;
  vector<Configuration> ref;
  vector<double> u;

  cout<<"Problem 1: "<<endl;
  init.x = 0, init.y = 0, init.theta = PI/2;
  ref = GenPath(init, 2.0, final);

  cout<<"Problem 2: "<<endl;
  init.x = 0.2, init.y = 0.2, init.theta = PI/2;
  Tracking(ref, init, u);

  cout<<"Problem 3: "<<endl;
  ReachTarget(5, u);
  ReachTarget(1, u);

  cout<<"Bonus question: We can have the cost function that sums the (distance between(each point on trajectory and goal configuration))"<<endl;

  return 0;
}



// For printing, I am creating two functions. 
// pose printPath(pose const &init, double controlInput, double T): assumes that we are running with constant control input for this _TIME_.
// INPUT: (init, control input, _TIME_) 
// OUTPUT: End pose of robot after _TIME_

// pose printPath(pose const &init, double controlInput): do one step motion
// INPUT: (init, control input) 
// OUTPUT: End pose of robot after STEP_SIZE