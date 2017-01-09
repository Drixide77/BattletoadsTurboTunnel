#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	// flying animation
	idle.frames.push_back({16, 442, 37, 30}); //16, 442, 53, 472

	/*
	// move upwards
	up.frames.push_back({100, 1, 32, 14});
	up.frames.push_back({132, 0, 32, 14});
	up.loop = false;
	up.speed = 0.1f;
	*/
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("battletoads/player.png");

	destroyed = false;
	position.x = 30;
	position.y = 130;

	hoverHeight = 0;
	hoverSpeed = 1;
	hoverCounter = 0;

	SDL_Rect collRec;
	collRec.x = 1;
	collRec.y = 1;
	collRec.h = 30;
	collRec.w = 37;
	collider = App->collision->AddCollider(collRec);
	collider->colliderType = PLAYER;
	collider->addObserver(this);

	current_animation = &idle;
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
	{
		position.x -= speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
	{
		position.x += speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
	{
		if (position.y < 150) position.y += speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
	{
		if (position.y > 110) position.y -= speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// JUMP	
	}

	collider->SetPos(position.x, position.y); //update collider position

	if (hoverCounter >= 2) {
		hoverHeight += hoverSpeed;
		hoverCounter = 0;
	}
	else hoverCounter++;
	if (hoverSpeed > 0 && hoverHeight >= 10) {
		hoverSpeed = -1;
	}
	if (hoverSpeed < 0 && hoverHeight <= 0) {
		hoverSpeed = 1;
	}

	// Draw everything --------------------------------------
	if(destroyed == false)
		App->renderer->Blit(graphics, position.x, (position.y + hoverHeight), &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player

void ModulePlayer::onNotify(GameEvent event) {
	if (event == DESTROY_PARTICLE) {
		destroyed = true;
		App->particles->AddParticle(App->particles->explosion, position.x+5, position.y); //create explosion
		App->particles->AddParticle(App->particles->explosion, position.x, position.y); //create explosion
		App->particles->AddParticle(App->particles->explosion, position.x-5, position.y); //create explosion
		destroyed = true;
		CleanUp();
		App->fade->FadeToBlack((Module *)App->scene_intro, (Module *)App->scene_space, 3.0f);
	}
}