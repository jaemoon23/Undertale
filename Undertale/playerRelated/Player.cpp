#include "stdafx.h"
#include "Player.h"
#include "Sans.h"
#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"

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
	maxHp = 10;
	hp = 10;
	SetAtt(20);

	//if (hpui)
	//{
	//	hpui->SetHp(hp, maxHp);
	//}

	//look = { 1.f, 0.f };
	SetOrigin(Origins::MC);

}

void Player::Update(float dt)
{
	if (!dialoguebox->GetActive() && !uichanger->GetActive())
	{
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
		direction.y = InputMgr::GetAxis(Axis::Vertical);
		Utils::Normalize(direction);
		SetPosition(GetPosition() + direction * speed * dt);
	}
	else
	{
		animator.Stop();
	}

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
					dialoguebox->NextLine();
				}
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::C))
		{
			dialoguebox->SetActive(false);
			inventoryui->SetActive(false);
			playerInfoUi->SetActive(false);
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Right))
	{
		animator.Play("Animation/rightwalking.csv");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Left))
	{
		animator.Play("Animation/leftwalking.csv");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Up))
	{
		animator.Play("Animation/upwalking.csv");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Down))
	{
		animator.Play("Animation/downwalking.csv");
	}

	//if (InputMgr::GetKey(sf::Keyboard::Up) == 0 &&
	//	InputMgr::GetKey(sf::Keyboard::Down) == 0 &&
	//	InputMgr::GetKey(sf::Keyboard::Left) == 0 &&
	//	InputMgr::GetKey(sf::Keyboard::Right) == 0)
	//{
	//	animator.Stop();
	//}

	animator.Update(dt);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::SetAtt(int a)
{
	att = a;
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerAttack(std::to_wstring(att));
	}
}

void Player::SansInteract()
{
	std::vector<std::wstring> testDialogues =
	{ L"¾È³ç", L"Å×½ºÆ®" };
	dialoguebox->StartDialogue(testDialogues);
}
