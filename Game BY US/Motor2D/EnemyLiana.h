#ifndef __ENEMYLIANA_H__
#define __ENEMYLIANA_H__

#include "j1Module.h"
#include "j1Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Mix_Chunk;
struct Collider;

class EnemyLiana : public j1Entity
{
public:
	EnemyLiana();
	virtual ~EnemyLiana();

	bool Awake(pugi::xml_node&config) { return true; };
	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	bool Load(pugi::xml_node&);
	bool Save(pugi::xml_node&) const;
	fPoint Move(fPoint);

public:
	Animation Current_Animation;
	Animation idle;
	Animation walk;
	SDL_Rect rectenemy;

	bool isup = true;
	fPoint initialposition;
	bool isincoltoplayer = false;
	fPoint enemyspeed = { 1.0, 1.0 };
	iPoint enemypoint;
	iPoint playerpoint;
	float angle = 0;
	float positionxinit;
	float positionyinit;
	Collider* body;

};

#endif
