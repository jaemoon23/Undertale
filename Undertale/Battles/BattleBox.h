#pragma once
#include "GameObject.h"
#include "Animator.h"

class SceneBattle;

class BattleBox : public GameObject
{
protected:
	sf::RectangleShape box;
	sf::RectangleShape maxHpBar;
	sf::RectangleShape hpBar;

	sf::Sprite fightSprite;
	sf::RectangleShape fightLine;

	sf::Text startDescribe;

	sf::Text describe1;
	sf::Text describe2;
	sf::Text describe3;
	sf::Text describe4;

	sf::Vector2f size = { 640.f,480.f };

	SceneBattle* scene;
	int* monsterHp;
	int* monsterMaxHp;

	const float fightLineSpeed = 320.f;

	sf::Sprite fightAniSprite;
	Animator animator;

	float timer = 0.f;
	const float fightAniTime = 0.6f;
	const float hpAniTime = 0.6f;

	bool isAttacking = false;
	bool playerCheck = false;
	bool isHpAni = false;

	float minusHpbarSize;

public:
	std::wstring startStr;
	std::wstring describeStr[4];
	bool fightBtPress = false;
	bool isDrawHpBar = false;

	BattleBox(const std::string& name = "");
	virtual ~BattleBox() = default;

	void SetStartDescribe() { startDescribe.setString(startStr); }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetBtBoxSize(sf::Vector2f size)
	{ 
		box.setSize(size);
		Utils::SetOrigin(box, Origins::MC);
	}

	sf::FloatRect GetBoxGlobalBounds() { return box.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;

	void UpdateBox();

	void Draw(sf::RenderWindow& window) override;

	void ResetBox()
	{
		box.setSize({ size.x * 0.95f, size.y * 0.25f }); 
		SetOrigin(Origins::MC);
		SetPosition({ size.x * 0.51f, size.y * 0.67f });
	}
};

