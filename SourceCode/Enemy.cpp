#include "Enemy.h"

void Enemy::init(int x, int y, int hp, sf::Texture& tex)
{
	this->x = x;
	this->y = y;
	this->hp = hp;
	sprite.setTexture(tex);
	sprite.setPosition(x, y);
	m_alive = true;
}

//simplest update function
void Enemy::update()
{
	if (hp < 1)
		m_alive = false;
}

bool Enemy::is_alive()
{
	return m_alive;
}

sf::Sprite* Enemy::getSprite()
{
	return &sprite;
}