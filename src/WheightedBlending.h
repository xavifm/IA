#pragma once
#include "Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class WheightedBlending :
	public Agent::SteeringBehavior
{
public:
<<<<<<< HEAD
	WheightedBlending(Agent* agent, Vector2D separation, Vector2D cohesion, Vector2D alignment, float Kseparation, float Kcohesion, float Kalignment);
	WheightedBlending::WheightedBlending(Agent* agent, Vector2D steering);
=======
	WheightedBlending(Agent* agent, Vector2D separation, Vector2D Cohesion, Vector2D alignment);
>>>>>>> 0dc1669039ca99face9377dc5543e437a8391d46
	~WheightedBlending();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
};