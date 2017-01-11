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
	background2 = App->textures->Load("battletoads/level2.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	App->audio->PlayMusic("battletoads/bgm.ogg", 1.0f);
	
	// TODO 15: create some colliders for the walls
	// solution wall coords: {0, 224, 3930, 16} {1375, 0, 111, 96} {1375, 145, 111, 96}
	
	initCol();

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
	App->player->xF += (float)base_speed;
	App->renderer->camera.x -= base_speed*3;
	
	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 28, NULL);
	App->renderer->Blit(background2, 11248, 28, NULL);
	
	return UPDATE_CONTINUE;
}

void ModuleSceneSpace::initCol() {
	//First Part
	Collider * tw1 = App->collision->AddCollider({ 1408, 120, 10, 80 });
	tw1->colliderType = TOP_WALL;

	Collider * bw1 = App->collision->AddCollider({ 2176, 120, 10, 80 });
	bw1->colliderType = BOT_WALL;

	Collider * tw2 = App->collision->AddCollider({ 2944, 120, 10, 80 });
	tw2->colliderType = TOP_WALL;

	Collider * bw2 = App->collision->AddCollider({ 3712, 120, 10, 80 });
	bw2->colliderType = BOT_WALL;

	Collider * tw3 = App->collision->AddCollider({ 4480, 120, 10, 80 });
	tw3->colliderType = TOP_WALL;

	Collider * bw3 = App->collision->AddCollider({ 5248, 120, 10, 80 });
	bw3->colliderType = BOT_WALL;

	Collider * bw4 = App->collision->AddCollider({ 5760, 120, 10, 80 });
	bw4->colliderType = BOT_WALL;

	Collider * tw4 = App->collision->AddCollider({ 6272, 120, 10, 80 });
	tw4->colliderType = TOP_WALL;

	Collider * tw5 = App->collision->AddCollider({ 6784, 120, 10, 80 });
	tw5->colliderType = TOP_WALL;

	Collider * lw1 = App->collision->AddCollider({ 7548, 120, 10, 80 });
	lw1->colliderType = LOW_WALL;

	Collider * bw5 = App->collision->AddCollider({ 7936, 120, 10, 80 });
	bw5->colliderType = BOT_WALL;

	Collider * tw6 = App->collision->AddCollider({ 8448, 120, 10, 80 });
	tw6->colliderType = TOP_WALL;

	Collider * lw2 = App->collision->AddCollider({ 8956, 120, 10, 80 });
	lw2->colliderType = LOW_WALL;

	Collider * lw3 = App->collision->AddCollider({ 9468, 120, 10, 80 });
	lw3->colliderType = LOW_WALL;

	Collider * lw4 = App->collision->AddCollider({ 9868, 120, 10, 80 });
	lw4->colliderType = LOW_WALL;

	Collider * tw7 = App->collision->AddCollider({ 10496, 120, 10, 80 });
	tw7->colliderType = TOP_WALL;

	Collider * bw6 = App->collision->AddCollider({ 10784, 120, 10, 80 });
	bw6->colliderType = BOT_WALL;

	Collider * tw8 = App->collision->AddCollider({ 11048, 120, 10, 80 });
	tw8->colliderType = TOP_WALL;

	//Second Part
	int offset = 11248;

	Collider * rp1 = App->collision->AddCollider({ 1648+offset, 120, 10, 80 });
	rp1->colliderType = RAMP;

	Collider * pit1 = App->collision->AddCollider({ 1730 + offset, 120, 295, 80 });
	pit1->colliderType = PIT;
}