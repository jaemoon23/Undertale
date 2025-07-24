#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& name)
	: GameObject(name)
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Enemy::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Enemy::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Enemy::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Enemy::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Enemy::Init()
{
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
}

void Enemy::Update(float dt)
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}