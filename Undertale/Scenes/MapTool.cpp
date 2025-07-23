#include "stdafx.h"
#include "MapTool.h"
#include "Button.h"
#include "InputText.h"
MapTool::MapTool() : Scene(SceneIds::MapTool)
{
	
}

void MapTool::Init()
{
	buttons.push_back((Button*)(AddGameObject(new Button("button1"))));
	buttons.push_back((Button*)(AddGameObject(new Button("button2"))));
	t1 = (InputText*)AddGameObject(new InputText("InputText1"));
	Scene::Init();
}

void MapTool::Enter()
{
	Scene::Enter();
	FRAMEWORK.SetWindowSize(1920, 1080);
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();

	worldView.setSize(windowSize);
	worldView.setCenter(windowSize.x * 0.5f, windowSize.y * 0.5f);

	uiView.setSize(windowSize);
	uiView.setCenter(windowSize * 0.5f);

	for (int i = 0; i < buttons.size(); ++i)
	{
		auto btn = buttons[i];

		btn->SetSize({ 100.f, 100.f });
		btn->SetColor(sf::Color::Red, sf::Color::Red);
		btn->SetPosition({ 150.f * (i + 1), 100.f });
		btn->SetSize({ 100.f, 100.f });
		btn->SetOrigin({ btn->GetLocalBounds().width * 0.5f, btn->GetLocalBounds().height * 0.5f });
		btn->setCallback([&, i]() {
			std::cout << "버튼 " << i + 1 << " 누름" << std::endl;
			std::cout << "현재 test 값: " << test << std::endl;
			t1->Activate([&](int value) {
				test = value;
				});
			std::cout << "입력 후 test 값: " << test << std::endl;
			});
	}
	
		
	
	

}

void MapTool::Exit()
{
	buttons.clear();
}

void MapTool::Update(float dt)
{
	
	/*if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::test);
	}*/
	Scene::Update(dt);
}

void MapTool::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
