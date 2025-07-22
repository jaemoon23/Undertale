#include "stdafx.h"
#include "BattleButton.h"

BattleButton::BattleButton(const std::string& name)
	: GameObject(name)
{
}

void BattleButton::SetTexture()
{
	if (!isOn)
	{
		sprite.setTexture(TEXTURE_MGR.Get(offTexId));
	}
	else
	{
		sprite.setTexture(TEXTURE_MGR.Get(onTexId));
	}
}

void BattleButton::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void BattleButton::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void BattleButton::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void BattleButton::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void BattleButton::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void BattleButton::Init()
{
}

void BattleButton::Release()
{
}

void BattleButton::Reset()
{
	SetTexture();
}

void BattleButton::Update(float dt)
{
}

void BattleButton::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}