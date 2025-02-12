#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "SoundManager.h"

class Explosion: public
	GameObject
{
public:
	Explosion(float positionX, float positionY);

	void start();
	void update();
	void draw();

private:
	int x;
	int y;
	int width;
	int height;
	float timer;
	float currentTimer;

	SDL_Texture* explosionTexture;
	Mix_Chunk* explosionSound;
};

