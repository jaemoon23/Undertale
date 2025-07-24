#include "stdafx.h"
#include "Player.h"
#include "Sans.h"
#include "HpUi.h"
#include "DialogueBox.h"

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

	animator.Play("Animation/idle.csv");

	direction = { 0.f, 0.f };
	maxHp = 20;
	hp = 20;
	if (hpui)
	{
		hpui->SetHp(hp, maxHp);
	}

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
		float distance = Utils::Distance(GetPosition(), sans->GetPosition());
		float interactDistance = 35.f;

		if (distance <= interactDistance)
		{
			if (!dialoguebox->GetActive())
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					SansInteract();
				}
			}
			else
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					std::cout << "Z" << std::endl;
					dialoguebox->NextLine();
				}
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::C))
		{
			dialoguebox->SetActive(false);
			std::cout << "대화나가기" << std::endl;
		}
	}


	if (InputMgr::GetKeyDown(sf::Keyboard::Right)&& !dialoguebox->GetActive())
	{
		animator.Play("Animation/rightwalking.csv");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left) && !dialoguebox->GetActive())
	{
		animator.Play("Animation/leftwalking.csv");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Up) && !dialoguebox->GetActive())
	{
		animator.Play("Animation/upwalking.csv");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down) && !dialoguebox->GetActive())
	{
		animator.Play("Animation/downwalking.csv");
	}

	//if (InputMgr::GetKey(sf::Keyboard::Up) == 0 &&
	//	InputMgr::GetKey(sf::Keyboard::Down) == 0 &&
	//	InputMgr::GetKey(sf::Keyboard::Left) == 0 &&
	//	InputMgr::GetKey(sf::Keyboard::Right) == 0)
	//{
	//	animator.Play("Animation/idle.csv");
	//}

	animator.Update(dt);
}


void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::SansInteract()
{
	std::vector<std::string> testDialogues =
	{ "Hidflaskdjflaksdjlfakjsld","Nextalsdkfjalskdfjalsdkfj","uihyun","junmo" };
	dialoguebox->StartDialogue(testDialogues);
}

void Player::SetHpUi(HpUi* hpui)
{
	this->hpui = hpui;
}

void Player::SetHp(int h, int maxh)
{
	hp = h;
	maxHp = maxh;
	if (hpui)
	{
		hpui->SetHp(hp, maxHp); // 동기화 
	}
}