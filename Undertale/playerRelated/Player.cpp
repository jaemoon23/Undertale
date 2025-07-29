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
	maxHp = 30;
	SetName(L"Frisk");
	SetAtt(20);
	SetDef(20);
	SetHp(5);
	SetLevel(1);
	SetGold(0);

	SetOrigin(Origins::MC);

}

void Player::Update(float dt)
{
	animator.Update(dt);
	prevPosition = GetPosition();


	if (sans)
	{
		float distance = Utils::Distance(GetPosition(), sans->GetPosition());
		float interactDistance = 35.f;

		if (distance <= interactDistance)
		{
			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				SansInteract();
				std::cout << "z" << std::endl;
			}
			if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
			{
				dialoguebox->NextLine();
			}
		}
		if (InputMgr::GetKeyDown(sf::Keyboard::X))
		{
			dialoguebox->SetActive(false);
			inventoryui->SetActive(false);
			playerInfoUi->SetActive(false);
		}
	}


	if (uichanger && uichanger->GetActive()) return; // UI 변경 중에는 플레이어 이동 불가
	if (dialoguebox && dialoguebox->GetActive()) return; // 대화 중에는 플레이어 이동 불가

	if (move)
	{
		direction.x = InputMgr::GetAxis(Axis::Horizontal);
		direction.y = InputMgr::GetAxis(Axis::Vertical);
		SetPosition(GetPosition() + direction * speed * dt);
		hitBox.UpdateTransform(body, body.getLocalBounds());
	}
	


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

void Player::SetHp(int h)
{
	hp = h;
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerHp(std::to_wstring(hp));
	}
}

void Player::SetAtt(int a)
{
	att = a;
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerAttack(std::to_wstring(att));
	}
}

void Player::SetDef(int d)
{
	def = d;
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerDefence(std::to_wstring(def));
	}
}

void Player::SetGold(int g)
{
	gold = g;
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerGold(std::to_wstring(gold));
	}
}

void Player::SetLevel(int l)
{
	level = l;
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerLevel(std::to_wstring(level));
	}
}

void Player::SetName(const std::wstring& n)
{
	name = n;
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerName(n);
	}
}

void Player::SansInteract()
{
	std::vector<std::wstring> testDialogues =
	{ L"* hi", L"* potion" };
	dialoguebox->StartDialogue(testDialogues);
}

void Player::Heal(int amount, int maxHp)
{
	int newHp = hp + amount;
	if (newHp > maxHp)
	{
		newHp = maxHp;
	}
	hp = newHp; // 실제로 HP를 회복
	if (playerInfoUi)
	{
		playerInfoUi->SetPlayerHp(std::to_wstring(hp));
	}
}

void Player::UseHealItem(HealItem* item)
{
	Heal(item->GetHealAmount(), maxHp);
}

const sf::RectangleShape& Player::GetHitBox() const
{
	return hitBox.rect;
}
