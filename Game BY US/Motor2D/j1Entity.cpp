#include "j1Entity.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Collision.h"
#include "j1EntityManager.h"

j1Entity::j1Entity(EntityType type) {
	this->type = type;
}

bool j1Entity::Awake(pugi::xml_node&) {
	return true;
}

bool j1Entity::Start() {
	bool ret = true;

	return ret;
}

bool j1Entity::CleanUp() {
	bool ret = true;
	App->tex->UnLoad(texture);
	if (body != nullptr) {
		body->to_delete = true;
		body = nullptr;
	}
	texture = nullptr;
	return ret;
}

bool j1Entity::PreUpdate() {
	bool ret = true;
	return ret;
}

bool j1Entity::Update(float dt) {
	bool ret = true;
	return ret;
}

bool j1Entity::PostUpdate() {
	bool ret = true;

	return ret;
}