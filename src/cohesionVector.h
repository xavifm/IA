#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class cohesionVector : public Agent::SteeringBehavior
{
public:
	cohesionVector();
	~cohesionVector();
	Vector2D cohesionVector::calculateCohesionVector(int agentIndex, std::vector<Agent*> agents);
};