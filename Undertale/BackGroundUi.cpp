#include "stdafx.h"
#include "BackGroundUi.h"

BackGroundUi::BackGroundUi(const std::string& name)
	: GameObject(name)
{
}

void BackGroundUi::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	backgroundUi.setPosition(pos);
}

void BackGroundUi::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	backgroundUi.setRotation(rot);
}

void BackGroundUi::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	backgroundUi.setScale(s);
}

void BackGroundUi::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	backgroundUi.setOrigin(o);
}

void BackGroundUi::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(backgroundUi, preset);
	}
}

void BackGroundUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
}

void BackGroundUi::Release()
{
}

void BackGroundUi::Reset()
{
	backgroundUi.setTexture(TEXTURE_MGR.Get(bguitexIds));
	backgroundUi.setPosition(420.f, 230.f);
	backgroundUi.setScale(0.6f, 0.8f);
	SetOrigin(Origins::MC);

	Square.setSize({ 374.f, 374.f });
	Square.setFillColor(sf::Color::Transparent);
	Square.setPosition({ backgroundUi.getPosition().x - 187.f ,backgroundUi.getPosition().y - 187.f });
	Square.setOutlineColor(sf::Color::White);
	Square.setOutlineThickness(5.f);
}

void BackGroundUi::Update(float dt)
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
	if (InputMgr::GetKeyDown(sf::Keyboard::W))
	{
		isActive = !isActive;
	}
}

void BackGroundUi::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(backgroundUi);
		window.draw(Square);
	}
}

void BackGroundUi::SetRect()
{
	isActive = false;
	this->Square = Square;
}
