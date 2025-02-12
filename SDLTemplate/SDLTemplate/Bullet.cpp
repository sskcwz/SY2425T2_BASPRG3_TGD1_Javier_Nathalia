#include "Bullet.h"

Bullet::Bullet(int positionX, int positionY, float directionX, float directionY, int speed, Side side)
{
	this->x = positionX;
	this->y = positionY;
	this->directionX = directionX;
	this->directionY = directionY;
	this->speed = speed;
	this->side = side;

}

void Bullet::start()
{
	texture = loadTexture("gfx/playerBullet.png");

	if (side == Side::ENEMY_SIDE)
		texture = loadTexture("gfx/alienBullet.png");

	// initialize variables to avoid garbage values

	width = 0;
	height = 0;

	// query textuure to set W and H
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Bullet::update()
{
	x += directionX * speed;
	y += directionY * speed;
}

void Bullet::draw()
{
	blit(texture, x, y);
}

int Bullet::getPositionX()
{
	return x;
}

int Bullet::getPositionY()
{
	return y;
}

int Bullet::getWidth()
{
	return width;
}

int Bullet::getHeight()
{
	return height;
}

Side Bullet::getSide()
{
	return side;
}