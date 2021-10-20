#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class WheightedBlending :
	public Agent::SteeringBehavior
{
public:
	WheightedBlending();
	~WheightedBlending();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};