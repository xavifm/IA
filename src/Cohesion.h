#pragma once
#include "Agent.h"
#include <vector>

class Cohesion : public Agent::SteeringBehavior
{
public:
	Cohesion();
	~Cohesion();
	Vector2D Cohesion::calculateSteeringForce(int agentIndex, std::vector<Agent*> agents);
};