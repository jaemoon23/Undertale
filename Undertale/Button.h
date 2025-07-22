#pragma once
enum class ButtonState { Normal, Hovered, Pressed };
class Button : public GameObject
{
protected:
	sf::RectangleShape body;
	sf::Text text;
	sf::FloatRect bounds;

	

	ButtonState state = ButtonState::Normal;
	std::function<void()> onClick;

	bool enabled = true;
public:
	Button(const std::string& name = "");
	~Button() override = default;

	void setText(const std::string& text);
	

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void SetColor(const sf::Color& color1, const sf::Color& color2);
	void SetSize(const sf::Vector2f& size);

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

