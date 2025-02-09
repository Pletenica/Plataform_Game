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

j1Scene::j1Scene() : j1Module()
{
	/////PLANT PORTAL ANIMATION//////
	plant_portal.PushBack({ 0, 64, 50, 64 });
	plant_portal.PushBack({ 50, 64, 50, 64 });
	plant_portal.PushBack({ 100, 64, 50, 64 });
	plant_portal.PushBack({ 50, 64, 50, 64 });
	plant_portal.speed = 0.08f;

	/////SNOW PORTAL ANIMATION//////
	ice_portal.PushBack({ 0, 128, 50, 64 });
	ice_portal.PushBack({ 50, 128, 50, 64 });
	ice_portal.PushBack({ 100, 128, 50, 64 });
	ice_portal.PushBack({ 50, 128, 50, 64 });
	ice_portal.speed = 0.08f;

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

	/////FIRE PORTAL ANIMATION//////
	fire_portal.PushBack({ 0, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.PushBack({ 100, 0, 50, 64 });
	fire_portal.PushBack({ 50, 0, 50, 64 });
	fire_portal.speed = 0.08f;

	/////WATTER PORTAL ANIMATION//////
	watter_portal.PushBack({ 0, 192, 50, 64 });
	watter_portal.PushBack({ 50, 192, 50, 64 });
	watter_portal.PushBack({ 100, 192, 50, 64 });
	watter_portal.PushBack({ 50, 192, 50, 64 });
	watter_portal.speed = 0.08f;

	/////FIRE RING ANIMATION//////
	fire_ring_anim.PushBack({ 150, 0, 55, 80 });
	fire_ring_anim.PushBack({ 150, 80, 55, 80 });
	fire_ring_anim.speed = 0.08f;

	/////WATTER WAVE ANIMATION//////
	watter_wave_anim.PushBack({ 150, 160, 96, 64 });
	watter_wave_anim.PushBack({ 150, 224, 96, 64 });
	watter_wave_anim.PushBack({ 150, 288, 96, 64 });
	watter_wave_anim.speed = 0.08f;

	name.create("scene");

}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;

	/////// SCENE 1 PORTALS ///////
	plantportalx = config.child("plantportal").attribute("x").as_int();
	plantportaly = config.child("plantportal").attribute("y").as_int();
	iceportalx = config.child("iceportal").attribute("x").as_int();
	iceportaly = config.child("iceportal").attribute("y").as_int();
	finalportalx = config.child("finalportal").attribute("x").as_int();
	finalportaly = config.child("finalportal").attribute("y").as_int();
	normal1portalx = config.child("normalportal1").attribute("x").as_int();
	normal1portaly = config.child("normalportal1").attribute("y").as_int();
	normal2portalx = config.child("normalportal2").attribute("x").as_int();
	normal2portaly = config.child("normalportal2").attribute("y").as_int();

	/////// SCENE 2 PORTALS ///////
	fireportalx = config.child("fireportal").attribute("x").as_int();
	fireportaly = config.child("fireportal").attribute("y").as_int();
	watterportalx = config.child("watterportal").attribute("x").as_int();
	watterportaly = config.child("watterportal").attribute("y").as_int();
	normal3portalx = config.child("normalportal3").attribute("x").as_int();
	normal3portaly = config.child("normalportal3").attribute("y").as_int();
	normal4portalx = config.child("normalportal4").attribute("x").as_int();
	normal4portaly = config.child("normalportal4").attribute("y").as_int();
	endportalx = config.child("endportal").attribute("x").as_int();
	endportaly = config.child("endportal").attribute("y").as_int();
	firering1x = config.child("firering1").attribute("x").as_int();
	firering1y = config.child("firering1").attribute("y").as_int();
	firering2x = config.child("firering2").attribute("x").as_int();
	firering2y = config.child("firering2").attribute("y").as_int();
	firering3x = config.child("firering3").attribute("x").as_int();
	firering3y = config.child("firering3").attribute("y").as_int();
	firering4x = config.child("firering4").attribute("x").as_int();
	firering4y = config.child("firering4").attribute("y").as_int();
	firering5x = config.child("firering5").attribute("x").as_int();
	firering5y = config.child("firering5").attribute("y").as_int();
	firering6x = config.child("firering6").attribute("x").as_int();
	firering6y = config.child("firering6").attribute("y").as_int();


	/////// PLAYER AND CAMERA VARIABLES ///////
	camlimitleft = config.child("camlimits").attribute("left").as_int();
	camlimitright = config.child("camlimits").attribute("right").as_int();
	positionplayerinitx = config.child("positionplayerinit").attribute("x").as_int();
	positionplayerinity = config.child("positionplayerinit").attribute("y").as_int();
	App->player->position.x = positionplayerinitx;
	App->player->position.y = positionplayerinity;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("Scene01.tmx");
	objects_graphics = App->tex->Load("textures/Objects.png");

	///// CAMERA COLLISIONS /////
	cameralimit01 = App->collision->AddCollider({ 0,0,20,350 }, COLLIDER_CAMERA, this);
	cameralimit02 = App->collision->AddCollider({ 380,0,20,350 }, COLLIDER_CAMERA, this);
	camleftlim = App->collision->AddCollider({ camlimitleft,0,20,350 }, COLLIDER_CAMERA_LLEFT, this);
	camrightlim = App->collision->AddCollider({ camlimitright,0,20,350 }, COLLIDER_CAMERA_LRIGHT, this);

	App->SaveGame();
	App->player->dimensionhielo = false;
	App->audio->PlayMusic("audio/music/back.ogg");
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	if (changelevel == false && donecollidersscene1 == false) {
		///// PORTAL COLLLIDERS SCENE 1/////
		plantportal = App->collision->AddCollider({ plantportalx + 30,plantportaly,20,64 }, COLLIDER_PORTAL_PLANTA, this);
		normalportal01 = App->collision->AddCollider({ normal1portalx + 30,normal1portaly,20,64 }, COLLIDER_PORTAL_NORMAL1, this);
		iceportal = App->collision->AddCollider({ iceportalx + 30,iceportaly,20,64 }, COLLIDER_PORTAL_HIELO, this);
		normalportal02 = App->collision->AddCollider({ normal2portalx + 30,normal2portaly,20,64 }, COLLIDER_PORTAL_NORMAL1, this);
		finalportal = App->collision->AddCollider({ finalportalx + 30,finalportaly,20,64 }, COLLIDER_PORTAL_CHANGESCENE1, this);
		donecollidersscene1 = true;
	}

	if (changelevel == true && donecollidersscene2 == false) {
		///// PORTAL COLLLIDERS SCENE 2/////
		firering11 = App->collision->AddCollider({ firering1x -17,firering1y+23,15,10 }, COLLIDER_DEATH, this);
		firering11 = App->collision->AddCollider({ firering1x -80,firering1y + 23,10,10 }, COLLIDER_DEATH, this);
		firering21 = App->collision->AddCollider({ firering2x + 23,firering2y,3,5 }, COLLIDER_DEATH, this);
		firering21 = App->collision->AddCollider({ firering2x + 23,firering2y +75,3,5 }, COLLIDER_DEATH, this);
		firering31 = App->collision->AddCollider({ firering3x + 23,firering3y,3,5 }, COLLIDER_DEATH, this);
		firering31 = App->collision->AddCollider({ firering3x + 23,firering3y + 75,3,5 }, COLLIDER_DEATH, this);
		firering41 = App->collision->AddCollider({ firering4x + 23,firering4y,3,5 }, COLLIDER_DEATH, this);
		firering41 = App->collision->AddCollider({ firering4x + 23,firering4y + 75,3,5 }, COLLIDER_DEATH, this);
		firering51 = App->collision->AddCollider({ firering5x - 17,firering5y + 23,10,10 }, COLLIDER_DEATH, this);
		firering51 = App->collision->AddCollider({ firering5x - 80,firering5y + 23,10,10 }, COLLIDER_DEATH, this);
		firering61 = App->collision->AddCollider({ firering6x + 23,firering6y,3,5 }, COLLIDER_DEATH, this);
		firering61 = App->collision->AddCollider({ firering6x + 23,firering6y + 75,3,5 }, COLLIDER_DEATH, this);
		fireportal = App->collision->AddCollider({ fireportalx + 30,fireportaly,20,64 }, COLLIDER_PORTAL_FUEGO, this);
		normalportal03 = App->collision->AddCollider({ normal3portalx + 30,normal3portaly,20,64 }, COLLIDER_PORTAL_NORMAL2, this);
		watterportal = App->collision->AddCollider({ watterportalx + 30,watterportaly,20,64 }, COLLIDER_PORTAL_AGUA, this);
		normalportal04 = App->collision->AddCollider({ normal4portalx + 30,normal4portaly,20,64 }, COLLIDER_PORTAL_NORMAL2, this);
		endportal = App->collision->AddCollider({ endportalx + 30,endportaly,20,64 }, COLLIDER_PORTAL_CHANGESCENEFINAL, this);
		donecollidersscene2 = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->LoadGame();

	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN)
		ResetCurrentLevel(changelevel);

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->SaveGame();

	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		App->player->ChangeToLevel1();

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
		App->player->ChangeToLevel2();

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	App->map->Draw();
	if (App->player->position.x > cameraxinvert + 200) {
		if ((((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (App->player->stop_right == false)) && (cameralimit02->CheckCollision(camrightlim->rect) == false))|| (App->player->ice_right == true)) {
			if (App->player->ice_right == true) {
				if ((App->player->right == false)) {
					cameraxinvert += App->player->speed_player_ice;
					App->render->camera.x -= App->player->speed_player_ice* App->win->GetScale();
					cameralimit01->rect.x += App->player->speed_player_ice;
					cameralimit02->rect.x += App->player->speed_player_ice;
				}
				else if (App->player->right == true) {
					cameraxinvert += App->player->speed_player_ice + App->player->speed_player;
					App->render->camera.x -= (App->player->speed_player_ice + App->player->speed_player) * App->win->GetScale();
					cameralimit01->rect.x += App->player->speed_player_ice + App->player->speed_player;
					cameralimit02->rect.x += App->player->speed_player_ice + App->player->speed_player;
				}

			}
			else {
				cameraxinvert += App->player->speed_player;
				App->render->camera.x -= App->player->speed_player * App->win->GetScale();
				cameralimit01->rect.x += App->player->speed_player;
				cameralimit02->rect.x += App->player->speed_player;
			}

		}
	}
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count());

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (changelevel == false) {
		App->render->Blit(objects_graphics, plantportalx, plantportaly, &(plant_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal1portalx, normal1portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, iceportalx, iceportaly, &(ice_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal2portalx, normal2portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, finalportalx, finalportaly, &(final_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	}
	else {
		if (App->player->dimensionfuego) {
			App->render->Blit(objects_graphics, firering1x, firering1y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 90, 0, 0, flip);
			App->render->Blit(objects_graphics, firering2x, firering2y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
			App->render->Blit(objects_graphics, firering3x, firering3y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
			App->render->Blit(objects_graphics, firering4x, firering4y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
			App->render->Blit(objects_graphics, firering5x, firering5y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 90, 0, 0, flip);
			App->render->Blit(objects_graphics, firering6x, firering6y, &(fire_ring_anim.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		}
		if (App->player->dimensionagua) {
			App->render->Blit(objects_graphics, 2464, 192, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 2816, 256, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 2816, 128, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 3168, 256, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
			App->render->Blit(objects_graphics, 3168, 128, &(watter_wave_anim.GetCurrentFrame()), 1.0f, 180, 0, 0, flip);
		}
		App->render->Blit(objects_graphics, fireportalx, fireportaly, &(fire_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal3portalx, normal3portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, watterportalx, watterportaly, &(watter_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, normal4portalx, normal4portaly, &(normal_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
		App->render->Blit(objects_graphics, endportalx, endportaly, &(final_portal.GetCurrentFrame()), 1.0f, 0, 0, 0, flip);
	}


	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = App->player->exitgame = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->map->CleanUp();
	App->tex->UnLoad(objects_graphics);
	return true;
}

bool j1Scene::Save(pugi::xml_node& data) const
{
	data.append_child("scene");
	data.child("scene").append_attribute("camx") = cameraxinvert;
	data.child("scene").append_attribute("actualscene") = changelevel;
	data.append_child("playerposition");
	data.child("playerposition").append_attribute("x") = App->player->position.x;
	data.child("playerposition").append_attribute("y") = App->player->position.y;
	data.append_child("playerworld");
	data.child("playerworld").append_attribute("watter") = App->player->dimensionagua;
	data.child("playerworld").append_attribute("fire") = App->player->dimensionfuego;
	data.child("playerworld").append_attribute("plant") = App->player->dimensionplanta;
	data.child("playerworld").append_attribute("ice") = App->player->dimensionhielo;
	data.child("playerworld").append_attribute("normal") = App->player->dimensionnormal;
	data.append_child("playerattribute");
	data.child("playerattribute").append_attribute("godmode") = App->player->godmode;
	data.child("playerattribute").append_attribute("ice_right") = App->player->ice_right;
	data.child("playerattribute").append_attribute("ice_left") = App->player->ice_left;
	return true;
}

bool j1Scene::Load(pugi::xml_node& data)
{
	bool changeyet = false;
	if (changelevel != data.child("scene").attribute("actualscene").as_bool()) {
		if (changelevel == false) {
			App->player->ChangeToLevel2();
			changelevel = data.child("scene").attribute("actualscene").as_bool();
			changeyet = true;
		}
		if (changelevel == true) {
			if (changeyet == false) {
				App->player->ChangeToLevel1();
				changelevel = data.child("scene").attribute("actualscene").as_bool();
			}
		}
	}
	cameraxinvert = data.child("scene").attribute("camx").as_int();
	App->player->position.x = data.child("playerposition").attribute("x").as_int();
	App->player->position.y = data.child("playerposition").attribute("y").as_int();
	App->player->dimensionnormal = data.child("playerworld").attribute("normal").as_bool();
	App->player->dimensionagua = data.child("playerworld").attribute("watter").as_bool();
	App->player->dimensionfuego = data.child("playerworld").attribute("fire").as_bool();
	App->player->dimensionplanta = data.child("playerworld").attribute("plant").as_bool();
	App->player->dimensionhielo = data.child("playerworld").attribute("ice").as_bool();
	App->player->godmode = data.child("playerattribute").attribute("godmode").as_bool();
	App->player->ice_right = data.child("playerattribute").attribute("ice_right").as_bool();
	App->player->ice_left = data.child("playerattribute").attribute("ice_left").as_bool();

	cameralimit01->rect.x = cameraxinvert;
	cameralimit02->rect.x = cameraxinvert + 380;
	return true;
}

void j1Scene::ResetCurrentLevel(bool current_level)
{
	if (current_level == true) {
		App->player->ChangeToLevel2();
	}
	else if (current_level == false) {
		App->player->ChangeToLevel1();
	}
}