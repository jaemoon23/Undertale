#include "stdafx.h"
#include "Bullet.h"
#include "SceneBattle.h"
#include "StatusInBattleUI.h"

Bullet::Bullet(const std::string& name)
	: GameObject(name)
{
}

void Bullet::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Bullet::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Bullet::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Bullet::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Bullet::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Bullet::SetBulletState(std::string tId, sf::Vector2f startPos, sf::Vector2f Dir, float speed, float waitTime, int d)
{
	texId = tId;
	pos = startPos;
	dir = Dir;
	moveSpeed = speed;
	waitingTime = waitTime;
	damage = d;
}

void Bullet::Init()
{
}

void Bullet::Release()
{
}

void Bullet::Reset()
{
	scene = (SceneBattle*)SCENE_MGR.GetCurrentScene();
	soul = scene->GetSoul();
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	sprite.setTexture(TEXTURE_MGR.Get(texId));
	SetPosition(pos);
}

void Bullet::Update(float dt)
{
	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());

	timer += dt;
	if (timer >= waitingTime)
	{
		sf::Vector2f position = sprite.getPosition();
		position += dir * moveSpeed * dt;
		SetPosition(position);
		if (soul->GetGlobalBounds().intersects(sprite.getGlobalBounds()) && !(soul->isBlink))
		{
			soul->isBlink = true;
			soul->TakeDamage(damage);
			scene->GetStatusUI()->UpdateHpUI();
			SetActive(false);
		}
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	hitBox.Draw(window);
}