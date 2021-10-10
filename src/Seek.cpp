#include "Seek.h"

Seek::Seek()
{
}

Seek::~Seek()
{
}

Vector2D Seek::calculateSteeringForce(Agent *agent, float dtime)
{
	if(agent->sceneNum == 0) 
	{
		Vector2D desiredVelocity = agent->getTarget() - agent->getPosition();
		desiredVelocity.Normalize();
		desiredVelocity *= agent->getMaxVelocity();
		Vector2D steeringForce = desiredVelocity - agent->getVelocity();
		steeringForce.Normalize();
		return steeringForce * agent->getMaxForce();
	}
	else if(agent->sceneNum == 2) 
	{
		return (agent->flockingFleePos * agent->KSeparation)
			 + (agent->cohesionDir * agent->KCohesion)
			 + (agent->alignmentDir * agent->KAlignment);
	}
	return Vector2D(0, 0);
}
