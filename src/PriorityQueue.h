#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include "Steering.h"
#include <vector>

class PriorityQueue : public Agent::SteeringBehavior
{
public:
	PriorityQueue();
	~PriorityQueue();
	void PriorityQueue::addSteeringBehaviourInList(Vector2D force, int KforcePriority);
	Vector2D PriorityQueue::returnSteeringBehaviourByPriority();
	void PriorityQueue::updateSteeringBehaviourInList(Vector2D newForce, int index);
	int PriorityQueue::getPriority();
private:
	std::vector<Steering*> steerings;
};