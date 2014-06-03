//=======================================================================================
//!	@file	:	DefaultShader.cpp
//!	@brief	:	DefaultShaderクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "DefaultShader.h"
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
DefaultShader::DefaultShader()
	:	m_hDiffuse		(NULL)
	,	m_hAmbient		(NULL)
	,	m_hSpecular		(NULL)
	,	m_hEmissive		(NULL)
	,	m_hPower		(NULL)
	,	m_hWorld		(NULL)
	,	m_hView			(NULL)
	,	m_hProjection	(NULL)
{
	//ZeroMemory(m_FadeColor.m, sizeof(float) * 3);
	m_DrawStep = 0;

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/DefaultShaderPackage.fx",
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

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
DefaultShader::~DefaultShader()
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
bool DefaultShader::Initilize()
{	
	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("HalfLambert"));
	m_hDiffuse			= m_Effect->GetParameterByName(m_hDiffuse	, "g_Diffuse");
	m_hAmbient			= m_Effect->GetParameterByName(m_hAmbient	, "g_Ambient");
	m_hSpecular			= m_Effect->GetParameterByName(m_hSpecular	, "g_Specular");
	m_hEmissive			= m_Effect->GetParameterByName(m_hEmissive	, "g_Emissive");
	m_hPower			= m_Effect->GetParameterByName(m_hPower		, "g_Power");

	m_hWorld		= m_Effect->GetParameterByName(m_hWorld,		"g_World");
	m_hView			= m_Effect->GetParameterByName(m_hView,			"g_View");
	m_hProjection	= m_Effect->GetParameterByName(m_hProjection,	"g_Projection");

	const Matrix view	= GraphicsManager::GetInstance()->GetView();
	const Matrix proj	= GraphicsManager::GetInstance()->GetProjection();
	m_Effect->SetMatrix(m_hView, &view);
	m_Effect->SetMatrix(m_hProjection, &proj);
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void DefaultShader::Draw()
{
	U32 maxPass = 0;
	m_Effect->Begin(&maxPass, 0);
	for (U32 iPass = 0; iPass < maxPass; ++iPass)
	{
		m_Effect->BeginPass(iPass);
		for (auto it = m_Renderer.begin(); it != m_Renderer.end(); ++it)
		{
			Material* material	= (*it)->GetMaterial();
			auto transform		= (*it)->GetTransform();
			Matrix world		= transform->GetTransform();
			m_Effect->SetMatrix(m_hWorld, &world);

			m_Effect->SetFloatArray(m_hDiffuse, material->m_Diffuse.m, 4);
			m_Effect->SetFloatArray(m_hAmbient, material->m_Ambient.m, 4);
			m_Effect->SetFloatArray(m_hSpecular, material->m_Specular.m, 4);
			m_Effect->SetFloatArray(m_hEmissive, material->m_Emissive.m, 4);
			m_Effect->SetFloat(m_hPower, material->m_SpecularPower);
			m_Effect->CommitChanges();

			(*it)->Draw();
		}
		m_Effect->EndPass();
	}

	m_Effect->End();
}
//-------------------------------------------------------------
//!	@brief		: シェーダテクニックを入れ替える(Phong,BlinnPhong,CookTorrance,Lambert,HalfLambert)
//!	@param[in]	: テクニック名(変な名前が入るとアサート)
//!	@return		: example
//-------------------------------------------------------------
void DefaultShader::SetShaderTechniqueByName(const std::string& techniqueName)
{
	if (FAILED( m_Effect->SetTechnique(m_Effect->GetTechniqueByName(techniqueName.c_str()))))
		assert(0);
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================