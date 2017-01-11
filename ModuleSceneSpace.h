#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneSpace : public Module
{
public:
	ModuleSceneSpace(bool active = true);
	~ModuleSceneSpace();

	bool Start();
	update_status Update();
	bool CleanUp();

	int speed_timer = 0;

public:
	
	SDL_Texture* background = nullptr;
	SDL_Texture* background2 = nullptr;
  SDL_Texture* gui = nullptr;
	SDL_Texture* stars = nullptr;

private:
	void initCol();
};

#endif // __MODULESCENESPACE_H__