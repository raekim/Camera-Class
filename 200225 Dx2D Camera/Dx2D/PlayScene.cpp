#include "stdafx.h"
#include "PlayScene.h"


void PlayScene::Init()
{
	// 클래스 생성
	m_pMap = new Map;
	m_pPlayer = new Player;

	if (m_pPlayer)
		m_pPlayer->Init(m_pMap->GetGroundY());
}

void PlayScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		g_pSceneManager->Change(SCENE_KIND::Title);

	if (m_pPlayer)
		m_pPlayer->Update();

	m_vTarget = (g_pKeyManager->isToggleKey(VK_F8)) ? m_pPlayer->GetPosition() : NULL;
	g_pCamera->Update(m_vTarget);
}

void PlayScene::Render()
{
	if (m_pMap)
		m_pMap->Render();

	if (m_pPlayer)
		m_pPlayer->Render();
}

void PlayScene::Release()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pPlayer);
}
