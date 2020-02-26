#pragma once
#include "iGameNode.h"
#include "Player.h"
#include "Map.h"


class MainGame : public iGameNode
{
private:
	ID3D11BlendState*	m_pNormalBlendState;	// �⺻ ���� �ɼ�
	ID3D11BlendState*	m_pAlphaBlendState;		// ������ ���� �ɼ�
	void SetBlendStates();	// �ɼǺ� ���� ���°� ����

private:
	Map*			m_pMap;
	Player*			m_pPlayer;
	D3DXVECTOR2*	m_vTarget;

public:
	MainGame();
	~MainGame();

	void CreateGameClasses();
	void DeleteGameClasses();
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
};

