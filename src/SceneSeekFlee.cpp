#include "SceneSeekFlee.h"
#include "Seek.h"
#include "Flee.h"
#include "WheightedBlending.h"
#include "AlignmentVector.h"
#include "SeparationVector.h"
#include "cohesionVector.h"

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

	SeparationVector* sepVec = new SeparationVector();
	cohesionVector* cohesionVec = new cohesionVector();
	AlignmentVector* alignVector = new AlignmentVector();

	//FALTA CREAR LA CLASSE QUE TINGUI LA LLISTA DE PRIORITATS PER COMBINAR SEEK I FLOCKING!!!!!
	for (size_t i = 0; i < agents.size()-1; i++)
	{
		Vector2D separationVector = sepVec->calculateSeparationVector(i, agents);
		Vector2D cohesionVector = cohesionVec->calculateCohesionVector(i, agents);
		Vector2D alignmentVector = alignVector->calculateAlignmentVector(i, agents);

		agents[i]->setBehavior(new WheightedBlending(agents[i], separationVector, cohesionVector, alignmentVector, 5000, 200, 0.2f));
	}


	timer -= 0.05f;

	if (timer <= 0)
		agents[agents.size() - 1]->sceneNum = 1;

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