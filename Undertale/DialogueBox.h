#pragma once
#include "GameObject.h"
class Player;
class DialogueBox : public GameObject
{
protected:
	//bool isActive = false;

	sf::Sprite dialogueBox;
	std::string dialogueboxtexIds = "Sprites/backgroundui.png";
	sf::RectangleShape line;

	sf::Text dialogueText;
	sf::Font font;
	
	std::vector<std::string> dialogueLines;
	size_t currentLineIndex = 0;

	Player* player; 
public:
	DialogueBox(const std::string& name = "");
	virtual ~DialogueBox() = default;

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

	void StartDialogue(const std::vector<std::string>& lines);
	void NextLine();

	void SetBox(sf::Sprite d, sf::RectangleShape l) { dialogueBox = d, line = l; }
	void SetPlayer(Player* p) { player = p; }
};

