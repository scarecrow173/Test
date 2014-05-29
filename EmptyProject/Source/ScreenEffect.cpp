//=======================================================================================
//!	@file	:	ScreenEffect.cpp
//!	@brief	:	ScreenEffectクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "ScreenEffect.h"
#include "GraphicsManager.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
ScreenEffect::ScreenEffect()
	:	m_FadeValue		(0.f)
	,	m_hFadeValue	(NULL)
	,	m_hFadeColor	(NULL)
{
	ZeroMemory(m_FadeColor.m, sizeof(float) * 3);
	m_DrawStep = 10;

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/ScreenEffect.fx",
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&m_Effect,
		&wError);
	if (FAILED(hr))
	{
		::MessageBoxA( NULL, (LPCSTR)wError->GetBufferPointer(), "Error", MB_OK );	// 失敗の原因を表示
		wError->Release();
	}
	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("Fade"));
	m_hFadeValue = m_Effect->GetParameterByName(m_hFadeValue, "g_FadeValue");
	m_hFadeColor = m_Effect->GetParameterByName(m_hFadeColor, "g_FadeColor");

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
ScreenEffect::~ScreenEffect()
{
	m_hFadeValue = NULL;
	m_hFadeColor = NULL;
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool ScreenEffect::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void ScreenEffect::Draw()
{
	m_Effect->SetFloat(m_hFadeValue, m_FadeValue);
	m_Effect->SetFloatArray(m_hFadeColor , m_FadeColor.m, 3);

	U32 maxPass = 0;
	m_Effect->Begin(&maxPass, 0);
	for (U32 iPass = 0; iPass < maxPass; ++iPass)
	{
		m_Effect->BeginPass(iPass);
		for (auto it = m_Renderer.begin(); it != m_Renderer.end(); ++it)
		{
			(*it)->Draw();
		}
		m_Effect->EndPass();
	}
	m_Effect->End();
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
F32	ScreenEffect::GetFadeValue() const
{
	return m_FadeValue;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
VertexFloat3 ScreenEffect::GetFadeColor() const
{
	return m_FadeColor;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void ScreenEffect::SetFadeValue(const F32 alpha)
{
	m_FadeValue = alpha;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void ScreenEffect::SetFadeColor(const VertexFloat3& color)
{
	m_FadeColor = color;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void	Reset()
{}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================