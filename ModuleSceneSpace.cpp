#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneSpace.h"

ModuleSceneSpace::ModuleSceneSpace(bool active) : Module(active)
{}

ModuleSceneSpace::~ModuleSceneSpace()
{}

// Load assets
bool ModuleSceneSpace::Start()
{
	LOG("Loading space scene");
	speed_timer = 0;

	background = App->textures->Load("battletoads/level1.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	App->audio->PlayMusic("battletoads/bgm.ogg", 1.0f);
	
	// TODO 15: create some colliders for the walls
	// solution wall coords: {0, 224, 3930, 16} {1375, 0, 111, 96} {1375, 145, 111, 96}
	/*
	Collider * wallCollider1 = App->collision->AddCollider({ 0, 224, 3930, 16 });
	wallCollider1->colliderType = WALL;
	Collider * wallCollider2 = App->collision->AddCollider({ 1375, 0, 111, 96 });
	wallCollider2->colliderType = WALL;
	Collider * wallCollider3 = App->collision->AddCollider({ 1375, 145, 111, 96 });
	wallCollider3->colliderType = WALL;
	*/

	return true;
}

// UnLoad assets
bool ModuleSceneSpace::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneSpace::Update()
{
	int base_speed = 6;
	if (speed_timer < 120) {
		speed_timer++;
		if (speed_timer < 20) base_speed = 1;
		else if (speed_timer < 40) base_speed = 2;
		else if (speed_timer < 60) base_speed = 3;
		else if (speed_timer < 80) base_speed = 4;
		else if (speed_timer < 100) base_speed = 5;
		else base_speed = 6;
	}

	// Move camera forward -----------------------------
	int scroll_speed = base_speed;

	App->player->position.x += base_speed;
	App->renderer->camera.x -= base_speed*3;
	
	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 28, NULL);
	
	return UPDATE_CONTINUE;
}