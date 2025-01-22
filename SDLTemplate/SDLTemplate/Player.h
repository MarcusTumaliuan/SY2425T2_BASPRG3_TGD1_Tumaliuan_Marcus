#pragma once
#include "GameObject.h"
#include "Common.h"
#include "Draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Scene.h"
#include <vector>

class Player : public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();
private:
	int x;
	int y;
	int width;
	int height;

	int speed;

	float reloadTime;
	float currentReloadTime;

	SDL_Texture* texture;
	Mix_Chunk* sound;

	std::vector<Bullet*> bullets;
};

