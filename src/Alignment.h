#pragma once
#include "Agent.h"
#include <vector>

class Alignment : public Agent::SteeringBehavior
{
public:
	Alignment();
	~Alignment();
	Vector2D Alignment::calculateSteeringForce(int agentIndex, std::vector<Agent*> agents);
};