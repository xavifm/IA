#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
}

PriorityQueue::~PriorityQueue()
{
}

void PriorityQueue::addSteeringBehaviourInPriorityList(Vector2D force, int KforcePriority)
{
	steeringForces.push_back(force);
	priorityL.push_back(KforcePriority);
}

Vector2D PriorityQueue::ReturnSteeringForceWithPriority()
{
	for (size_t i = 0; i < steeringForces.size(); i++)
	{
		if (steeringForces[i].Length() > priorityL[i])
			return steeringForces[i];
	}
	return Vector2D(0, 0);
}