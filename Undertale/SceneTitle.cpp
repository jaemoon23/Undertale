#include "stdafx.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle()
	: Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	texIds.push_back("graphics/spr_undertaletitle_0.png");

	fontIds.push_back("fonts/DungGeunMo.ttf");

	soundIds.push_back("sounds/mus_sfx_cinematiccut.wav");

	Scene::Init();
}

void SceneTitle::Enter()
{
	Scene::Enter();

	SOUND_MGR.PlaySfx("sounds/mus_sfx_cinematiccut.wav");

	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	background.setTexture(TEXTURE_MGR.Get("graphics/spr_undertaletitle_0.png"));
	text.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	text.setString("[PRESS Z OR ENTER]");
	text.setCharacterSize(10.f);
	text.setPosition({ 112.f,180.f });
	text.setFillColor(sf::Color(128, 128, 128));
}

void SceneTitle::Update(float dt)
{
	Scene::Update(dt);

	if (InputMgr::GetKeyDown(sf::Keyboard::Z) || InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::test);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(text);
	Scene::Draw(window);
}