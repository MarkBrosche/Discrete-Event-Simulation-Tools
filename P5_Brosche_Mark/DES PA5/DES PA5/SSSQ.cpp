#include "SSSQ.h"
#include <iostream>

using namespace std;

SSSQ::SSSQ(std::string name, Sink * sink, Distribution * serviceTime)
{
	_prevDepartureTime = -1;
	_sink = sink;
	_serviceTime = serviceTime;
	_name = name;
}

class SSSQ::ArriveEvent : public Event
{
public:
	ArriveEvent(SSSQ *sssq, Entity *en)
	{
		_sssq = sssq;
		_en = en;
		
	}

	void Execute()
	{
		_sssq->Arrive(_en);
	}

private:
	SSSQ *_sssq;
	Entity *_en;
};

void SSSQ::ScheduleArrivalIn(Time deltaT, Entity *en)
{
	//schedule an arrive event with the Simulation Executive
	ScheduleEventIn(deltaT, new ArriveEvent(this, en));
}

class SSSQ::DepartEvent : public Event
{
public:
	DepartEvent(SSSQ *sssq, Entity *en)
	{
		_sssq = sssq;
		_en = en;
	}

	void Execute()
	{
		_sssq->Depart(_en);
	}

private:
	SSSQ *_sssq;
	Entity *_en;
};

void SSSQ::Arrive(Entity * en)
{
	cout << GetCurrentSimTime() << ", SSSQ " << _name << ", Arrive, Entity " << en->GetID() << endl;
	Time departTime;
	if (_prevDepartureTime < GetCurrentSimTime())
	{
		departTime = GetCurrentSimTime() + _serviceTime->GetRV();
		en->setServiceStartTime(GetCurrentSimTime()); // Added by Brosche
	}
	else
	{
		departTime = _prevDepartureTime + _serviceTime->GetRV();
		en->setServiceStartTime(_prevDepartureTime); // Added by Brosche
	}
	_prevDepartureTime = departTime;
	ScheduleEventAt(departTime, new DepartEvent(this, en));
}

void SSSQ::Depart(Entity * en)
{
	cout << GetCurrentSimTime() << " , SSSQ " << _name << ", Depart, Entity " << en->GetID() << endl;
	_sink->Depart(en);
}
