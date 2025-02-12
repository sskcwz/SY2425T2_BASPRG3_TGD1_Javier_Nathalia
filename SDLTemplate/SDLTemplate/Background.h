#pragma once
#include "GameObject.h"
#include "draw.h"


class Background:public
	GameObject
{
public:
	void start();
	void update();
	void draw();

private:
	int x;
	int y;
	int width;
	int height;
	int scale;

	SDL_Texture* backgroundTexture;
};

