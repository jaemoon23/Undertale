#include "stdafx.h"
#include "Papyrus.h"
Papyrus::Papyrus(const std::string& name)
	: GameObject(name)
{
}

void Papyrus::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	papyrus.setPosition(pos);
}

void Papyrus::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	papyrus.setRotation(rot);
}

void Papyrus::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	papyrus.setScale(s);
}

void Papyrus::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	papyrus.setOrigin(o);
}

void Papyrus::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(papyrus, preset);
	}
}

void Papyrus::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	animator.SetTarget(&papyrus);
}

void Papyrus::Release()
{
}

void Papyrus::Reset()
{
	//papyrus.setTexture(TEXTURE_MGR.Get(papyrustexIds));
	animator.SetTarget(&papyrus);
	animator.Play("Animation/papyrusidle.csv");
	SetOrigin(Origins::MC);
}

void Papyrus::Update(float dt)
{
	hitBox.UpdateTransform(papyrus, papyrus.getLocalBounds());
	animator.Update(dt);
}

void Papyrus::Draw(sf::RenderWindow& window)
{
	window.draw(papyrus);
	hitBox.Draw(window);
}

const sf::RectangleShape& Papyrus::GetHitBox() const
{
	return hitBox.rect;
}