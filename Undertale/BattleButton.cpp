#include "stdafx.h"
#include "BattleButton.h"
#include "SceneBattle.h"

BattleButton::BattleButton(const std::string& name)
	: GameObject(name)
{
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
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void BattleButton::Release()
{
}

void BattleButton::Reset()
{
	soul = ((SceneBattle*)SCENE_MGR.GetCurrentScene())->GetSoul();
	sprite.setTexture(TEXTURE_MGR.Get(offTexId));
}

void BattleButton::Update(float dt)
{
	
}

void BattleButton::UpdateTexture()
{
	if (sprite.getGlobalBounds().intersects(soul->GetGlobalBounds()))
	{
		sprite.setTexture(TEXTURE_MGR.Get(onTexId));
	}
	else
	{
		sprite.setTexture(TEXTURE_MGR.Get(offTexId));
	}
}

void BattleButton::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}