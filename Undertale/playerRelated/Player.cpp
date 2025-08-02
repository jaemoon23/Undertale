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
	SOUNDBUFFER_MGR.Load("sounds/Map2/15 sans..flac");
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

	if (spin)
	{
		animator.Play("Animation/Player_Spin.csv");
		spin = false;
	}
	else if (event)
	{
		animator.Play("Animation/idle.csv");
		event = false;
	}

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
			if (dialoguebox && dialoguebox->GetActive())
				dialoguebox->SetActive(false);
			else if (inventoryui && inventoryui->GetActive())
				inventoryui->SetActive(false);
			else if (playerInfoUi && playerInfoUi->GetActive())
				playerInfoUi->SetActive(false);
			else if (uichanger && uichanger->GetActive())
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
	{ 
		L"* 인 간.  ",
		L"* 오랜만에 새로 들어왔군.", 
		L"* 돌아서서 나와 악수해."
	};
	dialoguebox->StartDialogue(testDialogues);
}

void Player::SansSecondsInteract()
{
	std::vector<std::wstring> testDialogues =
	{
		L"* 난 샌즈야.\n* 뼈다귀 샌즈.",
		L"* 원래 인간들을 감시하는\n  일을 해야 하는데.",
		L"* 누구 잡는 일은 딱히\n  신경 안써서.",
		L"* 근데 내 동생인, 파피루스는...",
		L"* 걔는 인간 사냥에\n  미친놈이야.",
		L"* 보안관이 되는게 꿈이거든.",
		L"* 그래도 너무 걱정하지마.\n  말만 그렇게 하거든.",
		L"* 혹시 마주치면 좀 봐줘.\n  아이스크림 줄게."
	};
	InventoryUi::healItem[0].SetInfo(L"아이스", 15);
	PlayerInfo::slot++;
	dialoguebox->StartDialogue(testDialogues);
}

void Player::PapyrusInteract()
{
	std::vector<std::wstring> testDialogues =
	{
	L"* 너는 인간이군!",
	L"* 드디어 내 첫 임무가 주어졌어!",
	L"* 위대한 파피루스님이 직접\n* 너를 체포하겠다!",
	L"* 하지만 먼저 테스트가 필요하지.",
	L"* 나의 특별한 퍼즐을 풀어봐!",
	L"* ...어라? 아직 준비가 안 됐네.",
	L"* 그럼 이 위대한 파피루스님의\n* 말을 잘 들어!",
	L"* 내 멋짐은 누구도 따라올 수 없지!",
	L"* 내 형 샌즈는 게으르지만...",
	L"* 나는 절대 쉬지 않고 정의를 실현한다!",
	L"* 준비되면 나에게 다시 말을 걸어라!",
	L"* 그때가 너와 나의\n* 운명적인 결투의 순간이 될 테니!"
	};
	dialoguebox->StartDialogue(testDialogues);
}

void Player::PapyrusBattleEndInteract()
{
	std::vector<std::wstring> testDialogues =
	{
		L"* 믿을 수 없어...",
		L"* 내가... 졌다니...",
		L"* 인간, 너는 생각보다 훨씬 강하군.",
		L"* 하지만... 이걸로 끝난 게 아니야.",
		L"* 진짜 마지막 시험이 남아있지.",
		L"* 사실, 지금까지 너를 지켜본 자가 있어.",
		L"* 바로... 내 형, 샌즈야.",
		L"* 샌즈는 평소엔 농담만 하고 게으르지만...",
		L"* 그 녀석... 진심을 숨기고 있어.",
		L"* 네가 여기까지 온다면...\n* 반드시 마주치게 될 거야.",
		L"* 그리고 그때...\n* 진짜 싸움이 시작될 거야.",
		L"* 조심해, 인간.",
		L"* 샌즈는 나와는 다르게...",
		L"* 진심일지도 모르니까."
	};
	dialoguebox->StartDialogue(testDialogues);
}

void Player::PapyrusMercyInteract()
{
	std::vector<std::wstring> testDialogues =
	{
		L"* ...뭐지?",
		L"* 왜 공격하지 않았지?",
		L"* 분명히 이길 수 있었을 텐데...",
		L"* 인간.",
		L"* 네가 보여준 건...",
		L"* 진짜 강함이었어.",
		L"* 나를 쓰러뜨리는 대신...",
		L"* 나를 이해하려고 했구나.",
		L"* 감동이야... 정말로.",
		L"* 이런 기분은 처음이야.",
		L"* 내 마음이...\n* 스파게티처럼 따뜻해지고 있어!",
		L"* 이제 난 너를...",
		L"* 친구라고 부를 수 있을 것 같아!",
		L"* 고마워 친구!",
	};
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
