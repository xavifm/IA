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
	void PriorityQueue::addSteeringBehaviourInPriorityList(Vector2D force, int KforcePriority);
	Vector2D PriorityQueue::ReturnSteeringForceWithPriority();
private:
	std::vector<Vector2D> steeringForces;
	std::vector<int> priorityL;
};