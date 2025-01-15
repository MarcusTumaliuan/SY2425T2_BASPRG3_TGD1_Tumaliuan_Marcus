#include "Player.h"

void Player::start()
{
	//load texture
	texture = loadTexture("gfx/player.png");

	// Initialize to avoid garbage value
	x = 200;
	y = 200;
	width = 0;
	height = 0;
	speed = 1;
	//Query the texturte to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += speed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= speed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += speed;
	}
	//More speed
	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		speed = 5;
	}
	//Revert Speed
	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		speed = 1;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}
