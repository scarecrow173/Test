//=======================================================================================
//!	@file	:	GraphicsManager.cpp
//!	@brief	:	GraphicsManagerクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "GraphicsManager.h"

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
GraphicsManager*	GraphicsManager::m_Instance = NULL;
VertexBaseData		GraphicsManager::m_VertexBase[VERTEX_NUM];
VertexARGB			GraphicsManager::m_VertexColor[VERTEX_NUM];
VertexFloat2		GraphicsManager::m_VertexUV[VERTEX_NUM];
F32					GraphicsManager::m_VertexInstance[VERTEX_NUM];

const D3DVERTEXELEMENT9 VertexElemnt[] = {
	{0, 0,						D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION,	0},
	{0, sizeof(VertexFloat3),	D3DDECLTYPE_FLOAT3,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL,		0},
	{1, 0,						D3DDECLTYPE_D3DCOLOR,	D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,		0},
	{2, 0,						D3DDECLTYPE_FLOAT2,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	0},
	{3, 0,						D3DDECLTYPE_FLOAT1,		D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,	1},
	D3DDECL_END()
};
IDirect3DVertexDeclaration9*	VertexDeclaration = NULL;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
GraphicsManager::GraphicsManager()
	:	m_Device			(NULL)
	,	m_BaseBuffer		(NULL)
	,	m_ColorBuffer		(NULL)
	,	m_UVBuffer			(NULL)
	,	m_InstanceBuffer	(NULL)
	,	m_VertexCount		(8)
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
GraphicsManager::~GraphicsManager()
{
	U32 count=0;

	if (m_BaseBuffer)
		SAFE_RELEASE(m_BaseBuffer);

	if (m_ColorBuffer)
		SAFE_RELEASE(m_ColorBuffer);
	
	if (m_UVBuffer)
		SAFE_RELEASE(m_UVBuffer);
	
	if (m_InstanceBuffer)
		SAFE_RELEASE(m_InstanceBuffer);

	if (m_Device)
		count = m_Device->Release();

}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
GraphicsManager* GraphicsManager::Create()
{
	if (m_Instance)
		return m_Instance;

	m_Instance = NEW GraphicsManager();
	return m_Instance;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::Destroy()
{
	SAFE_DELETE(m_Instance);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::AddShaderObject(IShaderObject* shader)
{
	auto it = std::find(m_ShaderList.begin(), m_ShaderList.end(), shader);
	if (it == m_ShaderList.end())
		m_ShaderList.push_back(shader);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::EraseShaderObject(IShaderObject* shader)
{
	auto it = std::find(m_ShaderList.begin(), m_ShaderList.end(), shader);
	if (it == m_ShaderList.end())
		return;
	m_ShaderList.erase(it);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool GraphicsManager::ReCreateVertexBuffer()
{
	//assert(!(m_VertexCount >= VERTEX_NUM));

	if (m_BaseBuffer)
		SAFE_RELEASE(m_BaseBuffer);
		
	//	座標バッファ作成
	if (FAILED(m_Device->CreateVertexBuffer(
		sizeof(VertexBaseData) * VERTEX_NUM, 
		0, 
		D3DFVF_XYZ | D3DFVF_NORMAL, 
		D3DPOOL_MANAGED,
		&m_BaseBuffer,
		0)))
		return false;
	
	if (m_ColorBuffer)
		SAFE_RELEASE(m_ColorBuffer);
		
	//	カラーバッファ作成
	if (FAILED(m_Device->CreateVertexBuffer(
		sizeof(VertexARGB) * VERTEX_NUM, 
		0, 
		D3DFVF_DIFFUSE, 
		D3DPOOL_MANAGED,
		&m_ColorBuffer,
		0)))
		return false;


	if (m_UVBuffer)
		SAFE_RELEASE(m_UVBuffer);
		
	//	UVバッファ作成
	if (FAILED(m_Device->CreateVertexBuffer(
		sizeof(VertexFloat2) * VERTEX_NUM, 
		0, 
		D3DFVF_TEX0, 
		D3DPOOL_MANAGED,
		&m_UVBuffer,
		0)))
		return false;


	if (m_InstanceBuffer)
		SAFE_RELEASE(m_InstanceBuffer);

	//	インスタンスIDバッファ作成
	if (FAILED(m_Device->CreateVertexBuffer(
		sizeof(F32) * VERTEX_NUM, 
		0, 
		D3DFVF_TEX1, 
		D3DPOOL_MANAGED,
		&m_InstanceBuffer,
		0)))
		return false;


	VertexBaseData*	base;
	VertexARGB*		color;
	VertexFloat2*	uv;
	U32*			instanceID;

	m_BaseBuffer->Lock(0, NULL, (void**)&base, 0);
	memcpy(base, m_VertexBase, sizeof(VertexBaseData) * VERTEX_NUM);
	m_BaseBuffer->Unlock();

	m_ColorBuffer->Lock(0, NULL, (void**)&color, 0);
	memcpy(color, m_VertexColor, sizeof(VertexARGB) * VERTEX_NUM);
	m_ColorBuffer->Unlock();

	m_UVBuffer->Lock(0, NULL, (void**)&uv, 0);
	memcpy(uv, m_VertexUV, sizeof(VertexFloat2) * VERTEX_NUM);
	m_UVBuffer->Unlock();

	m_InstanceBuffer->Lock(0, NULL, (void**)&instanceID, 0);
	memcpy(instanceID, m_VertexInstance, sizeof(F32) * VERTEX_NUM);
	m_InstanceBuffer->Unlock();

	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool GraphicsManager::Initialize()
{
	//m_Device->CreateVertexDeclaration(VertexElemnt, &VertexDeclaration);
	//m_Device->SetVertexDeclaration(VertexDeclaration);
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::Draw()
{
	for (auto it = m_ShaderList.begin(); it != m_ShaderList.end(); ++it)
	{
		(*it)->Draw();
	}
}

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::SetAllStreamSource()
{
	m_Device->SetVertexDeclaration(VertexDeclaration);
	m_Device->SetStreamSource(0, m_BaseBuffer,		0, sizeof(VertexBaseData));
	m_Device->SetStreamSource(1, m_ColorBuffer,		0, sizeof(VertexARGB));
	m_Device->SetStreamSource(2, m_UVBuffer,		0, sizeof(VertexFloat2));
	m_Device->SetStreamSource(3, m_InstanceBuffer,	0, sizeof(U32));
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::ChangeColor(U32 min, U32 max, VertexARGB color)
{
	U32 size = max - min;
	assert(!(size < 0));
	for (U32 i = min; i <= max; ++i)
	{
		m_VertexColor[i] = color;
	}
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::SetView(Matrix& view)
{
	m_View = view;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void GraphicsManager::SetProjection(Matrix& projction)
{
	m_Projection = projction;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Matrix GraphicsManager::GetView()
{
	return m_View;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Matrix GraphicsManager::GetProjection()
{
	return m_Projection;
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