#include "Powerup.h"

Powerup::Powerup(int positionX, int positionY, float directionX, float directionY, int speed)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
}

void Powerup::start()
{
	texture = loadTexture("gfx/points.png");

	width = 0;
	height = 0;

	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Powerup::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Powerup::draw()
{
	blit(texture, x, y);
}

int Powerup::getPositionX()
{
	return x;
}

int Powerup::getPositionY()
{
	return y;
}

int Powerup::getWidth()
{
	return width;
}

int Powerup::getHeight()
{
	return height;
}
