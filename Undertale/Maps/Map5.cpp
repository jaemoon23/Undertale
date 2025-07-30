#include "stdafx.h"
#include "Map5.h"
#include "Player.h"
#include "TextGo.h"
#include "SceneBattle.h"

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

	Scene::Init();
}

void Map5::Enter()
{
	SOUND_MGR.PlayBgm("sounds/Map5/47 Ooo.flac");
	std::srand(time(0));
	targetKeys = { sf::Keyboard::Q, sf::Keyboard::W, sf::Keyboard::E, sf::Keyboard::R };
	
	std::ifstream in("map5.json");
	if (!in)
	{
		std::cerr << "map5.json 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;
	auto& mapData = j["map5"];

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
		
		

		rect->setOutlineThickness(1.f);
		hitboxes.push_back({ rect, typeStr });
	}

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

}

void Map5::Update(float dt)
{
	worldView.setCenter(player->GetPosition());

	textQ->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textW->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textE->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });
	textR->SetPosition({ player->GetPosition().x - 5.f, player->GetPosition().y - 40.f });

	battleCheckTimer += dt;

	currentTime2 += dt;
	
	if (maxTime2 < currentTime2)
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
			player->SetPosition({ -134.f, 273.f });
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
			player->SetPosition({ -134.f, 273.f });
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
						std::cout << "배틀 확률 체크" << std::endl;
						battleCheckTimer = 0.f;

						// 1% 확률
						if (Utils::RandomRange(0.f, 1.f) < 0.1f)
						{
							std::cout << "랜덤 전투 발생!" << std::endl;
							SceneBattle::nextSceneId = SceneIds::Map5;
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
			else if (hit.type == "NextScene")
			{
				std::cout << "NextScene" << std::endl;
				SCENE_MGR.ChangeScene(SceneIds::MapPapyrus);
			}
			else if (hit.type == "PrevScene")
			{
				std::cout << "PrevScene" << std::endl;
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


