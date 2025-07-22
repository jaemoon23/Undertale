#include "stdafx.h"
#include "Sans.h"


Sans::Sans(const std::string& name)
	: GameObject(name)
{
}

void Sans::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sans.setPosition(pos);
}

void Sans::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sans.setRotation(rot);
}

void Sans::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sans.setScale(s);
}

void Sans::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sans.setOrigin(o);
}

void Sans::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sans, preset);
	}
}

void Sans::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Sans::Release()
{
}

void Sans::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	sans.setTexture(TEXTURE_MGR.Get(sanstexIds));
	sans.setPosition(100.f, 100.f);
}

void Sans::Update(float dt)
{
	hitBox.UpdateTransform(sans, sans.getLocalBounds());
}

void Sans::Draw(sf::RenderWindow& window)
{
	hitBox.Draw(window);
	window.draw(sans);
}

const sf::RectangleShape& Sans::GetHitBox() const
{
	return hitBox.rect;
}
