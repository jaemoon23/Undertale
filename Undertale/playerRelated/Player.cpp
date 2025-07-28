#include "stdafx.h"
#include "Player.h"
#include "Sans.h"
#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"

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
	animator.SetTarget(&body);
}

void Player::Release()
{
}

void Player::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	body.setTexture(TEXTURE_MGR.Get(texId));
	animator.Play("Animation/idle.csv");
	direction = { 0.f, 0.f };
	/*SetName(L"Frisk");
	SetAtt(20);
	SetDef(20);
	SetHp(10);
	SetLevel(1);
	SetGold(0);*/

	SetOrigin(Origins::MC);

}

void Player::Update(float dt)
{
	animator.Update(dt);
	prevPosition = GetPosition();

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	SetPosition(GetPosition() + direction * speed * dt);
	hitBox.UpdateTransform(body, body.getLocalBounds());

	
	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		animator.Play("Animation/rightwalking.csv");
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		animator.Play("Animation/leftwalking.csv");
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		animator.Play("Animation/upwalking.csv");
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		animator.Play("Animation/downwalking.csv");
	}
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

const sf::RectangleShape& Player::GetHitBox() const
{
	return hitBox.rect;
}
