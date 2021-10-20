#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class WheightedBlending :
	public Agent::SteeringBehavior
{
public:
	WheightedBlending(Agent* agent, Vector2D separation, Vector2D cohesion, Vector2D alignment, float Kseparation, float Kcohesion, float Kalignment);
	~WheightedBlending();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};