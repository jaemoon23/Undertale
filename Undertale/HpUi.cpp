#include "stdafx.h"
#include "HpUi.h"

HpUi::HpUi(const std::string& fontIds, const std::string& name)
	:TextGo("fonts/DungGeunMo.ttf", name)
{
}
void HpUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;

	TextGo::Init();
}
void HpUi::Reset()
{
	SetHp(20, 20);
	SetOrigin(Origins::MC);
	SetCharacterSize(25);
	SetFillColor(sf::Color::White);
	SetPosition({ 490.f, 50.f });

	TextGo::Reset();
}

void HpUi::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::P))
	{
		isActive = !isActive;
	}

	TextGo::Update(dt);
}
void HpUi::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		TextGo::Draw(window);
	}
}

void HpUi::SetHp(int maxHp, int hp)
{
	this->hp = hp;
	this->maxHp = maxHp;
	SetString("HP: " + std::to_string(this->hp) + " / " + std::to_string(this->maxHp));
}