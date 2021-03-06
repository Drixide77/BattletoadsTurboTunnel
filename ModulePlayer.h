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
	SDL_Texture* foreground = nullptr;
	SDL_Texture* foreground2 = nullptr;

	Animation* current_animation = nullptr;
	Animation idle;
	Animation jump;
	Animation falling;
	Animation dead;

  uint deathfx = 0;
  uint jumpfx = 0;

	iPoint position;
	float xF, yF;
	int height;
	float verticalOffset;
	float verticalSpeed;

	bool jumping;
	bool ramp_jumping;

	bool destroyed;
  float death_counter;
  bool isdead;

	Collider *collider;
};

#endif