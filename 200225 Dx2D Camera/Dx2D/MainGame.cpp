#include "stdafx.h"
#include "MainGame.h"
#include "TitleScene.h"
#include "PlayScene.h"


MainGame::MainGame()
{
	srand(time(NULL));
	SetBlendStates();

	// 사용할 씬 목록 추가
	g_pSceneManager->AddScene(SCENE_KIND::Title, new TitleScene);
	g_pSceneManager->AddScene(SCENE_KIND::Play, new PlayScene);

	g_pSceneManager->Change(SCENE_KIND::Title);
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
	SAFE_RELEASE(m_pNormalBlendState);
	SAFE_RELEASE(m_pAlphaBlendState);
}

void MainGame::Update()
{
	g_pSceneManager->Update();
}

void MainGame::Render()
{
	D3DXCOLOR Map = D3DXCOLOR(0, 0, 0, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)Map);
	DeviceContext->VSSetConstantBuffers(0, 1, g_pCamera->GetViewProjBuffer());

	DeviceContext->OMSetBlendState(m_pAlphaBlendState, NULL, 0xFF);

	g_pSceneManager->Render();

	DeviceContext->OMSetBlendState(m_pNormalBlendState, NULL, 0xFF);
	ImGui::Render();

	SwapChain->Present(0, 0);
}