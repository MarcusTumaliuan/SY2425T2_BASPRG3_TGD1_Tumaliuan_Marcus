#include "Player.h"

Player::Player()
{
	x = 360;
	y = 1200;
}

Player::~Player()
{
	// Memory manage our bullets. Delete all bullets on player deletion/death
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

	bullets.clear();
}

void Player::start()
{
	// Load Texture
	texture = loadTexture("gfx/player.png");

	// Initialize to avaoid garvage values
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	speed = 5;

	reloadTime = 8;
	currentReloadTime = reloadTime;

	isAlive = true;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Initialize sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	//0-128
	sound->volume = 64;
}

void Player::update()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			// Cache the variable so we can delete it later
			// We can't delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);

			delete bulletToErase;

			// We can't mutate (change) our vector while looping inside it
			// this might crash on the next loop iteration
			// To counter that, we only delete one bullet per frame
			break;
		}
	}

	if (!isAlive) return;

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] &&
		currentReloadTime <= 0)
	{
		Bullet* bullet = new Bullet(x + width - 28,
			y + (height * -0.4) - 5,
			0, -1, 5, Side::PLAYER_SIDE);

		getScene()->addGameObject(bullet);

		bullets.push_back(bullet);

		SoundManager::playSound(sound);

		currentReloadTime = reloadTime;
	}

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

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime <= 2)
	{
		Bullet* bulletI = new Bullet(x + width - 7, y + (height / 2) - 5, 0, -1, 5, Side::PLAYER_SIDE);
		Bullet* bulletII = new Bullet(x + width - 50, y + (height / 2), 0, -1, 5, Side::PLAYER_SIDE);
		getScene()->addGameObject(bulletI);
		getScene()->addGameObject(bulletII);
		bulletI->start();
		bulletII->start();
		bullets.push_back(bulletI);
		bullets.push_back(bulletII);
		SoundManager::playSound(sound);
		currentReloadTime = reloadTime;
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
	if (!isAlive) return;
	blit(texture, x, y);
}

int Player::GetPositionX()
{
	return x;
}

int Player::GetPositionY()
{
	return y;
}

int Player::GetWidth()
{
	return width;
}

int Player::GetHeight()
{
	return height;
}

bool Player::IsAlive()
{
	return isAlive;
}

void Player::DoDeath()
{
	isAlive = false;
}