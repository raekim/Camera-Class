#include "stdafx.h"
#include "Player.h"


Player::Player()
{
	g_pTextureManager->AddTexture(L"PlayerIdle", L"Player/Idle.png");
	g_pTextureManager->AddTexture(L"PlayerRun", L"Player/Run.png");
	g_pTextureManager->AddTexture(L"PlayerJumpUp", L"Player/Jump_Start.png");
	g_pTextureManager->AddTexture(L"PlayerJumpDown", L"Player/Jump_Down_Start.png");

	m_pAnimation = new Animation<STATE>;

	// 대기 동작 추가
	Clip* clip = new Clip;
	for (int i = 0; i < 20; i++)
	{
		Sprite* sprite = new Sprite(L"PlayerIdle", 10, 2, i);
		clip->AddFrame(sprite, 1 / 20.0f);
	}
	m_pAnimation->AddClip(IDLE, clip);

	// 달리기 동작 추가
	clip = new Clip;
	for (int i = 0; i < 20; i++)
	{
		Sprite* sprite = new Sprite(L"PlayerRun", 10, 2, i);
		clip->AddFrame(sprite, 1 / 20.0f);
	}
	m_pAnimation->AddClip(RUN, clip);
	
	// 점프 업 동작 추가
	clip = new Clip;
	for (int i = 0; i < 11; i++)
	{
		Sprite* sprite = new Sprite(L"PlayerJumpUp", 11, 1, i);
		clip->AddFrame(sprite, 1 / 11.0f);
	}
	m_pAnimation->AddClip(JUMPUP, clip);
	
	// 점프 다운 동작 추가
	clip = new Clip;
	for (int i = 0; i < 6; i++)
	{
		Sprite* sprite = new Sprite(L"PlayerJumpDown", 6, 1, i);
		clip->AddFrame(sprite, 1 / 6.0f);
	}
	m_pAnimation->AddClip(JUMPDOWN, clip);
}

Player::~Player()
{
	SAFE_DELETE(m_pAnimation);
}

void Player::Init(float groundY)
{
	m_eState = IDLE;
	m_pAnimation->Play(m_eState);
	m_pAnimation->SetScale(0.5f, 0.5f);

	m_vPosition = D3DXVECTOR2(HALFSIZEX, groundY);
	g_pCamera->SetFocus(m_vPosition);
	m_vRotaion = D3DXVECTOR3(0, 0, 0);

	m_fMoveSpeed = 300.0f;
	m_fGroundY = groundY;
	m_isJumping = false;
	m_fJumpPower = 450.0f;
}

void Player::Update()
{
	if (g_pKeyManager->isStayKeyDown('A'))
	{
		m_vPosition.x -= m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
		m_vRotaion.y = D3DX_PI;
		m_eState = RUN;
	}
	else if (g_pKeyManager->isStayKeyDown('D'))
	{	
		m_vPosition.x += m_fMoveSpeed * g_pTimeManager->GetDeltaTime();
		m_vRotaion.y = 0;
		m_eState = RUN;
	}
	else
	{
		m_eState = IDLE;
	}

	if (g_pKeyManager->isOnceKeyDown(VK_SPACE) && m_isJumping == false)
	{
		m_isJumping = true;
		m_fElapsedGravity = 0.0f;
	}

	if (m_isJumping)
	{
		m_vPosition.y += (m_fJumpPower - m_fElapsedGravity) * g_pTimeManager->GetDeltaTime();
		m_fElapsedGravity += GRAVITY * g_pTimeManager->GetDeltaTime();

		// 위로 올라갈 때
		if (m_fJumpPower > m_fElapsedGravity)
		{
			m_eState = JUMPUP;
		}
		else // 아래로 떨어질 때
		{
			m_eState = JUMPDOWN;
		}

		if (m_vPosition.y <= m_fGroundY)
		{
			m_vPosition.y = m_fGroundY;
			m_isJumping = false;
			m_fElapsedGravity = 0.0f;
		}
	}

	m_pAnimation->SetPosition(m_vPosition.x, m_vPosition.y + m_pAnimation->GetHeight() * 0.5f);
	m_pAnimation->SetRotation(m_vRotaion.x, m_vRotaion.y, m_vRotaion.z);
	m_pAnimation->Play(m_eState);
	m_pAnimation->Update();
}

void Player::Render()
{
	if (m_pAnimation)
		m_pAnimation->Render();
}
