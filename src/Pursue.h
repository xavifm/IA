#pragma once
#include "Agent.h"

class Pursue :
	public Agent::SteeringBehavior
{
public:
	Pursue();
	~Pursue();
	Vector2D calculateSteeringForce(Agent *agent, float dtime);
	bool getCollision(Vector2D obsP, Vector2D posA, Vector2D raycastVector, Vector2D intPoint);
	void Pursue::generateObstacles();
	Vector2D obstacles[2];
};
