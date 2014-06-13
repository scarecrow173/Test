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
#include "SoundManager.h"

using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
static const U32 SPEEDUP_SE_ID		= 12;
static const U32 SPEEDDOWN_SE_ID	= 15;
static const U32 POWERUP_SE_ID		= 14;
static const U32 EXPAND_SE_ID		= 12;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Item::Item(AbsNode* parent, Vector3 pos, ITEM_TYPE type)
	:	GameObject	(parent, pos)
	,	m_Type		(type)
	,	m_Effect	(NULL)
	,	m_AffectStep(AffectStep::StopedStep)
{
	static const F32 WIDTH	= 100.f;
	static const F32 HEIGHT	= 100.f;

	m_Renderer	= NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:BOX-Box01"));
	m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/TestMaterial.csv"));
	m_Renderer->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/Q2.png"));

	m_EffectContoroller	= NEW TextureAnimationController(2048, 512, 5, 2, 0.032f);
	m_Effect			= NEW UITextureRenderer(m_EffectContoroller);
	m_Effect->Initialize();
	m_Effect->SetActive(false);

	m_Effect->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/gra_effect_auraA.png"));


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
{
	SAFE_DELETE(m_Effect);
}
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
	

	
	switch(m_AffectStep)
	{
	case AffectStep::StopedStep:
		m_Collision->Update(l_list);
		for (auto it = l_list.begin(); it != l_list.end(); ++it)
			ItemAffect(RootNode::GetInstance()->FindNode(*it));
		UpdateRendererMatrix();
		break;
	case AffectStep::StartAffect:
		StartAffect();
		break;
	case AffectStep::UpdateEffect:
		UpdateEffect();
		break;
	case AffectStep::EndAffect:
		EndAffect();
		break;
	}

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
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
UITextureRenderer* Item::GetEffectRenderer() const
{
	return m_Effect;
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

	m_AffectStep = AffectStep::StartAffect;
	obj->Affect(this);
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
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Item::StartAffect()
{
	switch(m_Type)
	{
	case POWER_UP:
		Sound::SoundManager::GetInstance()->PlaySE(POWERUP_SE_ID, TRUE);
		break;
	case SPEED_UP:
		Sound::SoundManager::GetInstance()->PlaySE(SPEEDUP_SE_ID, TRUE);
		break;
	case SPEED_DOWN:
		Sound::SoundManager::GetInstance()->PlaySE(SPEEDDOWN_SE_ID, TRUE);
		break;
	case EXTEND_PADLLE:
		Sound::SoundManager::GetInstance()->PlaySE(EXPAND_SE_ID, TRUE);
		break;
	default:
		break;
	}
	m_Effect->SetTransform(std::make_shared<TransformObject>(GetDrawEffectTransform()));
	m_Effect->SetActive(true);
	m_Renderer->SetActive(false);
	m_AffectStep = AffectStep::UpdateEffect;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Item::UpdateEffect()
{
	if (m_EffectContoroller->IsEnd())
	{
		m_Effect->SetActive(false);
		m_AffectStep = AffectStep::EndAffect;
	}
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Item::EndAffect()
{
	SetActive(false);
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
TransformObject	Item::GetDrawEffectTransform() const
{
	TransformObject transform2D;
	Vector3 effectPos = m_Transform->GetTranslation();
	static const Vector2 Offset = Vector2(50, 40); 
	const Matrix viewproj		= GraphicsManager::GetInstance()->GetView() * GraphicsManager::GetInstance()->GetProjection();
	Vector2 tmp = Math::WorldToScreen(effectPos, WINDOW_WIDTH, WINDOW_HEIGHT, viewproj);
	tmp			-= Offset;
	effectPos.x = tmp.x;
	effectPos.y = WINDOW_HEIGHT+tmp.y;
	effectPos.z = 0.f;
	transform2D.SetTranslation(effectPos);
	transform2D.SetScaling(Vector3(0.2f, 0.2f, 1.f));
	transform2D.UpdateTransform();
	return transform2D;
}
//===============================================================
//	End of File
//===============================================================
