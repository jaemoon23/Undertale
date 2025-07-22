#include "stdafx.h"
#include "Player.h"
#include "Sans.h"

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

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "!!" << std::endl;
		}
	);

	animator.AddEvent("Idle", 0,
		[]()
		{
			std::cout << "??" << std::endl;
		}
	);
}

void Player::Release()
{
}

void Player::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;

	animator.Play("Animation/idle.csv");

	direction = { 0.f, 0.f };
	
	//look = { 1.f, 0.f };
	SetOrigin(Origins::MC);

}

void Player::Update(float dt)
{
	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	direction.y = InputMgr::GetAxis(Axis::Vertical);
	Utils::Normalize(direction);
	SetPosition(GetPosition() + direction * speed * dt);

	hitBox.UpdateTransform(body, body.getLocalBounds());
	

	if (sans)
	{
		if (Utils::CheckCollision(hitBox.rect, sans->GetHitBox()))
		{
			std::cout << "Ãæµ¹" << std::endl;
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		animator.Play("Animation/rightwalking.csv");
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Right))
	{
		animator.Play("Animation/idle.csv");
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		animator.Play("Animation/leftwalking.csv");
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Left))
	{
		animator.Play("Animation/idle.csv");
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		animator.Play("Animation/downwalking.csv");
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Down))
	{
		animator.Play("Animation/idle.csv");
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		animator.Play("Animation/upwalking.csv");
	}
	if (InputMgr::GetKeyUp(sf::Keyboard::Up))
	{
		animator.Play("Animation/idle.csv");
	}


	animator.Update(dt);
	SetPosition(position);
}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}