#include "SeparationVector.h"

SeparationVector::SeparationVector()
{
}

SeparationVector::~SeparationVector()
{
}

Vector2D SeparationVector::calculateSeparationVector(int agentIndex, std::vector<Agent*> agents)
{
	int neighbourCount = 0;
	Vector2D separationVector = Vector2D(0, 0);
	agents[agentIndex]->setTarget(agents[agents.size() - 1]->getPosition());
	for (size_t i = 0; i < agents.size() - 1; i++)
	{
		if (i != agentIndex && sqrt(pow(agents[i]->getPosition().x - agents[agentIndex]->getPosition().x, 2) + pow(agents[i]->getPosition().y - agents[agentIndex]->getPosition().y, 2) < 2000))
		{
			neighbourCount++;
			separationVector += (agents[agentIndex]->getPosition() - agents[i]->getPosition());
		}
	}
	return Vector2D::Normalize(separationVector);
}