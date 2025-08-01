#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "InventoryUi.h"
#include "HealItem.h"
#include "HitBox.h"

class TemMieBody;

class TemMieShop : public Scene
{
protected:
	SpriteGo* backGround = nullptr;
	TemMieBody* temMieBody = nullptr;
	SpriteGo* temShopBox = nullptr;
	SpriteGo* temShopTextWindow = nullptr;
	SpriteGo* temShopItemWindow = nullptr;
	SpriteGo* Selection_Icon = nullptr;
	SpriteGo* Buy_Selection_Icon = nullptr;

	TextGo* introText = nullptr;
	TextGo* buyText = nullptr;
	TextGo* sellText = nullptr;
	TextGo* exitText = nullptr;

	TextGo* goldText = nullptr;
	TextGo* slotText = nullptr;

	TextGo* iceText = nullptr;
	TextGo* cookieText = nullptr;
	TextGo* snowManText = nullptr;
	
	// 인트로 메뉴
	sf::RectangleShape Selection_Icon_HitBox;
	sf::RectangleShape sellText_HitBox;
	sf::RectangleShape buyText_HitBox;
	sf::RectangleShape exitText_HitBox;

	// 구매창 
	sf::RectangleShape Buy_Selection_Icon_HitBox;
	sf::RectangleShape SnowManText_HitBox;
	sf::RectangleShape CookieText_HitBox;
	sf::RectangleShape IceText_HitBox;

	std::wstring fullText = L"* 안뇽!\n* 테미 샵에 온 걸...\n * 화녕행!!!!";
	std::wstring currentText = L"";
	float textTimer = 0.f;
	float textSpeed = 0.05f; // 글자당 시간 (초)
	int currentIndex = 0;

	bool isIntro = true;
	bool isIntroText = true;
	bool menu = false;
	bool isMenuSelect = true;
	bool menuExit = false;
	bool isBuy = false;
	bool isSell = false;
	bool selectItem = false;
	bool sellItem = false;

	int textCount = 0;
	float textPos = 0.f;

	int buyTextCount = 0;
	float buyTextPos = 0.f;

	// 아이템 샵
	int snowManPrice = 10; // 눈사람 가격
	int cookiePrice = 15; // 쿠키 가격
	int icePrice = 20; // 아이스 가격

	std::wstring itemName = L"";
	
public:
    TemMieShop();
    ~TemMieShop() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void IntroText(float dt);
};

