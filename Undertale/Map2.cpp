#include "stdafx.h"
#include "Map2.h"
#include "Player.h"
#include "SceneBattle.h"
#include "DialogueBox.h"

#include <fstream>
#include "json.hpp"
#include "TextGo.h"
#include "Sans.h"

#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"

Map2::Map2() : Scene(SceneIds::Map2)
{
}

void Map2::Init()
{
	font.loadFromFile("fonts/DungGeunMo.ttf");

	texIds.push_back("Sprites/idle.png");
	texIds.push_back("graphics/back3.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/sprite_sheet_dark.png");
	texIds.push_back("Sprites/spr_sans_r_dark_2.png");
	texIds.push_back("Sprites/spr_heart_battle_pl_0.png");
	texIds.push_back("Sprites/backgroundui.png");
	texIds.push_back("Sprites/spr_sans_sleep_0.png");
	texIds.push_back("Sprites/spr_f_maincharad_0.png");
	texIds.push_back("Sprites/spr_f_maincharal_0.png");

	images.clear();
	sf::Texture tex1;
	sf::Texture tex2;
	sf::Texture tex3;
	sf::Texture tex4;

	if (tex1.loadFromFile("Sprites/spr_f_maincharad_0.png"))
		images.push_back(tex1);
	if (tex2.loadFromFile("Sprites/spr_f_maincharal_0.png"))
		images.push_back(tex2);
	if (tex2.loadFromFile("Sprites/spr_f_maincharal_0.png"))
		images.push_back(tex2);


	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");
	ANI_CLIP_MGR.Load("Animation/sansdarkwalking.csv");


	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	sans = (Sans*)AddGameObject(new Sans("Sprites/spr_sans_r_dark_2.png"));

	inventoryui = new InventoryUi("InventoryUi");
	dialoguebox = new DialogueBox("dialoguebox");
	uichanger = new UiChanger("uichanger");
	playerinfoui = new PlayerInfoUi("playerinfoui");

	player->SetBox(dialoguebox);
	player->SetUiChanger(uichanger);
	player->SetInventoryUi(inventoryui);
	player->SetPlayerInfoUi(playerinfoui);
	dialoguebox->SetPlayer(player);
	uichanger->SetPlayer(player);
	uichanger->SetInventoryUi(inventoryui);
	uichanger->SetPlayerInfoUi(playerinfoui);
	inventoryui->SetPlayer(player);
	player->SetSans(sans);
	inventoryui->SetBox(dialoguebox);

	AddGameObject(inventoryui);
	AddGameObject(dialoguebox);
	AddGameObject(uichanger);
	AddGameObject(playerinfoui);

	player->SetBox(dialoguebox);
	dialoguebox->SetPlayer(player);
	player->SetSans(sans);

	background2 = (SpriteGo*)AddGameObject(new SpriteGo());
	background2->sortingLayer = SortingLayers::Background;

	InventoryUi::healItem[0].SetInfo(L"아이스크림", 15); // 아이템 이름과 회복량 설정
	InventoryUi::healItem[1].SetInfo(L"쿠키", 10);
	InventoryUi::healItem[2].SetInfo(L"아이스크림", 15);
	InventoryUi::healItem[3].SetInfo(L"눈사탕", 5);

	Scene::Init();
}

void Map2::Enter()
{
	wall.setSize({ 14.f,100.f });
	wall.setFillColor(sf::Color::Transparent);
	wall.setOutlineColor(sf::Color::Green);
	wall.setOutlineThickness(1.f);
	wall.setPosition({ 470.f, 305.f });

	std::ifstream in("map2.json");
	if (!in)
	{
		std::cerr << "map1.json 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;
	auto& mapData = j["map2"];

	// 배경
	std::string bgTex = mapData["background"]["textureId"];
	sf::Vector2f bgPos(mapData["background"]["position"][0], mapData["background"]["position"][1]);
	sf::Vector2f scale(mapData["background"]["scale"][0], mapData["background"]["scale"][1]);

	background2->SetTextureId(bgTex);
	background2->SetOrigin(Origins::MC);
	background2->SetPosition(bgPos);
	background2->SetScale(scale);
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
			playerPlaced = true;
		}
		else
		{
			auto sprite = new SpriteGo(texId);
			sprite->SetTextureId(texId);
			sprite->SetOrigin(Origins::MC);
			sprite->SetPosition(pos);
			sprite->SetScale(scale);
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
		else
		{
			rect->setOutlineColor(sf::Color::Green);
		}
		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });

	}
	sans->SetPosition({ 220.f, 355.f });
	sans->SetActive(false);

	uiView.setSize(size);
	uiView.setCenter(center);
}

void Map2::Update(float dt)
{
	if (dialoguebox && dialoguebox->GetActive())
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
		{
			dialoguebox->NextLine();
		}
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
			if (hit.type == "Wall")
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
				if (battleCheckTimer >= battleCheckInterval)
				{
					std::cout << "배틀 확률 체크" << std::endl;
					battleCheckTimer = 0.f;

					// 1% 확률
					//if (Utils::RandomRange(0.f, 1.f) < 0.01f)
					//{
					//	std::cout << "랜덤 전투 발생!" << std::endl;
					//	SceneBattle::nextSceneId = SceneIds::test;
					//	SceneBattle::monsterJsonID = "jsons/frog.json";
					//	//SceneBattle::monsterJsonID = "jsons/sans.json";
					//	SCENE_MGR.ChangeScene(SceneIds::Battle);
					//}
					//else
					//{
					//	std::cout << "배틀 아님" << std::endl;
					//}
				}
			}
			else if (hit.type == "NextScene")
			{
				std::cout << "NextScene" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::Dev1);
			}
			else if (hit.type == "PrevScene")
			{
				std::cout << "PrevScene" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::Map0);
			}
		}
	}

	if (Utils::CheckCollision(player->GetHitBox(), wall))
	{
		player->SetMove(false);
		
		animationPlay = true;
		if (animationPlay)
		{
			sans->SetActive(true);
			sans->animator.Play("Animation/sansdarkwalking.csv");
			animationPlay = false;
		}
		
		sf::Vector2f sansPos = sans->GetPosition();
		sf::Vector2f playerPos = player->GetPosition();

		sf::Vector2f direction = playerPos - sansPos;
		Utils::Normalize(direction); // 방향 벡터 정규화

		float sansSpeed = 100.f; // 샌즈 이동 속도 (원하는 값으로 조정)
		sansPos += direction * sansSpeed * dt;
		sans->SetPosition(sansPos);


		if (Utils::CheckCollision(player->GetHitBox(), sans->GetHitBox()))
		{
			sans->SetMove(false);
			if (!InteractedSans)
			{
				InteractedSans = true;
				player->SansInteract();
			}
	
			if (InputMgr::GetKeyDown(sf::Keyboard::Z))
			{
				dialoguebox->NextLine();
			}		
		}
		if (InteractedSans && !firstInteractedEnds)
		{
			if (!dialoguebox->GetActive())
			{
				firstInteractedEnds = true;
				imageChangeTimer = 0.f;
			}
		}

		if (firstInteractedEnds)
		{
			imageChangeTimer += dt;
			if (imageChangeTimer >= 1.f)
			{
				imageChangeTimer = 0.f;
				currentImageIndex = (currentImageIndex + 1) % images.size();
				//sans->GetSprite().setTexture(images[currentImageIndex]);
			}
		}
	}


	//Scene::Update(dt);
	sans->Update(dt);
	player->Update(dt);
	playerinfoui->Update(dt);
	inventoryui->Update(dt);
	uichanger->Update(dt);
}

void Map2::Draw(sf::RenderWindow& window)
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
