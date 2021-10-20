#include "WheightedBlending.h"

WheightedBlending::WheightedBlending(Agent* agent, Vector2D separation, Vector2D Cohesion, Vector2D alignment)
{
	agent->flockingFleePos = separation;
	agent->cohesionDir = Cohesion;
	agent->alignmentDir = alignment;
}

WheightedBlending::WheightedBlending(Agent* agent, Vector2D steering)
{
	agent->steeringResult = steering;
}

Vector2D WheightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
	/*return (agent->flockingFleePos * agent->KSeparation)
		+ (agent->cohesionDir * agent->KCohesion)
		+ (agent->alignmentDir * agent->KAlignment);*/
	return agent->steeringResult;
}