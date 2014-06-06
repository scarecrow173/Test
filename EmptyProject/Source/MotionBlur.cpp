//=======================================================================================
//!	@file	:	MotionBlur.cpp
//!	@brief	:	MotionBlurクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "MotionBlur.h"
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
MotionBlur::MotionBlur()
	:	m_BlurringTextureObjectPtr	(NULL)
	,	m_VelocityMapObjectPtr		(NULL)
	,	m_BlurringTexture			(NULL)
	,	m_VelocityMap				(NULL)
	,	m_BlurringSurface			(NULL)
	,	m_VelocitySurface			(NULL)
	,	m_BlurringDepthSurface		(NULL)
	,	m_hPrevWorld				(NULL)
	,	m_PostProcessingRenderer	(NULL)
	,	m_WriteTextureSize			(1024)
{
	m_DrawStep = 50;

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/MotionBlur.fx",
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
MotionBlur::~MotionBlur()
{
	SAFE_DELETE(m_PostProcessingRenderer);
	m_Renderer.erase(m_Renderer.begin());


	SAFE_RELEASE(m_BlurringDepthSurface);
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool MotionBlur::Initilize()
{	
	m_PostProcessingRenderer = NEW WindowPolygonRenderer();
	m_PostProcessingRenderer->Initialize();
	m_PostProcessingRenderer->CreatePolygon();

	AddRenderer(m_PostProcessingRenderer);

	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("Tec3_FinalCheckZ"));
	

	m_VelocityMapObjectPtr = TexturePool::GetInstance()->GetResource("data:DefaultTexture - VelocityTexture");
	m_VelocityMap		= RTTI_PTR_DYNAMIC_CAST(DefaultTexture, m_VelocityMapObjectPtr.GetSharedObject());
	if (m_VelocityMap->GetTexture() == NULL)
	{
		LPDIRECT3DTEXTURE9 tex;
		D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
			m_WriteTextureSize, 
			m_WriteTextureSize,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFORMAT::D3DFMT_A32B32G32R32F,
			D3DPOOL_DEFAULT,
			&tex);
		m_VelocityMap->SetTexture(&tex);
	}
	m_VelocityMap->GetTexture()->GetSurfaceLevel(0, &m_VelocitySurface);
	m_VelocityMap->GetTexture()->Release();


	m_BlurringTextureObjectPtr = TexturePool::GetInstance()->GetResource("data:DefaultTexture - MotionBlurRenderTarget");
	m_BlurringTexture		= RTTI_PTR_DYNAMIC_CAST(DefaultTexture, m_BlurringTextureObjectPtr.GetSharedObject());
	if (m_BlurringTexture->GetTexture() == NULL)
	{
		LPDIRECT3DTEXTURE9 tex;
		D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
			m_WriteTextureSize, 
			m_WriteTextureSize,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFORMAT::D3DFMT_A32B32G32R32F,
			D3DPOOL_DEFAULT,
			&tex);
		m_BlurringTexture->SetTexture(&tex);
	}
	m_BlurringTexture->GetTexture()->GetSurfaceLevel(0, &m_BlurringSurface);
	m_BlurringTexture->GetTexture()->Release();

	//"data:DefaultTexture - BlurringTexture"
	IDirect3DSurface9 *pSurf;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface( &pSurf );
	D3DSURFACE_DESC Desc;
	pSurf->GetDesc( &Desc );
	SAFE_RELEASE(pSurf);
	
	auto hr = GraphicsManager::GetInstance()->GetD3DDevice()->CreateDepthStencilSurface(
		m_WriteTextureSize,
		m_WriteTextureSize,
		Desc.Format,
		Desc.MultiSampleType,
		Desc.MultiSampleQuality,
		FALSE,
		&m_BlurringDepthSurface,
		NULL
		);


	if(FAILED(hr))
		return false;

	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MotionBlur::Draw()
{
	//assert(m_BlurringTexture->GetTexture());

	IDirect3DSurface9* backbuffer = NULL;
	IDirect3DSurface9* backbufferDepthSurface = NULL;

	GraphicsManager::GetInstance()->GetD3DDevice()->GetRenderTarget(0, &backbuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface(&backbufferDepthSurface);
	//
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, m_BlurringSurface);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(m_BlurringDepthSurface);

	GraphicsManager::GetInstance()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0), 1.0f, 0 );
	

	for (auto it = m_AffectedShaders.begin(); it != m_AffectedShaders.end(); ++it)
	{
		if ((*it)->IsActive())
			(*it)->Draw();
	}
	//if (FAILED( hr))
	//D3DXSaveSurfaceToFile(L"test.jpg", D3DXIFF_JPG, m_BlurringSurface, NULL, NULL);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, backbuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(backbufferDepthSurface);

	GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(0, m_BlurringTexture->GetTexture());
	GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(1, m_VelocityMap->GetTexture());

	GraphicsManager::GetInstance()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 1.0f, 0 );

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

	SAFE_RELEASE(backbuffer);
	SAFE_RELEASE(backbufferDepthSurface);

}
//-------------------------------------------------------------
//!	@brief		: 放射ブラーをかけるテクスチャに描画するシェーダオブジェクトを追加
//!	@param[in]	: 
//-------------------------------------------------------------
void MotionBlur::AddBlurringTarget(IShaderObject* obj)
{
	auto it = std::find(m_AffectedShaders.begin(), m_AffectedShaders.end(), obj);
	
	if (it == m_AffectedShaders.end())
	{
		m_AffectedShaders.push_back(obj);
	//	std::sort(m_AffectedShaders.begin(), m_AffectedShaders.end(), std::greater<IShaderObject*>());
	}
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