//=======================================================================================
//!	@file	:	PhongShader.cpp
//!	@brief	:	PhongShaderクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "PhongShader.h"
#include "GraphicsManager.h"
#include "Material.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
PhongShader::PhongShader()
	:	m_hMaterial		(NULL)
	,	m_hWorld		(NULL)
	,	m_hView			(NULL)
	,	m_hProjection	(NULL)
{
	//ZeroMemory(m_FadeColor.m, sizeof(float) * 3);
	m_DrawStep = 0;

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/Phong.fx",
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
	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("Phong"));
	m_hMaterial		= m_Effect->GetParameterByName(m_hMaterial,		"g_Material");
	m_hWorld		= m_Effect->GetParameterByName(m_hWorld,		"g_World");
	m_hView			= m_Effect->GetParameterByName(m_hView,			"g_View");
	m_hProjection	= m_Effect->GetParameterByName(m_hProjection,	"g_Projection");

	//m_hFadeColor = m_Effect->GetParameterByName(m_hFadeColor, "g_FadeColor");

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
PhongShader::~PhongShader()
{
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool PhongShader::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void PhongShader::Draw()
{
	//m_Effect->SetFloat(m_hFadeValue, m_FadeValue);
	//m_Effect->SetFloatArray(m_hFadeColor , m_FadeColor.m, 3)
	auto view	= GraphicsManager::GetInstance()->GetView();
	auto proj	= GraphicsManager::GetInstance()->GetProjection();
	m_Effect->SetMatrix(m_hView, &view);
	m_Effect->SetMatrix(m_hProjection, &proj);
	U32 maxPass = 0;
	m_Effect->Begin(&maxPass, 0);
	for (U32 iPass = 0; iPass < maxPass; ++iPass)
	{
		m_Effect->BeginPass(iPass);
		for (auto it = m_Renderer.begin(); it != m_Renderer.end(); ++it)
		{
			Material* material = (*it)->GetMaterial();
			auto transform = (*it)->GetTransform();
			Matrix world	= transform->GetTransform();
			auto scale = transform->GetScaling();
			Matrix mamat;
			D3DXMatrixScaling(&mamat, scale.x, scale.y, scale.z);
			//D3DXMatrixTranspose(&world,&world);
			D3DXMatrixIdentity(&world);
			D3DXMatrixMultiply(&world, &world, &mamat);
			//D3DXMatrixTranspose(&world, &world);
			//D3DXMatrixTranspose(&view, &view);
			//D3DXMatrixTranspose(&proj, &proj);
			m_Effect->SetMatrix(m_hWorld, &world);

			m_Effect->SetValue(m_hMaterial, material, sizeof(Material));
			(*it)->Draw();
			Matrix mat;
			m_Effect->GetMatrix(m_hWorld, &mat);
		}
		m_Effect->EndPass();
	}

	m_Effect->End();
}
////-------------------------------------------------------------
////!	@brief		: example
////!	@param[in]	: example
////!	@return		: example
////-------------------------------------------------------------
//F32	PhongShader::GetFadeValue() const
//{
//	return m_FadeValue;
//}
////-------------------------------------------------------------
////!	@brief		: example
////!	@param[in]	: example
////!	@return		: example
////-------------------------------------------------------------
//VertexFloat3 PhongShader::GetFadeColor() const
//{
//	return m_FadeColor;
//}
////-------------------------------------------------------------
////!	@brief		: example
////!	@param[in]	: example
////!	@return		: example
////-------------------------------------------------------------
//void PhongShader::SetFadeValue(const F32 alpha)
//{
//	m_FadeValue = alpha;
//}
////-------------------------------------------------------------
////!	@brief		: example
////!	@param[in]	: example
////!	@return		: example
////-------------------------------------------------------------
//void PhongShader::SetFadeColor(const VertexFloat3& color)
//{
//	m_FadeColor = color;
//}
////-------------------------------------------------------------
////!	@brief		: example
////!	@param[in]	: example
////!	@return		: example
////-------------------------------------------------------------
//void	Reset()
//{}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================