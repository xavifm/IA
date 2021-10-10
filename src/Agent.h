#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include "SDL_SimpleApp.h"
#include "Vector2D.h"
#include "utils.h"


class Agent
{
public:
	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual Vector2D calculateSteeringForce(Agent* agent, float dtime)
		{
			return Vector2D(0,0);
		};
		void applySteeringForce(Agent *agent, float dtime) 
		{
			Vector2D v2d = (agent->flockingFleePos * agent->KSeparation);
			Vector2D steeringForce = this->calculateSteeringForce(agent, dtime);
			steeringForce /= agent->max_velocity;
			steeringForce *= agent->max_force;
			Vector2D acceleration = steeringForce / agent->getMass();
			Vector2D velocity;
			
			if (agent->sceneNum == 1 && (agent->position.x == 1280 || agent->position.x == 0 || agent->position.y == 768 || agent->position.y == 0))
				agent->enableBypass = true;
			if (agent->sceneNum == 1 && sqrt(pow(agent->position.x - agent->target.x, 2) + pow(agent->position.y - agent->target.y, 2)) <= 100)
				agent->enableBypass = false;

			if(agent->sceneNum == 1 && ((agent->position.x <= 1280 && agent->position.x > 1180) || (agent->position.x >= 0 && agent->position.x <= 100) || (agent->position.y > 0 && agent->position.y <= 100) || (agent->position.y <= 768 && agent->position.y > 700)) && agent->enableBypass)
			velocity = agent->getVelocity() - acceleration;
			else if(agent->sceneNum == 1) 
			{
				velocity = agent->getVelocity() + acceleration;
				if (agent->enableBypass)
				agent->enableBypass = false;
			}
			else if(agent->sceneNum == 0 || agent->sceneNum == 2)
			velocity = agent->getVelocity() + acceleration;

			velocity.Normalize();
			velocity *= agent->getMaxVelocity();
			agent->setVelocity(velocity);

			agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
		};
	};
private:
	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	float mass;
	float speed;
	float orientation;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Vector2D flockingFleePos;
	Vector2D cohesionDir;
	Vector2D alignmentDir;
	float max_force;
	float max_velocity;
	float KSeparation;
	float KCohesion;
	float KAlignment;
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void update(float dtime, SDL_Event *event);
	void draw();
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	int sceneNum;
	bool enableBypass;
	
};
