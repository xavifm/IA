#pragma once
#include <vector>
#include "Scene.h"
#include "Agent.h"
#include "Pursue.h"

class SceneSeekFlee :
	public Scene
{
public:
	SceneSeekFlee();
	~SceneSeekFlee();
	void update(float dtime, SDL_Event *event);
	void draw();
	const char* getTitle();
private:
	Pursue* pursue;
	std::vector<Agent*> agents;
	Vector2D target;
};

