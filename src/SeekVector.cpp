#include "SeekVector.h"

Vector2D SeekVector::calculateSeekVector(int agentIndex, std::vector<Agent*> agents)
{
	Vector2D desiredVelocity = agents[agentIndex]->getTarget() - agents[agentIndex]->getPosition();
	desiredVelocity.Normalize();
	desiredVelocity *= agents[agentIndex]->getMaxVelocity();
	Vector2D steeringForce = desiredVelocity - agents[agentIndex]->getVelocity();
	steeringForce.Normalize();
	return steeringForce * agents[agentIndex]->getMaxForce();
}
