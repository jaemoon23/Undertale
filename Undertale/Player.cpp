#include "stdafx.h"
#include "Player.h"
Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Player::Release()
{
}

void Player::Reset()
{
	body.setTexture(TEXTURE_MGR.Get(texIds), true);
	body.setPosition(0.f, 0.f);
	body.setScale(2.f, 2.f);
	SetOrigin(Origins::MC);
	
}

void Player::Update(float dt)
{

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}