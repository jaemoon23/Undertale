#pragma once
#include "Scene.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "InventoryUi.h"
#include "HealItem.h"
#include "HitBox.h"

class TemMieShop : public Scene
{
protected:
	SpriteGo* backGround = nullptr;
	SpriteGo* temMieBody = nullptr;
	SpriteGo* temShopBox = nullptr;
	SpriteGo* temShopTextWindow = nullptr;
	SpriteGo* temShopItemWindow = nullptr;
	SpriteGo* Selection_Icon = nullptr;

	TextGo* introText = nullptr;
	TextGo* buyText = nullptr;
	TextGo* sellText = nullptr;
	TextGo* exitText = nullptr;

	TextGo* goldText = nullptr;
	TextGo* slotText = nullptr;
	
	sf::RectangleShape Selection_Icon_HitBox;
	sf::RectangleShape sellText_HitBox;
	sf::RectangleShape buyText_HitBox;
	sf::RectangleShape exitText_HitBox;

	int slot;
	int gold;
	std::wstring fullText = L"* 안뇽!\n* 테미 샵에 온 걸...\n * 화녕행!!!!";
	std::wstring currentText = L"";
	float textTimer = 0.f;
	float textSpeed = 0.05f; // 글자당 시간 (초)
	int currentIndex = 0;

	bool isIntroText = true;

	int textCount = 0;
	float textPos = 0.f;
	
public:
    TemMieShop();
    ~TemMieShop() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

