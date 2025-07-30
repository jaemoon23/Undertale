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
	if (!move) return;
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Player::SetRotation(float rot)
{
	if (!move) return;
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
	
	SetOrigin(Origins::MC);
}

void Player::Update(float dt)
{
	animator.Update(dt);
	prevPosition = GetPosition();

	//if (sans)
	//{
	//	float distance = Utils::Distance(GetPosition(), sans->GetPosition());
	//	float interactDistance = 35.f;

	//	if (distance <= interactDistance)
	//	{
	//		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
	//		{
	//			SansInteract();
	//			std::cout << "z" << std::endl;
	//		}
	//		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	//		{
	//			dialoguebox->NextLine();
	//		}
	//	}
	//}
	if (InputMgr::GetKeyDown(sf::Keyboard::X))
	{
		dialoguebox->SetActive(false);
		inventoryui->SetActive(false);
		playerInfoUi->SetActive(false);
	}

	if (uichanger && uichanger->GetActive()) return; // UI 변경 중에는 플레이어 이동 불가
	if (dialoguebox && dialoguebox->GetActive()) return; // 대화 중에는 플레이어 이동 불가

	if (move)
	{
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
	

}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Player::SansInteract()
{
	std::vector<std::wstring> testDialogues =
	{ L"* 인간.  ", L"* 새로운 친구와 사귀는 법을 모르는건가?", L"*돌아서서 나와 악수해."};
	dialoguebox->StartDialogue(testDialogues);
}

void Player::SansSecondsInteract()
{
	std::vector<std::wstring> testDialogues =
	{ L"* 난 샌즈야. 뼈다귀 샌즈.",
		L"* 원래 인간들을 감시하는 일을 해야 하는데.",
		L"*내 동생인 파피루스에게 맡겨놨어.",
		L"* 나가고 싶다면 저 밖의 파피루스와\n 싸워서 이겨야 할거야." };
	dialoguebox->StartDialogue(testDialogues);
}


//void Player::Heal(int amount, int maxHp)
//{
//	PlayerInfo::hp == 10;
//	PlayerInfo::Heal(InventoryUi::healItem[0].GetHealAmount());
//	PlayerInfo::hp == 20;
//
//	int newHp = PlayerInfo::hp + amount;
//	if (newHp > maxHp)
//	{
//		newHp = maxHp;
//	}
//	PlayerInfo::hp = newHp; // 실제로 HP를 회복
//}


const sf::RectangleShape& Player::GetHitBox() const
{
	return hitBox.rect;
}

void Player::SetMove(bool a)
{
	move = a;
	if (!a) direction = sf::Vector2f(0.f, 0.f);
}
