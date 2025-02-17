#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	player = new Player();
	this->addGameObject(player);
}

GameScene::~GameScene()
{
	delete player;
}

void GameScene::start()
{
	Scene::start();

	bgTexture = loadTexture("gfx/background.png");

	spawnTime = 300;
	currentSpawnTime = spawnTime;

	for (int i = 0; i < 3; i++)
	{
		Spawn();
	}

	initFonts();
	points = 0;

	sound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	sound->volume = 14;
	SDL_QueryTexture(bgTexture, NULL, NULL, &bgWidth, &bgHeight);

	reloadTime = 3;
	reloadTime = currentReloadTime;
}

void GameScene::draw()
{
	blitScale(bgTexture, bgx, bgy, &bgWidth, &bgHeight, 3);

	Scene::draw();

	drawText(110, 20, 255, 255, 255, TEXT_CENTER, "POINTS: %03d", points);

	if (!player->IsAlive())
	{
		drawText(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 255, 255, 255, TEXT_CENTER, "GAME OVER!");
	}
}

void GameScene::update()
{
	Scene::update();

	DoSpawningLogic();
	DoCollisionLogic();
}

void GameScene::Spawn()
{
	enemy = new Enemy();
	this->addGameObject(enemy);
	enemy->SetPlayerTarget(player);

	spawnedEnemies.push_back(enemy);
}

void GameScene::DespawnEnemy(Enemy* enemy)
{
	int index = -1;
	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (enemy == spawnedEnemies[i])
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		Enemy* enemy = spawnedEnemies[index];
		spawnedEnemies.erase(spawnedEnemies.begin() + index);
		delete enemy;
	}
}

void GameScene::DoCollisionLogic()
{
	// Check for collision
	for (int i = 0; i < objects.size(); i++)
	{
		Bullet* bullet = dynamic_cast<Bullet*>(objects[i]);

		if (bullet != NULL)
		{
			// If the bullet is from the enemy side, check againts player
			if (bullet->getSide() == Side::ENEMY_SIDE)
			{
				int collision = checkCollision(
					player->GetPositionX(), player->GetPositionY(), player->GetWidth(), player->GetHeight(),
					bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());

				if (collision == 1)
				{
					//std::cout << "Player Has Been Hit!" << std::endl;
					player->DoDeath();
					break;
				}
			}

			// If the bullet is from the player side, check againts ememy
			else if (bullet->getSide() == Side::PLAYER_SIDE)
			{
				for (int i = 0; i < spawnedEnemies.size(); i++)
				{
					Enemy* currentEnemy = spawnedEnemies[i];

					int collision = checkCollision(
						currentEnemy->GetPositionX(), currentEnemy->GetPositionY(), currentEnemy->GetWidth(), currentEnemy->GetHeight(),
						bullet->getPositionX(), bullet->getPositionY(), bullet->getWidth(), bullet->getHeight());

					if (collision == 1)
					{
						Explosion* explosion = new Explosion(currentEnemy->GetPositionX(), currentEnemy->GetPositionY());
						this->addGameObject(explosion);
						//std::cout << "Enemy Has Been Hit!" << std::endl;
						DespawnEnemy(currentEnemy);
						points++;
						SoundManager::playSound(sound);
						if (currentReloadTime > 0)
						{
							currentReloadTime--;
						}
						if (currentReloadTime <= 0)
						{
						delete explosion;
						currentReloadTime = reloadTime;
						}
						break;
					}
				}
			}
		}
	}
}

void GameScene::DoSpawningLogic()
{
	if (currentSpawnTime > 0)
	{
		currentSpawnTime--;
	}

	if (currentSpawnTime <= 0)
	{
		Spawn();

		currentSpawnTime = spawnTime;
	}

	for (int i = 0; i < spawnedEnemies.size(); i++)
	{
		if (spawnedEnemies[i]->GetPositionX() < 0)
		{
			// Cache the variable so we can delete it later
			// We can't delete it after erasing from the vector (leaked pointer)
			Enemy* enemyToErase = spawnedEnemies[i];
			spawnedEnemies.erase(spawnedEnemies.begin() + i);

			delete enemyToErase;

			// We can't mutate (change) our vector while looping inside it
			// this might crash on the next loop iteration
			// To counter that, we only delete one bullet per frame
			break;

		}
	}
}


