#include "WheightedBlending.h"

WheightedBlending::WheightedBlending(Agent* agent, Vector2D separation, Vector2D Cohesion, Vector2D alignment, float Kseparation, float Kcohesion, float Kalignment)
{
	agent->flockingFleePos = separation;
	agent->KSeparation = Kseparation;
	agent->cohesionDir = Cohesion;
	agent->KCohesion = Kcohesion;
	agent->alignmentDir = alignment;
	agent->KAlignment = Kalignment;
}

WheightedBlending::~WheightedBlending()
{
}

Vector2D WheightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
	return (agent->flockingFleePos * agent->KSeparation)
		+ (agent->cohesionDir * agent->KCohesion)
		+ (agent->alignmentDir * agent->KAlignment);
}