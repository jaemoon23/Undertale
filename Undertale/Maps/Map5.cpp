#include "stdafx.h"
#include "Map5.h"
#include "Player.h"
#include "TextGo.h"
#include "SceneBattle.h"

#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"

Map5::Map5() : Scene(SceneIds::Map5)
{
}

void Map5::Init()
{
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("graphics/back6.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("Sprites/backgroundui.png");

	SOUNDBUFFER_MGR.Load("sounds/Map5/47 Ooo.flac");
	SOUNDBUFFER_MGR.Load("sounds/Map5/sw.wav");
	SOUNDBUFFER_MGR.Load("sounds/Map5/bell.wav");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;

	textQ = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	textW = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	textE = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	textR = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));

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

	Scene::Init();
}

void Map5::Enter()
{
	SOUND_MGR.PlayBgm("sounds/Map5/47 Ooo.flac");
	std::srand(time(0));
	targetKeys = { sf::Keyboard::Q, sf::Keyboard::W, sf::Keyboard::E, sf::Keyboard::R };
	Scene::LoadMapFromJson("map5.json", "map5", player, background, objects, hitboxes);

	Scene::Enter();

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	textQ->SetString("Q");
	textQ->SetCharacterSize(20.f);
	textQ->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textQ->SetActive(false);

	textW->SetString("W");
	textW->SetCharacterSize(20.f);
	textW->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textW->SetActive(false);

	textE->SetString("E");
	textE->SetCharacterSize(20.f);
	textE->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textE->SetActive(false);

	textR->SetString("R");
	textR->SetCharacterSize(20.f);
	textR->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textR->SetActive(false);

	player->SetPosition(startPos);
	isCheck = false;
}

void Map5::Update(float dt)
{
	// 테스트 코드
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad5))
	{
		SceneBattle::nextSceneId = SceneIds::Map5;
		SceneBattle::monsterJsonID = "jsons/aaron.json";
		startPos = player->GetPosition();
		player->StartBattle();
		isCheck = true;
	}
	//

	if (InputMgr::GetKeyDown(sf::Keyboard::C))
	{
		if ((inventoryui && inventoryui->GetActive()) ||
			(playerinfoui && playerinfoui->GetActive()) ||
			(dialoguebox && dialoguebox->GetActive()))
		{
			return;
		}
		uichanger->SetActive(!uichanger->GetActive());
	}

	worldView.setCenter(player->GetPosition());

	textQ->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textW->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textE->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textR->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });

	battleCheckTimer += dt;

	currentTime2 += dt;
	
	if (!isCheck && maxTime2 < currentTime2)
	{
		battle = false;
		if (ran)
		{
			r = std::rand() % 4; // 0 ~ 3
			ran = false;
		}
		if (r == 0)
		{
			textQ->SetActive(true);
			player->SetMove(false);
		}
		else if (r == 1)
		{
			textW->SetActive(true);
			player->SetMove(false);
		}
		else if (r == 2)
		{
			textE->SetActive(true);
			player->SetMove(false);
		}
		else if (r == 3)
		{
			textR->SetActive(true);
			player->SetMove(false);
		}

		currentTime += dt;
		
		if (maxTime < currentTime)
		{
			SOUND_MGR.PlaySfx("sounds/Map5/sw.wav");
			std::cout << "시간 초과!" << std::endl;
			currentTime = 0.f;
			currentTime2 = 0.f;
			player->SetMove(true);
			player->SetPosition({ 78.f, 248.f });
			battle = true;
			ran = true;
		}
		if (InputMgr::GetKeyDown(targetKeys[r]))
		{
			SOUND_MGR.PlaySfx("sounds/Map5/bell.wav");
			std::cout << "정답 입력" << std::endl;
			currentTime = 0.f;
			currentTime2 = 0.f;
			player->SetMove(true);
			battle = true;
			ran = true;
		}
		else if (
			InputMgr::GetKeyDown(sf::Keyboard::Q)||
			InputMgr::GetKeyDown(sf::Keyboard::W)||
			InputMgr::GetKeyDown(sf::Keyboard::E)||
			InputMgr::GetKeyDown(sf::Keyboard::R))
		{
			SOUND_MGR.PlaySfx("sounds/Map5/sw.wav");
			std::cout << "입력 실패" << std::endl;
			player->SetMove(true);
			player->SetPosition({ 78.f, 248.f });
			currentTime2 = 0.f;
			battle = true;
			ran = true;
		}
		if (ran)
		{
			textQ->SetActive(false);
			textW->SetActive(false);
			textE->SetActive(false);
			textR->SetActive(false);
		}
		
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
				if (battle)
				{
					if (battleCheckTimer >= battleCheckInterval)
					{
						battleCheckTimer = 0.f;

						// 1% 확률
						if (player->GetMove() && Utils::RandomRange(0.f, 1.f) < 0.01f)
						{
							SceneBattle::nextSceneId = SceneIds::Map5;
							SceneBattle::monsterJsonID = "jsons/aaron.json";
							startPos = player->GetPosition();
							player->StartBattle();
							isCheck = true;
						}
					}
				}
			}
			else if (hit.type == "NextScene")
			{
				startPos = player->GetPosition() + sf::Vector2f(-20.f, 0.f);
				SCENE_MGR.ChangeScene(SceneIds::MapPapyrus);
			}
			else if (hit.type == "PrevScene")
			{
				startPos = { 78.f,248.f };
				SCENE_MGR.ChangeScene(SceneIds::Map4);
			}
			else if (hit.type == "Signs")
			{
				std::cout << "Signs" << std::endl;
			}
		}
	}
	Scene::Update(dt);
}

void Map5::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape); // worldView 기준으로 그려짐
		}
	}
}


