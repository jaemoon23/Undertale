#include "stdafx.h"
#include "BattleBox.h"

BattleBox::BattleBox(const std::string& name)
	: GameObject(name)
{
}

void BattleBox::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	box.setPosition(pos);
	startDescribe.setPosition(pos + sf::Vector2f({ -size.x * 0.51f + 35.f,-60.f }));
}

void BattleBox::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	box.setRotation(rot);
}

void BattleBox::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	box.setScale(s);
}

void BattleBox::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	box.setOrigin(o);
}

void BattleBox::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(box, preset);
	}
}

void BattleBox::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;
	box.setFillColor(sf::Color::Black);
	box.setOutlineColor(sf::Color::White);
	box.setOutlineThickness(5.f);

	startDescribe.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	startDescribe.setCharacterSize(30.f);
}

void BattleBox::Release()
{
}

void BattleBox::Reset()
{
	box.setSize({ size.x * 0.95f, size.y * 0.25f });
	SetOrigin(Origins::MC);
	SetPosition({ size.x * 0.51f, size.y * 0.67f });

	std::wstring ws = utf8_to_wstring(startStr);
	startDescribe.setString(ws);
}

void BattleBox::Update(float dt)
{
}

void BattleBox::Draw(sf::RenderWindow& window)
{
	window.draw(box);
	window.draw(startDescribe);
}