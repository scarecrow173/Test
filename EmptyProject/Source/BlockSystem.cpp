//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "BlockSystem.h"
#include "ICollisonObject.h"
#include "Block.h"
#include "GraphicsManager.h"
#include "Ball.h"
#include "CSVReader.h"

using namespace AK;
using namespace Collision;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BlockSystem::BlockSystem(INode* parent)
	:	INode	(parent)
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
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BlockSystem::Update()
{

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
bool BlockSystem::CreateStageBlocks(std::string& filePath, IShaderObject* shader)
{
	assert(m_Ball);

	Matrix view,proj;
	view = GraphicsManager::GetInstance()->GetView();
	proj = GraphicsManager::GetInstance()->GetProjection();
	auto StageData = CSVReader::ReadInteger(filePath);

	for (int i = 0; i < StageData.row * StageData.column; ++i)
	{
		if (StageData.Data[i] == 0)
			continue;

		Vector3 vec3(450.f - ((i % StageData.row) * 125.f) , 450.f - ((i / StageData.row) * 100.f), 0);
		Block* block = NEW Block(this, vec3, StageData.Data[i]);
		this->AttachNode(block);
		shader->AddRenderer(block->GetRenderer());
		m_Ball->GetCollison()->PushCollisonList(block->GetCollison());
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
	//return m_Children.empty();
}
//-------------------------------------------------------------
//!	@brief		: ブロックの削除
//!	@param[in]	: 削除したいブロックのコリジョン
//-------------------------------------------------------------
void BlockSystem::DeleteBlock(ICollisonObject* obj)
{
	auto it = m_BlockList.begin();
	while (it != m_BlockList.end())
	{
		if (obj == (*it)->GetCollison())
		{
			if ((*it)->Death())
			{
				m_Ball->PopItem((*it)->GetPosition());
				it = m_BlockList.erase(it);
				continue;
			}
		}
		++it;
	}
	//	案2 : Castが多いからなし
	//for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	//{
	//	if (obj == ((Block*)(*it))->GetCollison())
	//		((Block*)(*it))->Death();
	//}
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