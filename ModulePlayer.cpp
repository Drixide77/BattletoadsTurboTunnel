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

#define GRAVITY 0.2f
#define JUMP_SPEED 4.0f
#define INITIAL_SPEED -1.0f

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	idle.frames.push_back({16, 442, 37, 30});

	jump.frames.push_back({63, 440, 37, 30});

	falling.frames.push_back({105, 439, 46, 31});

	dead.frames.push_back({193, 443, 26, 34});
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("battletoads/player.png");
	foreground = App->textures->Load("battletoads/foreground.png");
	foreground2 = App->textures->Load("battletoads/foreground2.png");

  if (deathfx == 0)
    deathfx = App->audio->LoadFx("battletoads/explosion.wav");

  if (jumpfx == 0)
    jumpfx = App->audio->LoadFx("battletoads/jump.ogg");

	destroyed = false;
	position.x = 30;
	xF = 30.0f;
	position.y = 130;
	yF = 130.0f;

	height = 4;
	verticalOffset = 4.0f;
	verticalSpeed = INITIAL_SPEED;

	jumping = false;
	ramp_jumping = false;

	SDL_Rect collRec;
	collRec.x = 1;
	collRec.y = 1;
	collRec.h = 30;
	collRec.w = 37;
	collider = App->collision->AddCollider(collRec);
	collider->colliderType = PLAYER;
	collider->addObserver(this);

  destroyed = false;
  death_counter = 2.0f;
  isdead = false;

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
	if (!destroyed) {
		float hSpeed = 2.0;
		float vSpeed = 3.5;
		int camera = App->renderer->camera.x / 3;

		if (!jumping) {
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
			{
				if (position.y < 150) yF += vSpeed;
			}

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
			{
				if (position.y > 110) yF -= vSpeed;
			}

			if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				verticalSpeed = -JUMP_SPEED;
				jumping = true;
				current_animation = &jump;
			}

			if (verticalOffset < 4.0f) verticalSpeed += GRAVITY;
			else verticalSpeed -= GRAVITY;

			verticalOffset += verticalSpeed;
		}
		else {
			if (ramp_jumping) {
				if (position.x < 2400 + 11248) {
					verticalSpeed += GRAVITY*0.5f;
				}
				else if (position.x < 2400 + 11248) {
					verticalSpeed += GRAVITY*0.5f;
				}
			}
			else verticalSpeed += GRAVITY;
			if (verticalSpeed > -0.5f) current_animation = &falling;
			verticalOffset += verticalSpeed;
			if (verticalOffset > 4.0f) {
				verticalOffset = 4.0f;
				verticalSpeed = -INITIAL_SPEED;
				jumping = false;
				ramp_jumping = false;
				current_animation = &idle;
			}
		}

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		{
			if (position.x + camera > 5) xF -= hSpeed;
		}

		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT || App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		{
			if (position.x + camera < 200) xF += hSpeed;
		}

	}
	else {
    if (death_counter > 0.0f) {
      verticalSpeed += GRAVITY;
      verticalOffset += verticalSpeed;
      death_counter -= 0.01666f;
    }
    else if (!isdead) {
      isdead = true;
      CleanUp();
      App->fade->FadeToBlack((Module *)App->scene_intro, (Module *)App->scene_space, 1.0f);
    }
	}

	height = (int)verticalOffset;

	position.x = (int)xF;
	position.y = (int)yF;

	collider->SetPos(position.x, position.y); //update collider position

	// Draw everything --------------------------------------
  if (death_counter > 0.0f) App->renderer->Blit(graphics, position.x, (position.y + height), &(current_animation->GetCurrentFrame()));

	App->renderer->Blit(foreground, 0, 28, NULL);
	App->renderer->Blit(foreground2, 11248, 28, NULL);
	return UPDATE_CONTINUE;
}

void ModulePlayer::onNotify(GameEvent event) {
	if (event == CRASH && !destroyed) {
		destroyed = true;
		current_animation = &dead;
    verticalSpeed = -JUMP_SPEED;
    App->audio->PlayFx(deathfx);
	}
	else if (event == RAMP_JUMP && !destroyed) {
		if (!jumping && position.y < 140 && position.y > 120) {
			if (position.x < 1700 + 11248) {
				verticalSpeed = -JUMP_SPEED*1.2f;
			} else if (position.x < 1700 + 11248) {
				verticalSpeed = -JUMP_SPEED*1.2f;
			}
			jumping = true;
			ramp_jumping = true;
			current_animation = &jump;
      App->audio->PlayFx(jumpfx);
		}
	}
	else if (event == CHECK_LOW && !destroyed) {
		if (!jumping || height > 0) {
			destroyed = true;
			current_animation = &dead;
      verticalSpeed = -JUMP_SPEED;
      App->audio->PlayFx(deathfx);
		}
	}
	else if (event == CROSS_GOAL && !destroyed) {
		//Do victory
    CleanUp();
    App->fade->FadeToBlack((Module *)App->scene_intro, (Module *)App->scene_space, 0.5f);
	}
	else if (event == CHECK_PIT && !destroyed) {
		if (!jumping) {
			destroyed = true;
			current_animation = &dead;
      verticalSpeed = -JUMP_SPEED;
      App->audio->PlayFx(deathfx);
		}
	}
}