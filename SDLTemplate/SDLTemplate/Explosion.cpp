#include "Explosion.h"

Explosion::Explosion(int positionX, int positionY)
{
	this->x = positionX;
	this->y = positionY;
}

void Explosion::start()
{
	texture = loadTexture("gfx/explosion.png");
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
	width = 0;
	height = 0;
}

void Explosion::update()
{
}

void Explosion::draw()
{
	blit(texture, x, y);
}

int Explosion::GetPositionX()
{
	return x;
}

int Explosion::GetPositionY()
{
	return y;
}

int Explosion::GetWidth()
{
	return width;
}

int Explosion::GetHeight()
{
	return height;
}
