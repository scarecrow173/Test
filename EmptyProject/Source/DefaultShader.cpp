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
#include "TexturePool.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
DefaultShader::DefaultShader()
	:	m_hVelocityTechnique(NULL)
	,	m_hDiffuse		(NULL)
	,	m_hAmbient		(NULL)
	,	m_hSpecular		(NULL)
	,	m_hEmissive		(NULL)
	,	m_hPower		(NULL)
	,	m_hWorld		(NULL)
	,	m_hView			(NULL)
	,	m_hProjection	(NULL)
	,	m_hPrevWorld	(NULL)
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
	
	m_VelocityTextureObjectPtr = TexturePool::GetInstance()->GetResource("data:DefaultTexture - VelocityTexture");
	m_VelocityTexture		= RTTI_PTR_DYNAMIC_CAST(DefaultTexture, m_VelocityTextureObjectPtr.GetSharedObject());
	LPDIRECT3DTEXTURE9 tex;
	auto hr = D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
		1024, 
		1024,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFORMAT::D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&tex);

	IDirect3DSurface9 *pSurf;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface( &pSurf );
	D3DSURFACE_DESC Desc;
	pSurf->GetDesc( &Desc );
	SAFE_RELEASE(pSurf);
	
	hr = GraphicsManager::GetInstance()->GetD3DDevice()->CreateDepthStencilSurface(
		1024,
		1024,
		Desc.Format,
		Desc.MultiSampleType,
		Desc.MultiSampleQuality,
		FALSE,
		&m_VelocityDepthSurface,
		NULL
		);

	m_VelocityTexture->SetTexture(&tex);
	hr = tex->GetSurfaceLevel(0, &m_VelocitySurface);
	SAFE_RELEASE(tex);


	m_hVelocityTechnique = m_Effect->GetTechniqueByName("Velo");
	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("HalfLambert"));
	m_hDiffuse			= m_Effect->GetParameterByName(m_hDiffuse	, "g_Diffuse");
	m_hAmbient			= m_Effect->GetParameterByName(m_hAmbient	, "g_Ambient");
	m_hSpecular			= m_Effect->GetParameterByName(m_hSpecular	, "g_Specular");
	m_hEmissive			= m_Effect->GetParameterByName(m_hEmissive	, "g_Emissive");
	m_hPower			= m_Effect->GetParameterByName(m_hPower		, "g_Power");

	m_hWorld		= m_Effect->GetParameterByName(m_hWorld,		"g_World");
	m_hView			= m_Effect->GetParameterByName(m_hView,			"g_View");
	m_hProjection	= m_Effect->GetParameterByName(m_hProjection,	"g_Projection");
	m_hPrevWorld	= m_Effect->GetParameterByName(m_hPrevWorld,	"g_PrevWorld");

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
	IDirect3DSurface9* backbuffer				= NULL;
	IDirect3DSurface9* backbufferDepthSurface	= NULL;
	U32 maxPass = 0;
	m_Effect->Begin(&maxPass, 0);
	for (U32 iPass = 0; iPass < maxPass; ++iPass)
	{
		U32 matCount = 0;
		m_Effect->BeginPass(iPass);
		for (auto it = m_Renderer.begin(); it != m_Renderer.end(); ++it)
		{
			Material* material	= (*it)->GetMaterial();
			auto transform		= (*it)->GetTransform();
			Matrix world		= transform->GetTransform();
			m_Effect->SetMatrix(m_hWorld, &world);
			m_Effect->SetMatrix(m_hPrevWorld, &m_PrevMatrix[matCount]);

			m_Effect->SetFloatArray(m_hDiffuse, material->m_Diffuse.m, 4);
			m_Effect->SetFloatArray(m_hAmbient, material->m_Ambient.m, 4);
			m_Effect->SetFloatArray(m_hSpecular, material->m_Specular.m, 4);
			m_Effect->SetFloatArray(m_hEmissive, material->m_Emissive.m, 4);
			m_Effect->SetFloat(m_hPower, material->m_SpecularPower);
			m_Effect->CommitChanges();

			(*it)->Draw();
			m_PrevMatrix[matCount] = iPass != 0 ? world : m_PrevMatrix[matCount];
			++matCount;
		}
		m_Effect->EndPass();
	

		if (iPass == 0)
		{
			GraphicsManager::GetInstance()->GetD3DDevice()->GetRenderTarget(0, &backbuffer);
			GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface(&backbufferDepthSurface);

			GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, m_VelocitySurface);
			GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(m_VelocityDepthSurface);
			GraphicsManager::GetInstance()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0), 1.0f, 0 );
		}
	}

	m_Effect->End();
	//D3DXSaveSurfaceToFile(L"test.jpg", D3DXIFF_JPG, m_VelocitySurface, NULL, NULL);

	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, backbuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(backbufferDepthSurface);

	SAFE_RELEASE(backbuffer);
	SAFE_RELEASE(backbufferDepthSurface);
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