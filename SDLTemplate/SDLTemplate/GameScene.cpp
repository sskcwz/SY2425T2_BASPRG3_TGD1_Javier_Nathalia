#include "GameScene.h"

GameScene::GameScene()
{
	// Register and add game objects on constructor
	backgroundTexture = new Background();
	this->addGameObject(backgroundTexture);
	
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

	spawnTime = 300;
	currentSpawnTime = spawnTime;

	for (int i = 0; i < 3; i++)
	{
		Spawn();
	}

	initFonts();
	points = 0;
}

void GameScene::draw()
{
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

	enemy->setPosition(300 + (rand() % 350), -50);
	spawnedEnemies.push_back(enemy);

	PowerUp* powerUp = new PowerUp;
	this->addGameObject(powerUp);
	powerUp->setPosition(250, 250);
	spawnedPowerUp.push_back(powerUp);
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

		PowerUp* powerUp = dynamic_cast<PowerUp*>(objects[i]);

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
					float playerX = player->GetPositionX();
					float playerY = player->GetPositionY();

					Explosion* explosion = new Explosion(playerX, playerY);

					this->addGameObject(explosion);
					
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
						float enemyX = enemy->GetPositionX();
						float enemyY = enemy->GetPositionY();

						Explosion* explosion = new Explosion(enemyX, enemyY);

						this->addGameObject(explosion);

						//std::cout << "Enemy Has Been Hit!" << std::endl;
						DespawnEnemy(currentEnemy);
						points++;
						break;
					}
				}
			}
		}

		if (powerUp != NULL)
		{
			int collision = checkCollision(
				player->GetPositionX(), player->GetPositionY(), player->GetWidth(), player->GetHeight(),
				powerUp->getPositionX(), powerUp->getPositionY(), powerUp->getWidth(), powerUp->getHeight()
			);

			if (collision == 1)
			{
				player->usePowerUp();
				powerUp->deletePowerUp();
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

void GameScene::spawnPowerUp()
{
	PowerUp* powerUp = new PowerUp;
	this->addGameObject(powerUp);
	powerUp->setPosition(300 + (rand() % 350), -30);
	spawnedPowerUp.push_back(powerUp);
}
