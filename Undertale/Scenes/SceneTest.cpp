#include "stdafx.h"
#include "SceneTest.h"
#include "Player.h"
#include "Sans.h"
#include "TestBackGround.h"
#include "InventoryUi.h"
#include "DialogueBox.h"
#include "UiChanger.h"
#include "PlayerInfoUi.h"

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
	inventoryui = new InventoryUi("InventoryUi");
	dialoguebox = new DialogueBox("dialoguebox");
	uichanger = new UiChanger("uichanger");
	playerinfoui = new PlayerInfoUi("playerinfoui");


	//hpui->SetHp(20, 20);
	player->SetSans(sans);
	player->SetBox(dialoguebox);
	player->SetUiChanger(uichanger);
	player->SetInventoryUi(inventoryui);
	player->SetPlayerInfoUi(playerinfoui);
	dialoguebox->SetPlayer(player);
	uichanger->SetPlayer(player);
	uichanger->SetInventoryUi(inventoryui);
	uichanger->SetPlayerInfoUi(playerinfoui);
	
	
	AddGameObject(testbackground);
	AddGameObject(player);
	AddGameObject(sans);
	AddGameObject(inventoryui);
	AddGameObject(dialoguebox);
	AddGameObject(uichanger);
	AddGameObject(playerinfoui);

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
	//std::cout << player->GetPosition().x << ", " << player->GetPosition().y << std::endl;
	player->Update(dt);
	sans->Update(dt);
	dialoguebox->Update(dt);
	inventoryui->Update(dt);
	uichanger->Update(dt);
	playerinfoui->Update(dt);


	if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	{
		SCENE_MGR.ChangeScene(SceneIds::Test);
	}

	if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	{
		SCENE_MGR.ChangeScene(SceneIds::Battle);
	}
}
void SceneTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}