#pragma once
#include "GameObject.h"
#include "common.h"
#include "draw.h"
#include "Scene.h"

class PowerUp : public GameObject
{
public:
	void start();
	void update();
	void draw();
	void setPosition(int positionX, int positionY);
	void deletePowerUp();

	int getPositionX();
	int getPositionY();
	int getWidth();
	int getHeight();

private:
	SDL_Texture* texture;
	int x;
	int y;
	int width;
	int height;
	int speed;
	float directionX;
	float directionY;
};
