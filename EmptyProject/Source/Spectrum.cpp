//=======================================================================================
//!	@file	:	Spectrum.cpp
//!	@brief	:	Spectrumクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "Spectrum.h"
#include "Elements.h"
#include "MyMath.h"
using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
//D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Spectrum::Spectrum()
	:	m_VertexBuffer	(NULL)
	,	m_IndexBuffer	(NULL)
	,	m_Effect		(NULL)
	,	m_Texture		(NULL)
	,	m_FVF			(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
{
	m_FVF=D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
}	
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Spectrum::~Spectrum()
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
void Spectrum::CreateSpectrumData()
{

	D3DXCreateTextureFromFile(DXUTGetD3D9Device(), L"Assets/Texture/spectrum.png", &m_Texture);

	//std::vector<U32> index;
	
	const U32 windowWidth	= WINDOW_WIDTH + 150;
	const U32 windowHeight	= WINDOW_HEIGHT;
	const F32 sideOffset	= 0.0f;
	const F32 topOffset		= 0.1f;
	const F32 margin		= 0.001f;
	const U32 divisionNum	= 64;
	const U32 vertexNum		= divisionNum * 4;// * 64;
	const F32 onePanelSizeX	= (1.f - (sideOffset * 2.f)) / (F32)divisionNum;

	for (U32 i = 0; i < vertexNum; i += 4)
	{
		SpectrumVertex Spectrum[4];

		Spectrum[0].x	= (sideOffset + (onePanelSizeX * (i / 4)) + (margin * 0.5f)) * windowWidth;
		Spectrum[0].y	= (topOffset) * windowHeight;
		Spectrum[0].z	= 0.f;
		Spectrum[0].w	= 1.f;
		Spectrum[0].u	= 0;//(0.f + 0.5f) / (float)windowWidth;//0.f;
		Spectrum[0].v	= 0;//(0.f + 0.5f) / (float)windowHeight;//1.f;
		Spectrum[0].color	= 0x00FF0000;

		Spectrum[1].x	= (sideOffset + (onePanelSizeX * ((i / 4) + 1) - (margin * 0.5f))) * windowWidth;
		Spectrum[1].y	= (topOffset) * windowHeight;
		Spectrum[1].z	= 0.f;
		Spectrum[1].w	= 1.f;
		Spectrum[1].u	= 1;//(1.f + 0.5f) / (float)windowWidth;
		Spectrum[1].v	= 0;//(0.f + 0.5f) / (float)windowHeight;//1.f;
		Spectrum[1].color	= 0x00FF0000;

		Spectrum[2].x	= (sideOffset + (onePanelSizeX * (i / 4)) + (margin * 0.5f)) * windowWidth;
		Spectrum[2].y	= 0.98f * windowHeight;
		Spectrum[2].z	= 0.f;
		Spectrum[2].w	= 1.f;
		Spectrum[2].u	= 0;//(0.f + 0.5f) / (float)windowWidth;//0.f;
		Spectrum[2].v	= 1;//(1.f + 0.5f) / (float)windowHeight;//0.f;
		Spectrum[2].color	= 0x0000FF00;

		Spectrum[3].x	= (sideOffset + (onePanelSizeX * ((i / 4) + 1) - (margin * 0.5f))) * windowWidth;
		Spectrum[3].y	= 0.98f * windowHeight;
		Spectrum[3].z	= 0.f;
		Spectrum[3].w	= 1.f;
		Spectrum[3].u	= 0;//(1.f + 0.5f) / (float)windowWidth;//1.f;
		Spectrum[3].v	= 0;//(1.f + 0.5f) / (float)windowHeight;//0.f;
		Spectrum[3].color	= 0x0000FF00;

		m_Vertex.push_back(Spectrum[0]);
		m_Vertex.push_back(Spectrum[1]);
		m_Vertex.push_back(Spectrum[2]);
		m_Vertex.push_back(Spectrum[3]);

		m_Index.push_back(i + 0);
		m_Index.push_back(i + 1);
		m_Index.push_back(i + 2);

		m_Index.push_back(i + 3);
		m_Index.push_back(i + 2);
		m_Index.push_back(i + 1);
	}

	if (FAILED(DXUTGetD3D9Device()->CreateVertexBuffer(
		sizeof(SpectrumVertex) * m_Vertex.size(), 
		D3DUSAGE_WRITEONLY, 
		m_FVF, 
		D3DPOOL_MANAGED,
		&m_VertexBuffer,
		0)))
		return;

	if (FAILED(DXUTGetD3D9Device()->CreateIndexBuffer(
		sizeof(SpectrumVertex) * m_Vertex.size(), 
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_IndexBuffer,
		0)))
		return;

	SpectrumVertex* data;


	m_VertexBuffer->Lock(0, NULL, (void**)&data, 0);
	memcpy(data, &m_Vertex[0], sizeof(SpectrumVertex) * m_Vertex.size());
	m_VertexBuffer->Unlock();

	U32* IData;
	m_IndexBuffer->Lock(0, 0, (void**)&IData, 0);
	memcpy(IData, &m_Index[0], sizeof(U32) * m_Index.size());
	m_IndexBuffer->Unlock();

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		DXUTGetD3D9Device(),
		L"Source/Spectrum.fx",
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
	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("Spectrum"));
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Spectrum::Draw()
{

	LPDIRECT3DVERTEXBUFFER9 oldBuf;
	UINT oldNum = 0;
	UINT oldStride = 0;
	DXUTGetD3D9Device()->GetStreamSource(0, &oldBuf, &oldNum, &oldStride);
	LPDIRECT3DINDEXBUFFER9 oldIndexBuf;
	DXUTGetD3D9Device()->GetIndices(&oldIndexBuf);

	LPDIRECT3DVERTEXDECLARATION9 olddel;
	DXUTGetD3D9Device()->GetVertexDeclaration(&olddel);
	DXUTGetD3D9Device()->SetVertexDeclaration(NULL);

	//DXUTGetD3D9Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	m_Effect->Begin(0,0);
	m_Effect->BeginPass(0);
	DXUTGetD3D9Device()->SetStreamSource(0, m_VertexBuffer, 0, sizeof(SpectrumVertex));
	DXUTGetD3D9Device()->SetFVF(m_FVF);
	DXUTGetD3D9Device()->SetIndices(m_IndexBuffer);
	DXUTGetD3D9Device()->SetTexture(0, m_Texture);
	//DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	//DXUTGetD3D9Device()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	DXUTGetD3D9Device()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_Vertex.size(), 0, m_Index.size() / 3);
	//DXUTGetD3D9Device()->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 64*2);

	DXUTGetD3D9Device()->SetTexture(0, NULL);

	DXUTGetD3D9Device()->SetFVF(NULL);
	DXUTGetD3D9Device()->SetStreamSource(0, oldBuf, oldNum, oldStride);
	DXUTGetD3D9Device()->SetIndices(oldIndexBuf);
	DXUTGetD3D9Device()->SetVertexDeclaration(olddel);
	m_Effect->EndPass();
	m_Effect->End();
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Spectrum::Update(F32* data, U32 size)
{

	const U32 div = size / 64;
	F32 FData[64];
	for (U32 i = 0; i < 64; ++i)
	{
		FData[i] = 0.f;
		F32 center;
		for (U32 j = 0; j < div; ++j)
			FData[i] = FData[i] < data[(div * i) + j] ? data[(div * i) + j] : FData[i];

	}
	for (U32 i = 0; i < m_Vertex.size(); i += 4)
	{
		m_Vertex[i].y = m_Vertex[i+1].y = FData[i/4];
		m_Vertex[i].v = m_Vertex[i+1].v = m_Vertex[i+1].y / 480;
		//static const DWORD src = 0x0000FF00;
		//static const DWORD dst = 0x00FF0000;
		////FData[i/4] + WINDOW_HEIGHT;
		//Math::LinearInterpolation(&m_Vertex[i].color, src, dst, 1.f - (FData[i/4] / WINDOW_HEIGHT));
		//m_Vertex[i + 1].color = m_Vertex[i].color;
	}

	m_VertexBuffer->Lock(0, NULL, (void**)&data, 0);
	memcpy(data, &m_Vertex[0], sizeof(SpectrumVertex) * m_Vertex.size());
	m_VertexBuffer->Unlock();
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
//void Spectrum::UV()
//{
//	std::vector<VertexFloat2> l_pos;
//
//	const U32 divisionNum	= 64;
//	const U32 vertexNum		= divisionNum * 4;
//
//	for (U32 i = 0; i < vertexNum; i += 4)
//	{
//		VertexFloat2 uv[4];
//
//		uv[0].u = 1.f;
//		uv[0].v = 0.f;
//
//		uv[1].u = 1.f;
//		uv[1].v = 1.f;
//
//		uv[2].u = 0.f;
//		uv[2].v = 0.f;
//
//		uv[3].u = 0.f;
//		uv[3].v = 1.f;
//
//		l_pos.push_back(uv[0]);
//		l_pos.push_back(uv[1]);
//		l_pos.push_back(uv[2]);
//		l_pos.push_back(uv[3]);
//	}
//}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================