#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Audio.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "SDL/include/SDL_timer.h"

j1Player::j1Player()
{
	/////IDLE ANIMATION//////
	idle.PushBack({ 0, 0, 32, 32 });
	idle.PushBack({ 32, 0, 32, 32 });
	idle.PushBack({ 64, 0, 32, 32 });
	idle.PushBack({ 32, 0, 32, 32 });
	idle.speed = 0.07f;

	/////JUMP ANIMATION//////
	//jump.PushBack({ 0, 32, 32, 32 });
	//jump.PushBack({ 32, 32, 32, 32 });
	jump.PushBack({ 64, 32, 32, 32 });
	jump.speed = 0.007f;

	/////WALK ANIMATION//////
	walk.PushBack({ 0, 64, 32, 32 });
	walk.PushBack({ 32, 64, 32, 32 });
	walk.PushBack({ 64, 64, 32, 32 });
	walk.PushBack({ 96, 64, 32, 32 });
	walk.speed = 0.07f;

	/////LIANA ANIMATION//////
	liana.PushBack({ 0, 96, 32, 32 });
	liana.PushBack({ 32, 96, 32, 32 });
	liana.PushBack({ 64, 96, 32, 32 });
	liana.speed = 0.007f;

	/////DEAD ANIMATION//////
	dead.PushBack({ 96, 96, 32, 32 });
	dead.PushBack({ 96, 32, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.PushBack({ 96, 0, 32, 32 });
	dead.speed = 0.1f;
}

j1Player::~j1Player()
{}

bool dimensionnormal = true;
bool dimensionagua = false;
bool dimensionfuego = false;
bool dimensionhielo = false;
bool dimensionplanta = false;

// Load assets
bool j1Player::Start()
{
	//// Load All CONDITIONS //// 
	Current_Animation =idle;

	//// Load All Graphics //// 
	normal_graphics = App->tex->Load("textures/PlayerNormal.png");
	fire_graphics = App->tex->Load("textures/PlayerFire.png");
	plant_graphics = App->tex->Load("textures/PlayerPlant.png");
	ice_graphics = App->tex->Load("textures/PlayerSnow.png");
	watter_graphics = App->tex->Load("textures/PlayerWatter.png");
	current_graphics = normal_graphics;

	//// Load All SOUNDS & COLLISIONS //// 
	//walksound = App->audio->LoadChunk("Audio_FX/Punch.wav");
	body = App->collision->AddCollider({ position.x,position.y,20,32 }, COLLIDER_PLAYER, this);
	
	return true;
}

//Clean Up
bool j1Player::CleanUp() {
	App->tex->UnLoad(current_graphics);
	App->tex->UnLoad(fire_graphics);
	App->tex->UnLoad(plant_graphics);
	App->tex->UnLoad(ice_graphics);
	App->tex->UnLoad(watter_graphics);
	App->tex->UnLoad(normal_graphics);
	//App->audio->StopChunk();
	//App->audio->UnLoadChunk(punchsound);
	return true;
}


bool j1Player::PreUpdate() {
	if (deadbool == false && isinair == false && isjumping == false) {
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
	}


	//////// FLIP ////////
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
		flip = SDL_FLIP_HORIZONTAL;
	}

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
		flip = SDL_FLIP_NONE;
	}


	//////// GOD MODE ////////
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN) {
		if (body->to_delete != false) {
			body = App->collision->AddCollider({ position.x,position.y,20,32 }, COLLIDER_PLAYER, this);
			godmode = false;
		}
		else {
			body->to_delete = true;
			isinair = false;
			App->player->godmode = true;

		}
	}
	if (godmode == true) {
		isinair = false;
		isjumping = false;
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
			position.y += speed_player;
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
			position.y -= speed_player;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			position.x -= speed_player;
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			position.x += speed_player;
			flip = SDL_FLIP_NONE;
		}
	}


	//////// INPUTS WHEN TOUCHES GROUND ////////
	if (isinair ==false && !isinliana && !godmode) {
		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && !stop_jump)
			isjumping = true;

		if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)&&!stop_left) {
			position.x -= speed_player;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}

		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)&&!stop_right) {
			position.x += speed_player;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
		}
	}

	//////// LIANA ////////
	if (isinliana == true) {
		isinair = false;
		isjumping = false;
		Current_Animation.GetCurrentFrame() = liana.GetCurrentFrame();
		if (limit_liana == 0) {
			position.y++;
		}
		limit_liana++;
		if (limit_liana == 3) {
			limit_liana = 0;
		}

		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
			position.x -= speed_player;
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
			position.x += speed_player;
			flip = SDL_FLIP_NONE;
		}

		if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_DOWN) {
			position.y -= 10;
		}
	}


	//////// JUMPING ////////
	if (isjumping == true) {
		Current_Animation.GetCurrentFrame() = jump.GetCurrentFrame();
		isinair = false;
		if (G < G_max) {
			G++;
		}
		position.y += G - jump_vel;

		if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && !stop_left) {
			position.x -= speed_player_jump;
		}

		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && !stop_right) {
			position.x += speed_player_jump;
		}
	}


	//////// AIR ////////
	if (isinair==true && isinliana==false) {
		isjumping = false;
		Current_Animation.GetCurrentFrame() = jump.GetCurrentFrame();
		if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && !stop_left) {
			position.x -= speed_player;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_HORIZONTAL;
		}

		if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && !stop_right) {
			position.x += speed_player;
			Current_Animation.GetCurrentFrame() = walk.GetCurrentFrame();
			flip = SDL_FLIP_NONE;
		}
		if (G < G_max) {
			G++;
		}
		position.y += G;
	}


	//////// INPUT FAILS ////////
	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)) {
		Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
	}



	//////// DEATH ////////
	if (deadbool == true) {
		Current_Animation.GetCurrentFrame() = dead.GetCurrentFrame();
		stop_left = true;
		stop_jump = true;
		stop_right = true;

		if (dead.finished == 1) {
			position.x = App->scene->positionplayerinitx;
			position.y = App->scene->positionplayerinity;
			deadbool = false;
		}
	}


	//////// CHANGE PLAYER COLLIDER IF FLIP ////////
	if (flip == SDL_FLIP_HORIZONTAL) {
		body->rect.x = App->player->position.x +7;
		body->rect.y = position.y;
	}
	if (flip == SDL_FLIP_NONE) {
		body->rect.x = App->player->position.x +5;
		body->rect.y = position.y;
	}
	return true;
}


// Update: draw background
bool j1Player::Update()
{
	return true;
}

bool j1Player::PostUpdate() {
	isinair = true;
	isinliana = false;
	stop_right = false;
	stop_left = false;
	stop_jump = false;
	App->render->Blit(current_graphics, position.x, position.y, &(Current_Animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	
	return true;
}


void j1Player::OnCollision(Collider* player, Collider* other) {
	if (player->type == COLLIDER_PLAYER) {
		if (other->type == COLLIDER_PORTAL_AGUA) {
			dimensionnormal = false;
			dimensionagua = true;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = false;
			changeplantmap = false;
			changefiremap = false;
			changenormalmap = false;
			changeicemap = false;
			current_graphics = watter_graphics;
			
			if (changewattermap == false) {
				App->map->CleanUp();
				App->map->Load("lvl2scene04.tmx");
				changewattermap = true;
			}
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_FUEGO) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = true;
			dimensionhielo = false;
			dimensionplanta = false;
			dimensionplanta = false;
			changeplantmap = false;
			changewattermap = false;
			changenormalmap = false;
			changeicemap = false;
			current_graphics = fire_graphics;
			
			if (changefiremap == false) {
				App->map->CleanUp();
				App->map->Load("lvl2scene04.tmx");
				changefiremap = true;
			}
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_HIELO) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = true;
			dimensionplanta = false;
			changeplantmap = false;
			changewattermap = false;
			changenormalmap = false;
			changefiremap = false;
			current_graphics = ice_graphics;	
			
			if (changeicemap == false) {
				App->map->CleanUp();
				App->map->Load("lvl1scene02.tmx");
				changeicemap = true;
			}
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_PLANTA) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = true;
			changeicemap = false;
			changewattermap = false;
			changenormalmap = false;
			changefiremap = false;
			current_graphics = plant_graphics;
			
			if (changeplantmap == false) {
				App->map->CleanUp();
				App->map->Load("lvl1scene02.tmx");
				changeplantmap = true;
			}
			if (position.x > other->rect.x-32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_NORMAL1) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = true;
			changeicemap = false;
			changewattermap = false;
			changeplantmap = false;
			changefiremap = false;
			current_graphics = normal_graphics;
			if (changenormalmap == false) {
				App->map->CleanUp();
				App->map->Load("Scene01.tmx");
				changenormalmap = true;
			}
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}
		if (other->type == COLLIDER_PORTAL_NORMAL2) {
			dimensionnormal = false;
			dimensionagua = false;
			dimensionfuego = false;
			dimensionhielo = false;
			dimensionplanta = true;
			changeicemap = false;
			changewattermap = false;
			changeplantmap = false;
			changefiremap = false;
			current_graphics = normal_graphics;
			if (changenormalmap == false) {
				App->map->CleanUp();
				App->map->Load("Scene02.tmx");
				changenormalmap = true;
			}
			if (position.x > other->rect.x - 32) {
				stop_left = true;
				stop_jump = true;
			}
		}

		else {
			isinair = true;
			isinliana = false;
		}
		if (other->type == COLLIDER_SUELO) {
			isinliana = false;
			isinair = false;
			isinice = false;
			isjumping = false;
			G = Ginit;
			if ((other->rect.y < position.y + 20)&& position.x < other->rect.x) {
				stop_right = true;
				Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
			}
			if ((other->rect.y < position.y + 20) && position.x > other->rect.x) {
				stop_left = true;
				Current_Animation.GetCurrentFrame() = idle.GetCurrentFrame();
			}
		}
		if (other->type == COLLIDER_LIANA) {
			isinliana = true;
			isinair = false;
		}
		if (other->type == COLLIDER_DEATH) {
			isinair = false;
			deadbool = true;
		}

	}
}
