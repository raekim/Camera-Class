#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	// 뷰 매트릭스 셋팅
	m_vEye = D3DXVECTOR3(0, 0, -1);
	m_vLookAt = D3DXVECTOR3(0, 0, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixLookAtLH(&m_stViewProjMatrix.View, &m_vEye, &m_vLookAt, &m_vUp);
	D3DXMatrixTranspose(&m_stViewProjMatrix.View, &m_stViewProjMatrix.View);
	// 셰이더에서 매트릭스의 행과 열의 방향이 바껴있기 때문에 트랜스포즈를 해주어야 한다.

	// 프로젝션 매트릭스 셋팅
	D3DXMatrixOrthoOffCenterLH(&m_stViewProjMatrix.Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
	D3DXMatrixTranspose(&m_stViewProjMatrix.Projection, &m_stViewProjMatrix.Projection);

	// 버퍼 생성
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 버퍼에 담을 데이터
	D3D11_SUBRESOURCE_DATA data = { 0, };
	data.pSysMem = &m_stViewProjMatrix;

	HRESULT hr = Device->CreateBuffer(&desc, &data, &m_pViewProjBuffer);
}


Camera::~Camera()
{
	SAFE_RELEASE(m_pViewProjBuffer);
}

void Camera::Init()
{
	m_vFocus = D3DXVECTOR2(HALFSIZEX, HALFSIZEY);
	m_vTarget = D3DXVECTOR2(0, 0);

	m_vMapSize.x = WINSIZEX;
	m_vMapSize.y = WINSIZEY;
}

void Camera::Update(D3DXVECTOR2* target)
{
	if (g_pKeyManager->isStayKeyDown(VK_LEFT))
		m_vTarget.x -= MOVESPEED * g_pTimeManager->GetDeltaTime();
	else if (g_pKeyManager->isStayKeyDown(VK_RIGHT))
		m_vTarget.x += MOVESPEED * g_pTimeManager->GetDeltaTime();

	if (g_pKeyManager->isStayKeyDown(VK_DOWN))
		m_vTarget.y -= MOVESPEED * g_pTimeManager->GetDeltaTime();
	else if (g_pKeyManager->isStayKeyDown(VK_UP))
		m_vTarget.y += MOVESPEED * g_pTimeManager->GetDeltaTime();

	if (target)
	{
		m_vTarget = *target - m_vFocus;
	}

	if (m_vTarget.x <= 0)
		m_vTarget.x = 0;
	else if (m_vTarget.x > m_vMapSize.x - WINSIZEX)
		m_vTarget.x = m_vMapSize.x - WINSIZEX;

	if (m_vTarget.y <= 0)
		m_vTarget.y = 0;
	else if (m_vTarget.y > m_vMapSize.y - WINSIZEY)
		m_vTarget.y = m_vMapSize.y - WINSIZEY;

	// 뷰 매트릭스 셋팅
	m_vEye = D3DXVECTOR3(m_vTarget.x, m_vTarget.y, -1);
	m_vLookAt = D3DXVECTOR3(m_vTarget.x, m_vTarget.y, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixLookAtLH(&m_stViewProjMatrix.View, &m_vEye, &m_vLookAt, &m_vUp);
	D3DXMatrixTranspose(&m_stViewProjMatrix.View, &m_stViewProjMatrix.View);

	DeviceContext->UpdateSubresource(m_pViewProjBuffer, 0, 0, &m_stViewProjMatrix, 0, 0);
}
