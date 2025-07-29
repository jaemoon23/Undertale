#include "stdafx.h"
#include "InventoryUi.h"
#include "Player.h"
#include "HealItem.h"
#include "DialogueBox.h"

HealItem InventoryUi::healItem[4];

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
	inventory.setPosition(420.f, 230.f);
	inventory.setScale(0.45f, 0.6f);
	SetOrigin(Origins::MC);

	square.setSize({ 282.f, 278.f });
	square.setFillColor(sf::Color::Transparent);
	square.setPosition({ inventory.getPosition().x - 139.f ,inventory.getPosition().y - 139.f });
	square.setOutlineColor(sf::Color::White);
	square.setOutlineThickness(5.f);

	sf::FloatRect invBounds = inventory.getGlobalBounds();

	fonts.loadFromFile(fonttexIds);

	inventext.setFont(fonts);
	inventext.setFillColor(sf::Color::White);
	inventext.setString("Inventory");
	inventext.setCharacterSize(22.f);
	inventext.setPosition({invBounds.getPosition().x + 95.f ,invBounds.getPosition().y + 14.f});
	
	text.setFont(fonts);
	text.setFillColor(sf::Color::White);
	text.setString("Press [X] to Finish ");
	text.setCharacterSize(18.f);
	text.setPosition({ (invBounds.left + invBounds.width) *0.5f + 56.f ,invBounds.top + invBounds.height - 35.f});

	//healItem = nullptr;
	itemText1.setFont(fonts);
	itemText1.setFillColor(sf::Color::White);
	itemText1.setCharacterSize(20.f);
	itemText1.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y - 85.f });

	itemText2.setFont(fonts);
	itemText2.setFillColor(sf::Color::White);
	itemText2.setCharacterSize(20.f);
	itemText2.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y  -30.f});

	itemText3.setFont(fonts);
	itemText3.setFillColor(sf::Color::White);
	itemText3.setCharacterSize(20.f);
	itemText3.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y + 25.f });

	itemText4.setFont(fonts);
	itemText4.setFillColor(sf::Color::White);
	itemText4.setCharacterSize(20.f);
	itemText4.setPosition({ inventory.getPosition().x - 45.f, inventory.getPosition().y + 80.f });

	selectSprite.setTexture(TEXTURE_MGR.Get(selecttexIds));
	//selectSprite.setPosition({ inventory.getPosition().x - 80.f, inventory.getPosition().y - 47.f });
}

void InventoryUi::Update(float dt)
{
	if (!GetActive()) return; // 인벤토리가 활성화되지 않은 경우 업데이트 중지

	static bool prevDown = false; // 이전 프레임에서 Up,Down 키가 눌렸는지 여부
	static bool prevUp = false;

	bool currDown = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
	bool currUp = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	if (currDown && !prevDown) // 현재 프레임에서 Down 키가 눌렸고, 이전 프레임에서는 눌리지 않았을 때
	{
		selectIndex = (selectIndex + 1) % 4;
	}
	else if (currUp && !prevUp)
	{
		selectIndex = (selectIndex + 3) % 4;  // selectIndex를 3으로 나눈 나머지로 설정하여 인덱스를 감소시킴
	}
	prevDown = currDown; // 현재 프레임에서 Down 키가 눌렸는지 여부를 저장
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
	selectSprite.setPosition({ inventory.getPosition().x - 80.f, selectY + 10.f });

	// 2. 이제부터만 엔터 입력 처리
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		HealItem* selectedItem = nullptr;
		switch (selectIndex)
		{
		case 0: selectedItem = &healItem[0]; break;
		case 1: selectedItem = &healItem[1]; break;
		case 2: selectedItem = &healItem[2]; break;
		case 3: selectedItem = &healItem[3]; break;
		}
		if (selectedItem && selectedItem->GetHealAmount() > 0)
		{
			if (player)
			{
				for (int i = 0; i<4; ++i)
				{
					PlayerInfo::Heal(InventoryUi::healItem[i].GetHealAmount());
				}

				std::cout << "Player HP: " << player->GetHp() << " / " << player->GetMaxHp()<< std::endl;
			}
			selectedItem->SetInfo(L"", 0);			
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
		itemText1.setString(healItem[0].GetName());
		itemText2.setString(healItem[1].GetName());
		itemText3.setString(healItem[2].GetName());
		itemText4.setString(healItem[3].GetName());

		window.draw(itemText1);
		window.draw(itemText2);
		window.draw(itemText3);
		window.draw(itemText4);
	}
}



