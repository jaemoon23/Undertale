#include "stdafx.h"
#include "InventoryUi.h"
#include "Player.h"
#include "HealItem.h"

HealItem InventoryUi::healItem1;
HealItem InventoryUi::healItem2;
HealItem InventoryUi::healItem3;
HealItem InventoryUi::healItem4;


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
	sortingLayer = SortingLayers::UI;
	sortingOrder = 1;
	SetActive(false);
	inventory.setPosition(320.f, 230.f);
	inventory.setScale(0.8f, 0.8f);
	SetOrigin(Origins::MC);

	square.setSize({ 502.f, 374.f });
	square.setFillColor(sf::Color::Transparent);
	square.setPosition({ inventory.getPosition().x - 251.f ,inventory.getPosition().y - 187.f });
	square.setOutlineColor(sf::Color::White);
	square.setOutlineThickness(5.f);

	sf::FloatRect invBounds = inventory.getGlobalBounds();

	//line.setSize({ 1.f, invBounds.height * 0.7f });
	//line.setFillColor(sf::Color(130, 130, 130));
	//line.setOutlineColor(sf::Color(130, 130, 130));
	//line.setPosition({ invBounds.left + invBounds.width * 0.5f, invBounds.top + 60.f});
	//line.setOutlineThickness(2.5f);
	
	fonts.loadFromFile(fonttexIds);

	inventext.setFont(fonts);
	inventext.setFillColor(sf::Color::White);
	inventext.setString("Inventory");
	inventext.setCharacterSize(25.f);
	inventext.setPosition({invBounds.getPosition().x + 200.f ,invBounds.getPosition().y + 20.f});

	/*boxtext.setFont(fonts);
	boxtext.setFillColor(sf::Color::White);
	boxtext.setString("Box");
	boxtext.setCharacterSize(25.f);
	boxtext.setPosition({ invBounds.left + invBounds.width - 145.f ,invBounds.getPosition().y + 20.f });*/
	
	text.setFont(fonts);
	text.setFillColor(sf::Color::White);
	text.setString("Press [X] to Finish ");
	text.setCharacterSize(20.f);
	text.setPosition({ (invBounds.left + invBounds.width) *0.5f - 64.f ,invBounds.top + invBounds.height - 50.f});

	//healItem = nullptr;
	itemText1.setFont(fonts);
	itemText1.setFillColor(sf::Color::White);
	itemText1.setCharacterSize(22.f);
	itemText1.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y - 95.f });

	itemText2.setFont(fonts);
	itemText2.setFillColor(sf::Color::White);
	itemText2.setCharacterSize(22.f);
	itemText2.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y  -40.f});

	itemText3.setFont(fonts);
	itemText3.setFillColor(sf::Color::White);
	itemText3.setCharacterSize(22.f);
	itemText3.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y + 15.f });

	itemText4.setFont(fonts);
	itemText4.setFillColor(sf::Color::White);
	itemText4.setCharacterSize(22.f);
	itemText4.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y + 70.f });

	selectSprite.setTexture(TEXTURE_MGR.Get(selecttexIds));
	selectSprite.setPosition({ inventory.getPosition().x - 80.f, inventory.getPosition().y - 87.f });
}

void InventoryUi::Update(float dt)
{

	static bool prevDown = false;
	static bool prevUp = false;

	bool currDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	if (currDown && !prevDown)
	{
		selectIndex = (selectIndex + 1) % 4;
	}
	else if (currUp && !prevUp)
	{
		selectIndex = (selectIndex + 3) % 4;
	}
	prevDown = currDown;
	prevUp = currUp;


	if (selectIndex == 0)
	{
		itemText1.setFillColor(sf::Color::White);
		itemText2.setFillColor(sf::Color(130, 130, 130));
		itemText3.setFillColor(sf::Color(130, 130, 130));
		itemText4.setFillColor(sf::Color(130, 130, 130));
	}
	else if (selectIndex == 1)
	{
		itemText1.setFillColor(sf::Color(130, 130, 130));
		itemText2.setFillColor(sf::Color::White);
		itemText3.setFillColor(sf::Color(130, 130, 130));
		itemText4.setFillColor(sf::Color(130, 130, 130));
	}
	else if (selectIndex == 2)
	{
		itemText1.setFillColor(sf::Color(130, 130, 130));
		itemText2.setFillColor(sf::Color(130, 130, 130));
		itemText3.setFillColor(sf::Color::White);
		itemText4.setFillColor(sf::Color(130, 130, 130));
	}
	else if (selectIndex == 3)
	{
		itemText1.setFillColor(sf::Color(130, 130, 130));
		itemText2.setFillColor(sf::Color(130, 130, 130));
		itemText3.setFillColor(sf::Color(130, 130, 130));
		itemText4.setFillColor(sf::Color::White);
	}

	float selectY = inventory.getPosition().y - 87.f + selectIndex * 54.f; // sprite 위치 인덱스 따라 조정
	selectSprite.setPosition({ inventory.getPosition().x - 80.f, selectY });
	
	if (isActive && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		if (selectIndex == 0)
		{

		}
		if (selectIndex == 1)
		{
		}
	}
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
		window.draw(selectSprite);

		 //힐 아이템 이름 표시
		itemText1.setString(healItem1.GetName());
		itemText2.setString(healItem2.GetName());
		itemText3.setString(healItem3.GetName());
		itemText4.setString(healItem4.GetName());

		window.draw(itemText1);
		window.draw(itemText2);
		window.draw(itemText3);
		window.draw(itemText4);
	}
}
