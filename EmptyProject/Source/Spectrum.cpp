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
#include "GraphicsManager.h"
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
	SAFE_RELEASE(m_Texture);
	SAFE_RELEASE(m_VertexBuffer);
	SAFE_RELEASE(m_IndexBuffer);
	SAFE_RELEASE(m_Effect);
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

	D3DXCreateTextureFromFile(GraphicsManager::GetInstance()->GetD3DDevice(), L"Assets/Texture/spectrum.png", &m_Texture);

	//std::vector<U32> index;
	
	const U32 windowWidth	= WINDOW_WIDTH;
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
		Spectrum[0].color	= 0x0000FF00;

		Spectrum[1].x	= (sideOffset + (onePanelSizeX * ((i / 4) + 1) - (margin * 0.5f))) * windowWidth;
		Spectrum[1].y	= (topOffset) * windowHeight;
		Spectrum[1].z	= 0.f;
		Spectrum[1].w	= 1.f;
		Spectrum[1].u	= 1;//(1.f + 0.5f) / (float)windowWidth;
		Spectrum[1].v	= 0;//(0.f + 0.5f) / (float)windowHeight;//1.f;
		Spectrum[1].color	= 0x0000FF00;

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
		Spectrum[3].u	= 1;//(1.f + 0.5f) / (float)windowWidth;//1.f;
		Spectrum[3].v	= 1;//(1.f + 0.5f) / (float)windowHeight;//0.f;
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

	if (FAILED(GraphicsManager::GetInstance()->GetD3DDevice()->CreateVertexBuffer(
		(UINT)(sizeof(SpectrumVertex) * m_Vertex.size()), 
		D3DUSAGE_WRITEONLY, 
		m_FVF, 
		D3DPOOL_MANAGED,
		&m_VertexBuffer,
		0)))
		return;

	if (FAILED(GraphicsManager::GetInstance()->GetD3DDevice()->CreateIndexBuffer(
		(UINT)(sizeof(SpectrumVertex) * m_Vertex.size()), 
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
		GraphicsManager::GetInstance()->GetD3DDevice(),
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
	for (U32 i = 0; i < m_PeakData.GetSize(); ++i )
	{
		m_PeakData[i] = -FLT_MAX;
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
	GraphicsManager::GetInstance()->GetD3DDevice()->GetStreamSource(0, &oldBuf, &oldNum, &oldStride);
	
	LPDIRECT3DINDEXBUFFER9 oldIndexBuf;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetIndices(&oldIndexBuf);
	LPDIRECT3DVERTEXDECLARATION9 olddel;
	GraphicsManager::GetInstance()->GetD3DDevice()->GetVertexDeclaration(&olddel);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetVertexDeclaration(NULL);

	m_Effect->Begin(0,0);
	m_Effect->BeginPass(0);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetStreamSource(0, m_VertexBuffer, 0, sizeof(SpectrumVertex));
	GraphicsManager::GetInstance()->GetD3DDevice()->SetFVF(m_FVF);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetIndices(m_IndexBuffer);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(0, m_Texture);
	GraphicsManager::GetInstance()->GetD3DDevice()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, (UINT)m_Vertex.size(), 0, (UINT)m_Index.size() / 3);

	GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(0, NULL);

	GraphicsManager::GetInstance()->GetD3DDevice()->SetFVF(NULL);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetStreamSource(0, oldBuf, oldNum, oldStride);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetIndices(oldIndexBuf);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetVertexDeclaration(olddel);


	
	m_Effect->EndPass();
	m_Effect->End();

	SAFE_RELEASE(oldBuf);
	SAFE_RELEASE(oldIndexBuf);

}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Spectrum::Update(const F32* data, const U32 size)
{
	for (U32 i = 0; i < size; ++i)
	{
		F32 Fdata = data[i];
		if (Fdata > m_PeakData[i])
			m_PeakData[i]		= Fdata;

		Math::LinearInterpolation(&m_PeakData[i], m_PeakData[i], Fdata, 0.02f);
		
		const U32 vIndex = i * 4;
		m_Vertex[vIndex].y = m_Vertex[vIndex + 1].y = WINDOW_HEIGHT - m_PeakData[i];
	}


	SpectrumVertex* vertexData;
	m_VertexBuffer->Lock(0, NULL, (void**)&vertexData, 0);
	memcpy(vertexData, &m_Vertex[0], sizeof(SpectrumVertex) * m_Vertex.size());
	m_VertexBuffer->Unlock();
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