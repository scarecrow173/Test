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
#include "PrimitivePool.h"
#include "MaterialPool.h"
#include "TexturePool.h"
#include "RootNode.h"

using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Item::Item(AbsNode* parent, Vector3 pos, ITEM_TYPE type)
	:	GameObject(parent, pos)
	,	m_Type	(type)
{
	static const F32 WIDTH	= 100.f;
	static const F32 HEIGHT	= 100.f;

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:BOX-Box01"));
	m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/TestMaterial.csv"));
	m_Renderer->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/Q2.png"));


	m_Size.x = WIDTH;
	m_Size.y = HEIGHT;
	m_Size.z = 50.f;

	m_Transform = std::make_shared<TransformObject>(pos, m_Size);

	m_Renderer->SetTransform(m_Transform);

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
	std::vector<AbsCollisionObject*> l_list;
	
	m_Collision->Update(l_list);

	for (auto it = l_list.begin(); it != l_list.end(); ++it)
		ItemAffect(RootNode::GetInstance()->FindNode(*it));
	UpdateRendererMatrix();

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
//!	@brief		: アイテムが当たるもの
//-------------------------------------------------------------
void Item::AddCollision(AbsCollisionObject* collison)
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
void Item::UpdateRendererMatrix()
{

	m_Transform->SetTranslation(m_Collision->GetPosition());
	m_Transform->SetScaling(m_Size);
	m_Transform->UpdateTransform();
}
//===============================================================
//	End of File
//===============================================================
