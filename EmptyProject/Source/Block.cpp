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
#include "TexturePool.h"
#include "Material.h"
#include "RootNode.h"
#include <algorithm>



using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
static std::string	MaterialDataCode[BLOCK_LEVEL_NUM] = 
{
	"file:Default-Assets/CSV/Material/BlockLevel1.csv",
	"file:Default-Assets/CSV/Material/BlockLevel2.csv",
	"file:Default-Assets/CSV/Material/BlockLevel3.csv",
	"file:Default-Assets/CSV/Material/BlockLevel4.csv",
	"file:Default-Assets/CSV/Material/BlockLevel5.csv",
	"file:Default-Assets/CSV/Material/BlockLevel6.csv",
	"file:Default-Assets/CSV/Material/BlockLevel7.csv",
	"file:Default-Assets/CSV/Material/BlockLevelHard.csv",
	"file:Default-Assets/CSV/Material/BlockLevelImmortality.csv",
};
static RefCountedObjectPtr	BlockStrengthMaterial[BLOCK_LEVEL_NUM];
static bool					g_InitializedMaterials = false;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Block::Block(AbsNode* parent, Vector3 pos, U32 lifeCount)
	:	GameObject	(parent, pos)
	,	m_LifeCount	(lifeCount)
	,	m_SEHandle		(0)
{
	if (!g_InitializedMaterials)
	{
		g_InitializedMaterials = true;
	
		for (int i = 0; i < BLOCK_LEVEL_NUM; ++i)
		{
			BlockStrengthMaterial[i] = MaterialPool::GetInstance()->GetResource(MaterialDataCode[i]);
		}
	}


	static const F32 WIDTH	= 100.f;
	static const F32 HEIGHT	= 50.f;
	
	m_BlockLevel	= m_LifeCount >= BLOCK_LEVEL_NUM ? BLOCK_LEVEL_NUM : (BlockLevel)(m_LifeCount - 1);
	m_LifeCount		= m_BlockLevel == BLOCK_HARD ? 5 : 1;

	m_Color.color = 0x00FF0000;
	m_Color.color = m_Color.color >> m_LifeCount;

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:BOX-Box01"));
	m_Renderer->SetMaterial(BlockStrengthMaterial[m_BlockLevel]);



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
	if (m_BlockLevel == BLOCK_IMMORTALITY)
		return true;

	m_Renderer->SetActive(false);
	m_Collision->SetActive(false);
	U32 addingScore = 0;
	switch(m_BlockLevel)
	{
	case BLOCK_WHITE:
		addingScore = 50;
		break;
	case BLOCK_ORANGE:
		addingScore = 60;
		break;
	case BLOCK_AQUA:
		addingScore = 70;
		break;
	case BLOCK_GREEN:
		addingScore = 80;
		break;
	case BLOCK_RED:
		addingScore = 90;
		break;
	case BLOCK_BLUE:
		addingScore = 100;
		break;
	case BLOCK_PINK:
		addingScore = 110;
		break;
	case BLOCK_HARD:
		addingScore = 300;
		break;
	case BLOCK_IMMORTALITY:
	case BLOCK_LEVEL_NUM:
	default:
		break;
	}
	RootNode::GetInstance()->GetScorer()->AddScore(addingScore);
	return true;
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