#pragma once

#include <string>
#include "Entity.h"

class Sink
{
public:
	Sink(std::string name);
	/*
		Sink
			Parameters:
				string	name - the name of the entity departing
			Return value:
				none
			Behavior:
				Constructor for the sink class
	*/

	void Depart(Entity *en);
	/*
		Depart
			Parameters:
				Entity	*en	pointer to the departing entity
			Return value:
				none
			Behavior:
				identifies the entity departing the application
	*/

	int TotalEntitiesProcessed();
	/*
		Total Entities Processed
			Parameters:
				none
			Return value:
				int
			Behavior:
				increases count for the number of entities that have departed the application
	*/

	Time AverageDelayInQueue(Entity *en);
	/*
		Average Waiting Time 
			Parameters:
				_totalDelayInQueue
				_totalEntitiesProcessed
				_arrivalTime (Entity)
				_serviceStartTime (Entity)
			Return value:
				time (double) 
			Behavior:
				calculates the average wait time in the queue after all entities are processed or time is up
	*/

	Time MaxDelayInQueue(Entity *en);
	/*
		Longest waiting time
			Parameters:
				_delayInQueue
				_maxDelayInQueue
				_arrivalTime (Entity)
				_serviceStartTime (Entity)
			Return value:
				time (double)
			Behavior:
				compares the current delay time with the highest recorded delay time and returns whichever is higher
	*/
	
	Time AverageFlowTime(Entity *en);
	/*
		Average time to get through system
			Parameters:
				_totalFlowTime
				_flowTime
				_totalEntitiesProcessed
				_arrivalTime (Entity)
				_departureTime (Entity)
			Return value:
				time (double)
			Behavior:
				calculates the average time in system for all entities				
	*/
	
	Time MaxFlowTime(Entity *en);
	/*
		Longest time spent in system
			Parameters:
				_maxFlowTime
				_flowTime
				_arrivalTime (Entity)
				_departureTime (Entity)
			Return value:
				time (double)
			Behavior:
				compares current flowtime with previously recorded maximum flow time and returns whichever is higher
	*/
	
	Time GetEndTime(Entity *en, Time endTime);
	/*
		The time the application ends
			Parameters:
				Entity *	en			The pointer to the current entity departing the Sink
				Time		endTime		The simulation end time called in SimObj::RunSimulation(Time endTime)
			Return value:
				Time (double)
			Behavior:
				records the time of the last departure or the set end time of SimObj::RunSimulation()
	*/	

	void ServerUtilization();
	/*
		How much of the total simulation time is the server busy
			Parameters:
				none
			Return value:
				none
			Behavior:
				calculates how much time the server was busy out of the whole run time of the application
	*/

private:
	std::string _name;
	int _totalEntitiesProcessed = 0;
	Time _totalDelayInQueue = 0.0;
	Time _maxDelayInQueue = 0.0;
	Time _delayInQueue = 0;
	Time _totalFlowTime = 0.0;
	Time _maxFlowTime = 0.0;
	Time _flowTime = 0.0;
	Time _endTime = 1.0;
	Time _serverActiveTime = 0.0;


};
