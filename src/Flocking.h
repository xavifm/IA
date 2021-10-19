#pragma once
#include "../src/Agent.h"
#include "Seek.h"
#include "Flee.h"
#include <vector>

class Flocking :
	public Agent::SteeringBehavior
{
public:
	Flocking();
	~Flocking();
	Vector2D calculateSteeringForce(Agent* agent, float dtime);
	void calculateSeparationVector(std::vector<Agent*>& agents);
	void calculateCohesionVector(std::vector<Agent*>& agents);
	void calculateAlignmentVector(std::vector<Agent*>& agents);
};