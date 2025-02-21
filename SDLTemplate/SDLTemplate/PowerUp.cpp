#include "PowerUp.h"

void PowerUp::start()
{
	texture = loadTexture("gfx/points.png");
	x = 0;
	y = 0;
	directionX = 1;
	directionY = 1;
	width = 0;
	height = 0;
	speed = 1;
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void PowerUp::update()
{
	y += directionY * speed;
}

void PowerUp::draw()
{
	blit(texture, x, y);
}

void PowerUp::setPosition(int positionX, int positionY)
{
	this->x = positionX;
	this->y = positionY;
}

int PowerUp::getPositionX()
{
	return x;
}

int PowerUp::getPositionY()
{
	return y;
}

int PowerUp::getWidth()
{
	return width;
}

int PowerUp::getHeight()
{
	return height;
}
void PowerUp::deletePowerUp()
{
	delete this;
}