#include "stdafx.h"
#include "SceneIntro.h"

SceneIntro::SceneIntro()
	: Scene(SceneIds::Intro)
{
}

void SceneIntro::Init()
{
	for (int i = 0; i < INTRO_IMAGE_COUNT; i++)
	{
		std::string texId = "graphics/spr_introimage_" + std::to_string(i) + ".png";
		texIds.push_back(texId);
		imageTexIds.push_back(texId);
	}

	fontIds.push_back("fonts/DungGeunMo.ttf");

	soundIds.push_back("sounds/01 Once Upon a Time.flac");

	texts.push_back(L"���� ��, �ΰ��� ����,�� ������ ������    �ٽ��Ƚ��ϴ�.");
	texts.push_back(L"��� ��, �� �������� ������ �߹��߽��ϴ�.");
	texts.push_back(L"��� �� �ο� ����,  �ΰ��� �¸��߽��ϴ�.");
	texts.push_back(L"�׵��� ���� �ֹ���  �̿��Ͽ� ��������   �� �ӿ� �����߽��ϴ�.");
	texts.push_back(L"���� �ð��� �帥 ��..");
	texts.push_back(L"���� ��, 202X��");
	texts.push_back(L"������ ������ �꿡  ���� �̴� ���� ���ƿ��� ���Ѵٰ� �մϴ�.");
	texts.push_back(L"");
	texts.push_back(L"");
	texts.push_back(L"");
	texts.push_back(L"");

	black.setSize({ 320.f,28.f });
	black.setFillColor(sf::Color::Black);
	black2.setSize({ 320.f,102.f });
	black2.setPosition({ 0.f,138.f });
	black2.setFillColor(sf::Color::Black);

	Scene::Init();
}

void SceneIntro::Enter()
{
	Scene::Enter();

	SOUND_MGR.PlayBgm("sounds/01 Once Upon a Time.flac");

	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	introIndex = 0;
	image.setTexture(TEXTURE_MGR.Get(imageTexIds[introIndex]));
	image.setPosition({ 0.f,0.f });
	sf::Color color = image.getColor();
	color.a = 255;
	image.setColor(color);
	text.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	text.setMaxWidth(190.f);
	text.setCharacterSize(18);
	text.setString(texts[introIndex]);
	text.setPosition({ 58.0f,150.f });

	isFadeOut = false;
	lastIntro = false;
	isDrawBlack = false;
}

void SceneIntro::Exit()
{
	Scene::Exit();
}

void SceneIntro::Update(float dt)
{
	Scene::Update(dt);

	if (lastIntro)
	{
		waitingTimer += dt;
		if (waitingTimer >= waitingTime)
		{
			sf::Vector2f pos = image.getPosition();
			pos.y += moveSpeed * dt;
			pos.y = Utils::Clamp(pos.y, -220.f, 28.f);
			image.setPosition(pos);

			if (pos.y == 28.f)
			{
				lastIntro = false;
			}
		}
	}
	else if (isFadeOut)
	{
		fadeTimer += dt;
		fadeIntervalTimer += dt;

		if (fadeIntervalTimer > fadeInterval)
		{
			fadeIntervalTimer = 0.f;
			float alpha = static_cast<float>(imageColor.a);
			alpha -= 255.f * fadeInterval / fadeTime;
			imageColor.a = static_cast<sf::Uint8>(std::max(0.f, alpha));
			image.setColor(imageColor);
		}


		if (fadeTimer >= fadeTime || imageColor.a == 0)
		{
			fadeTimer = 0.f;
			fadeIntervalTimer = 0.f;
			isFadeOut = false;

			introIndex++;
			if (introIndex < INTRO_IMAGE_COUNT - 1)
			{
				imageColor.a = 255;
				image.setColor(imageColor);
				image.setTexture(TEXTURE_MGR.Get(imageTexIds[introIndex]));
				text.setString(texts[introIndex]);
			}
			else if(introIndex == INTRO_IMAGE_COUNT - 1)
			{
				imageColor.a = 255;
				image.setColor(imageColor);
				image.setTexture(TEXTURE_MGR.Get(imageTexIds[introIndex]), true);
				text.setString(texts[introIndex]);
				lastIntro = true;
				isDrawBlack = true;
				image.setPosition({ 0.f,-210.f });
			}
			else if (introIndex == INTRO_IMAGE_COUNT)
			{
				SCENE_MGR.ChangeScene(SceneIds::Intro);
			}
		}
	}
	else
	{
		timer += dt;
		if (timer >= introInterval)
		{
			timer = 0.f;
			isFadeOut = true;
			imageColor = image.getColor();
		}
	}
}

void SceneIntro::Draw(sf::RenderWindow& window)
{
	window.draw(image);
	window.draw(black);
	window.draw(text);
	if(isDrawBlack)
		window.draw(black2);
	Scene::Draw(window);
}