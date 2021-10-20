#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
}

PriorityQueue::~PriorityQueue()
{
}

void PriorityQueue::addSteeringBehaviourInList(Vector2D force, int KforcePriority)
{
	Steering* localSteering = new Steering();
	localSteering->force = force;
	localSteering->priority = KforcePriority;

	steerings.push_back(localSteering);
}

Vector2D PriorityQueue::returnSteeringBehaviourByPriority()
{
	for (size_t i = 0; i < steerings.size() -1; i++)
	{
		if(steerings[i]->force.Length() > steerings[i]->priority)
		{
			return steerings[i]->force;
		}
	}
	return Vector2D(0, 0);
}

void PriorityQueue::updateSteeringBehaviourInList(Vector2D newForce, int index)
{
	steerings[index]->force = newForce;
}

int PriorityQueue::getPriority()
{
	return 0;
}