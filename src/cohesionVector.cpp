#include "cohesionVector.h"

cohesionVector::cohesionVector()
{
}

cohesionVector::~cohesionVector()
{
}

Vector2D cohesionVector::calculateCohesionVector(int agentIndex, std::vector<Agent*> agents)
{
	Vector2D averagePosition = Vector2D(0, 0);
	agents[agentIndex]->sceneNum = 0;
	int neighbourCount = 0;
	agents[agentIndex]->setTarget(agents[agents.size() - 1]->getPosition());
	for (size_t i = 0; i < agents.size() - 1; i++)
	{
		if (i != agentIndex && sqrt(pow(agents[i]->getPosition().x - agents[agentIndex]->getPosition().x, 2) + pow(agents[i]->getPosition().y - agents[agentIndex]->getPosition().y, 2) < 2000))
		{
			agents[agentIndex]->sceneNum = 2;
			neighbourCount++;
			averagePosition += agents[i]->getPosition();
		}
	}
	averagePosition /= neighbourCount;
	averagePosition -= agents[agentIndex]->getPosition();
	return Vector2D::Normalize(averagePosition);
}
