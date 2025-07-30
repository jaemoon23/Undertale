#include "stdafx.h"
#include "TemMie.h"

TemMie::TemMie(const std::string& name) : GameObject(name)
{
}
void TemMie::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	temMie.setPosition(pos);
}

void TemMie::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	temMie.setRotation(rot);
}

void TemMie::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	temMie.setScale(s);
}

void TemMie::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	temMie.setOrigin(o);
}

void TemMie::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(temMie, preset);
	}
}
void TemMie::Init()
{
	animator.SetTarget(&temMie);
}

void TemMie::Release()
{
}

void TemMie::Reset()
{
	temMie.setTexture(TEXTURE_MGR.Get(texId));
	animator.Play("Animation/temmie/Temmie_Idle.csv");
	SetPosition({ 524.f, 240.f });
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void TemMie::Update(float dt)
{
	hitBox.UpdateTransform(temMie, temMie.getLocalBounds());
	animator.Update(dt);
}

void TemMie::Draw(sf::RenderWindow& window)
{
	window.draw(temMie);
	hitBox.Draw(window);
}
