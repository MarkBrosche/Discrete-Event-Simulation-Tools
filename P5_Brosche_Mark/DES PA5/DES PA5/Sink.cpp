#include "Sink.h"
#include "Simulation.h"
#include <iostream>

using namespace std;

Sink::Sink(std::string name)
{
	_name = name;
}

void Sink::Depart(Entity * en) //Brosche-edited
{
	cout << SimObj::GetCurrentSimTime() << ", Sink " << _name << ", Depart, Entity " << en->GetID() << endl;
	en->setDepartureTime(SimObj::GetCurrentSimTime());
	TotalEntitiesProcessed();
	cout << _totalEntitiesProcessed << " Entities Processed" << endl;
	cout << "The avergae delay in queue is " << AverageDelayInQueue(en) << endl;
	cout << "The maximum time spent in queue is " << MaxDelayInQueue(en) << endl;	
	cout << "The average flow time is " << AverageFlowTime(en) << endl;
	cout << "The maximum flow time for any entity is " << MaxFlowTime(en) << endl;
	GetEndTime(en, SimObj::GetEndTime());
	ServerUtilization();
}

int Sink::TotalEntitiesProcessed() //Brosche-added
{
	_totalEntitiesProcessed++;	
	return 0;
}

Time Sink::AverageDelayInQueue(Entity *en) //Brosche-added
{
	_delayInQueue = en->getServiceStartTime() - en->getArrivalTime();
	_totalDelayInQueue += _delayInQueue;
	return _totalDelayInQueue / _totalEntitiesProcessed;
}

Time Sink::MaxDelayInQueue(Entity *en) //Brosche-added
{
	_delayInQueue = en->getServiceStartTime() -en->getArrivalTime();
	if (_maxDelayInQueue > _delayInQueue)
		return _maxDelayInQueue;
	else 
	{
		_maxDelayInQueue = _delayInQueue;
		return _maxDelayInQueue;
	}
}

Time Sink::AverageFlowTime(Entity *en) //Brosche-added
{
	_flowTime = en->getDepartureTime() - en->getArrivalTime();
	_totalFlowTime += _flowTime;
	return _totalFlowTime / _totalEntitiesProcessed;
}

Time Sink::MaxFlowTime(Entity *en) //Brosche-added
{
	_flowTime = en->getDepartureTime() - en->getArrivalTime();
	if (_maxFlowTime > _flowTime) 
	{
		return _maxFlowTime;
	}
	else
	{
		_maxFlowTime = _flowTime;
		return _maxFlowTime;
	}
}

Time Sink::GetEndTime(Entity *en, Time endTime) //Brosche-added
{
	if (endTime > _endTime) 
	{
		_endTime = endTime;
	}
	else
	{
		_endTime = en->getDepartureTime();
	}
	return _endTime;
}

void Sink::ServerUtilization() //Brosche-added
{
	_serverActiveTime = (_totalFlowTime - _totalDelayInQueue);
	double utilization = 100*_serverActiveTime / _endTime;
	cout << "SSSQ busy " << utilization << "% of total time." << endl;
}
