#include "stdafx.h"
#include "SceneTest.h"
#include "Player.h"

SceneTest::SceneTest()
	:Scene(SceneIds::Test)
{

}

void SceneTest::Init()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };

	uiView.setSize(size);
	uiView.setCenter(center);

	worldView.setSize(size);
	worldView.setCenter(center);


	texIds.push_back("Sprites/spr_f_maincharad_0.png");


	player = new Player("player");


	AddGameObject(player);



	Scene::Init();
}

void SceneTest::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
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
	Scene::Update(dt);
}
void SceneTest::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}