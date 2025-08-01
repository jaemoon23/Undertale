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

	std::ifstream in("map4.json");
	if (!in)
	{
		std::cerr << "map4.json 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;
	auto& mapData = j["map4"];

	// 배경
	std::string bgTex = mapData["background"]["textureId"];
	sf::Vector2f bgPos(mapData["background"]["position"][0], mapData["background"]["position"][1]);
	sf::Vector2f scale(mapData["background"]["scale"][0], mapData["background"]["scale"][1]);

	background->SetTextureId(bgTex);
	background->SetOrigin(Origins::MC);
	background->SetPosition(bgPos);
	background->SetScale(scale);
	Scene::Enter();

	sf::Vector2f size = { 640.f, 480.f };
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size * 0.5f);
	uiView.setSize(size);
	uiView.setCenter(center);

	// 오브젝트
	bool playerPlaced = false;
	for (auto& obj : mapData["objects"])
	{
		std::string texId = obj["textureId"];
		sf::Vector2f pos(obj["position"][0], obj["position"][1]);
		sf::Vector2f scale(1.f, 1.f);
		if (obj.contains("scale"))
			scale = { obj["scale"][0], obj["scale"][1] };

		if (!playerPlaced)
		{
			player->SetOrigin(Origins::MC);
			player->SetPosition(pos);
			player->sortingOrder = 4;
			playerPlaced = true;
		}
		else
		{
			auto sprite = new SpriteGo(texId);
			sprite->SetTextureId(texId);
			sprite->SetOrigin(Origins::MC);
			sprite->SetPosition(pos);
			sprite->SetScale(scale);
			sprite->sortingLayer = SortingLayers::Foreground;
			sprite->sortingOrder = 0;
			sprite->Reset();
			AddGameObject(sprite);
			testObjects.push_back(sprite);
		}
	}

	//  히트박스 로드
	for (auto& box : mapData["hitboxes"])
	{
		sf::Vector2f pos(box["position"][0], box["position"][1]);
		sf::Vector2f size(box["size"][0], box["size"][1]);
		std::string typeStr = box["type"];

		auto rect = new sf::RectangleShape(size);
		rect->setPosition(pos);
		rect->setFillColor(sf::Color::Transparent);

		if (typeStr == "Wall")
		{
			rect->setOutlineColor(sf::Color::Green);
		}
		else if (typeStr == "SceneChanege")
		{
			rect->setOutlineColor(sf::Color(128, 0, 128));
		}
		else if (typeStr == "NextScene")
		{
			rect->setOutlineColor(sf::Color(255, 165, 0));
		}
		else if (typeStr == "PrevScene")
		{
			rect->setOutlineColor(sf::Color(135, 206, 250));
		}
		else if (typeStr == "Battle")
		{
			rect->setOutlineColor(sf::Color::Red);
		}
		else if (typeStr == "Switch")
		{
			rect->setOutlineColor(sf::Color(170, 255, 195));
		}

		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });
	}

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
					std::cout << "배틀 확률 체크" << std::endl;
					battleCheckTimer = 0.f;

					// 1% 확률
					if (Utils::RandomRange(0.f, 1.f) < 0.01f)
					{
						std::cout << "랜덤 전투 발생!" << std::endl;
						SceneBattle::nextSceneId = SceneIds::Map4;
						SceneBattle::monsterJsonID = "jsons/icecap.json";
						startPos = player->GetPosition();
						player->StartBattle();
					}
					else
					{
						std::cout << "배틀 아님" << std::endl;
					}
				}
			}
			else if (hit.type == "Switch")
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					SOUND_MGR.PlaySfx("sounds/Map4/sw.wav");
					puzzleSuccess = true;
					std::cout << "스위치 누름" << std::endl;
				}
			}
			else if (hit.type == "NextScene")
			{
				std::cout << "NextScene" << std::endl;
				startPos = player->GetPosition() + sf::Vector2f(-30.f, 0.f);
				SCENE_MGR.ChangeScene(SceneIds::Map5);
			}
			else if (hit.type == "PrevScene")
			{
				std::cout << "PrevScene" << std::endl;
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
				std::cout << "알 수 없는 힘에 의해 막힘" << std::endl;
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
			window.draw(*hit.shape); // worldView 기준으로 그려짐
		}
		window.draw(wall);
	}
}

