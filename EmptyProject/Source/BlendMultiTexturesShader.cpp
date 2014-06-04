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
{
	m_DrawStep = 50000;

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/RadialBlur.fx",
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

	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("Blur"));

	//IDirect3DSurface9 *pSurf;
	//GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface( &pSurf );
	//D3DSURFACE_DESC Desc;
	//pSurf->GetDesc( &Desc );
	//SAFE_RELEASE(pSurf);
	//
	//auto hr = GraphicsManager::GetInstance()->GetD3DDevice()->CreateDepthStencilSurface(
	//	m_BlurringTextureWidth,
	//	m_BlurringTextureHeight,
	//	Desc.Format,
	//	Desc.MultiSampleType,
	//	Desc.MultiSampleQuality,
	//	FALSE,
	//	&m_BlurringDepthSurface,
	//	NULL
	//	);

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
	GraphicsManager::GetInstance()->GetD3DDevice();

	const U32 TextureNum	= m_BlendTextures.size();
	const U32 divisionNum	= 5;
	for (U32 i = 0; i < TextureNum; ++i)
	{
		GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(i % divisionNum, m_BlendTextures[i]);
		if (i % (divisionNum - 1) == 0)
		{
		}
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