#include "Simulation.h"
#include <iostream>
#include "Distribution.h"
#include "Sink.h"
#include "SSSQ.h"
#include "Source.h"

using namespace std;

void main()
{
	double endTime = 200.0;
	
	Sink sink("Sink");

	SSSQ sssq("SSSQ", &sink, new Triangular(2, 3, 4));

	//Source source("Source", &sssq, new Triangular(1, 3, 5), 100);		//creates 100 entities for the simulation

	Source source("Source", &sssq, new Triangular(1, 3, 5));			//creates entities at given interarrival distributions forever (to be used when a desired end time is known)

	//SimObj::RunSimulation();							//runs the simulation until no events are left

	SimObj::RunSimulation(endTime);				  	    //runs the simulation to a specific end time
		
	cout << "<enter> to terminate: ";
	cin.get();											//pauses the simulation to keep the window open
}