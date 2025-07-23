#include "stdafx.h"
#include "NameUi.h"

NameUi::NameUi(const std::string& fontIds, const std::string& name)
	:TextGo("fonts/DungGeunMo.ttf", name)
{
}
void NameUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}
void NameUi::Reset()
{
	SetOrigin(Origins::MC);
	SetCharacterSize(25);
	SetFillColor(sf::Color::White);
	SetPosition({ 310.f, 60.f });

	TextGo::Reset();
}
void NameUi::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::P))
	{
		isActive = !isActive;
	}
}
void NameUi::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		TextGo::Draw(window);
	}
		
}

void NameUi::SetName(std::string name)
{
	this->name = name;
	SetString(std::string("\"") + this->name + "\"");
}

