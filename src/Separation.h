#pragma once
#include "Agent.h"
#include <vector>

class Separation : public Agent::SteeringBehavior
{
public:
	Separation();
	~Separation();
	Vector2D calculateSteeringForce(int agentIndex, std::vector<Agent*> agents);
};