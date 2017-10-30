#include "Source.h"
#include <iostream>

using namespace std;

class Source::CreateEntityEvent : public Event
{
public:
	CreateEntityEvent(Source *source)
	{
		_source = source;
	}

	void Execute()
	{
		_source->CreateEntity();
	}

private:
	Source *_source;
};

Source::Source(std::string name, SSSQ * sssq, Distribution * interarrivalTime)
{
	_sssq = sssq;
	_interarrivalTime = interarrivalTime;
	//schedule first entity creation
	ScheduleEventAt(0.0, new CreateEntityEvent(this));
	_name = name;
	_numGen = -1;
}

Source::Source(std::string name, SSSQ * sssq, Distribution * interarrivalTime, int numGen)
{
	_sssq = sssq;
	_interarrivalTime = interarrivalTime;
	//schedule first entity creation
	ScheduleEventAt(0.0, new CreateEntityEvent(this));
	_name = name;
	_numGen = numGen;
}

void Source::CreateEntity()
{
	if ((_numGen == -1) || (_numGen > 0))
	{
		if (_numGen > 0)
		{
			_numGen--;
		}
		Entity *en = new Entity(SimObj::GetCurrentSimTime()); //Edited by Brosche to set arrival time
		cout << GetCurrentSimTime() << ", " << _name << ", CreateEntity, Entity " << en->GetID() << endl;
		_sssq->ScheduleArrivalIn(0.0, en);
		ScheduleEventIn(_interarrivalTime->GetRV(), new CreateEntityEvent(this));
	}
}
