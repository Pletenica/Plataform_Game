#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Collision.h"
#include "j1Player.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Scene2.h"

j1Scene2::j1Scene2() : j1Module()
{
	/////FIRE PORTAL ANIMATION//////
	fire_portal.PushBack({ 0, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.PushBack({ 100, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.speed = 0.08f;

	/////WATTER PORTAL ANIMATION//////
	watter_portal.PushBack({ 0, 96, 50, 64 });
	watter_portal.PushBack({ 50, 96, 50, 64 });
	watter_portal.PushBack({ 100, 96, 50, 64 });
	watter_portal.PushBack({ 50, 96, 50, 64 });
	watter_portal.speed = 0.08f;

	/////NORMAL PORTAL ANIMATION//////
	normal_portal.PushBack({ 0, 256, 50, 64 });
	normal_portal.PushBack({ 50, 256, 50, 64 });
	normal_portal.PushBack({ 100, 256, 50, 64 });
	normal_portal.PushBack({ 50, 256, 50, 64 });
	normal_portal.speed = 0.08f;

	/////FINAL PORTAL ANIMATION//////
	final_portal.PushBack({ 0, 320, 50, 64 });
	final_portal.PushBack({ 50, 320, 50, 64 });
	final_portal.PushBack({ 100, 320, 50, 64 });
	final_portal.PushBack({ 50, 320, 50, 64 });
	final_portal.speed = 0.08f;

	/////FIRE RING ANIMATION//////
	fire_ring_animation.PushBack({ 150, 0, 55, 80 });
	fire_ring_animation.PushBack({ 150, 80, 55, 80 });
	fire_ring_animation.speed = 0.08f;

	name.create("scene");

}

// Destructor
j1Scene2::~j1Scene2()
{}

// Called before render is available
bool j1Scene2::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	firering1x = config.child("firering1").attribute("x").as_int();;
	firering1y = config.child("firering1").attribute("x").as_int();;
	firering2x = config.child("firering2").attribute("x").as_int();;
	firering2y = config.child("firering2").attribute("x").as_int();;
	firering3x = config.child("firering3").attribute("x").as_int();;
	firering3y = config.child("firering3").attribute("x").as_int();;
	fireportalx = config.child("fireportal").attribute("x").as_int();
	fireportaly = config.child("fireportal").attribute("y").as_int();
	watterportalx = config.child("watterportal").attribute("x").as_int();
	watterportaly = config.child("watterportal").attribute("y").as_int();
	finalportalx = config.child("finalportal").attribute("x").as_int();
	finalportaly = config.child("finalportal").attribute("y").as_int();
	normal1portalx = config.child("normalportal1").attribute("x").as_int();
	normal1portaly = config.child("normalportal1").attribute("y").as_int();
	normal2portalx = config.child("normalportal2").attribute("x").as_int();
	normal2portaly = config.child("normalportal2").attribute("y").as_int();
	camlimitleft = config.child("camlimits").attribute("left").as_int();
	camlimitright = config.child("camlimits").attribute("right").as_int();
	positionplayerinitx = config.child("positionplayerinit").attribute("x").as_int();
	positionplayerinity = config.child("positionplayerinit").attribute("y").as_int();
	App->player->position.x = positionplayerinitx;
	App->player->position.y = positionplayerinity;

	return ret;
}


// Called before the first frame
bool j1Scene2::Start()
{
	App->map->Load("Scene02.tmx");
	objects_graphics = App->tex->Load("textures/Objects.png");

	///// CAMERA COLLISIONS /////
	cameralimit01 = App->collision->AddCollider({ 0,0,20,350 }, COLLIDER_CAMERA, this);
	cameralimit02 = App->collision->AddCollider({ 380,0,20,350 }, COLLIDER_CAMERA, this);
	camleftlim = App->collision->AddCollider({ camlimitleft,0,20,350 }, COLLIDER_CAMERA_LLEFT, this);
	camrightlim = App->collision->AddCollider({ camlimitright,0,20,350 }, COLLIDER_CAMERA_LRIGHT, this);

	///// PORTAL COLLLIDERS /////
	fireportal = App->collision->AddCollider({ fireportalx + 30,fireportaly,20,64 }, COLLIDER_PORTAL_PLANTA, this);
	normalportal01 = App->collision->AddCollider({ normal1portalx + 30,normal1portaly,20,64 }, COLLIDER_PORTAL_NORMAL1, this);
	watterportal = App->collision->AddCollider({ watterportalx + 30,watterportaly,20,64 }, COLLIDER_PORTAL_HIELO, this);
	normalportal02 = App->collision->AddCollider({ normal2portalx + 30,normal2portaly,20,64 }, COLLIDER_PORTAL_NORMAL1, this);
	finalportal = App->collision->AddCollider({ finalportalx + 30,finalportaly,20,64 }, COLLIDER_PORTAL_CHANGESCENE1, this);

	return true;
}

// Called each loop iteration
bool j1Scene2::PreUpdate()
{
	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame();



	return true;
}

// Called each loop iteration
bool j1Scene2::Update(float dt)
{

	App->map->Draw();
	if (App->player->position.x > cameraxinvert + 200) {
		if (((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && (App->player->stop_right == false)) && (cameralimit02->CheckCollision(camrightlim->rect) == false)) {

			cameraxinvert += App->player->speed_player;
			App->render->camera.x -= App->player->speed_player * App->win->GetScale();
			cameralimit01->rect.x += App->player->speed_player;
			cameralimit02->rect.x += App->player->speed_player;
		}
	}
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.count());

	return true;
}

// Called each loop iteration
bool j1Scene2::PostUpdate()
{
	bool ret = true;


	App->render->Blit(objects_graphics, fireportalx, fireportaly, &(fire_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, normal1portalx, normal1portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, watterportalx, watterportaly, &(watter_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, normal2portalx, normal2portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, finalportalx, finalportaly, &(final_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, firering1x, firering1x, &(fire_ring_animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, firering2x, firering2x, &(fire_ring_animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	App->render->Blit(objects_graphics, firering3x, firering3x, &(fire_ring_animation.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene2::CleanUp()
{
	LOG("Freeing scene");
	App->map->CleanUp();
	return true;
}