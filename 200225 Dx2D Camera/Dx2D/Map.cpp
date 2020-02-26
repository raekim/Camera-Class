#include "stdafx.h"
#include "Map.h"
#include "Player.h"


Map::Map()
{
	g_pTextureManager->AddTexture(L"Back00", L"2DMountain.png");

	m_pBackground = new Sprite(L"Back00");
	m_pBackground->SetSize(2, 2);
	m_pBackground->SetLBPosition(0, 0);
	m_pBackground->Update();
	m_fGroundY = 130;

	g_pCamera->SetMapSize(D3DXVECTOR2(m_pBackground->GetWidth(), m_pBackground->GetHeight()));
}


Map::~Map()
{
	SAFE_DELETE(m_pBackground);
}

void Map::Render()
{
	m_pBackground->Render();
}