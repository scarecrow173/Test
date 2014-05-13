//=======================================================================================
//!	@file	:	Block.cpp
//!	@brief	:	Blockクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "Block.h"
#include "BoxFactory.h"
#include "TriangleRenderer.h"
#include "Colors.h"
#include "CollisionBox.h"
#include <algorithm>


using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
	

	
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Block::Block(INode* parent, Vector3 pos)
	:	GameObject	(parent, pos)
	,	m_LifeCount	(5)
{
	std::vector<U32> indexSrc;
	m_IndexData = BoxFactory::GetInstance()->CreateBox(Vector3(0, 0, 0), Vector3(0.5f, 0.5f, 0.5f), ARGBColors::Green, indexSrc);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->Initialize(DXUTGetD3D9Device());
	m_Renderer->AddIndex(indexSrc);
	m_Renderer->ReCreateIndexBuffer();
	m_Renderer->UpdateIndexData(m_IndexData);
	
	Matrix mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);

	m_Renderer->SetWorld(mat);

	m_Collison = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), 0.5f, 0.5f, 0.5f);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Block::~Block()
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
void Block::Update()
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Block::Start()
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool Block::Death()
{
	if (--m_LifeCount == 0)
	{
		m_Renderer->SetActive(false);
		m_Collison->SetActive(false);
		return true;
	}
	U32 r = ARGBColors::White.color;
	GraphicsManager::GetInstance()->ChangeColor(m_IndexData.start, m_IndexData.start + m_IndexData.vertexNum, VertexARGB(r >> (5 - m_LifeCount)));
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
	return false;
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