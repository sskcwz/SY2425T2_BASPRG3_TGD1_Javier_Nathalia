#include "Player.h"

void Player::start()
{
	texture = loadTexture("gfx/player.png");

	// initialize variables to avoid garbage values
	x = 100;
	y = 100;
	width = 0;
	height = 0;
	speedDefault = 2;
	speedBoost = 5;
	currentSpeed = speedDefault;
	


	// query textuure to set W and H
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);
}

void Player::update()
{
	if (app.keyboard[SDL_SCANCODE_W])
	{
		y -= currentSpeed;
	}

	if (app.keyboard[SDL_SCANCODE_S])
	{
		y += currentSpeed;
	}

	if (app.keyboard[SDL_SCANCODE_A])
	{
		x -= currentSpeed;
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		x += currentSpeed;
	}

	if (app.keyboard[SDL_SCANCODE_LSHIFT])
	{
		currentSpeed = speedBoost;
	}

	if (app.keyboard[SDL_SCANCODE_BACKSPACE])
	{
		currentSpeed = speedDefault;
	}
}

void Player::draw()
{
	blit(texture, x, y);
}
