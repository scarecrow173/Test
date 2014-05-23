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
#include "ResourceManager.h"


using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Item::Item(INode* parent, Vector3 pos, ITEM_TYPE type)
	:	GameObject(parent, pos)
	,	m_Type	(type)
{
	static const F32 WIDTH	= 100.f;
	static const F32 HEIGHT	= 50.f;

	m_Renderer = (IRenderer*)ResourceManager::GetInstance()->GetResouce("Box", PRIMITIVE_BOX);

	m_Size.x = WIDTH;
	m_Size.y = HEIGHT;
	m_Size.z = 50.f;
	Matrix trans, scale, mat;
	D3DXMatrixTranslation(&trans, pos.x, pos.y, pos.z);
	D3DXMatrixScaling(&scale, WIDTH, HEIGHT, 50.f);
	D3DXMatrixMultiply(&mat, &scale, &trans);
	m_Renderer->SetWorld(mat);

	m_Collision = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), WIDTH, HEIGHT, 50.f);
	m_Collision->SetGravity(true);
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
//!	@brief		: 更新（衝突していたら効果発動）
//-------------------------------------------------------------
void Item::Update()
{
	TRACE(1,"Item::Update");
	std::vector<ICollisionObject*> l_list;
	
	m_Collision->Update(l_list);

	for (auto it = l_list.begin(); it != l_list.end(); ++it)
		ItemAffect(m_Parent->GetParent()->FindNode(*it));
	Move();

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
Item*	Item::DownCastItem()
{
	return this;
}
//-------------------------------------------------------------
//!	@brief		: アイテムが当たるもの
//-------------------------------------------------------------
void Item::AddCollision(ICollisionObject* collison)
{
	TRACE(1,"Item::AddCollision");
	m_Collision->PushCollisionList(collison);
}

//-------------------------------------------------------------
//!	@brief		: アイテムタイプを取得（これで効果を判断する）
//-------------------------------------------------------------
ITEM_TYPE Item::GetType() const
{
	return m_Type;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 効果発動
//!	@param[in]	: 発動相手
//-------------------------------------------------------------
void Item::ItemAffect(GameObject* obj)
{
	TRACE(1,"Item::ItemAffect");
	if (!obj)
		return;

	obj->Affect(this);
	m_Renderer->SetActive(false);
	SetActive(false);
}
//-------------------------------------------------------------
//!	@brief		: 移動のみ
//-------------------------------------------------------------
void Item::Move()
{
	m_Position = m_Collision->GetPosition();
	Matrix trans, scale, mat;
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	D3DXMatrixScaling(&scale, m_Size.x, m_Size.y, m_Size.z);
	D3DXMatrixMultiply(&mat, &scale, &trans);
	m_Renderer->SetWorld(mat);
}
//===============================================================
//	End of File
//===============================================================
