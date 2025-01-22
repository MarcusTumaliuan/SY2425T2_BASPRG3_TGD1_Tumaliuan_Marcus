#include "Player.h"

Player::~Player()
{
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	bullets.clear();
}

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

	reloadTime = 8;
	currentReloadTime = reloadTime;

	//Query the texturte to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	//Initialize sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser");
}

void Player::update()
{
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] && currentReloadTime <= 0)
	{
		Bullet* bullet = new Bullet(x + width - 2 , y + (height/2) - 5, 1, 0, 5);
		getScene()->addGameObject(bullet);
		bullet->start();
		bullets.push_back(bullet);
		SoundManager::playSound(sound);
		currentReloadTime = reloadTime;
	}

	if (app.keyboard[SDL_SCANCODE_G] && currentReloadTime <= 2)
	{
		Bullet* bulletI = new Bullet(x + width - 45, y + (height / 50) - 5, 1, 0, 5);
		Bullet* bulletII = new Bullet(x + width - 45, y + (height / 1.1), 1, 0, 5);
		getScene()->addGameObject(bulletI);
		getScene()->addGameObject(bulletII);
		bulletI->start();
		bulletII->start();
		bullets.push_back(bulletI);
		bullets.push_back(bulletII);
		SoundManager::playSound(sound);
		currentReloadTime = reloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			//Cache the variable so we can delete it later
			//We cant delete it after erasing it from the vector (leak pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);
			delete bulletToErase;
			//We can't mutate(change) our vector while looping inside it
			//this might crash thenext loop
			//to counter that, we only delete one bullet per frame
			break;
		}
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
