#include "stdafx.h"
#include "SceneBattle.h"

SceneBattle::SceneBattle()
	: Scene(SceneIds::Battle)
{
}

void SceneBattle::Init()
{	
	texIds.push_back("graphics/spr_battlebg_0.png");
	texIds.push_back("graphics/spr_froggit_2.png");
	texIds.push_back("graphics/spr_dialogueBox.png");
	texIds.push_back("graphics/spr_actbt_off.png");
	texIds.push_back("graphics/spr_actbt_on.png");

	describeBox.setSize({ 880.f, 275.f });
	describeBox.setFillColor(sf::Color::Black);
	describeBox.setOutlineColor(sf::Color::White);
	describeBox.setOutlineThickness(10.f);
	describeBox.setPosition({ 200.f, 400.f });

	dialogue.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));

	describe1.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));

	statusUI = (StatusInBattleUI*)AddGameObject(new StatusInBattleUI());
	statusUI->SetPosition({ 200.f, 700.f });

	attackButton = (BattleButton*)AddGameObject(new BattleButton());
	attackButton->SetTexIds("graphics/spr_actbt_off.png", "graphics/spr_actbt_on.png");
	attackButton->SetScale({ 1.5f,1.5f });
	attackButton->SetPosition({ 450.f, 800.f });

	Scene::Init();
}

void SceneBattle::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/spr_battlebg_0.png"));
	background.setScale({ 1.5f,1.5f });
	Utils::SetOrigin(background, Origins::TC);
	background.setPosition({ windowSize.x * 0.5f,20.f });

	dialogueBox.setTexture(TEXTURE_MGR.Get("graphics/spr_dialogueBox.png"));
	dialogueBox.setPosition({ 700.f,250.f });

	monster.setTexture(TEXTURE_MGR.Get("graphics/spr_froggit_2.png"));
	Utils::SetOrigin(monster, Origins::MC);
	monster.setPosition({ windowSize.x * 0.5f, 300.f });
}

void SceneBattle::Exit()
{
	Scene::Exit();
}

void SceneBattle::Update(float dt)
{
	Scene::Update(dt);
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(dialogueBox);
	Scene::Draw(window);
	window.draw(monster);
	window.draw(describeBox);
}