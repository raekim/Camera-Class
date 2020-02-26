#pragma once
#include "SingletonBase.h"

#define g_pCamera Camera::GetInstance()

class Camera : public SingletonBase<Camera>
{
#define MOVESPEED 500

private:
	ID3D11Buffer*		m_pViewProjBuffer;	// 뷰, 프로젝션 매트릭스 버퍼
	ViewProjectionDesc	m_stViewProjMatrix;

	D3DXVECTOR2			m_vTarget;
	D3DXVECTOR2			m_vFocus;
	D3DXVECTOR2			m_vMapSize;

	D3DXVECTOR3			m_vEye;
	D3DXVECTOR3			m_vLookAt;
	D3DXVECTOR3			m_vUp;

public:
	Camera();
	~Camera();

	void Init();
	void Update(D3DXVECTOR2* target = NULL);

	void SetFocus(D3DXVECTOR2 v) { m_vFocus = v; }
	void SetFocus(float x, float y) { SetFocus(D3DXVECTOR2(x, y)); }
	void SetMapSize(D3DXVECTOR2 v) { m_vMapSize = v; }
	ID3D11Buffer *const *GetViewProjBuffer() { return &m_pViewProjBuffer; }
};

