#include "Enemy.h"

Enemy::Enemy()
{
	x = 1000;
	y = rand() % 400 + 200;
}

Enemy::~Enemy()
{
}

void Enemy::start()
{
	// Load Texture
	texture = loadTexture("gfx/enemy.png");

	directionX = -1;
	directionY = -1;

	width = 0;
	height = 0;
	speed = 2;

	reloadTime = 60;
	currentReloadTime = reloadTime;

	directionChangeTime = rand() % 300 + 180;
	currentDirectionChangeTime = directionChangeTime;

	// Query the texture to set our width and height
	SDL_QueryTexture(texture, NULL, NULL, &width, &height);

	// Initialize sound
	sound = SoundManager::loadSound("sound/334227__jradcoolness__laser.ogg");
	sound->volume = 64;

}

void Enemy::update()
{
	x += directionX * speed;
	y += directionY * speed;

	if (y + height > SCREEN_HEIGHT || y < 0)
	{
		directionY = -directionY;
	}

#pragma region Direction Change Logic
	if (currentDirectionChangeTime > 0)
	{
		currentDirectionChangeTime--;
	}

	if (currentDirectionChangeTime <= 0)
	{
		directionY = -directionY;
		currentDirectionChangeTime = directionChangeTime;
	}
#pragma endregion

	if (currentReloadTime > 0)
	{
		currentReloadTime--;
	}

	if (currentReloadTime <= 0)
	{
		float dx;
		float dy;

		calcSlope(playerTarget->GetPositionX(), playerTarget->GetPositionY(),
			x, y,
			&dx, &dy);

		Bullet* bullet = new Bullet (x + width, y - 2 + height / 2, dx, dy, 10, Side::ENEMY_SIDE);

		getScene()->addGameObject(bullet);

		bullets.push_back(bullet);

		SoundManager::playSound(sound);

		currentReloadTime = reloadTime;
	}

	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->getPositionX() < 0)
		{
			// Cache the variable so we can delete it later
			// We can't delete it after erasing from the vector (leaked pointer)
			Bullet* bulletToErase = bullets[i];
			bullets.erase(bullets.begin() + i);

			delete bulletToErase;

			// We can't mutate (change) our vector while looping inside it
			// this might crash on the next loop iteration
			// To counter that, we only delete one bullet per frame
			break;
		}
	}
}

void Enemy::draw()
{
	blit(texture, x, y);
}

void Enemy::SetPlayerTarget(Player* player)
{
	playerTarget = player;
}

int Enemy::GetPositionX()
{
	return x;
}

int Enemy::GetPositionY()
{
	return y;
}

void Enemy::setPosition(int xPos, int yPos)
{
	this->x = xPos;
	this->y = yPos;
}

int Enemy::GetWidth()
{
	return width;
}

int Enemy::GetHeight()
{
	return height;
}
