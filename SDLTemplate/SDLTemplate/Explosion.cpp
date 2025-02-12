#include "Explosion.h"

Explosion::Explosion(float positionX, float positionY)
{
	this->x = positionX;
	this->y = positionY;
}

void Explosion::start()
{
	explosionTexture = loadTexture("gfx/Explosion.png");
	
	timer = 10;
	currentTimer = 0;

	SDL_QueryTexture(explosionTexture, NULL, NULL, &width, &height);

	explosionSound = SoundManager::loadSound("sound/245372__quaker540__hq-explosion.ogg");
	explosionSound->volume = 50;

	SoundManager::playSound(explosionSound);

}

void Explosion::update()
{
	if (timer > 0)
	{
		timer--;
	}
	else
	{
		delete this;
	}
}

void Explosion::draw()
{
	blit(explosionTexture, x, y);
}
