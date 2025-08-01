#pragma once
#include "GameObject.h"
#include "Player.h"
#include "TextWindow.h"

class TalkObject : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string texId;

	Player* player;
	TextWindow* textWindow;

	int lineIndex = 0;
	int lineCount;
	int charIndex = 0;
	float typeTimer = 0.f;
	float typeTime = 0.07f;
	bool isDrawingText = false;

	std::wstring tempLine;
	std::wstring currentLine;

public:
	std::vector<std::wstring> lines;

	TalkObject(const std::string& name = "");
	virtual ~TalkObject() = default;

	void SetTexId(std::string Id) { texId = Id; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

