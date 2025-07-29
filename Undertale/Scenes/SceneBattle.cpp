#include "stdafx.h"
#include <fstream>
#include "SceneBattle.h"
#include "BattleDialogueBox.h"
#include "BattleBox.h"
#include "Bullet.h"
#include "InventoryUi.h"
#include "HealItem.h"

std::string SceneBattle::monsterJsonID = "jsons/sans.json";
SceneIds SceneBattle::nextSceneId = SceneIds::test;

SceneBattle::SceneBattle()
	: Scene(SceneIds::Battle)
{
}

void SceneBattle::Init()
{	
	ANI_CLIP_MGR.Load("animations/sans_beam.csv");
	ANI_CLIP_MGR.Load("animations/sans_idle.csv");
	ANI_CLIP_MGR.Load("animations/fist.csv");
	ANI_CLIP_MGR.Load("animations/frogit_idle.csv");
	ANI_CLIP_MGR.Load("animations/whimsun_idle.csv");
	ANI_CLIP_MGR.Load("animations/migosp_idle.csv");
	ANI_CLIP_MGR.Load("animations/icecap_idle.csv");
	ANI_CLIP_MGR.Load("animations/aaron_idle.csv");
	ANI_CLIP_MGR.Load("animations/papyrus_idle.csv");
	fontIds.push_back("fonts/DungGeunMo.ttf");
	texIds.push_back("graphics/spr_battlebg_0.png");
	texIds.push_back("graphics/spr_sans_beam_0.png");
	texIds.push_back("graphics/spr_sans_beam_1.png");
	texIds.push_back("graphics/spr_sans_beam_2.png");
	texIds.push_back("graphics/spr_sans_beam_3.png");
	texIds.push_back("graphics/spr_firebullet.png");
	texIds.push_back("graphics/spr_kissbullet_0.png");
	texIds.push_back("graphics/spr_papyrusboss_0.png");
	texIds.push_back("graphics/spr_heavybullet.png");
	texIds.push_back("graphics/spr_aaron_0.png");
	texIds.push_back("graphics/spr_aaron_1.png");
	texIds.push_back("graphics/spr_icecap_0.png");
	texIds.push_back("graphics/spr_icecap_1.png");
	texIds.push_back("graphics/spr_icecap_2.png");
	texIds.push_back("graphics/spr_icecap_3.png");
	texIds.push_back("graphics/spr_clawbullet_1.png");
	texIds.push_back("graphics/spr_migosp_0.png");
	texIds.push_back("graphics/spr_migosp_1.png");
	texIds.push_back("graphics/spr_bulletsm_0.png");
	texIds.push_back("graphics/spr_whimsun_0.png");
	texIds.push_back("graphics/spr_whimsun_1.png");
	texIds.push_back("graphics/spr_heartbreak_0.png");
	texIds.push_back("graphics/spr_gameoverbg_0.png");
	texIds.push_back("graphics/spr_heart_blue.png");
	texIds.push_back("graphics/spr_barrier.png");
	texIds.push_back("graphics/spr_heart_green.png");
	texIds.push_back("graphics/spr_arrow_up.png");
	texIds.push_back("graphics/spr_arrow_right.png");
	texIds.push_back("graphics/spr_arrow_left.png");
	texIds.push_back("graphics/spr_arrow_down.png");
	texIds.push_back("graphics/spr_bonesaver.png");
	texIds.push_back("graphics/spr_bone_bullet.png");
	texIds.push_back("graphics/spr_sans_battle.png");
	texIds.push_back("graphics/spr_sans_idle.png");
	texIds.push_back("graphics/spr_gun_bullet_.png");
	texIds.push_back("graphics/spr_bluespear.png");
	texIds.push_back("graphics/spr_eggbullet.png");
	texIds.push_back("graphics/spr_dumbtarget_0.png");
	texIds.push_back("graphics/spr_froggit_2.png");
	texIds.push_back("graphics/spr_froggit_3.png");
	texIds.push_back("graphics/spr_dialogueBox.png");
	texIds.push_back("graphics/spr_fightbt_0.png");
	texIds.push_back("graphics/spr_fightbt_1.png");
	texIds.push_back("graphics/spr_actbt_0.png");
	texIds.push_back("graphics/spr_actbt_1.png");
	texIds.push_back("graphics/spr_itembt_0.png");
	texIds.push_back("graphics/spr_itembt_1.png");
	texIds.push_back("graphics/spr_sparebt_0.png");
	texIds.push_back("graphics/spr_sparebt_1.png");
	texIds.push_back("graphics/spr_heart_battle_pl_0.png");
	texIds.push_back("graphics/spr_hyperfist_0.png");
	texIds.push_back("graphics/spr_hyperfist_1.png");
	texIds.push_back("graphics/spr_hyperfist_2.png");
	texIds.push_back("graphics/spr_hyperfist_3.png");
	texIds.push_back("graphics/spr_hyperfist_4.png");
	texIds.push_back("graphics/spr_hyperfist_5.png"); 
	soundIds.push_back("sounds/09 Enemy Approaching.flac");
	soundIds.push_back("sounds/11 Determination.flac");
	soundIds.push_back("sounds/100 MEGALOVANIA.flac");
	soundIds.push_back("sounds/16 Nyeh Heh Heh!.flac");
	soundIds.push_back("sounds/snd_squeak.wav");
	soundIds.push_back("sounds/snd_select.wav");
	soundIds.push_back("sounds/snd_hurt1.wav");
	soundIds.push_back("sounds/snd_heal_c.wav");
	soundIds.push_back("sounds/snd_punchweak.wav");
	soundIds.push_back("sounds/snd_punchstrong.wav");
	soundIds.push_back("sounds/snd_escaped.wav");
	soundIds.push_back("sounds/snd_chug.wav");
	soundIds.push_back("sounds/snd_bell.wav");
	soundIds.push_back("sounds/snd_vaporized.wav");
	soundIds.push_back("sounds/snd_break1_c.wav");
	soundIds.push_back("sounds/mus_sfx_segapower.wav");
	soundIds.push_back("sounds/snd_grab.wav");
	soundIds.push_back("sounds/snd_bombsplosion.wav");
	
	statusUI = (StatusInBattleUI*)AddGameObject(new StatusInBattleUI());
	statusUI->SetPosition({ size.x * 0.02f, size.y * 0.8f });

	fightButton = (BattleButton*)AddGameObject(new BattleButton());
	fightButton->SetTexIds("graphics/spr_fightbt_0.png", "graphics/spr_fightbt_1.png");
	fightButton->SetPosition({ size.x * 0.02f, size.y * 0.9f });
	actButton = (BattleButton*)AddGameObject(new BattleButton());
	actButton->SetTexIds("graphics/spr_actbt_0.png", "graphics/spr_actbt_1.png");
	actButton->SetPosition({ size.x * 0.28f, size.y * 0.9f });
	itemButton = (BattleButton*)AddGameObject(new BattleButton());
	itemButton->SetTexIds("graphics/spr_itembt_0.png", "graphics/spr_itembt_1.png");
	itemButton->SetPosition({ size.x * 0.54f, size.y * 0.9f });
	mercyButton = (BattleButton*)AddGameObject(new BattleButton());
	mercyButton->SetTexIds("graphics/spr_sparebt_0.png", "graphics/spr_sparebt_1.png");
	mercyButton->SetPosition({ size.x * 0.8f, size.y * 0.9f });

	btBox = (BattleBox*)AddGameObject(new BattleBox());
	soul = (Soul*)AddGameObject(new Soul());
	dialBox = (BattleDialogueBox*)AddGameObject(new BattleDialogueBox());
	dialBox->SetMaxWidth(size.x * 0.3);
	Scene::Init();
}

void SceneBattle::Enter()
{
	isPlaying = true;
	isGameOver = false;
	isMonsterShaking = false;
	isFadeIn = false;
	isDrawGameOverText = false;
	isBreak = false;
	mercyPoint = 0;
	btIndex = 0;
	PatternIndex = 0; // 0으로 바꾸기
	itemChooseIndex = 0;
	actChooseIndex = 0;
	mercyChooseIndex = 0;
	lineIndex = 0;
	heartbreakTimer = 0.f;
	fadeTimer = 0.f;
	turnTimer = 0.f;
	dialTimer = 0.f;

	Scene::Enter();
	// JSON 파일 불러오기	
	std::ifstream file(monsterJsonID);
	std::ifstream file2("jsons/testInventory.json");
	file >> data;

	dialExistTime = data["lineExistTime"];
	dialBox->SetString(data["lines"][lineIndex]);
	lineCount = data["lines"].size();
	lineIndex = ++lineIndex % lineCount;
	btBox->startStr = utf8_to_wstring(data["startDescribe"]);
	btBox->SetStartDescribe();
	patternCount = data["attackPattern"].size();
	monsterTexId = data["texId"];
	monsterMaxHp = data["hp"];
	monsterHp = monsterMaxHp;
	actChooseCount = data["ActDescribe"].size();
	animationId = data["animationId"];
	bgmId = data["bgmId"];
	SOUND_MGR.SetBgmVolume(50.f);
	SOUND_MGR.PlayBgm(bgmId, true);
	//
	worldView.setSize(size);
	worldView.setCenter(size * 0.5f);

	background.setTexture(TEXTURE_MGR.Get("graphics/spr_battlebg_0.png"));
	Utils::SetOrigin(background, Origins::TC);
	background.setPosition({ size.x * 0.5f,10.f });

	gameOver.setTexture(TEXTURE_MGR.Get("graphics/spr_gameoverbg_0.png"));
	Utils::SetOrigin(gameOver, Origins::TC);
	gameOver.setPosition({ size.x * 0.5f, 40.f });
	gameOverColor = gameOver.getColor();
	gameOverColor.a = 0;
	gameOver.setColor(gameOverColor);

	gameOverText.setFont(FONT_MGR.Get("fonts/DungGeunMo.ttf"));
	gameOverText.setCharacterSize(30.f);
	gameOverText.setPosition({ size.x * 0.25f, size.y * 0.55f });
	gameOverText.setString(L"지금 끝낼 수는 없어!");

	monster.setTexture(TEXTURE_MGR.Get(monsterTexId));
	animator.SetTarget(&monster);
	Utils::SetOrigin(monster, Origins::MC);
	animator.Play(animationId);
	monster.setPosition({ size.x * 0.45f, size.y * 0.35f });
	monsterOriginalPos = monster.getPosition();
	monsteroriginColor = monster.getColor();
	monsteroriginColor.a = 255;
	monsterblinkColor = monster.getColor();
	monsterblinkColor.a = 100;
	monster.setColor(monsteroriginColor);
	statusUI->UpdateHpUI();
}

void SceneBattle::Exit()
{
	Scene::Exit();

	btState = ButtonState::None;
}

void SceneBattle::Update(float dt)
{
	if (isPlaying)
	{
		Scene::Update(dt);
		if (!isPlaying)
			return;
		animator.Update(dt);

		if (isMonsterBlink)
			MonsterBlinkUpdate(dt);

		if (isMyTurn)
		{
			if (btState == ButtonState::None)
			{
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					SOUND_MGR.PlaySfx("sounds/snd_select.wav");
					switch (btIndex)
					{
					case 0:
						btState = ButtonState::ChooseFight;
						btBox->describeStr[0] = utf8_to_wstring(data["FightDescribe"]);
						break;
					case 1:
						btState = ButtonState::ChooseAct;
						actChooseIndex = 0;
						for (int i = 0; i < actChooseCount; ++i)
						{
							btBox->describeStr[i] = utf8_to_wstring(data["ActDescribe"][i]["act"]);
						}
						for (int i = actChooseCount; i < 4; ++i)
						{
							btBox->describeStr[i] = L"";
						}
						break;
					case 2:
						btState = ButtonState::ChooseItem;
						itemChooseIndex = 0;
						for (int i = 0; i < itemChooseCount; ++i)
						{
							std::wstring temp = InventoryUi::healItem[i].GetName();
							if (temp == L"")
							{
								btBox->describeStr[i] = L"== 비어 있음 ==";
							}
							else
							{
								btBox->describeStr[i] = temp;
								healAmount[i] = InventoryUi::healItem[i].GetHealAmount();
							}
						}
						break;
					case 3:
						btState = ButtonState::ChooseMercy;
						mercyChooseIndex = 0;
						btBox->describeStr[0] = L"* 살려주기";
						btBox->describeStr[2] = L"* 도망";
						break;
					}
					soul->SetPosition({ size.x * 0.05f, size.y * 0.57f });
					btBox->UpdateBox();
				}
				else
				{
					fightButton->UpdateTexture();
					actButton->UpdateTexture();
					itemButton->UpdateTexture();
					mercyButton->UpdateTexture();
				}
			}
		}
		else
		{
			dialTimer += dt;
			turnTimer += dt;
			if (dialTimer >= dialExistTime)
			{
				dialTimer = 0.f;
				dialBox->isDraw = false;
			}
			if (turnTimer >= turnDuration)
			{
				turnTimer = 0.f;
				SetPlayerTurn();
			}
		}
	}
	else if (isGameOver)
	{
		heartbreakTimer += dt;
		if (heartbreakTimer >= heartbreakTime)
		{
			isFadeIn = true;
			if (!isBreak)
			{
				isBreak = true;
				soul->SetTexture("graphics/spr_heartbreak_0.png");
				SOUND_MGR.PlaySfx("sounds/snd_break1_c.wav");
				SOUND_MGR.PlayBgm("sounds/11 Determination.flac");
			}
		}

		if (isFadeIn)
		{
			fadeTimer += dt;
			fadeIntervalTimer += dt;

			if (fadeIntervalTimer > fadeInterval)
			{
				fadeIntervalTimer = 0.f;
				float alpha = static_cast<float>(gameOverColor.a);
				alpha += 255.f * fadeInterval / fadeTime;
				gameOverColor.a = static_cast<sf::Uint8>(std::min(255.f, alpha));
				gameOver.setColor(gameOverColor);
			}

			if (fadeTimer >= fadeTime || gameOverColor.a == 255.f)
			{
				isDrawGameOverText = true;
				if (InputMgr::GetKeyDown(sf::Keyboard::Z))
				{
					isFadeIn = false;
					SCENE_MGR.ChangeScene(SceneIds::test);
				}
				fadeIntervalTimer = 0.f;
			}
		}
	}
	else
	{
		if (InputMgr::GetKeyDown(sf::Keyboard::Z))
		{
			SCENE_MGR.ChangeScene(nextSceneId);
		}
	}

	if (isMonsterShaking)
		MonsterShakeUpdate(dt);
}

void SceneBattle::Draw(sf::RenderWindow& window)
{
	if (!isGameOver)
	{
		if (data["name"] != "sans" && data["name"] != "papyrus")
			window.draw(background);
		window.draw(monster);
		Scene::Draw(window);
	}
	else
	{
		soul->Draw(window);
		window.draw(gameOver);
		if (isDrawGameOverText)
			window.draw(gameOverText);
	}
}

void SceneBattle::SetMonsterTurn()
{
	isMyTurn = false;
	isMonsterShaking = false;
	monsterShakeTimer = 0.f;
	monster.setPosition(monsterOriginalPos);
	btState = ButtonState::None;
	btBox->SetBtBoxSize({ size.x * 0.4f, size.y * 0.25f });
	soul->SetPosition({ size.x * 0.49f, size.y * 0.64f });
	soul->SetBoundary(btBox->GetBoxGlobalBounds());
	dialBox->isDraw = true;
	dialBox->SetString(data["lines"][lineIndex]);
	lineIndex = ++lineIndex % lineCount;

	//
	SetBulletPattern();	
}

void SceneBattle::SetPlayerTurn()
{
	isMyTurn = true;
	soul->CanMove = true;
	soul->isGravity = false;
	soul->SetTexture("graphics/spr_heart_battle_pl_0.png");
	soul->SetPosition({ size.x * 0.03f + size.x * 0.26f * btIndex, size.y * 0.93f });
	btBox->ResetBox();
	for (auto& b : bulletTemp)
	{
		RemoveGameObject(b);
	}
	bulletTemp.clear();
}

void SceneBattle::SetActDescribe()
{
	btBox->describeStr[0] = utf8_to_wstring(data["ActDescribe"][actChooseIndex]["describes"][0]["describe"]);
	btBox->describeStr[2] = utf8_to_wstring(data["ActDescribe"][actChooseIndex]["describes"][1]["describe"]);
	btBox->UpdateBox();
	
	mercyPoint += data["ActDescribe"][actChooseIndex]["mercyPoint"];
}

void SceneBattle::TryUseItem()
{
	if(InventoryUi::healItem[itemChooseIndex].GetName() != L"")
	{
		InventoryUi::healItem[itemChooseIndex].SetUse();
		PlayerInfo::hp = Utils::ClampInt(PlayerInfo::hp + healAmount[itemChooseIndex], 0, PlayerInfo::maxHp);
		healAmount[itemChooseIndex] = 0;
		statusUI->UpdateHpUI();
		SetMonsterTurn();
		SOUND_MGR.PlaySfx("sounds/snd_heal_c.wav");
	}
	else
	{
		SOUND_MGR.PlaySfx("sounds/snd_select.wav");
	}
}

void SceneBattle::TryMercy()
{
	if (mercyChooseIndex == 0 && mercyPoint >= mercyCanPoint)
	{
		isPlaying = false;
		isMyTurn = true;
		monster.setColor(monsterblinkColor);
		btState = ButtonState::None;
		int gold = data["gold"];
		btBox->startStr = L"* 승리! 0 XP와 " + std::to_wstring(gold) + L"G 를 얻었다.";
		btBox->SetStartDescribe();
		soul->SetPosition({ -100.f,-100.f });
		PlayerInfo::gold += gold;
		PlayerInfo::Moral += 1;
		SOUND_MGR.PlaySfx("sounds/snd_vaporized.wav");
		SOUND_MGR.StopBgm();
	}
	else if (mercyChooseIndex == 1)
	{		
		isPlaying = false;
		std::cout << "도망가기 실행" << std::endl;
		SOUND_MGR.PlaySfx("sounds/snd_escaped.wav");
		SOUND_MGR.StopBgm();
	}
	else
	{
		SOUND_MGR.PlaySfx("sounds/snd_select.wav");
	}
}

void SceneBattle::MonsterBlinkUpdate(float dt)
{
	monsterblinkTimer += dt;
	monsterblinkPeriodTimer += dt;
	if (monsterblinkTimer >= monsterblinkTime)
	{
		isMonsterBlink = false;
		monsterblinkTimer = 0.f;
		monsterblinkPeriodTimer = 0.f;
		monster.setColor(monsteroriginColor);
	}

	if (monsterblinkPeriodTimer >= monsterblinkPeriod)
	{
		if (monster.getColor() == monsteroriginColor)
			monster.setColor(monsterblinkColor);
		else
			monster.setColor(monsteroriginColor);
		monsterblinkPeriodTimer = 0.f;
	}
}

void SceneBattle::MonsterDie()
{
	isMyTurn = true;
	soul->SetPosition({ size.x * 0.03f + size.x * 0.26f * btIndex, size.y * 0.93f });
	int exp = data["exp"];
	int gold = data["gold"];
	btBox->startStr = L"* 승리! " + std::to_wstring(exp) + L" XP와 " + std::to_wstring(gold) + L"G 를 얻었다.";
	PlayerInfo::PlusExp(exp);
	PlayerInfo::gold += gold;
	PlayerInfo::Moral -= 1;
	statusUI->Reset();
	btBox->SetStartDescribe();
	btState = ButtonState::None;
	sf::Color color = monster.getColor();
	color.a = 100;
	monster.setColor(color);
	std::cout << "몬스터 사망" << std::endl;
	isPlaying = false;
	isMonsterShaking = false;
	monsterShakeTimer = 0.f;
	monster.setPosition(monsterOriginalPos);
	SOUND_MGR.StopBgm();
	SOUND_MGR.PlaySfx("sounds/snd_vaporized.wav");
}

void SceneBattle::PlayerDie()
{
	isMyTurn = true;
	btState = ButtonState::None;
	btBox->startStr = L"* 패배!";
	btBox->SetStartDescribe();
	for (auto& b : bulletTemp)
	{
		RemoveGameObject(b);
	}
	bulletTemp.clear();
	isPlaying = false;
	isGameOver = true;
	SOUND_MGR.StopBgm();
}

void SceneBattle::SetBulletPattern()
{
	int bulletCount = data["attackPattern"][PatternIndex]["bullets"].size();
	turnDuration = data["attackPattern"][PatternIndex]["duration"];
	if ("Normal" == data["attackPattern"][PatternIndex]["name"])
	{
		for (int i = 0; i < bulletCount; ++i)
		{
			Bullet* b = (Bullet*)AddGameObject(new Bullet());
			bulletTemp.push_back(b);
			b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
				{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
				{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
				data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
				data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
				data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
			);
			b->Reset();
			b->pattern = BulletPattern::Normal;
		}
	}
	else if ("Rotate" == data["attackPattern"][PatternIndex]["name"])
	{
		for (int i = 0; i < bulletCount; ++i)
		{
			Bullet* b = (Bullet*)AddGameObject(new Bullet());
			bulletTemp.push_back(b);
			b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
				{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
				{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
				data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
				data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
				data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
			);
			b->Reset();
			b->pattern = BulletPattern::Rotate;
		}
	}
	else if ("Homing" == data["attackPattern"][PatternIndex]["name"])
	{
		for (int i = 0; i < bulletCount; ++i)
		{
			Bullet* b = (Bullet*)AddGameObject(new Bullet());
			bulletTemp.push_back(b);
			b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
				{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
				{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
				data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
				data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
				data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
			);
			b->Reset();
			b->pattern = BulletPattern::Homing;
		}
	}
	else if ("Arrow" == data["attackPattern"][PatternIndex]["name"])
	{
		soul->CanMove = false;
		soul->SetTexture("graphics/spr_heart_green.png");
		for (int i = 0; i < bulletCount; ++i)
		{
			Bullet* b = (Bullet*)AddGameObject(new Bullet());
			bulletTemp.push_back(b);
			b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
				{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
				{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
				data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
				data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
				data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
			);
			b->Reset();
			b->pattern = BulletPattern::Arrow;
		}
	}
	else if ("Gravity" == data["attackPattern"][PatternIndex]["name"])
	{
		soul->isGravity = true;
		soul->SetTexture("graphics/spr_heart_blue.png");
		for (int i = 0; i < bulletCount; ++i)
		{
			Bullet* b = (Bullet*)AddGameObject(new Bullet());
			bulletTemp.push_back(b);
			b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
				{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
				{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
				data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
				data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
				data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
			);
			b->Reset();
			b->pattern = BulletPattern::Normal;
		}
	}
	else if ("Split" == data["attackPattern"][PatternIndex]["name"])
	{
		sf::Vector2f tempDir[8] = { { 1.0f,0.0f}, { 1.0f,1.0f}, { 0.0f,1.0f}, { -1.0f,1.0f}, { -1.0f,0.0f}, { -1.0f,-1.0f}, { 0.0f,-1.0f}, { 1.0f,-1.0f} };
		for (int i = 0; i < bulletCount; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				Bullet* b = (Bullet*)AddGameObject(new Bullet());
				b->splitDir = Utils::GetNormal(tempDir[j]);
				bulletTemp.push_back(b);
				b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
					{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
					{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
					data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
					data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
					data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
				);
				b->Reset();
				b->pattern = BulletPattern::Split;
			}
		}
	}
	else if ("Beam" == data["attackPattern"][PatternIndex]["name"])
	{
		for (int i = 0; i < bulletCount; ++i)
		{
			Bullet* b = (Bullet*)AddGameObject(new Bullet());
			bulletTemp.push_back(b);
			b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
				{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
				{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
				data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
				data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
				data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
			);
			b->aniId = data["attackPattern"][PatternIndex]["bullets"][i]["animationId"];
			b->Reset();
			b->pattern = BulletPattern::Beam;
		}
	}
	else if ("BeamHoming" == data["attackPattern"][PatternIndex]["name"])
	{
		for (int i = 0; i < bulletCount; ++i)
		{
			Bullet* b = (Bullet*)AddGameObject(new Bullet());
			bulletTemp.push_back(b);
			b->SetBulletState(data["attackPattern"][PatternIndex]["bullets"][i]["texId"],
				{ data["attackPattern"][PatternIndex]["bullets"][i]["PosX"], data["attackPattern"][PatternIndex]["bullets"][i]["PosY"] },
				{ data["attackPattern"][PatternIndex]["bullets"][i]["DirX"], data["attackPattern"][PatternIndex]["bullets"][i]["DirY"] },
				data["attackPattern"][PatternIndex]["bullets"][i]["speed"],
				data["attackPattern"][PatternIndex]["bullets"][i]["delay"],
				data["attackPattern"][PatternIndex]["bullets"][i]["damage"]
			);
			b->aniId = data["attackPattern"][PatternIndex]["bullets"][i]["animationId"];
			b->Reset();			
			b->pattern = BulletPattern::BeamHoming;
		}
	}

	PatternIndex = (PatternIndex + 1) % patternCount;
}

void SceneBattle::MonsterShakeUpdate(float dt)
{
	monsterShakeTimer += dt;
	float shakeOffset = 4.f;
	if (monsterShakeTimer >= monsterShakeInterval)
	{
		if (fmod(monsterShakeTimer, monsterShakeInterval * 2) < monsterShakeInterval)
		{
			monster.setPosition(monsterOriginalPos.x + shakeOffset, monsterOriginalPos.y);
		}
		else
		{
			monster.setPosition(monsterOriginalPos.x - shakeOffset, monsterOriginalPos.y);
		}
	}
}
