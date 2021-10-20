#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class PriorityQueue : public Agent::SteeringBehavior
{
public:
	PriorityQueue();
	~PriorityQueue();
	void PriorityQueue::addForce(Vector2D force, int KforcePriority);
	Vector2D PriorityQueue::ReturnAcumulatedForcePriority();
	void PriorityQueue::setPriority(int priority);
	int PriorityQueue::getPriority();
private:
	Vector2D steeringForceAcumulated;
	int priorityL;
};