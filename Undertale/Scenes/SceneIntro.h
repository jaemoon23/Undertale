#pragma once
#include "Scene.h"
class SceneIntro : public Scene
{
protected:
	sf::RectangleShape black;
	sf::RectangleShape black2;

	sf::Sprite image;
	WrappedText text;

	std::vector<std::string> imageTexIds;
	std::vector<std::wstring> texts;

	sf::Color imageColor;

	sf::Vector2f size = { 320.f,240.f };

	int introIndex = 0;
	const int INTRO_IMAGE_COUNT = 11;

	float timer = 0.f;
	float introInterval = 5.0f;

	float fadeTimer = 0.f;
	float fadeTime = 0.5f;
	float fadeIntervalTimer = 0.f;
	float fadeInterval = 0.02f;
	bool isFadeOut = false;

	float waitingTimer = 0.f;
	float waitingTime = 3.5f;

	float lastIntroTimer = 0.f;
	float lastIntroTime = 6.0f;
	float moveSpeed = 40.f;
	bool lastIntro = false;

	bool isDrawBlack = false;

public:
	SceneIntro();
	~SceneIntro() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

