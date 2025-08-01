#include "stdafx.h"
#include "TalkObject.h"

TalkObject::TalkObject(const std::string& name)
	: GameObject(name)
{
}

void TalkObject::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void TalkObject::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void TalkObject::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void TalkObject::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void TalkObject::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void TalkObject::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void TalkObject::Release()
{
}

void TalkObject::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get(texId), true);
	SetOrigin(Origins::MC);

	player = ((Player*)SCENE_MGR.GetCurrentScene()->FindGameObject("Sprites/idle.png"));
	textWindow = ((TextWindow*)SCENE_MGR.GetCurrentScene()->FindGameObject("textWindow"));
}

void TalkObject::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Z) && player->GetGlobalBounds().intersects(sprite.getGlobalBounds()))
	{

		textWindow->isDraw = true;
	}
}

void TalkObject::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}