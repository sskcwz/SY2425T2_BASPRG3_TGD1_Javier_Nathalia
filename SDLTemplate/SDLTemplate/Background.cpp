#include "Background.h"

void Background::start()
{
	backgroundTexture = loadTexture("gfx/background.png");

	SDL_QueryTexture(backgroundTexture, NULL, NULL, &width, &height);
}

void Background::update()
{
}

void Background::draw()
{
	blit(backgroundTexture, 0, 0);
	blit(backgroundTexture, 500, 0);
	blit(backgroundTexture, 1000, 0);
	blit(backgroundTexture, 0, 500);
	blit(backgroundTexture, 500, 500);
	blit(backgroundTexture, 1000, 500);
}
