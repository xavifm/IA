#include "Agent.h"

using namespace std;

Agent::Agent() : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
				 mass(0.01),
	             speed(0.5),
	             max_force(5),
	             max_velocity(200),
	             orientation(0),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
	             draw_sprite(false)
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior *behavior)
{
	steering_behaviour = behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}

void Agent::update(float dtime, SDL_Event *event)
{

	//cout << "agent update:" << endl;

	switch (event->type) {
		/* Keyboard & Mouse events */
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}

	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);
	
	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::draw()
{
	if (draw_sprite)
	{
		Uint32 sprite;
		
		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;
		
		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else 
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}
}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}

std::vector<Vector2D> Agent::GetSteeringGroups()
{
	return steeringGroups;
}

Vector2D Agent::GetAllSteeringGroupsInAVector() 
{
	Vector2D allSteerings = Vector2D(0, 0);
	for (size_t i = 0; i < steeringGroups.size(); i++)
	{
		allSteerings += steeringGroups[i];
	}
	return allSteerings;
}

void Agent::AddSteeringGroupsForce(Vector2D force)
{
	steeringGroups.push_back(force);
}

void Agent::ClearSteeringGroupsForce()
{
	steeringGroups.clear();
}

void Agent::SteeringBehavior::applySteeringForce(Agent* agent, float dtime)
{
	Vector2D v2d = (agent->separationDir * agent->KSeparation);
	Vector2D steeringForce = this->calculateSteeringForce(agent, dtime);
	steeringForce /= agent->max_velocity;
	steeringForce *= agent->max_force;
	Vector2D acceleration = steeringForce / agent->getMass();
	Vector2D velocity;

	if (agent->sceneNum == 1 && (agent->position.x == 1280 || agent->position.x == 0 || agent->position.y == 768 || agent->position.y == 0))
		agent->enableBypass = true;
	if (agent->sceneNum == 1 && sqrt(pow(agent->position.x - agent->target.x, 2) + pow(agent->position.y - agent->target.y, 2)) <= 100)
		agent->enableBypass = false;

	if (agent->sceneNum == 1 && ((agent->position.x <= 1280 && agent->position.x > 1180) || (agent->position.x >= 0 && agent->position.x <= 100) || (agent->position.y > 0 && agent->position.y <= 100) || (agent->position.y <= 768 && agent->position.y > 700)) && agent->enableBypass)
		velocity = agent->getVelocity() - acceleration;
	else if (agent->sceneNum == 1)
	{
		velocity = agent->getVelocity() + acceleration;
		if (agent->enableBypass)
			agent->enableBypass = false;
	}
	else if (agent->sceneNum == 0 || agent->sceneNum == 2)
		velocity = agent->getVelocity() + acceleration;

	velocity.Normalize();
	velocity *= agent->getMaxVelocity();
	agent->setVelocity(velocity);

	agent->setPosition(agent->getPosition() + agent->getVelocity() * dtime);
}
