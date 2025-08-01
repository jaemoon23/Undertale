#include "stdafx.h"
#include "Map1.h"
#include "SceneBattle.h"
#include "Player.h"
#include "TextGo.h"
#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"

Map1::Map1() : Scene(SceneIds::Map1)
{
}

void Map1::Init()
{
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("graphics/back2.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/TextWindow.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("Sprites/backgroundui.png");
	texIds.push_back("Sprites/spin_sheet.png");
	texIds.push_back("Sprites/TextWindow.png");

	SOUNDBUFFER_MGR.Load("sounds/Map1/05 Ruins.flac");
	SOUNDBUFFER_MGR.Load("sounds/Map1/Fall2.wav");
	SOUNDBUFFER_MGR.Load("sounds/Map1/sw.wav");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");
	ANI_CLIP_MGR.Load("Animation/Player_Spin.csv");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	background = (SpriteGo*)AddGameObject(new SpriteGo());
	background->sortingLayer = SortingLayers::Background;
	textWindow = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TextWindow.png"));
	textWindow2 = (SpriteGo*)AddGameObject(new SpriteGo("Sprites/TextWindow.png"));
	text = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));
	text2 = (TextGo*)AddGameObject(new TextGo("fonts/DungGeunMo.ttf"));

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
	player->SetBox(dialoguebox);
	dialoguebox->SetPlayer(player);

	AddGameObject(inventoryui);
	AddGameObject(dialoguebox);
	AddGameObject(uichanger);
	AddGameObject(playerinfoui);

	wall.setSize({ 10.f,70.f });
	wall.setFillColor(sf::Color::Transparent);
	wall.setOutlineColor(sf::Color::Green);
	wall.setOutlineThickness(1.f);
	wall.setPosition({ 640.f, -10.f });

	textWindow->sortingLayer = SortingLayers::UI;
	textWindow->SetPosition({ 35.f, 300.f });
	textWindow->SetActive(false);

	textWindow2->sortingLayer = SortingLayers::UI;
	textWindow2->SetPosition({ 35.f, 300.f });
	textWindow2->SetActive(false);

	text->sortingLayer = SortingLayers::UI;
	text->SetString(L"* 알 수 없는 힘에 의해 막힘");
	text->SetCharacterSize(35.f);
	text->SetPosition({ textWindow->GetPosition().x + 10, textWindow->GetPosition().y + 5 });
	text->SetActive(false);

	text2->SetString("");
	text2->SetCharacterSize(35.f);
	text2->sortingLayer = SortingLayers::UI;
	text2->sortingOrder = 1;
	Scene::Init();
}

void Map1::Enter()
{
	SOUND_MGR.PlayBgm("sounds/Map1/05 Ruins.flac");
	direction = { 0.f,1.f };

	Scene::LoadMapFromJson("map1.json", "map1", player, background, objects, hitboxes);
	Scene::Enter();

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	player->SetPosition(startPos);
}

void Map1::Update(float dt)
{
	// 테스트 코드
	if (InputMgr::GetKeyDown(sf::Keyboard::Numpad5))
	{
		SceneBattle::nextSceneId = SceneIds::Map1;
		SceneBattle::monsterJsonID = "jsons/frog.json";
		startPos = player->GetPosition();
		player->StartBattle();
	}

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
	battleCheckTimer += dt;
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	}
	for (auto& hit : hitboxes)
	{
		if (Utils::CheckCollision(player->GetHitBox(), *hit.shape))
		{
			if (hit.type == "Wall" && wallHitBox)
			{
				player->SetPosition(player->getPos());
			}
			else if (hit.type == "SceneChange")
			{
				std::cout << "씬 전환 트리거됨!" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::Dev1);
			}
			else if (hit.type == "Battle")
			{
				if (!event)
				{
					if (battleCheckTimer >= battleCheckInterval)
					{
						//std::cout << "배틀 확률 체크" << std::endl;
						//battleCheckTimer = 0.f;

						//// 5% 확률
						//if (Utils::RandomRange(0.f, 1.f) < 0.05f)
						//{
						//	SceneBattle::nextSceneId = SceneIds::Map1;
						//	SceneBattle::monsterJsonID = "jsons/frog.json";
						//	startPos = player->GetPosition();
						//	player->StartBattle();
						//}
						//else
						//{
						//	std::cout << "배틀 아님" << std::endl;
						//}
					}
				}
			}
			else if (hit.type == "Switch")
			{
				std::cout << "Switch" << std::endl;
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					SOUND_MGR.PlaySfx("sounds/Map1/sw.wav");
					puzzleSuccess = true;
				}
			}
			else if (hit.type == "NextScene")
			{
				std::cout << "NextScene" << std::endl;
				startPos = player->GetPosition() + sf::Vector2f(-40.f, 0.f);
				SCENE_MGR.ChangeScene(SceneIds::Map2);
			}
			else if (hit.type == "PrevScene")
			{
				std::cout << "PrevScene" << std::endl;
				startPos = { -9.f,-61.f };
				SCENE_MGR.ChangeScene(SceneIds::Map0);
			}
			else if (hit.type == "Signs")
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					isText = true;
					std::cout << "Signs" << std::endl;
				}
			}
			else if (hit.type == "Door")
			{
				std::cout << "Door" << std::endl;
				player->SetPosition({ -2.0f, -50.f });
			}
			if (!moveEvent)
			{
				if (hit.type == "Event")
				{
					SOUND_MGR.PlaySfx("sounds/Map1/Fall2.wav");
					std::cout << "Event" << std::endl;
					eventMoveRemaining = 420.f;
					event = true;
					moveEvent = true;
					player->SetMove(false);
					player->SetSpin(true);
				}
			}
		}
	}
	if (event)
	{
		wallHitBox = false;
		direction.y = 1.f;

		float moveStep = eventMoveSpeed * dt;

		if (eventMoveRemaining <= 0.f)
		{
			std::cout << "Event 이동 완료" << std::endl;
			wallHitBox = true;
			event = false;
			moveEvent = false;
			player->SetMove(true);
			player->SetEvent(true);
		}
		else
		{
			// 이동할 거리 vs 남은 거리 중 더 작은 값만큼 이동
			float actualStep = std::min(moveStep, eventMoveRemaining);
			player->SetPosition(player->GetPosition() + direction * actualStep);
			eventMoveRemaining -= actualStep;
			std::cout << "남은 거리: " << eventMoveRemaining << ", 이번 이동: " << actualStep << std::endl;
		}
	}
	if (!puzzleSuccess)
	{
		if (Utils::CheckCollision(player->GetHitBox(), wall))
		{
			player->SetPosition(player->getPos());
			showText = true;
			std::cout << "* 알 수 없는 힘에 의해 막힘" << std::endl;
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
	else if (!showText)
	{
		textWindow->SetActive(false);
		text->SetActive(false);
	}
	textTimer += dt;

	if (isText)
	{
		if (currentIndex >= fullText.size())
		{
			time += dt;
			if (time > 1.5f)
			{
				isText = false;
				time = 0.f;
				currentIndex = 0;
				currentText = L"";
				textWindow2->SetActive(false);
				text2->SetActive(false);
			}

		}
		else if (textTimer >= textSpeed) // 글자 출력 간격
		{
			textWindow2->SetActive(true);
			text2->SetActive(true);

			textTimer = 0.f;
			currentText += fullText[currentIndex];
			currentIndex++;

			text2->SetString(currentText); // 실제 텍스트 객체에 반영
			text2->SetPosition({ textWindow2->GetPosition().x + 30.f, textWindow2->GetPosition().y + 25.f });
		}
	}

	Scene::Update(dt);
}

void Map1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	window.setView(worldView);

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape); // worldView 기준으로 그려짐
		}
		window.draw(wall);
	}
}
