#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	// �� ��Ʈ���� ����
	m_vEye = D3DXVECTOR3(0, 0, -1);
	m_vLookAt = D3DXVECTOR3(0, 0, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixLookAtLH(&m_stViewProjMatrix.View, &m_vEye, &m_vLookAt, &m_vUp);
	D3DXMatrixTranspose(&m_stViewProjMatrix.View, &m_stViewProjMatrix.View);
	// ���̴����� ��Ʈ������ ��� ���� ������ �ٲ��ֱ� ������ Ʈ������� ���־�� �Ѵ�.

	// �������� ��Ʈ���� ����
	D3DXMatrixOrthoOffCenterLH(&m_stViewProjMatrix.Projection, 0, (float)WINSIZEX, 0, (float)WINSIZEY, -1, 1);
	D3DXMatrixTranspose(&m_stViewProjMatrix.Projection, &m_stViewProjMatrix.Projection);

	// ���� ����
	D3D11_BUFFER_DESC desc = { 0, };
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(ViewProjectionDesc);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// ���ۿ� ���� ������
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
	m_vFocus = D3DXVECTOR2(0, 0);
}

void Camera::Update(D3DXVECTOR2* target)
{
	// ī�޶� ��ġ ������ ���� ���� ����
	static float time = 0;
	static D3DXVECTOR2 from;
	static float focusTime = 1.0f; // �� �ʿ� ���� ī�޶� ���� ��ȯ�� �� ���ΰ�
	ImGui::SliderFloat("focusTime", &focusTime, 1, 10);

	if (g_pKeyManager->isOnceKeyDown(VK_F8))
	{
		from = m_vTarget;
		time = 0;
	}
	
	if (target)
	{
		// ĳ���� �̵����� ī�޶� ����
		if (time/focusTime <= 1)
		{
			// ������ ����Ͽ� ī�޶� ������ ĳ���ͷ� �ε巴�� ��ȯ
			m_vTarget = LinearInterpolation(from, (*target - m_vFocus), time / focusTime);
			time += g_pTimeManager->GetDeltaTime();
		}
		else
		{
			m_vTarget = *target - m_vFocus;
		}
	}
	else
	{
		// ���콺 �̵����� ī�޶� ����
		if (g_ptMouse.x >= WINSIZEX)
			m_vTarget.x += MOVESPEED * g_pTimeManager->GetDeltaTime();
		else if (g_ptMouse.x <= 0)
			m_vTarget.x -= MOVESPEED * g_pTimeManager->GetDeltaTime();

		if (g_ptMouse.y >= WINSIZEY)
			m_vTarget.y += MOVESPEED * g_pTimeManager->GetDeltaTime();
		else if (g_ptMouse.y <= 0)
			m_vTarget.y -= MOVESPEED * g_pTimeManager->GetDeltaTime();
	}

	// ī�޶� ��ǥ�� �� ũ�⸦ ���� ���ϰ� clamp
	if (m_vTarget.x < 0)
		m_vTarget.x = 0;
	else if (m_vTarget.x > m_vMapSize.x - WINSIZEX)
		m_vTarget.x = m_vMapSize.x - WINSIZEX;

	if (m_vTarget.y < 0)
		m_vTarget.y = 0;
	else if (m_vTarget.y > m_vMapSize.y - WINSIZEY)
		m_vTarget.y = m_vMapSize.y - WINSIZEY;

	// �� ��Ʈ���� ����
	m_vEye = D3DXVECTOR3(m_vTarget.x, m_vTarget.y, -1);
	m_vLookAt = D3DXVECTOR3(m_vTarget.x, m_vTarget.y, 0);
	m_vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMatrixLookAtLH(&m_stViewProjMatrix.View, &m_vEye, &m_vLookAt, &m_vUp);
	D3DXMatrixTranspose(&m_stViewProjMatrix.View, &m_stViewProjMatrix.View);

	DeviceContext->UpdateSubresource(m_pViewProjBuffer, 0, 0, &m_stViewProjMatrix, 0, 0);
}
