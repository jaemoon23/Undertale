#include "stdafx.h"
#include "SceneEnding.h"

SceneEnding::SceneEnding()
	: Scene(SceneIds::Ending)
{
}

void SceneEnding::Init()
{
	for (int i = 0; i < INTRO_IMAGE_COUNT; i++)
	{
		std::string texId = "graphics/end_" + std::to_string(i) + ".png";
		texIds.push_back(texId);
		imageTexIds.push_back(texId);
		texts.push_back(L"       The End");
	}

	fontIds.push_back("fonts/DungGeunMo.ttf");

	soundIds.push_back("sounds/96 Last Goodbye.flac");

	Scene::Init();
}

void SceneEnding::Enter()
{
	Scene::Enter();

	SOUND_MGR.PlayBgm("sounds/96 Last Goodbye.flac");

	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	introIndex = 0;
	image.setTexture(TEXTURE_MGR.Get(imageTexIds[introIndex]));
	sf::Color color = image.getColor();
	color.a = 255;
	image.setColor(color);
	text.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	text.setCharacterSize(36);
	text.setString(texts[introIndex]);
	text.setPosition({ -120.0f,0.f });

	isFadeOut = false;
	lastIntro = false;
	timer = 0.f;
	fadeTimer = 0.f;
	waitingTimer = 0.f;
	lastIntroTimer = 0.f;
}

void SceneEnding::Exit()
{
	Scene::Exit();
}

void SceneEnding::Update(float dt)
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
			else if (introIndex == INTRO_IMAGE_COUNT - 1)
			{
				imageColor.a = 255;
				image.setColor(imageColor);
				image.setTexture(TEXTURE_MGR.Get(imageTexIds[introIndex]), true);
				text.setString(texts[introIndex]);
				lastIntro = true;
				image.setPosition({ 0.f,-210.f });
			}
			else if (introIndex == INTRO_IMAGE_COUNT)
			{
				SCENE_MGR.ChangeScene(SceneIds::Title);
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

void SceneEnding::Draw(sf::RenderWindow& window)
{
	window.draw(image);
	window.draw(text);
	Scene::Draw(window);
}