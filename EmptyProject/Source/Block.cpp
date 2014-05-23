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
#include "ResourceManager.h"
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
Block::Block(INode* parent, Vector3 pos, U32 lifeCount)
	:	GameObject	(parent, pos)
	,	m_LifeCount	(lifeCount)
	,	m_SEHandle		(0)
{
	static const F32 WIDTH	= 100.f;
	static const F32 HEIGHT	= 50.f;

	std::vector<U32> indexSrc;

	m_Color.color = 0x00FF0000;
	m_Color.color = m_Color.color >> m_LifeCount;

	m_Renderer = (IRenderer*)ResourceManager::GetInstance()->GetResouce("Box", PRIMITIVE_BOX);


	
	Matrix mat, scale;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&scale, WIDTH, HEIGHT, 50.f);
	D3DXMatrixMultiply(&mat, &scale, &mat);
	m_Renderer->SetWorld(mat);

	m_Collision = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), WIDTH, HEIGHT, 50.f);
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
//!	@brief		: 死亡時
//-------------------------------------------------------------
bool Block::Death()
{
	Sound::SoundManager::GetInstance()->PlaySE(m_SEHandle, TRUE);
	if (--m_LifeCount == 0)
	{
		m_Renderer->SetActive(false);
		m_Collision->SetActive(false);
		return true;
	}
	auto col = m_Color.color >> 4;
	m_Color.color = m_Color.color | col;
	GraphicsManager::GetInstance()->ChangeColor(m_IndexData.start, m_IndexData.start + m_IndexData.vertexNum, m_Color);
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
	return false;
}
//-------------------------------------------------------------
//!	@brief		: 死んだときになるSEのハンドルをセット
//-------------------------------------------------------------
void Block::SetSEHandle(const U32 handle)
{
	m_SEHandle = handle;
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