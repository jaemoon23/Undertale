#include "stdafx.h"
#include "UiChanger.h"
#include "Player.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "DialogueBox.h"

UiChanger::UiChanger(const std::string& name)
	: GameObject(name)
{
}

void UiChanger::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	uiChanger.setPosition(pos);
}

void UiChanger::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	uiChanger.setRotation(rot);
}

void UiChanger::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	uiChanger.setScale(s);
}

void UiChanger::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	uiChanger.setOrigin(o);
}

void UiChanger::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(uiChanger, preset);
	}
}

void UiChanger::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;
	SetActive(false);
	SOUNDBUFFER_MGR.Load("sounds/snd_select.wav");

}

void UiChanger::Release()
{
}

void UiChanger::Reset()
{
	//font.loadFromFile(fonttexIds);

	uiChanger.setTexture(TEXTURE_MGR.Get(uiChangertexIds));
	uiChanger.setPosition(50.f, 170.f);
	uiChanger.setScale(0.3f, 0.3f);

	sf::FloatRect uiChangerBounds = uiChanger.getGlobalBounds();

	line.setSize({190.f, 143.f});
	line.setFillColor(sf::Color::Transparent);
	line.setOutlineColor(sf::Color::White);
	line.setPosition(50.f, 170.f);
	line.setOutlineThickness(5.f);

	invenText.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	invenText.setString("Inventory");
	invenText.setCharacterSize(20);
	invenText.setFillColor(sf::Color(130, 130, 130));
	invenText.setPosition(95.f, 200.f);

	statText.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	statText.setString("Stat");
	statText.setCharacterSize(20);
	statText.setFillColor(sf::Color(130, 130, 130));
	statText.setPosition(122.f, 250.f);

	SetActive(false);
}

void UiChanger::Update(float dt)
{
	if (!GetActive()) return;

	// 하위 UI가 켜져 있으면 UiChanger 입력 무시
	if ((inventoryui && inventoryui->GetActive()) || 
		(playerinfoui && playerinfoui->GetActive()) ||
		(dialogueBox && dialogueBox -> GetActive()))
	{
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		selectIndex = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		selectIndex = 0;
	}

	if (selectIndex == 0)
	{
		invenText.setFillColor(sf::Color::White);
		statText.setFillColor(sf::Color(130, 130, 130));
	}
	else
	{
		invenText.setFillColor(sf::Color(130, 130, 130));
		statText.setFillColor(sf::Color::White);
	}


	if (GetActive() && InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		if (selectIndex == 0 && inventoryui)
		{
			inventoryui->SetActive(true);
		}
		if (selectIndex == 1 && playerinfoui)
		{
			playerinfoui->SetActive(true);
		}
		SOUND_MGR.PlaySfx("sounds/snd_select.wav");
	}
}

void UiChanger::Draw(sf::RenderWindow& window)
{
	window.draw(uiChanger);
	window.draw(line);
	window.draw(invenText);
	window.draw(statText);
}

