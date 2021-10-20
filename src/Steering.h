#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"

class Steering
	: public Agent::SteeringBehavior
{
public:
	Steering() {}
	~Steering() {}
	int priority;
	Vector2D force;
};

