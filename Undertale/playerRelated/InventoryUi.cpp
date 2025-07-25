#include "stdafx.h"
#include "InventoryUi.h"
#include "Player.h"


InventoryUi::InventoryUi(const std::string& name)
	: GameObject(name)
{
}

void InventoryUi::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	inventory.setPosition(pos);
}

void InventoryUi::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	inventory.setRotation(rot);
}

void InventoryUi::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	inventory.setScale(s);
}

void InventoryUi::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	inventory.setOrigin(o);
}

void InventoryUi::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(inventory, preset);
	}
}

void InventoryUi::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
	SetActive(false);
}

void InventoryUi::Release()
{
}

void InventoryUi::Reset()
{
	inventory.setTexture(TEXTURE_MGR.Get(inventorytexIds));
	inventory.setPosition(320.f, 230.f);
	inventory.setScale(0.8f, 0.8f);
	SetOrigin(Origins::MC);

	square.setSize({ 502.f, 374.f });
	square.setFillColor(sf::Color::Transparent);
	square.setPosition({ inventory.getPosition().x - 251.f ,inventory.getPosition().y - 187.f });
	square.setOutlineColor(sf::Color::White);
	square.setOutlineThickness(5.f);

	sf::FloatRect invBounds = inventory.getGlobalBounds();

	line.setSize({ 1.f, invBounds.height * 0.7f });
	line.setFillColor(sf::Color(130, 130, 130));
	line.setOutlineColor(sf::Color(130, 130, 130));
	line.setPosition({ invBounds.left + invBounds.width * 0.5f, invBounds.top + 60.f});
	line.setOutlineThickness(2.5f);
	
	fonts.loadFromFile(fonttexIds);

	inventext.setFont(fonts);
	inventext.setFillColor(sf::Color::White);
	inventext.setString("Inventory");
	inventext.setCharacterSize(25.f);
	inventext.setPosition({invBounds.getPosition().x + 70.f ,invBounds.getPosition().y + 20.f});

	boxtext.setFont(fonts);
	boxtext.setFillColor(sf::Color::White);
	boxtext.setString("Box");
	boxtext.setCharacterSize(25.f);
	boxtext.setPosition({ invBounds.left + invBounds.width - 145.f ,invBounds.getPosition().y + 20.f });
	
	text.setFont(fonts);
	text.setFillColor(sf::Color::White);
	text.setString("Press [X] to Finish ");
	text.setCharacterSize(20.f);
	text.setPosition({ (invBounds.left + invBounds.width) *0.5f - 64.f ,invBounds.top + invBounds.height - 50.f});
}

void InventoryUi::Update(float dt)
{
	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();
}

void InventoryUi::Draw(sf::RenderWindow& window)
{
	if (isActive)
	{
		window.draw(inventory);
		window.draw(square);
		window.draw(line);
		window.draw(inventext);
		window.draw(boxtext);
		window.draw(text);
	}
}