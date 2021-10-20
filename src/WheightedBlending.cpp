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

WheightedBlending::~WheightedBlending()
{
}

Vector2D WheightedBlending::calculateSteeringForce(Agent* agent, float dtime)
{
<<<<<<< HEAD
	/*return (agent->flockingFleePos * agent->KSeparation)
		+ (agent->cohesionDir * agent->KCohesion)
		+ (agent->alignmentDir * agent->KAlignment);*/
	return agent->steeringResult;
=======
	return (agent->flockingFleePos * KSeparation)
		+ (agent->cohesionDir * KCohesion)
		+ (agent->alignmentDir * KAlignment);
>>>>>>> 0dc1669039ca99face9377dc5543e437a8391d46
}