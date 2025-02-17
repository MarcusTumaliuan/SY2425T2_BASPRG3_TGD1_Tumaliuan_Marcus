#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Scene.h"
#include <vector>

class Explosion : public GameObject
{
public:
	Explosion(int positionX, int positionY);
	void start();
	void update();
	void draw();
	int GetPositionX();
	int GetPositionY();
	int GetWidth();
	int GetHeight();
private:
	int x;
	int y;
	int width;
	int height;

	float reloadTime;
	float currentReloadTime;

	SDL_Texture* texture;

	float directionX;
	float directionY;
};
