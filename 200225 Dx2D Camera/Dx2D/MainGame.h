#pragma once
#include "iGameNode.h"
#include "Player.h"
#include "Map.h"


class MainGame : public iGameNode
{
private:
	ID3D11BlendState*	m_pNormalBlendState;	// 기본 블렌드 옵션
	ID3D11BlendState*	m_pAlphaBlendState;		// 반투명 블렌드 옵션
	void SetBlendStates();	// 옵션별 블렌드 상태값 생성

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

