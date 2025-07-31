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
	
	// ��Ʈ�� �޴�
	sf::RectangleShape Selection_Icon_HitBox;
	sf::RectangleShape sellText_HitBox;
	sf::RectangleShape buyText_HitBox;
	sf::RectangleShape exitText_HitBox;

	// ����â 
	sf::RectangleShape Buy_Selection_Icon_HitBox;
	sf::RectangleShape SnowManText_HitBox;
	sf::RectangleShape CookieText_HitBox;
	sf::RectangleShape IceText_HitBox;

	std::wstring fullText = L"* �ȴ�!\n* �׹� ���� �� ��...\n * ȭ����!!!!";
	std::wstring currentText = L"";
	float textTimer = 0.f;
	float textSpeed = 0.05f; // ���ڴ� �ð� (��)
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

	// ������ ��
	int snowManPrice = 10; // ����� ����
	int cookiePrice = 15; // ��Ű ����
	int icePrice = 20; // ���̽� ����

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

