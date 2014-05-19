//=======================================================================================
//!	@file	:	Item.cpp
//!	@brief	:	Itemクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "Item.h"
#include "BoxFactory.h"
#include "TriangleRenderer.h"
#include "CollisionBox.h"
#include "Colors.h"

using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Item::Item(Paddle* parent, Vector3 pos, ITEM_TYPE type)
	:	GameObject(parent, pos)
	,	m_Type	(type)
{
	//switch(m_Type)
	//{
	//case ITEM_TYPE::EXTEND_PADLLE:
	//	break;
	//case ITEM_TYPE::POWER_UP:
	//	break;
	//case ITEM_TYPE::SPEED_DOWN:
	//	break;
	//case ITEM_TYPE::SPEED_UP:
	//	break;
	//default:
	//	break;
	//}

	//	TODO:
	//	コリジョン作成	: ○
	//	アイテム効果	: ○
	//	表示			: ○

	std::vector<U32> indexSrc;
	IndexData indexData;
	indexData = BoxFactory::GetInstance()->CreateBox(Vector3(0, 0, 0), Vector3(0.5f, 0.5f, 0.5f), ARGBColors::Magenta, indexSrc);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->Initialize(DXUTGetD3D9Device());
	m_Renderer->AddIndex(indexSrc);
	m_Renderer->ReCreateIndexBuffer();
	m_Renderer->UpdateIndexData(indexData);

	Matrix mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);

	m_Renderer->SetWorld(mat);

	m_Collison = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), 0.5f, 0.5f, 0.5f);
	m_Collison->SetGravity(true);
	m_Collison->PushCollisonList(parent->GetCollison());
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Item::~Item()
{}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Item::Update()
{
	std::vector<ICollisonObject*> l_list;
	
	m_Collison->Update(l_list);

	for (auto it = l_list.begin(); it != l_list.end(); ++it)
	{
		ItemAffect(FindGameObject(*it));
		m_Renderer->SetActive(false);
	}

	m_Position = m_Collison->GetPosition();
	Matrix t;
	D3DXMatrixTranslation(&t, m_Position.x, m_Position.y, m_Position.z);
	m_Renderer->SetWorld(t);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Item::Start()
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Item::ItemAffect(GameObject* obj)
{
	if (!obj)
		return;
	//ICollisonObject* collison = obj->GetCollison();

	switch(m_Type)
	{
	case ITEM_TYPE::EXTEND_PADLLE:
		break;
	case ITEM_TYPE::POWER_UP:
		break;
	case ITEM_TYPE::SPEED_DOWN:
		//collison->SetSpeed(collison->GetSpeed() * 0.95f);
		break;
	case ITEM_TYPE::SPEED_UP:
		//collison->SetSpeed(collison->GetSpeed() * 1.05f);
		break;
	default:
		break;
	}
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
