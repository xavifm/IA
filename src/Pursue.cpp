#include "Pursue.h"

Pursue::Pursue()
{
	generateObstacles();
}

Pursue::~Pursue()
{
}

Vector2D Pursue::calculateSteeringForce(Agent *agent, float dtime)
{
	Vector2D raycastVector = agent->getPosition();
	raycastVector += agent->getVelocity().Normalize() * 100;

	Vector2D intersectionpoint, normalVector;
	bool obstacleCollision = false;
	Vector2D fleeForce;
	for (int i = 0; i < 2; i++) 
	{
		obstacleCollision = getCollision(obstacles[i], agent->getPosition(), raycastVector, intersectionpoint);
		if (obstacleCollision) 
		{
			normalVector = agent->getPosition() - obstacles[i];
			normalVector.Normalize();
			break;
		}
	}
	if (obstacleCollision) 
	{
		fleeForce = normalVector * 7;
	}
	return fleeForce;
}

bool Pursue::getCollision(Vector2D obsP, Vector2D posA, Vector2D raycastVector, Vector2D intPoint) 
{
	raycastVector = raycastVector.Normalize() * 100;
	float dist = sqrt(pow(obsP.x - posA.x, 2) + pow(obsP.y - posA.y, 2));
	float modV = sqrt(pow(raycastVector.x, 2) + pow(raycastVector.y, 2));
	if (dist < 7 + modV) return true;
	else return false;
}

void Pursue::generateObstacles() 
{

	for (int i = 0; i < 2; i++) 
	{
		obstacles[i] = Vector2D(rand() % 800, rand() % 800);
	}
}
