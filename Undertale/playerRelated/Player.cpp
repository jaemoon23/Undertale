#include "stdafx.h"
#include "Player.h"
#include "Sans.h"
#include "DialogueBox.h"
#include "UiChanger.h"
#include "InventoryUi.h"
#include "PlayerInfoUi.h"
#include "HealItem.h"

Player::Player(const std::string& name)
	: GameObject(name)
{
}

void Player::SetPosition(const sf::Vector2f& pos)
{	
	GameObject::SetPosition(pos);
	body.setPosition(pos);
	blackBackground.setPosition(pos);
	soul.setPosition(pos + sf::Vector2f(0.f,6.f));
	battleSymbol.setPosition(pos + sf::Vector2f(0.f, -21.f));
}

void Player::SetRotation(float rot)
{	
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Player::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Player::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Player::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
		Utils::SetOrigin(soul, preset);
		Utils::SetOrigin(battleSymbol, preset);
	}
}

void Player::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	animator.SetTarget(&body);
}

void Player::Release()
{
}

void Player::Reset()
{	
	SOUNDBUFFER_MGR.Load("sounds/snd_b.wav");
	SOUNDBUFFER_MGR.Load("sounds/snd_noise.wav");
	SOUNDBUFFER_MGR.Load("sounds/snd_battlefall.wav");
	TEXTURE_MGR.Load("graphics/spr_word!.png");
	TEXTURE_MGR.Load("graphics/spr_heartsmall_0.png");
	battleSymbol.setTexture(TEXTURE_MGR.Get("graphics/spr_word!.png"));
	soul.setTexture(TEXTURE_MGR.Get("graphics/spr_heartsmall_0.png"));
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
	body.setTexture(TEXTURE_MGR.Get(texId));
	animator.Play("Animation/idle.csv");
	direction = { 0.f, 0.f };
	
	SetOrigin(Origins::MC);

	//
	isBattleEnter = false;
	isDrawSymbol = false;
	isDrawSoul = false;
	isSoulMove = false;
	isSansMap = false;
	timer = 0.f;
	soulBlinkTimer = 0.f;
	blackBackground.setSize({ 640.f,480.f });
	blackBackground.setFillColor(sf::Color::Black);
	blackBackground.setPosition(body.getPosition());
	Utils::SetOrigin(blackBackground, Origins::MC);
	scene = SCENE_MGR.GetCurrentScene();
	//
}

void Player::Update(float dt)
{
	// 배틀 입장 연출
	if (isBattleEnter)
	{
		timer += dt;
		if (isSoulMove)
		{
			sf::Vector2f pos = soul.getPosition();
			pos += Utils::GetNormal(destVec) * Utils::Magnitude(destVec) / soulMoveTime * dt;
			soul.setPosition(pos);

			if (timer >= soulMoveTime)
			{
				timer = 0.f;
				isSoulMove = false;
				SCENE_MGR.ChangeScene(SceneIds::Battle);
			}
		}
		else if (timer >= symbolExistTime)
		{			
			isDrawSymbol = false;
			soulBlinkTimer += dt;
			if (timer <= symbolExistTime + soulBlinkTime)
			{
				if (soulBlinkTimer >= 0.07f)
				{
					soulBlinkTimer = 0.f;
					isDrawSoul = !isDrawSoul;
					if (isDrawSoul)
						SOUND_MGR.PlaySfx("sounds/snd_noise.wav");
				}
			}
			else
			{
				destVec = scene->ScreenToWorld({25,455}) - soul.getPosition();				
				isSoulMove = true;
				isDrawSoul = true;
				timer = 0.f;
				soulBlinkTimer = 0.f;
				SOUND_MGR.PlaySfx("sounds/snd_battlefall.wav");
			}
		}
	}
	else
	{
		animator.Update(dt);
		prevPosition = GetPosition();

		if (InputMgr::GetKeyDown(sf::Keyboard::X))
		{
			dialoguebox->SetActive(false);
			inventoryui->SetActive(false);
			playerInfoUi->SetActive(false);
			uichanger->SetActive(false);
		}

		if (uichanger && uichanger->GetActive()) return; // UI 변경 중에는 플레이어 이동 불가
		if (dialoguebox && dialoguebox->GetActive()) return; // 대화 중에는 플레이어 이동 불가

		if (move)
		{
			direction.x = InputMgr::GetAxis(Axis::Horizontal);
			direction.y = InputMgr::GetAxis(Axis::Vertical);
			if (isSansMap)
				direction.y = 0;
			SetPosition(GetPosition() + direction * speed * dt);
			hitBox.UpdateTransform(body, body.getLocalBounds());

			std::string currentClipPath = animator.currentClipPath;
			if (direction.x == 0 && direction.y == 0)
			{
				animator.Stop();
			}
			else if (std::abs(direction.x) > std::abs(direction.y))
			{
				if (direction.x > 0 && currentClipPath != "Animation/rightwalking.csv")
				{
					animator.Play("Animation/rightwalking.csv");
				}
				else if (direction.x < 0 && currentClipPath != "Animation/leftwalking.csv")
				{
					animator.Play("Animation/leftwalking.csv");
				}
			}
			else
			{
				if (direction.y > 0 && currentClipPath != "Animation/downwalking.csv")
				{
					animator.Play("Animation/downwalking.csv");
				}
				else if (direction.y < 0 && currentClipPath != "Animation/upwalking.csv")
				{
					animator.Play("Animation/upwalking.csv");
				}
			}
		}
	}		

}

void Player::Draw(sf::RenderWindow& window)
{
	if (isBattleEnter)
	{		
		window.draw(blackBackground);
	}
	window.draw(body);
	if(isDrawSymbol)
		window.draw(battleSymbol);
	if(isDrawSoul)
		window.draw(soul);
	hitBox.Draw(window);
}

void Player::SansInteract()
{
	std::vector<std::wstring> testDialogues =
	{ L"* 인간.  ", L"* 새로운 친구와 사귀는 법을 모르는건가?", L"* 돌아서서 나와 악수해."};
	dialoguebox->StartDialogue(testDialogues);
}

void Player::SansSecondsInteract()
{
	std::vector<std::wstring> testDialogues =
	{ L"* 난 샌즈야.\n* 뼈다귀 샌즈.",
		L"* 원래 인간들을 감시하는\n* 일을 해야 하는데.",
		L"* 내 동생인 파피루스에게 맡겨놨어.",
		L"* 나가고 싶다면 저 밖의 파피루스와\n* 싸워서 이겨야 할거야.",
		L"* 자 이걸 받아.\n* 파피루스와 싸울 때 도움이 될거야",
	L"* 회복아이템: 아이스크림을 받았습니다!",
	L"* 인벤토리를 확인해봐.\n* C키를 누르면 인벤토리를\n* 확인할 수 있을거야.",
	L"* 행운을 빌어.\n* 다시 만나지는 않기를 바랄게."};
	InventoryUi::healItem[0].SetInfo(L"아이스크림", 15);
	dialoguebox->StartDialogue(testDialogues);
}

const sf::RectangleShape& Player::GetHitBox() const
{
	return hitBox.rect;
}

void Player::SetMove(bool a)
{
	move = a;
	if (!a) direction = sf::Vector2f(0.f, 0.f);
}

void Player::StartBattle()
{
	isDrawSymbol = true;
	isBattleEnter = true;
	SOUND_MGR.PlaySfx("sounds/snd_b.wav");
}
