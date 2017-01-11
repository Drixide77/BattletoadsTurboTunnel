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

	Collider * rp1 = App->collision->AddCollider({ 1648 + offset, 120, 10, 80 });
	rp1->colliderType = RAMP;

	Collider * pit1 = App->collision->AddCollider({ 1730 + offset, 120, 295, 80 });
	pit1->colliderType = PIT;

  Collider * lw5 = App->collision->AddCollider({ 2445 + offset, 120, 10, 80 });
  lw5->colliderType = LOW_WALL;

  Collider * rp2 = App->collision->AddCollider({ 2925 + offset, 120, 10, 80 });
  rp2->colliderType = RAMP;

  Collider * pit2 = App->collision->AddCollider({ 3005 + offset, 120, 585, 80 });
  pit2->colliderType = PIT;

  Collider * lw6 = App->collision->AddCollider({ 3980 + offset, 120, 10, 80 });
  lw6->colliderType = LOW_WALL;

  Collider * lw7 = App->collision->AddCollider({ 4300 + offset, 120, 10, 80 });
  lw7->colliderType = LOW_WALL;

  Collider * rp3 = App->collision->AddCollider({ 4719 + offset, 120, 10, 80 });
  rp3->colliderType = RAMP;

  Collider * pit3 = App->collision->AddCollider({ 4805 + offset, 120, 560, 80 });
  pit3->colliderType = PIT;

  Collider * tw9 = App->collision->AddCollider({ 5520 + offset, 120, 10, 80 });
  tw9->colliderType = TOP_WALL;

  Collider * bw7 = App->collision->AddCollider({ 5776 + offset, 120, 10, 80 });
  bw7->colliderType = BOT_WALL;

  Collider * tw10 = App->collision->AddCollider({ 6032 + offset, 120, 10, 80 });
  tw10->colliderType = TOP_WALL;

  Collider * rp4 = App->collision->AddCollider({ 6254 + offset, 120, 10, 80 });
  rp4->colliderType = RAMP;

  Collider * pit4 = App->collision->AddCollider({ 6338 + offset, 120, 1077, 80 });
  pit4->colliderType = PIT;

  Collider * tw11 = App->collision->AddCollider({ 7696 + offset, 120, 10, 80 });
  tw11->colliderType = TOP_WALL;

  Collider * bw8 = App->collision->AddCollider({ 7952 + offset, 120, 10, 80 });
  bw8->colliderType = BOT_WALL;

  Collider * tw12 = App->collision->AddCollider({ 8208 + offset, 120, 10, 80 });
  tw12->colliderType = TOP_WALL;

  Collider * bw9 = App->collision->AddCollider({ 8464 + offset, 120, 10, 80 });
  bw9->colliderType = BOT_WALL;

  Collider * tw13 = App->collision->AddCollider({ 8720 + offset, 120, 10, 80 });
  tw13->colliderType = TOP_WALL;

  Collider * bw10 = App->collision->AddCollider({ 8976 + offset, 120, 10, 80 });
  bw10->colliderType = BOT_WALL;

  Collider * rp5 = App->collision->AddCollider({ 9327 + offset, 120, 10, 80 });
  rp5->colliderType = RAMP;

  Collider * pit5 = App->collision->AddCollider({ 9412 + offset, 120, 1330, 80 });
  pit5->colliderType = PIT;

  Collider * lw8 = App->collision->AddCollider({ 11148 + offset, 120, 10, 80 });
  lw8->colliderType = LOW_WALL;

  Collider * lw9 = App->collision->AddCollider({ 11596 + offset, 120, 10, 80 });
  lw9->colliderType = LOW_WALL;

  Collider * goal = App->collision->AddCollider({ 12012 + offset, 120, 10, 80 });
  goal->colliderType = GOAL;
}