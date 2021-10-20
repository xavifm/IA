#include "PriorityQueue.h"

PriorityQueue::PriorityQueue()
{
}

PriorityQueue::~PriorityQueue()
{
}

void PriorityQueue::addForce(Vector2D force, int KforcePriority)
{
	steeringForceAcumulated = steeringForceAcumulated + (force * KforcePriority);
}

Vector2D PriorityQueue::ReturnAcumulatedForcePriority()
{
	return steeringForceAcumulated;
}

void PriorityQueue::setPriority(int priority) 
{
	priorityL = priority;
}

int PriorityQueue::getPriority()
{
	return priorityL;
}