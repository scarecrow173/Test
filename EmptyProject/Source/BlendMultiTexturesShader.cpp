//=======================================================================================
//!	@file	:	RadialBlur.cpp
//!	@brief	:	RadialBlurクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "BlendMultiTexturesShader.h"
#include "GraphicsManager.h"
#include "Material.h"
#include "TexturePool.h"
#include "WindowPolygonRenderer.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BlendMultiTexturesShader::BlendMultiTexturesShader()
	:	m_BackBuffer				(NULL)
	,	m_FinalOutPutTextureRefPtr	(NULL)
	,	m_FinalOutPutTextureRef		(NULL)
	,	m_FinalOutPutSurface		(NULL)
	,	m_hBlendTextureNum			(NULL)
{
	m_DrawStep = 50000;

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/BlendMultiTextures.fx",
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
BlendMultiTexturesShader::~BlendMultiTexturesShader()
{
	SAFE_DELETE(m_Renderer[0]);
	m_Renderer.erase(m_Renderer.begin());
	SAFE_RELEASE(m_BackBuffer);
	SAFE_RELEASE(m_FinalOutPutSurface);
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool BlendMultiTexturesShader::Initilize()
{	
	WindowPolygonRenderer* wpr = NEW WindowPolygonRenderer();
	wpr->Initialize();
	wpr->CreatePolygon();

	AddRenderer(wpr);

	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("BlendMultiTexture"));

	m_hBlendTextureNum = m_Effect->GetParameterByName(m_hBlendTextureNum, "BlendTextureNum");
	
	m_FinalOutPutTextureRefPtr = AK::Graphics::TexturePool::GetInstance()->GetResource("data:DefaultTexture - bmt");
	m_FinalOutPutTextureRef = RTTI_PTR_DYNAMIC_CAST(DefaultTexture, m_FinalOutPutTextureRefPtr.GetSharedObject());
	if (m_FinalOutPutTextureRef->GetTexture() == NULL)
	{
		LPDIRECT3DTEXTURE9 tex;
		D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
			1024, 
			1024,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFORMAT::D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			&tex);
		m_FinalOutPutTextureRef->SetTexture(&tex);
	}
	m_FinalOutPutTextureRef->GetTexture()->GetSurfaceLevel(0, &m_FinalOutPutSurface);
	m_FinalOutPutTextureRef->GetTexture()->Release();

	IDirect3DSurface9 *pSurf;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface( &pSurf );
	D3DSURFACE_DESC Desc;
	pSurf->GetDesc( &Desc );
	SAFE_RELEASE(pSurf);
	
	auto hr = GraphicsManager::GetInstance()->GetD3DDevice()->CreateDepthStencilSurface(
		1024,
		1024,
		Desc.Format,
		Desc.MultiSampleType,
		Desc.MultiSampleQuality,
		FALSE,
		&m_DefaultRenderTargetDepthSurface,
		NULL
		);

	//if(FAILED(hr))
	//	return false;

	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlendMultiTexturesShader::Draw()
{
	IDirect3DSurface9* backBuffer		= NULL;
	IDirect3DSurface9* backBufferDepth	= NULL;


	GraphicsManager::GetInstance()->GetD3DDevice()->GetRenderTarget(0, &backBuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface(&backBufferDepth);
	
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, m_FinalOutPutSurface);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(m_DefaultRenderTargetDepthSurface);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(0, m_FinalOutPutTextureRef->GetTexture());
	GraphicsManager::GetInstance()->GetD3DDevice()->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0), 1.0f, 0 );

	const U32 TextureNum	= m_BlendTextures.size();
	const U32 divisionNum	= 5;
	
	U32 maxPass = 0;
	S32 drawTextureNum = 0;

	m_Effect->Begin(&maxPass, 0);
	m_Effect->BeginPass(0);
	for (U32 i = 0; i < TextureNum; ++i)
	{
		drawTextureNum = (i % divisionNum) + 1;
		GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(drawTextureNum, m_BlendTextures[i]);
		if ((i + 1) % divisionNum == 0)
		{
			m_Effect->SetInt(m_hBlendTextureNum, drawTextureNum);
			m_Effect->CommitChanges();
			m_Renderer[0]->Draw();
		}
	}
	if (drawTextureNum != 0)
	{
		m_Effect->SetInt(m_hBlendTextureNum, drawTextureNum);
		m_Effect->CommitChanges();
		m_Renderer[0]->Draw();
	}
	m_Effect->EndPass();
	m_Effect->End();
	//D3DXSaveSurfaceToFile(L"test.jpg", D3DXIFF_JPG, m_FinalOutPutSurface, NULL, NULL);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderTarget(0, backBuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetDepthStencilSurface(backBufferDepth);

	SAFE_RELEASE(backBuffer);
	SAFE_RELEASE(backBufferDepth);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlendMultiTexturesShader::SetBackBuffer(IDirect3DSurface9** backbuffer)
{
	SAFE_RELEASE(m_BackBuffer);
	m_BackBuffer = *backbuffer;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlendMultiTexturesShader::AddBlendTexture(IDirect3DTexture9** blendtex)
{
	auto it = std::find(m_BlendTextures.begin(),m_BlendTextures.end(), *blendtex);

	if (it == m_BlendTextures.end())
		m_BlendTextures.push_back(*blendtex);
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