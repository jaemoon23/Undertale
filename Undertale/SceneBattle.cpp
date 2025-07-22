#include "stdafx.h"
#include "SceneBattle.h"

SceneBattle::SceneBattle()
	: Scene(SceneIds::Battle)
{
}

void SceneBattle::Init()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	
	texIds.push_back("graphics/spr_battlebg_0.png");
	texIds.push_back("graphics/spr_froggit_2.png");
	texIds.push_back("graphics/spr_dialogueBox.png");
	texIds.push_back("graphics/spr_fightbt_0.png");
	texIds.push_back("graphics/spr_fightbt_1.png");
	texIds.push_back("graphics/spr_actbt_0.png");
	texIds.push_back("graphics/spr_actbt_1.png");
	texIds.push_back("graphics/spr_itembt_0.png");
	texIds.push_back("graphics/spr_itembt_1.png");
	texIds.push_back("graphics/spr_sparebt_0.png");
	texIds.push_back("graphics/spr_sparebt_1.png");
	texIds.push_back("graphics/spr_heart_battle_pl_0.png");

	describeBox.setSize({ windowSize.x * 0.95f, windowSize.y * 0.25f });
	Utils::SetOrigin(describeBox, Origins::TC);
	describeBox.setFillColor(sf::Color::Black);
	describeBox.setOutlineColor(sf::Color::White);
	describeBox.setOutlineThickness(5.f);
	describeBox.setPosition({ windowSize.x * 0.5f, windowSize.y * 0.53f });

	dialogue.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));

	describe1.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));

	statusUI = (StatusInBattleUI*)AddGameObject(new StatusInBattleUI());
	statusUI->SetPosition({ windowSize.x * 0.02f, windowSize.y * 0.8f });

	fightButton = (BattleButton*)AddGameObject(new BattleButton());
	fightButton->SetTexIds("graphics/spr_fightbt_0.png", "graphics/spr_fightbt_1.png");
	fightButton->SetPosition({ windowSize.x * 0.02f, windowSize.y * 0.9f });
	actButton = (BattleButton*)AddGameObject(new BattleButton());
	actButton->SetTexIds("graphics/spr_actbt_0.png", "graphics/spr_actbt_1.png");
	actButton->SetPosition({ windowSize.x * 0.28f, windowSize.y * 0.9f });
	itemButton = (BattleButton*)AddGameObject(new BattleButton());
	itemButton->SetTexIds("graphics/spr_itembt_0.png", "graphics/spr_itembt_1.png");
	itemButton->SetPosition({ windowSize.x * 0.54f, windowSize.y * 0.9f });
	mercyButton = (BattleButton*)AddGameObject(new BattleButton());
	mercyButton->SetTexIds("graphics/spr_sparebt_0.png", "graphics/spr_sparebt_1.png");
	mercyButton->SetPosition({ windowSize.x * 0.8f, windowSize.y * 0.9f });

	soul = (Soul*)AddGameObject(new Soul());

	Scene::Init();
}

void SceneBattle::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter(windowSize * 0.5f);

	Scene::Enter();

	background.setTexture(TEXTURE_MGR.Get("graphics/spr_battlebg_0.png"));
	Utils::SetOrigin(background, Origins::TC);
	background.setPosition({ windowSize.x * 0.5f,10.f });

	dialogueBox.setTexture(TEXTURE_MGR.Get("graphics/spr_dialogueBox.png"));
	dialogueBox.setPosition({ windowSize.x * 0.55f, windowSize.y * 0.3f });

	monster.setTexture(TEXTURE_MGR.Get("graphics/spr_froggit_2.png"));
	Utils::SetOrigin(monster, Origins::MC);
	monster.setPosition({ windowSize.x * 0.45f, windowSize.y * 0.4f });
}

void SceneBattle::Exit()
{
	Scene::Exit();
}

void SceneBattle::Update(float dt)
{
	Scene::Update(dt);

	if (btState == ButtonState::None)
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			switch (btIndex)
			{
				case 0:
					btState = ButtonState::Fight;
					break;
				case 1:
					btState = ButtonState::Act;
					break;
				case 2:
					btState = ButtonState::Item;
					break;
				case 3:
					btState = ButtonState::Mercy;
					break;
			}
		}
		else
		{
			fightButton->UpdateTexture();
			actButton->UpdateTexture();
			itemButton->UpdateTexture();
			mercyButton->UpdateTexture();
		}
	}
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(monster);
	window.draw(dialogueBox);
	window.draw(describeBox);
	Scene::Draw(window);
}