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
}

void test::Draw(sf::RenderWindow& window)
{
}
