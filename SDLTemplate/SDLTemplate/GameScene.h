#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Explosion.h"
#include "Powerup.h"

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();
	void start();
	void draw();
	void update();
private:
	void Spawn();
	void DespawnEnemy(Enemy* enemy);

	void DoCollisionLogic();
	void DoSpawningLogic();

	int points;

	Player* player;
	Enemy* enemy;

	float spawnTime;
	float currentSpawnTime;

	float reloadTime;
	float currentReloadTime;

	int bgx;
	int bgy;
	int bgWidth;
	int bgHeight;

	int random;

	Mix_Chunk* sound;
	Mix_Chunk* soundI;
	SDL_Texture* bgTexture;
	std::vector<Enemy*> spawnedEnemies;
};