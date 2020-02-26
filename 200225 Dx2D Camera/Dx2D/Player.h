#pragma once

class Player
{
	enum STATE
	{
		READY = -1,
		IDLE,
		RUN,
		JUMPUP,
		JUMPDOWN,
		DIE,
		MAX
	};

private:
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR3			m_vRotaion;

	Animation<STATE>*	m_pAnimation;
	STATE				m_eState;

	float				m_fMoveSpeed;

	float				m_fGroundY;
	bool				m_isJumping;
	float				m_fJumpPower;
	float				m_fElapsedGravity;

public:
	Player();
	~Player();

	void Init(float groundY);
	void Update();
	void Render();

	D3DXVECTOR2* GetPosition() { return &m_vPosition; }
};

