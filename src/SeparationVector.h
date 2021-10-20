#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class SeparationVector : public Agent::SteeringBehavior
{
public:
	SeparationVector();
	~SeparationVector();
	Vector2D calculateSeparationVector(int agentIndex, std::vector<Agent*> agents);
};