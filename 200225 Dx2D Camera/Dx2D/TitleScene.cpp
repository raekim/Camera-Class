#include "stdafx.h"
#include "TitleScene.h"


void TitleScene::Init()
{
	m_strTitle = "Any Key To Continue";
	m_fElapsedTime = 0.0f;
	m_isRender = true;
}

void TitleScene::Update()
{
	if (g_pKeyManager->isOnceKeyDown(VK_ESCAPE))
		PostQuitMessage(0);
	else if (g_pKeyManager->isOnceKeyDown(VK_RETURN))
		g_pSceneManager->Change(SCENE_KIND::Play);

	m_fElapsedTime += g_pTimeManager->GetDeltaTime();

	if (m_fElapsedTime >= 0.5f)
	{
		m_fElapsedTime = 0.0f;
		m_isRender = !m_isRender;
	}
}

void TitleScene::Render()
{
	if (m_isRender)
		g_pTextManager->AlphabetRender(m_strTitle.c_str(), HALFSIZEX - 280, HALFSIZEY, 50);
}

void TitleScene::Release()
{
}
