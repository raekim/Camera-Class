#include "stdafx.h"
#include "MainGame.h"


MainGame::MainGame()
{
	srand(time(NULL));
	SetBlendStates();
	CreateGameClasses();
	this->Init();
}

void MainGame::SetBlendStates()
{
	D3D11_BLEND_DESC desc = { 0, };

	desc.RenderTarget[0].BlendEnable = false;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	Device->CreateBlendState(&desc, &m_pNormalBlendState);

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	Device->CreateBlendState(&desc, &m_pAlphaBlendState);
}

MainGame::~MainGame()
{
	DeleteGameClasses();

	SAFE_RELEASE(m_pNormalBlendState);
	SAFE_RELEASE(m_pAlphaBlendState);
}

void MainGame::CreateGameClasses()
{
	// 클래스 생성
	m_pMap = new Map;
	m_pPlayer = new Player;
}

void MainGame::DeleteGameClasses()
{
	SAFE_DELETE(m_pMap);
	SAFE_DELETE(m_pPlayer);
}

void MainGame::Init()
{
	if (m_pPlayer)
		m_pPlayer->Init(m_pMap->GetGroundY());
}

void MainGame::Update()
{
	if (m_pPlayer)
		m_pPlayer->Update();

	m_vTarget = (g_pKeyManager->isToggleKey(VK_F8)) ? m_pPlayer->GetPosition() : NULL;
	g_pCamera->Update(m_vTarget);
}

void MainGame::Render()
{
	D3DXCOLOR Map = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)Map);
	DeviceContext->VSSetConstantBuffers(0, 1, g_pCamera->GetViewProjBuffer());

	DeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);

	if (m_pMap)
		m_pMap->Render();

	if (m_pPlayer)
		m_pPlayer->Render();

	DeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF);
	ImGui::Render();

	SwapChain->Present(0, 0);
}