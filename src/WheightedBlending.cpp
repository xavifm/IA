#include "WheightedBlending.h"

WheightedBlending::WheightedBlending()
{
	/*agent->separationDir = separation;
	agent->cohesionDir = Cohesion;
	agent->alignmentDir = alignment;*/
}

WheightedBlending::~WheightedBlending()
{
}

Vector2D WheightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
	Vector2D totalSteeringBehaviors = Vector2D(0, 0);
	std::vector<Vector2D> aux = agent->GetSteeringGroups();

	for (int i = 0; i < aux.size(); i++)
	{
		totalSteeringBehaviors += aux[i];
	}

	return totalSteeringBehaviors;
}