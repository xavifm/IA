#include "SceneSeekFlee.h"
#include "Seek.h"
#include "Flee.h"
#include "WheightedBlending.h"
#include "Alignment.h"
#include "Separation.h"
#include "cohesion.h"
#include "PriorityQueue.h"
#include "SeekVector.h"

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

	Separation* sepVec = new Separation();
	Cohesion* cohesionVec = new Cohesion();
	Alignment* alignVector = new Alignment();

	//FALTA CREAR LA CLASSE QUE TINGUI LA LLISTA DE PRIORITATS PER COMBINAR SEEK I FLOCKING!!!!!

	//PriorityList ha de guardar un contenidor de steerings behaviours (array de steerings) després ha d'iterar per tots els behaviours i quan un retorni > que la prioritat d'aquell ho retorna
	//per cada vector que retorna crear una classe d'interfície
	for (size_t i = 0; i < agents.size()-1; i++)
	{
		PriorityQueue* localSteering1 = new PriorityQueue();

		Vector2D separationVector = sepVec->calculateSteeringForce(i, agents);
		Vector2D Cohesion = cohesionVec->calculateSteeringForce(i, agents);
		Vector2D alignmentVector = alignVector->calculateSteeringForce(i, agents);

		localSteering1->addForce(separationVector, 5000);
		localSteering1->addForce(Cohesion, 200);
		localSteering1->addForce(alignmentVector, 0.2f);

		localSteering1->setPriority(4700);

		PriorityQueue* localSteering2 = new PriorityQueue();
		SeekVector* seekVector = new SeekVector();

		localSteering2->addForce(seekVector->calculateSeekVector(i, agents), 1);

		localSteering2->setPriority(1);

		int length1 = localSteering1->ReturnAcumulatedForcePriority().Length();
		int length2 = localSteering2->ReturnAcumulatedForcePriority().Length();

		if (localSteering1->ReturnAcumulatedForcePriority().Length() > localSteering1->getPriority())
		agents[i]->setBehavior(new WheightedBlending(agents[i], separationVector, Cohesion, alignmentVector));
		else if (localSteering2->ReturnAcumulatedForcePriority().Length() > localSteering2->getPriority())
		agents[i]->setBehavior(new Seek());
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