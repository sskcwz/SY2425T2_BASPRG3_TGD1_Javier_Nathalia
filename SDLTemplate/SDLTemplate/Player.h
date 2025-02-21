#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"
#include "Bullet.h"
#include "Scene.h"
#include <vector>


class Player : public GameObject
{
public:
	~Player();
	void start();
	void update();
	void draw();
	int GetPositionX();
	int GetPositionY();
	int GetWidth();
	int GetHeight();
	bool IsAlive();
	void DoDeath();
	void usePowerUp();

private:
	int x;
	int y;
	int width;
	int height;
	
	int currentSpeed;
	int speedBoost;
	int speedDefault;

	bool isAlive;

	float reloadTime;
	float currentReloadTime;

	float secondReloadTime;
	float currentSecondReloadTime;

	int powerUp;

	SDL_Texture* texture;
	Mix_Chunk* sound;

	std::vector<Bullet*> bullets;
};

