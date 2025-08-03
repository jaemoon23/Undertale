#include "stdafx.h"
#include "Map4.h"
#include "Player.h"
#include "SceneBattle.h"
#include "InventoryUi.h"
#include "HealItem.h"
#include "TemMie.h"

#include "UiChanger.h"
#include "PlayerInfoUi.h"
#include "DialogueBox.h"
Map4::Map4() : Scene(SceneIds::Map4)
{
}

void Map4::Init()
{
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("graphics/back5.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/TextWindow.png");
	texIds.push_back("Sprites/Temmie_sheet.png");
	texIds.push_back("Sprites/backgroundui.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("graphics/spr_switch_0.png");
	soundIds.push_back("sounds/snd_select.wav");

	SOUNDBUFFER_MGR.Load("sounds/Map4/31 Waterfall.flac");
	SOUNDBUFFER_MGR.Load("sounds/Map4/sw.wav");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");

	ANI_CLIP_MGR.Load("Animation/temmie/Temmie_Idle.csv");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;
	textWindow = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TextWindow.png"));
	text = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	temMie = (TemMie*)AddGameObject(new TemMie("Sprites/temmie/spr_temmie_lt_0.png"));

	inventoryui = new InventoryUi("InventoryUi");
	dialoguebox = new DialogueBox("dialoguebox");
	uichanger = new UiChanger("uichanger");
	playerinfoui = new PlayerInfoUi("playerinfoui");

	player->SetBox(dialoguebox);
	player->SetUiChanger(uichanger);
	player->SetInventoryUi(inventoryui);
	player->SetPlayerInfoUi(playerinfoui);
	dialoguebox->SetPlayer(player);
	uichanger->SetDialogueBox(dialoguebox);
	uichanger->SetPlayer(player);
	uichanger->SetInventoryUi(inventoryui);
	uichanger->SetPlayerInfoUi(playerinfoui);
	inventoryui->SetPlayer(player);
	inventoryui->SetBox(dialoguebox);


	AddGameObject(inventoryui);
	AddGameObject(dialoguebox);
	AddGameObject(uichanger);
	AddGameObject(playerinfoui);

	player->SetBox(dialoguebox);
	dialoguebox->SetPlayer(player);

	textWindow->sortingLayer = SortingLayers::UI;
	textWindow->SetPosition({ 35.f, 300.f });
	textWindow->SetActive(false);

	text->sortingLayer = SortingLayers::UI;
	text->SetString(L"알 수 없는 힘에 의해 막힘");
	text->SetCharacterSize(35.f);
	text->SetPosition({ textWindow->GetPosition().x + 10, textWindow->GetPosition().y + 5 });
	text->SetActive(false);
	Scene::Init();

	

	PlayerInfo::gold;
}

void Map4::Enter()
{
	SOUND_MGR.PlayBgm("sounds/Map4/31 Waterfall.flac");
	wall.setSize({ 10.f,150.f });
	wall.setFillColor(sf::Color::Transparent);
	wall.setOutlineColor(sf::Color::Green);
	wall.setOutlineThickness(1.f);
	wall.setPosition({ 695.f, 220.f });
	
	Scene::LoadMapFromJson("map4.json", "map4", player, background, objects, hitboxes);
	Scene::Enter();
	

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	player->SetPosition(startPos);
}

void Map4::Update(float dt)
{
	// 테스트 코드
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad5))
	{
		SceneBattle::nextSceneId = SceneIds::Map4;
		SceneBattle::monsterJsonID = "jsons/icecap.json";
		startPos = player->GetPosition();
		player->StartBattle();
	}
	//

	worldView.setCenter(player->GetPosition());
	battleCheckTimer += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::C))
	{
		if ((inventoryui && inventoryui->GetActive()) ||
			(playerinfoui && playerinfoui->GetActive()) ||
			(dialoguebox && dialoguebox->GetActive()))
		{
			return;
		}
		uichanger->SetActive(!uichanger->GetActive());
		SOUND_MGR.PlaySfx("sounds/snd_select.wav");
	}
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	}
	for (auto& hit : hitboxes)
	{
		if (Utils::CheckCollision(player->GetHitBox(), *hit.shape))
		{
			if (hit.type == "Wall")
			{
				player->SetPosition(player->getPos());
			}
			else if (hit.type == "Battle")
			{
				if (battleCheckTimer >= battleCheckInterval)
				{
					battleCheckTimer = 0.f;

					// 1% 확률
					if (player->GetMove() && Utils::RandomRange(0.f, 1.f) < 0.01f)
					{
						SceneBattle::nextSceneId = SceneIds::Map4;
						SceneBattle::monsterJsonID = "jsons/icecap.json";
						startPos = player->GetPosition();
						player->StartBattle();
					}
				}
			}
			else if (hit.type == "Switch")
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					SOUND_MGR.PlaySfx("sounds/Map4/sw.wav");
					puzzleSuccess = true;
				}
			}
			else if (hit.type == "NextScene")
			{
				startPos = player->GetPosition() + sf::Vector2f(-30.f, 0.f);
				SCENE_MGR.ChangeScene(SceneIds::Map5);
			}
			else if (hit.type == "PrevScene")
			{
				startPos = { -53.f,263.f };
				SCENE_MGR.ChangeScene(SceneIds::Map3);
			}
			else if (hit.type == "Signs")
			{
				std::cout << "Signs" << std::endl;
			}
		}
		if (!puzzleSuccess)
		{
			if (Utils::CheckCollision(player->GetHitBox(), wall))
			{
				player->SetPosition(player->getPos());
				showText = true;
			}
			else
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					showText = false;
				}
			}
		}
		if (showText)
		{
			textWindow->SetActive(true);
			text->SetActive(true);
		}
		else
		{
			textWindow->SetActive(false);
			text->SetActive(false);
		}
	}
	if (Utils::CheckCollision(player->GetHitBox(), temMie->GetHitBox()))
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			std::cout << "테미 z키 입력" << std::endl;
			startPos = player->GetPosition();
			SCENE_MGR.ChangeScene(SceneIds::TemMieShop);
		}
	}
	Scene::Update(dt);
}

void Map4::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape);
		}
		window.draw(wall);
	}
}

