#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Background.h"
#include "Explosion.h"
#include "PowerUp.h"


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

	void spawnPowerUp();

	int points;

	Player* player;
	Enemy* enemy;
	Background* backgroundTexture;
	PowerUp* powerUp;

	float spawnTime;
	float currentSpawnTime;

	float powerUpSpawnTime;
	float currentPowerUpSpawnTime;

	std::vector<Enemy*> spawnedEnemies;
	std::vector<PowerUp*> spawnedPowerUp;
};

