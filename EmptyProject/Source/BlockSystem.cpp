//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "BlockSystem.h"
#include "AbsCollisionObject.h"
#include "Block.h"
#include "GraphicsManager.h"
#include "Ball.h"
#include "CSVReader.h"
#include "Stage1.h"
#include "UIStepAdd.h"

using namespace AK;
using namespace Collision;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BlockSystem::BlockSystem(AbsNode* parent)
	:	AbsNode	(parent)
	,	m_Ball	(NULL)
{

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
BlockSystem::~BlockSystem()
{
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 更新
//-------------------------------------------------------------
void BlockSystem::Update()
{
	TRACE(1, "BlockSystem::Update");
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlockSystem::Start()
{
	
}
//-------------------------------------------------------------
//!	@brief		: ステージにブロックを配置
//!	@param[in]	: ブロック数
//!	@param[in]	: 行数
//!	@param[in]	: 列数
//!	@return		: 作成に成功したら true
//-------------------------------------------------------------
bool BlockSystem::CreateStageBlocks(const std::string& filePath, AbsShaderObject* shader, UIStepAdd* addStep)
{
	assert(m_Ball);

	Matrix view,proj;
	view = GraphicsManager::GetInstance()->GetView();
	proj = GraphicsManager::GetInstance()->GetProjection();

	CSVReader StageData;
	StageData.Load(filePath.c_str());
	for (U32 i = 0; i < StageData.row * StageData.column; ++i)
	{
		if (StageData[i].GetInteger() == 0)
			continue;

		Vector3 vec3(450.f - ((i % StageData.row) * 125.f) , 400.f - ((i / StageData.row) * 100.f), 0);
		Block* block = NEW Block(this, vec3, StageData[i].GetInteger());
		block->SetSEHandle((i % StageData.row) + 1);
		this->AttachNode(block);
		shader->AddRenderer(block->GetRenderer());
		addStep->AddRenderer(block->GetEffectRenderer());
		addStep->AddRenderer(block->GetHardEffectRenderer());
		m_Ball->GetCollision()->PushCollisionList(block->GetCollision());
		m_BlockList.push_back(block);
	}


	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();



	return true;
}
//-------------------------------------------------------------
//!	@brief		: ゲームのクリア条件判定
//!	@return		: 生存ブロックが0ならtrue
//-------------------------------------------------------------
bool BlockSystem::Clear()
{
	return m_BlockList.empty();
}
//-------------------------------------------------------------
//!	@brief		: ブロックの削除
//!	@param[in]	: 削除したいブロックのコリジョン
//-------------------------------------------------------------
bool BlockSystem::DeleteBlock(AbsCollisionObject* obj)
{
	bool isBlock = false;
	auto it = m_BlockList.begin();
	while (it != m_BlockList.end())
	{
		if (obj == (*it)->GetCollision())
		{
			isBlock = true;
			if ((*it)->Death())
			{
				((Stage1*)m_Parent)->PopItem((*it)->GetTransform()->GetTranslation());
				//(*it)->SetActive(false);
				it = m_BlockList.erase(it);
				continue;
			}
		}
		++it;
	}
	return isBlock;

}
//-------------------------------------------------------------
//!	@brief		: ボールのコリジョンをセット(このボールにブロックのコリジョンがアタッチされる)
//!	@param[in]	: セットしたいコリジョン
//-------------------------------------------------------------
void BlockSystem::SetBall(Ball* ball)
{
	m_Ball = ball;
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