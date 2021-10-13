#include "SceneSeekFlee.h"
#include "Seek.h"
#include "Flee.h"

using namespace std;

float timer = 100;

SceneSeekFlee::SceneSeekFlee()
{
	Agent* agent;
	for (size_t i = 0; i < 20; i++)
	{
		agent = new Agent;
		agent->setBehavior(new Seek);
		agent->setPosition(Vector2D(599, 350+i));
		agent->loadSpriteTexture("../res/zombie1.png", 8);
		agent->sceneNum = 2;
		agent->max_force = 2;
		agent->max_velocity = agent->max_velocity;
		agents.push_back(agent);
	}
	agent = new Agent();
	agent->setBehavior(new Flee);
	agent->setPosition(Vector2D(600,350));
	agent->setTarget(Vector2D(900, 650));
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->sceneNum = 5;
	agents.push_back(agent); 
	target = Vector2D(100, 100);
}

SceneSeekFlee::~SceneSeekFlee()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void SceneSeekFlee::update(float dtime, SDL_Event *event)
{
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
		}
		break;
	default:
		break;
	}

	Vector2D separationVector = Vector2D(0, 0);
	Vector2D averagePosition = Vector2D(0, 0);
	Vector2D cohesionDirection = Vector2D(0, 0);
	Vector2D averageVelocity = Vector2D(0, 0);
	Vector2D alignmentDirection = Vector2D(0, 0);
	int neighbourCount = 0;

	timer -= 0.05f;

	if(timer <= 0)
		agents[agents.size() - 1]->sceneNum = 1;

	for (size_t o = 0; o < agents.size() - 1; o++)
	{
		agents[o]->sceneNum = 0;
		neighbourCount = 0;
		averageVelocity = Vector2D(0, 0);
		averagePosition = Vector2D(0, 0);
		separationVector = Vector2D(0, 0);
		agents[o]->setTarget(agents[agents.size() - 1]->getPosition());
		for (size_t i = 0; i < agents.size() - 1; i++)
		{
			if (i != o && sqrt(pow(agents[i]->getPosition().x - agents[o]->getPosition().x, 2) + pow(agents[i]->getPosition().y - agents[o]->getPosition().y, 2) < 2000))
			{
				agents[o]->sceneNum = 2;
				neighbourCount++;
				averageVelocity += agents[i]->getVelocity();
				averagePosition += agents[i]->getPosition();
				separationVector += (agents[o]->getPosition() - agents[i]->getPosition());
			}
		}
		averageVelocity /= neighbourCount;
		averagePosition /= neighbourCount;
		cohesionDirection = Vector2D::Normalize(averagePosition);
		separationVector /= neighbourCount;
		separationVector = Vector2D::Normalize(separationVector);
		alignmentDirection = Vector2D::Normalize(averageVelocity);
		agents[o]->KSeparation = 5000;
		agents[o]->KCohesion = 200;
		agents[o]->KAlignment = 0.2f;
		agents[o]->flockingFleePos = separationVector;
		agents[o]->cohesionDir = cohesionDirection;
		agents[o]->alignmentDir = alignmentDirection;
	}

	agents[agents.size() - 1]->setTarget(agents[0]->getPosition());

	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->update(dtime, event);
	}
	
}

void SceneSeekFlee::draw()
{
	for (int i = 0; i < (int)agents.size(); i++)
	{
		agents[i]->draw();
	}
}

const char* SceneSeekFlee::getTitle()
{
	return "SDL Steering Behaviors :: Seek and Flee Demo";
}