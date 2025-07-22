#include "stdafx.h"
#include "MapTool.h"
#include "Button.h"

MapTool::MapTool() : Scene(SceneIds::MapTool)
{
	
}

void MapTool::Init()
{
	b1 = (Button*)(AddGameObject(new Button("button1")));
	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	FRAMEWORK.SetWindowSize(1920, 1080);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	b1->SetPosition({100.f, 100.f});
	b1->SetOrigin({ b1->GetLocalBounds().width * 0.5f, b1->GetLocalBounds().height * 0.5f });
	b1->SetColor(sf::Color::Red, sf::Color::Red);
	b1->SetSize({ 100.f, 100.f });

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);
}

void MapTool::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::test);
	}
	Scene::Update(dt);
}

void MapTool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
