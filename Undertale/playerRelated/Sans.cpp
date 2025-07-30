#include "stdafx.h"
#include "Sans.h"


Sans::Sans(const std::string& name)
	: GameObject(name)
{
}

void Sans::SetPosition(const sf::Vector2f& pos)
{
	if (!move) return;
	GameObject::SetPosition(pos);
	sans.setPosition(pos);
}

void Sans::SetRotation(float rot)
{
	if (!move) return;
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
	sortingOrder = 0;
}

void Sans::Release()
{
}

void Sans::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	sans.setTexture(TEXTURE_MGR.Get(sanstexIds));
	sans.setPosition(250.f,625.f);
	SetOrigin(Origins::MC);
	SetActive(false);

	//animator.Play("Animation/idle.csv");
	animator.SetTarget(&sans); // 애니메이션 플레이 하려면 해줘야함
}

void Sans::Update(float dt)
{
	animator.Update(dt);
	hitBox.UpdateTransform(sans, sans.getLocalBounds());

}

void Sans::Draw(sf::RenderWindow& window)
{
	if (GetActive())
	{
		hitBox.Draw(window);
		window.draw(sans);
	}
}

const sf::RectangleShape& Sans::GetHitBox() const
{
	return hitBox.rect;
}

sf::Vector2f Sans::GetPosition() const
{
	return sans.getPosition();
}
void Sans::SetActive(bool active)
{
	GameObject::SetActive(active);
}

void Sans::SetMove(bool a)
{
	move = a;
	if (!a) direction = sf::Vector2f(0.f, 0.f);
}