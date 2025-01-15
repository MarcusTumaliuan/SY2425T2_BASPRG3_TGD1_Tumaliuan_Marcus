#pragma once
#include "GameObject.h"
#include "Common.h"
#include "Draw.h"

class Player : public GameObject
{
public:
	void start();
	void update();
	void draw();
private:
	int x;
	int y;
	int width;
	int height;

	int speed;

	SDL_Texture* texture;
};

