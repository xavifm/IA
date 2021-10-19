#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class AlignmentVector : public Agent::SteeringBehavior
{
public:
	AlignmentVector();
	~AlignmentVector();
	Vector2D AlignmentVector::calculateAlignmentVector(int agentIndex, std::vector<Agent*> agents);
};