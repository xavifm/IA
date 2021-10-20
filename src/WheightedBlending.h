#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class WheightedBlending :
	public Agent::SteeringBehavior
{
public:
	WheightedBlending(Agent* agent, Vector2D separation, Vector2D Cohesion, Vector2D alignment);
	~WheightedBlending();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};