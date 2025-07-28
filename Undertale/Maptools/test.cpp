#include "stdafx.h"
#include "test.h"
#include <fstream>
#include "json.hpp"
#include "Player.h"
#include "SceneBattle.h"

test::test() : Scene(SceneIds::test)
{

}
void test::Init()
{
	
	texIds.push_back("Sprites/idle.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/backgroundui.png");
	texIds.push_back("Sprites/bg_asgore_livingroom_0.png");
	texIds.push_back("Sprites/spr_sans_sleep_0.png");
	texIds.push_back("graphics/bg_innrooms_0.png");
	texIds.push_back("graphics/bg_firstroom.png");
	texIds.push_back("graphics/spr_cutetable_0.png");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");

	player = (Player*)AddGameObject(new Player("Sprites/idle.png"));
	Scene::Init();
}

void test::Enter()
{
	Scene::Enter();
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	worldView.setSize(size);
	worldView.setCenter(center);

	std::ifstream in("map0.json");
	if (!in)
	{
		std::cerr << "map0.json 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;
	auto& mapData = j["map0"];

	// 배경
	std::string bgTex = mapData["background"]["textureId"];
	sf::Vector2f bgPos(mapData["background"]["position"][0], mapData["background"]["position"][1]);
	sf::Vector2f scale(mapData["background"]["scale"][0], mapData["background"]["scale"][1]);

	background = new SpriteGo(bgTex);
	background->SetTextureId(bgTex);
	background->SetOrigin(Origins::MC);
	background->SetPosition(bgPos);
	background->SetScale(scale);
	background->Reset();

	// 오브젝트
	bool playerPlaced = false;
	for (auto& obj : mapData["objects"])
	{
		std::string texId = obj["textureId"];
		sf::Vector2f pos(obj["position"][0], obj["position"][1]);
		sf::Vector2f scale(1.f, 1.f);
		if (obj.contains("scale"))
			scale = { obj["scale"][0], obj["scale"][1] };

		if (!playerPlaced)  // 첫 번째 오브젝트를 player 위치로 사용
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
		else if (typeStr == "SceneChange")
		{
			rect->setOutlineColor(sf::Color(128, 0, 128));
		}
		else if (typeStr == "Battle")
		{
			rect->setOutlineColor(sf::Color::Red);
		}

		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });
	}
}
void test::Update(float dt)
{
	Scene::Update(dt);
	battleCheckTimer += dt;
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
				SCENE_MGR.ChangeScene(SceneIds::Battle);
			}
			else if (hit.type == "Battle")
			{
				if (battleCheckTimer >= battleCheckInterval)
				{
					std::cout << "배틀 확률 체크" << std::endl;
					battleCheckTimer = 0.f;

					// 10% 확률
					if (Utils::RandomRange(0.f, 1.f) < 0.1f)
					{
						std::cout << "랜덤 전투 발생!" << std::endl;
						SceneBattle::nextSceneId = SceneIds::test;
						SceneBattle::monsterJsonID = "jsons/frog.json";
						//SceneBattle::monsterJsonID = "jsons/sans.json";
						SCENE_MGR.ChangeScene(SceneIds::Battle);
					}
					else
					{
						std::cout << "배틀 아님" << std::endl;
					}
				}
			}
		}
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num8))
	{
		SceneBattle::nextSceneId = SceneIds::test;
		SceneBattle::monsterJsonID = "jsons/frog.json";
		SCENE_MGR.ChangeScene(SceneIds::Battle);
	}
	else if (InputMgr::GetKeyDown(sf::Keyboard::Num9))
	{
		SceneBattle::nextSceneId = SceneIds::test;
		SceneBattle::monsterJsonID = "jsons/sans.json";
		SCENE_MGR.ChangeScene(SceneIds::Battle);
	}
}

void test::Draw(sf::RenderWindow& window)
{
	if (background)
	{
		background->Draw(window);
	}

	for (auto* obj : testObjects)
	{
		obj->Draw(window);
	}

	if (Variables::isDrawHitBox)
	{
		for (auto& hit : hitboxes)
		{
			window.draw(*hit.shape);
		}
	}
	
	Scene::Draw(window);
}
