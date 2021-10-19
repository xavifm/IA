#include "Flocking.h"

Flocking::Flocking()
{
}

Flocking::~Flocking()
{
}

Vector2D Flocking::calculateSteeringForce(Agent* agent, float dtime)
{
	return (agent->flockingFleePos * agent->KSeparation)
		+ (agent->cohesionDir * agent->KCohesion)
		+ (agent->alignmentDir * agent->KAlignment);
}

void Flocking::calculateSeparationVector(std::vector<Agent*> &agents)
{
	for (size_t o = 0; o < agents.size() - 1; o++)
	{
		agents[o]->sceneNum = 0;
		int neighbourCount = 0;
		Vector2D separationVector = Vector2D(0, 0);
		agents[o]->setTarget(agents[agents.size() - 1]->getPosition());
		for (size_t i = 0; i < agents.size() - 1; i++)
		{
			if (i != o && sqrt(pow(agents[i]->getPosition().x - agents[o]->getPosition().x, 2) + pow(agents[i]->getPosition().y - agents[o]->getPosition().y, 2) < 2000))
			{
				agents[o]->sceneNum = 2;
				neighbourCount++;
				separationVector += (agents[o]->getPosition() - agents[i]->getPosition());
			}
		}
		agents[o]->KSeparation = 5000;
		agents[o]->flockingFleePos = Vector2D::Normalize(separationVector);
	}
}

void Flocking::calculateCohesionVector(std::vector<Agent*> &agents)
{
	for (size_t o = 0; o < agents.size() - 1; o++)
	{
		Vector2D averagePosition = Vector2D(0, 0);
		agents[o]->sceneNum = 0;
		int neighbourCount = 0;
		agents[o]->setTarget(agents[agents.size() - 1]->getPosition());
		for (size_t i = 0; i < agents.size() - 1; i++)
		{
			if (i != o && sqrt(pow(agents[i]->getPosition().x - agents[o]->getPosition().x, 2) + pow(agents[i]->getPosition().y - agents[o]->getPosition().y, 2) < 2000))
			{
				agents[o]->sceneNum = 2;
				neighbourCount++;
				averagePosition += agents[i]->getPosition();
			}
		}
		averagePosition /= neighbourCount;
		averagePosition -= agents[o]->getPosition();
		agents[o]->KCohesion = 200;
		agents[o]->cohesionDir = Vector2D::Normalize(averagePosition);
	}
}

void Flocking::calculateAlignmentVector(std::vector<Agent*>& agents) 
{

	for (size_t o = 0; o < agents.size() - 1; o++)
	{
		agents[o]->sceneNum = 0;
		agents[o]->setBehavior(new Seek);
		int neighbourCount = 0;
		Vector2D averageVelocity = Vector2D(0, 0);
		agents[o]->setTarget(agents[agents.size() - 1]->getPosition());
		for (size_t i = 0; i < agents.size() - 1; i++)
		{
			if (i != o && sqrt(pow(agents[i]->getPosition().x - agents[o]->getPosition().x, 2) + pow(agents[i]->getPosition().y - agents[o]->getPosition().y, 2) < 2000))
			{
				agents[o]->sceneNum = 2;
				agents[o]->setBehavior(new Flocking);
				neighbourCount++;
				averageVelocity += agents[i]->getVelocity();
			}
		}
		agents[o]->KAlignment = 0.2f;
		agents[o]->alignmentDir = Vector2D::Normalize(averageVelocity);
	}
}

