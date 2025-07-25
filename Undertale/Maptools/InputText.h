#pragma once
#include "Button.h"
class InputText : public GameObject
{
protected:
	sf::RectangleShape box;  
	sf::Text text;			 
	std::string currentInput; 

	bool active = false;

	std::function<void(int)> onSubmit;
	sf::Event event;

public:
	InputText(const std::string name = "");
	~InputText() override = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Activate(std::function<void(int)> callback);
	void Deactivate();
	void SetColor(const sf::Color& color1, const sf::Color& color2);
	void SetSize(const sf::Vector2f& size);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	
};

