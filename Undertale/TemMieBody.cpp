#include "stdafx.h"
#include "TemMieBody.h"


TemMieBody::TemMieBody(const std::string& name) : GameObject(name)
{
}
void TemMieBody::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	temMieBody.setPosition(pos);
}

void TemMieBody::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	temMieBody.setRotation(rot);
}

void TemMieBody::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	temMieBody.setScale(s);
}

void TemMieBody::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	temMieBody.setOrigin(o);
}

void TemMieBody::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(temMieBody, preset);
	}
}
void TemMieBody::Init()
{
	animator.SetTarget(&temMieBody);
}

void TemMieBody::Release()
{
}

void TemMieBody::Reset()
{
	temMieBody.setTexture(TEXTURE_MGR.Get(texId));
	animator.Play("Animation/temmie/Temmie_shop_Idle.csv");
	timer = 0.f;
	
	SetPosition({ 524.f, 240.f });
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
}

void TemMieBody::Update(float dt)
{
	animator.Update(dt);
	if (isSmiling)
	{
		animator.Play("Animation/temmie/Temmie_smiling.csv");

		
		isIdle = true;
		isSmiling = false;
		
	}
	if (isIdle)
	{
		timer += dt;
	}
	std::cout << timer << std::endl;
	if (isIdle && timer >= 3.f)
	{
		animator.Play("Animation/temmie/Temmie_shop_Idle.csv");
		isIdle = false;
		timer = 0;
	}

}

void TemMieBody::Draw(sf::RenderWindow& window)
{
	window.draw(temMieBody);
}
