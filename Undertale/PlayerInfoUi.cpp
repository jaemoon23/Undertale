#include "stdafx.h"
#include "PlayerInfoUi.h"


PlayerInfoUi::PlayerInfoUi(const std::string& name)
	: GameObject(name)
{
}

void PlayerInfoUi::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	background.setPosition(pos);
}

void PlayerInfoUi::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	background.setRotation(rot);
}

void PlayerInfoUi::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	background.setScale(s);
}

void PlayerInfoUi::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	background.setOrigin(o);
}

void PlayerInfoUi::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(background, preset);
	}
}

void PlayerInfoUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
}

void PlayerInfoUi::Release()
{
}

void PlayerInfoUi::Reset()
{
	font.loadFromFile(fonttexIds);

	SetOrigin(Origins::MC);
	background.setTexture(TEXTURE_MGR.Get(playerInfotexIds));
	background.setPosition(350.f, 100.f);
	background.setScale(0.4f, 0.6f);

	line.setSize({ 251.f, 285.f });
	line.setPosition(350.f, 103.f);
	line.setFillColor(sf::Color::Transparent);
	line.setOutlineColor(sf::Color::White);
	line.setOutlineThickness(5.f);
}

void PlayerInfoUi::Update(float dt)
{
}

void PlayerInfoUi::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(line);
	window.draw(name);
}