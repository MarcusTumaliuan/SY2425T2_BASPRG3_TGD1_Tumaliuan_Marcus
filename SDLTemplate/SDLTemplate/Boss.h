#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Scene.h"
#include <vector>
#include "util.h"
#include "Player.h"

class Boss : public GameObject
{
public:
	Boss();
	~Boss();
	void start();
	void update();
	void draw();
	void SetPlayerTarget(Player* player);
	int GetPositionX();
	int GetPositionY();
	int GetWidth();
	int GetHeight();
private:
	int x;
	int y;
	int directionX;
	int directionY;
	int width;
	int height;

	int speed;

	float reloadTime;
	float currentReloadTime;
	float directionChangeTime;
	float currentDirectionChangeTime;

	SDL_Texture* texture;
	Mix_Chunk* sound;

	std::vector<Bullet*> bullets;

	Player* playerTarget;
};

