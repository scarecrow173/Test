//=======================================================================================
//!	@file	:	BlurFilter.cpp
//!	@brief	:	BlurFilterクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "BlurFilter.h"
#include "GraphicsManager.h"
#include "Material.h"
#include "TexturePool.h"
#include "WindowPolygonRenderer.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
LPD3DXSPRITE g_sprite = NULL;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BlurFilter::BlurFilter()
//	:	
{
	D3DXCreateSprite( GraphicsManager::GetInstance()->GetD3DDevice() , &g_sprite );

	//ZeroMemory(m_FadeColor.m, sizeof(float) * 3);
	m_DrawStep = 20;

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/BlurFilter.fx",
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
BlurFilter::~BlurFilter()
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
bool BlurFilter::Initilize()
{	
	WindowPolygonRenderer* wpr = NEW WindowPolygonRenderer();
	wpr->Initialize();
	wpr->CreatePolygon();

	AddRenderer(wpr);

	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("Blur"));
	m_BlurringTextureObject = TexturePool::GetInstance()->GetResource("data:DefaultTexture - BlurringTexture");
	m_BlurringTexture		= RTTI_PTR_DYNAMIC_CAST(DefaultTexture, m_BlurringTextureObject.GetSharedObject());
	LPDIRECT3DTEXTURE9 tex;
	auto hr = D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
		1024,1024,
		1,
		D3DUSAGE_RENDERTARGET,
		D3DFORMAT::D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		&tex);

	IDirect3DSurface9 *pSurf;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface( &pSurf );
	D3DSURFACE_DESC Desc;
	pSurf->GetDesc( &Desc );
	pSurf->Release();
	hr = GraphicsManager::GetInstance()->GetD3DDevice()->CreateDepthStencilSurface(
		1024, 1024,
		Desc.Format,
		Desc.MultiSampleType,
		Desc.MultiSampleQuality,
		FALSE,
		&m_BlurringDepthSurface,
		NULL
		);

	m_BlurringTexture->SetTexture(&tex);
	hr = tex->GetSurfaceLevel(0, &m_BlurringSurface);
	if(FAILED(hr))
		return false;

	//GraphicsManager::GetInstance()->GetD3DDevice()->CreateTexture(4,4,1,0, D3DFMT_A16B16G16R16F, D3DPOOL_MANAGED, 
	//m_hDiffuse			= m_Effect->GetParameterByName(m_hDiffuse	, "g_Diffuse");
	//m_hAmbient			= m_Effect->GetParameterByName(m_hAmbient	, "g_Ambient");
	//m_hSpecular			= m_Effect->GetParameterByName(m_hSpecular	, "g_Specular");
	//m_hEmissive			= m_Effect->GetParameterByName(m_hEmissive	, "g_Emissive");
	//m_hPower			= m_Effect->GetParameterByName(m_hPower		, "g_Power");

	//m_hWorld		= m_Effect->GetParameterByName(m_hWorld,		"g_World");
	//m_hView			= m_Effect->GetParameterByName(m_hView,			"g_View");
	//m_hProjection	= m_Effect->GetParameterByName(m_hProjection,	"g_Projection");

	//const Matrix view	= GraphicsManager::GetInstance()->GetView();
	//const Matrix proj	= GraphicsManager::GetInstance()->GetProjection();
	//m_Effect->SetMatrix(m_hView, &view);
	//m_Effect->SetMatrix(m_hProjection, &proj);
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlurFilter::Draw()
{
	assert(m_BlurringTexture->GetTexture());
	IDirect3DSurface9* backbuffer = NULL;
	IDirect3DSurface9* backbufferDepthSurface = NULL;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetRenderTarget(0, &backbuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface(&backbufferDepthSurface);
	auto hr = GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, m_BlurringSurface);
	hr = GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(m_BlurringDepthSurface);
	GraphicsManager::GetInstance()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0), 1.0f, 0 );
	

	for (auto it = m_AffectedShaders.begin(); it != m_AffectedShaders.end(); ++it)
	{
		(*it)->Draw();
	}
	//if (FAILED( hr))
	//D3DXSaveSurfaceToFile(L"test.jpg", D3DXIFF_JPG, m_BlurringSurface, NULL, NULL);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, backbuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(backbufferDepthSurface);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(0, m_BlurringTexture->GetTexture());

	GraphicsManager::GetInstance()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 1.0f, 0 );

	m_Effect->CommitChanges();

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
//	D3DXSaveSurfaceToFile(L"test.jpg", D3DXIFF_JPG, m_BlurringSurface, NULL, NULL);

	//g_sprite->Begin(0);
	//g_sprite->Draw(m_BlurringTexture->GetTexture(), NULL,NULL,NULL,NULL);
	//g_sprite->End();
}
//-------------------------------------------------------------
//!	@brief		: シェーダテクニックを入れ替える(Phong,BlinnPhong,CookTorrance,Lambert,HalfLambert)
//!	@param[in]	: テクニック名(変な名前が入るとアサート)
//!	@return		: example
//-------------------------------------------------------------
void BlurFilter::SetShaderTechniqueByName(const std::string& techniqueName)
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