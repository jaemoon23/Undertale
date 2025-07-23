#include "stdafx.h"
#include "SceneTest.h"
#include "Player.h"
#include "Sans.h"
#include "BackGroundUi.h"
#include "TestBackGround.h"
#include "HpUi.h"
#include "NameUi.h"

SceneTest::SceneTest()
	:Scene(SceneIds::Test)
{

}

void SceneTest::Init()
{
	auto size = FRAMEWORK.GetWindowSizeF()* 0.5f;
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

	fontIds.push_back("fonts/DungGeunMo.ttf");

	uiView.setSize(size);
	uiView.setCenter(center);

	worldView.setSize(size);
	worldView.setCenter(center);

	texIds.push_back("Sprites/idle.png");
	texIds.push_back("Sprites/downwalking.png");
	texIds.push_back("Sprites/upwalking.png");
	texIds.push_back("Sprites/leftwalking.png");
	texIds.push_back("Sprites/rightwalking.png");
	texIds.push_back("Sprites/backgroundui.png");
	texIds.push_back("Sprites/bg_asgore_livingroom_0.png");
	texIds.push_back("Sprites/spr_sans_sleep_0.png");

	ANI_CLIP_MGR.Load("Animation/idle.csv");
	ANI_CLIP_MGR.Load("Animation/downwalking.csv");
	ANI_CLIP_MGR.Load("Animation/upwalking.csv");
	ANI_CLIP_MGR.Load("Animation/leftwalking.csv");
	ANI_CLIP_MGR.Load("Animation/rightwalking.csv");
	

	player = new Player("player");
	sans = new Sans("sans");
	testbackground = new TestBackGround("testbackground ");
	backgroundui = new BackGroundUi("backgroundui");
	hpui = new HpUi("hpui");
	nameui = new NameUi("nameui");

	nameui->SetName("Chara");
	hpui->SetHp(20, 20);
	player->SetSans(sans);
	player->SetHpUi(hpui);


	AddGameObject(testbackground);
	AddGameObject(player);
	AddGameObject(sans);
	AddGameObject(backgroundui);
	AddGameObject(hpui);
	AddGameObject(nameui);

	Scene::Init();
}

void SceneTest::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF()* 0.5f;
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

	uiView.setSize(size);
	uiView.setCenter(center);

	worldView.setSize(size);
	worldView.setCenter(center);

	Scene::Enter();
}
void SceneTest::Exit()
{
	Scene::Exit();
}
void SceneTest::Update(float dt)
{	
	worldView.setCenter(player->GetPosition().x, player->GetPosition().y);
	//std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl; 잘모르겠으면 좌표 찍어보자 
	player->Update(dt);
	sans->Update(dt);
	Scene::Update(dt);
}
void SceneTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}