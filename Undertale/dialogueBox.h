#pragma once
#include "GameObject.h"
class dialogueBox : public GameObject
{
protected:
	sf::Sprite sprite;
	sf::Text text;

	sf::Vector2f size = { 640.f,480.f };

public:
	dialogueBox(const std::string& name = "");
	virtual ~dialogueBox() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetString(std::string s) 
	{
		std::wstring ws = utf8_to_wstring(s);
		text.setString(ws);
	}

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

