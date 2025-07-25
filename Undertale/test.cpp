#include "stdafx.h"
#include "test.h"

test::test() : Scene(SceneIds::test)
{

}
void test::Init()
{
}

void test::Enter()
{
	Scene::Enter();
	FRAMEWORK.SetWindowSize(640, 480);
	
}

void test::Update(float dt)
{
	if (InputMgr::GetKeyDown(sf::Keyboard::Return))
	{
		SCENE_MGR.ChangeScene(SceneIds::MapTool);
	}
}
	


void test::Draw(sf::RenderWindow& window)
{
}
