#include "Player.h"

Player::~Player()
{
	// memory manage player

	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}

	bullets.clear();
}

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
	
	reloadTime = 8;
	currentReloadTime = reloadTime;

	isAlive = true;

	secondReloadTime = 16;
	currentSecondReloadTime = 0;

	// query textuure to set W and H
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// initialize sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;
}

void Player::update()
{
	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_F] &&
		currentReloadTime <=0)
	{
		Bullet* bullet = new Bullet(x + width - 2, 
									y+ (height/2) - 5,
									1, 0, 5, Side::PLAYER_SIDE);

		getScene()->addGameObject(bullet);
		bullet->start();

		bullets.push_back(bullet);

		SoundManager::playSound(sound);

		currentReloadTime = reloadTime;
	}

	if (!isAlive) return;

	if (currentSecondReloadTime > 0)
	{
		currentSecondReloadTime--;
	}

	if (app.keyboard[SDL_SCANCODE_G] &&
		currentSecondReloadTime <= 0)
	{
		Bullet* additionalBullet1 = new Bullet(x + width - 2,
			y + (height / 2) - 25,
			1, 0, 5, Side::PLAYER_SIDE);

		Bullet* additionalBullet2 = new Bullet(x + width - 2,
			y + (height / 2) + 20,
			1, 0, 5, Side::PLAYER_SIDE);

		getScene()->addGameObject(additionalBullet1);
		getScene()->addGameObject(additionalBullet2);

		additionalBullet1->start();
		additionalBullet2->start();

		bullets.push_back(additionalBullet1);
		bullets.push_back(additionalBullet2);

		SoundManager::playSound(sound);

		currentSecondReloadTime = secondReloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() > SCREEN_WIDTH)
		{
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);

			delete bulletToErase;

			break;
		}
	}

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
	if (!isAlive) return;
	blit(texture, x, y);
}

int Player::GetPositionX()
{
	return x;
}

int Player::GetPositionY()
{
	return y;
}

int Player::GetWidth()
{
	return width;
}

int Player::GetHeight()
{
	return height;
}

bool Player::IsAlive()
{
	return isAlive;
}

void Player::DoDeath()
{
	isAlive = false;
}