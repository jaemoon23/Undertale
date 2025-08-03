#pragma once
#include "Scene.h"
class SceneEnding : public Scene
{
protected:
	sf::Sprite image;
	sf::Text text;
	sf::Text EndMessage;

	std::vector<std::string> imageTexIds;
	std::vector<std::wstring> texts;

	sf::Color imageColor;

	sf::Vector2f size = { 640.f,480.f };

	int introIndex = 0;
	const int INTRO_IMAGE_COUNT = 15;

	float timer = 0.f;
	float introInterval = 3.0f;

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
	bool isDrawEndText = false;
public:
	SceneEnding();
	~SceneEnding() = default;

	void Init() override;
	void Enter() override;
	void Exit() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

