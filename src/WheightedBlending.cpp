#include "WheightedBlending.h"

WheightedBlending::WheightedBlending(Agent* agent, Vector2D separation, Vector2D Cohesion, Vector2D alignment)
{
	agent->separationDir = separation;
	agent->cohesionDir = Cohesion;
	agent->alignmentDir = alignment;
}

WheightedBlending::~WheightedBlending()
{
}

Vector2D WheightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
	return (agent->separationDir * KSeparation)
		+ (agent->cohesionDir * KCohesion)
		+ (agent->alignmentDir * KAlignment);
}