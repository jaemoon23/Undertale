#include "stdafx.h"
#include "Soul.h"
#include "SceneBattle.h"

Soul::Soul(const std::string& name)
	: GameObject(name)
{
}

void Soul::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Soul::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Soul::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Soul::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Soul::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Soul::Init()
{
	SetOrigin(Origins::MC);
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	SetPosition({ size.x * 0.03f, size.y * 0.93f });
}

void Soul::Release()
{
}

void Soul::Reset()
{
	scene = (SceneBattle*)SCENE_MGR.GetCurrentScene();
	btIndex = &(scene->btIndex);
	sprite.setTexture(TEXTURE_MGR.Get("graphics/spr_heart_battle_pl_0.png"));
}

void Soul::Update(float dt)
{
	sf::Vector2f pos = GetPosition();
	switch (scene->btState)
	{
		case ButtonState::None:
			if (*btIndex != 0 && InputMgr::GetKeyDown(sf::Keyboard::Left))
			{
				pos.x -= size.x * 0.26f;
				SetPosition(pos);
				(*btIndex)--;
			}
			if (*btIndex != 3 && InputMgr::GetKeyDown(sf::Keyboard::Right))
			{
				pos.x += size.x * 0.26f;
				SetPosition(pos);
				(*btIndex)++;
			}
			break;
		case ButtonState::Fight:
			break;
		case ButtonState::Act:
			break;
		case ButtonState::Item:
			break;
		case ButtonState::Mercy:
			break;
	}
}

void Soul::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}