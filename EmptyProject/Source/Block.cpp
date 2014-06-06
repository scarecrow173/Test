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
#include "MaterialPool.h"
#include "PrimitivePool.h"
#include "Material.h"
#include <algorithm>



using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
//	残り56分
static std::string	MaterialDataCode[5] = 
{
	"file:Default-Assets/CSV/Material/BlockLevel1.csv",
	"file:Default-Assets/CSV/Material/BlockLevel2.csv",
	"file:Default-Assets/CSV/Material/BlockLevel3.csv",
	"file:Default-Assets/CSV/Material/BlockLevel4.csv",
	"file:Default-Assets/CSV/Material/BlockLevel5.csv"
};
static RefCountedObjectPtr	BlockStrengthMaterial[5];
static bool					g_InitializedMaterials = false;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Block::Block(INode* parent, Vector3 pos, U32 lifeCount)
	:	GameObject	(parent, pos)
	,	m_LifeCount	(lifeCount)
	,	m_SEHandle		(0)
{
	if (!g_InitializedMaterials)
	{
		g_InitializedMaterials = true;
	
		for (int i = 0; i < 5; ++i)
		{
			BlockStrengthMaterial[i] = MaterialPool::GetInstance()->GetResource(MaterialDataCode[i]);
		}
	}


	static const F32 WIDTH	= 100.f;
	static const F32 HEIGHT	= 50.f;

	m_LifeCount = m_LifeCount >= 4 ? 4 : m_LifeCount;

	m_Color.color = 0x00FF0000;
	m_Color.color = m_Color.color >> m_LifeCount;

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:BOX-Box01"));
	m_Renderer->SetMaterial(BlockStrengthMaterial[m_LifeCount - 1]);


	m_Transform = std::make_shared<TransformObject>(pos, Vector3(WIDTH, HEIGHT, 50.f));

	m_Renderer->SetTransform(m_Transform);

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
	m_Renderer->SetMaterial(BlockStrengthMaterial[m_LifeCount - 1]);
	//GraphicsManager::GetInstance()->ChangeColor(m_IndexData.start, m_IndexData.start + m_IndexData.vertexNum, m_Color);
	//GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	//GraphicsManager::GetInstance()->SetAllStreamSource();
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