#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Observer.h"
#include "ModuleCollision.h"

struct SDL_Texture;

class ModulePlayer : public Module ,Observer
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void onNotify(GameEvent event);
public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	iPoint position;

	//use floats casted to int for parabolic jumping and hovering
	int hoverHeight;
	int hoverSpeed;
	int hoverCounter;

	bool jumping;
	bool ramp_jumping;
	int verticalSpeed;
	int verticalCounter;

	bool destroyed = false;

	Collider *collider;
};

#endif