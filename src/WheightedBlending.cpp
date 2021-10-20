#include "WheightedBlending.h"

WheightedBlending::WheightedBlending(Agent* agent, Vector2D separation, Vector2D cohesion, Vector2D alignment, float Kseparation, float Kcohesion, float Kalignment)
{
	agent->flockingFleePos = separation;
	agent->KSeparation = Kseparation;
	agent->cohesionDir = cohesion;
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