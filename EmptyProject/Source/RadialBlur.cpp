//=======================================================================================
//!	@file	:	RadialBlur.cpp
//!	@brief	:	RadialBlurクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "RadialBlur.h"
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
RadialBlur::RadialBlur()
	:	m_BlurringTextureObject	()
	,	m_BlurringTexture		(NULL)
	,	m_BlurringSurface		(NULL)
	,	m_BlurringDepthSurface	(NULL)
	,	m_hBlurPower			(NULL)
	,	m_hSamplingNum			(NULL)
	,	m_BlurringTextureWidth	(1024)	//	デフォルト値。変更するならInitilize前に
	,	m_BlurringTextureHeight	(1024)	//	今はとりあえずこのまま。
	,	m_BluerPower			(2.f)
	,	m_SamplingNum			(32)
{
	m_DrawStep = 20;

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
RadialBlur::~RadialBlur()
{
	SAFE_DELETE(m_Renderer[0]);
	m_Renderer.erase(m_Renderer.begin());

	SAFE_RELEASE(m_BlurringDepthSurface);
	SAFE_RELEASE(m_BlurringSurface);

}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool RadialBlur::Initilize()
{	
	WindowPolygonRenderer* wpr = NEW WindowPolygonRenderer();
	wpr->Initialize();
	wpr->CreatePolygon();

	AddRenderer(wpr);

	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("Blur"));
	m_hBlurPower	= m_Effect->GetParameterByName(m_hBlurPower, "g_BlurPower");
	m_hSamplingNum	= m_Effect->GetParameterByName(m_hSamplingNum, "g_SamplingNum");
	
	m_Effect->SetFloat(m_hBlurPower, m_BluerPower);
	m_Effect->SetInt(m_hSamplingNum, m_SamplingNum);


	m_BlurringTextureObject = TexturePool::GetInstance()->GetResource("data:DefaultTexture - BlurringTexture");
	m_BlurringTexture		= RTTI_PTR_DYNAMIC_CAST(DefaultTexture, m_BlurringTextureObject.GetSharedObject());
	LPDIRECT3DTEXTURE9 tex;
	auto hr = D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
		m_BlurringTextureWidth, 
		m_BlurringTextureHeight,
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
		m_BlurringTextureWidth,
		m_BlurringTextureHeight,
		Desc.Format,
		Desc.MultiSampleType,
		Desc.MultiSampleQuality,
		FALSE,
		&m_BlurringDepthSurface,
		NULL
		);

	m_BlurringTexture->SetTexture(&tex);
	hr = tex->GetSurfaceLevel(0, &m_BlurringSurface);
	SAFE_RELEASE(tex);
	if(FAILED(hr))
		return false;

	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void RadialBlur::Draw()
{
	assert(m_BlurringTexture->GetTexture());
	static F32 time = 0.f;
	time += 0.4f;
	SetBlurPower((0.5f - cos(Math::PI * 2.f * time * 0.002f) * 0.5f ) * 100.0f);

	IDirect3DSurface9* backbuffer				= NULL;
	IDirect3DSurface9* backbufferDepthSurface	= NULL;

	GraphicsManager::GetInstance()->GetD3DDevice()->GetRenderTarget(0, &backbuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface(&backbufferDepthSurface);
	
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
	SAFE_RELEASE(backbuffer);
	SAFE_RELEASE(backbufferDepthSurface);

}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: example
//-------------------------------------------------------------
void RadialBlur::SetShaderTechniqueByName(const std::string& techniqueName)
{
	if (FAILED( m_Effect->SetTechnique(m_Effect->GetTechniqueByName(techniqueName.c_str()))))
		assert(0);
}
//-------------------------------------------------------------
//!	@brief		: 放射ブラーをかけるテクスチャに描画するシェーダオブジェクトを追加
//!	@param[in]	: 
//-------------------------------------------------------------
void RadialBlur::AddBlurringTarget(IShaderObject* obj)
{
	auto it = std::find(m_AffectedShaders.begin(), m_AffectedShaders.end(), obj);
	
	if (it == m_AffectedShaders.end())
	{
		m_AffectedShaders.push_back(obj);
		std::sort(m_AffectedShaders.begin(), m_AffectedShaders.end(), std::greater<IShaderObject*>());
	}
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
void RadialBlur::SetBlurPower(const F32 power)
{
	m_BluerPower = power;
	m_Effect->SetFloat(m_hBlurPower, m_BluerPower);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
F32	RadialBlur::GetBlurPower() const
{
	return m_BluerPower;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
void RadialBlur::SetSamplingNum(const S32 sampling)
{
	m_SamplingNum = sampling;
	m_Effect->SetInt(m_hSamplingNum, m_SamplingNum);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
S32	RadialBlur::GetSamplingNum() const
{
	return m_SamplingNum;
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