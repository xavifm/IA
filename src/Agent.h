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
		void applySteeringForce(Agent* agent, float dtime);;
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

	std::vector<Vector2D> steeringGroups;

public:
	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	Vector2D separationDir;
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
	std::vector<Vector2D> GetSteeringGroups();
	Vector2D GetAllSteeringGroupsInAVector();
	void AddSteeringGroupsForce(Vector2D force);
	void ClearSteeringGroupsForce();
	
};
