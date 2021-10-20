#pragma once
#include "Agent.h"
#include <vector>

class SeekVector : public Agent::SteeringBehavior
{
public:
	Vector2D calculateSeekVector(int agentIndex, std::vector<Agent*> agents);
};