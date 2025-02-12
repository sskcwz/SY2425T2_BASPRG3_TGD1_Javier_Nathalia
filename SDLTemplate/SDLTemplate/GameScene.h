#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>
#include "text.h"
#include "Background.h"
#include "Explosion.h"


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
	Background* backgroundTexture;

	float spawnTime;
	float currentSpawnTime;

	std::vector<Enemy*> spawnedEnemies;
};

