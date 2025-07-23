#include "stdafx.h"
#include "MapTool.h"
#include "Button.h"
#include "InputText.h"
MapTool::MapTool() : Scene(SceneIds::MapTool), grid(sf::Lines)
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

	

	for (int i = 0; i < buttons.size(); ++i)
	{
		auto btn = buttons[i];

		btn->SetSize({ 100.f, 100.f });
		btn->SetColor(sf::Color::Red, sf::Color::Red);
		btn->SetPosition({ 300.f * (i + 1), 100.f });
		btn->SetSize({ 100.f, 100.f });
		btn->SetOrigin({ btn->GetLocalBounds().width * 0.5f, btn->GetLocalBounds().height * 0.5f });
		btn->setCallback([&, i]() {
			std::cout << "��ư " << i + 1 << " ����" << std::endl;
			std::cout << "���� test ��: " << test << std::endl;
			t1->Activate([&](int value) {
				test = value;
				});
			std::cout << "�Է� �� test ��: " << test << std::endl;
			});
	}
	// ������
	for (int y = 0; y <= gridHeight; y += cellSize)
	{
		grid.append(sf::Vertex(sf::Vector2f(0, y), sf::Color::Green));       // ����
		grid.append(sf::Vertex(sf::Vector2f(gridWidth, y), sf::Color::Green)); // ������
	}

	// ������
	for (int x = 0; x <= gridWidth; x += cellSize)
	{
		grid.append(sf::Vertex(sf::Vector2f(x, 0), sf::Color::White));       // ����
		grid.append(sf::Vertex(sf::Vector2f(x, gridHeight), sf::Color::White)); // �Ʒ���
	}
}

void MapTool::Exit()
{
	buttons.clear();
}

void MapTool::Update(float dt)
{
	if (InputMgr::GetMouseButtonDown(sf::Mouse::Left))
	{
		sf::Mouse mo;
		sf::Vector2i pos = mo.getPosition();
		std::cout << pos.x << ", " << pos.y << std::endl;
	}
	/*if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::test);
	}*/
	Scene::Update(dt);
}

void MapTool::Draw(sf::RenderWindow& window)
{
	window.draw(grid);
	Scene::Draw(window);
}
