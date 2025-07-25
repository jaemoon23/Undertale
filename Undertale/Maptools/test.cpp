#include "stdafx.h"
#include "test.h"
#include <fstream>
#include "json.hpp"

test::test() : Scene(SceneIds::test)
{

}
void test::Init()
{
	
	texIds.push_back("graphics/spr_f_maincharad_0.png");
	texIds.push_back("graphics/spr_cutetable_0.png");
	texIds.push_back("graphics/spr_darkelevator_l_0.png");
	texIds.push_back("graphics/spr_darknesstotem_0.png");
	texIds.push_back("graphics/bg_firstroom.png");
	texIds.push_back("graphics/bg_innrooms_0.png");
}

void test::Enter()
{
	Scene::Enter();
	//FRAMEWORK.SetWindowSize(640, 480);
	//sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	auto size = FRAMEWORK.GetWindowSizeF() * 0.5f;
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

	uiView.setSize(size);
	uiView.setCenter(center);

	worldView.setSize(size);
	worldView.setCenter(center);
	// JSON 파일 열기
	std::ifstream in("map0.json");
	if (!in)
	{
		std::cerr << "map0.json 파일을 열 수 없습니다!" << std::endl;
		return;
	}

	nlohmann::json j;
	in >> j;

	auto& mapData = j["map0"];

	// 백그라운드 생성
	std::string bgTex = mapData["background"]["textureId"];
	sf::Vector2f bgPos(
		mapData["background"]["position"][0],
		mapData["background"]["position"][1]
	);
	sf::Vector2f scale(
		mapData["background"]["scale"][0],
		mapData["background"]["scale"][1]
	);

	background = new SpriteGo(bgTex);
	background->SetTextureId(bgTex);
	
	background->SetOrigin(Origins::MC);
	
	background->SetPosition(bgPos);
	background->Reset();
	background->SetScale({ 2.f, 2.f });
	

	// 오브젝트 생성
	for (auto& obj : mapData["objects"])
	{
		std::string texId = obj["textureId"];
		sf::Vector2f pos(obj["position"][0], obj["position"][1]);

		SpriteGo* sprite = new SpriteGo(texId);
		sprite->SetTextureId(texId);
		sprite->SetOrigin(Origins::MC);
		sprite->SetPosition(pos);
		sprite->Reset();

		testObjects.push_back(sprite);
	}
}

void test::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::MapTool);
	}
}
	
void test::Exit()
{
	if (background)
	{
		delete background;
		background = nullptr;
	}
	for (auto s : testObjects)
	{
		delete s;
	}
	testObjects.clear();
}

void test::Draw(sf::RenderWindow& window)
{
	if (background)
	{
		background->Draw(window);
	}
		
	for (auto sprite : testObjects)
	{
		sprite->Draw(window);
	}
}
