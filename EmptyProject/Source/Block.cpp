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
#include "MyMath.h"


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
	:	GameObject			(parent, pos)
	,	m_LifeCount			(lifeCount)
	,	m_SEHandle			(0)
	,	m_DeadStep			(DeadStep::StopedStep)
	,	m_HardEffectStep	(HardBlockStep::StopedHardEffectStep)
	,	m_RingEffect		(nullptr)
{
	if (!g_InitializedMaterials)
	{
		g_InitializedMaterials = true;
	
		for (int i = 0; i < BLOCK_LEVEL_NUM; ++i)
		{
			BlockStrengthMaterial[i] = MaterialPool::GetInstance()->GetResource(MaterialDataCode[i]);
		}
	}


	static const F32 WIDTH	= 50.f;
	static const F32 HEIGHT	= 25.f;
	
	m_BlockLevel	= m_LifeCount >= BLOCK_LEVEL_NUM ? BLOCK_LEVEL_NUM : (BlockLevel)(m_LifeCount - 1);
	m_LifeCount		= m_BlockLevel == BLOCK_HARD ? 5 : 1;

	m_Color.color = 0x00FF0000;
	m_Color.color = m_Color.color >> m_LifeCount;

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:BOX-Box01"));
	m_Renderer->SetMaterial(BlockStrengthMaterial[m_BlockLevel]);

	//m_EffectContoroller	= NEW TextureAnimationController(4096, 1024, 7, 2, 0.032f);
	//m_Effect			= NEW UITextureRenderer(m_EffectContoroller);
	//m_Effect->Initialize();
	//m_Effect->SetActive(false);
	//m_Effect->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/gra_effect_hitN.png"));

	//m_HardEffectContoroller	= NEW TextureAnimationController(1024, 1024, 4, 3, 0.032f);
	//m_HardEffect			= NEW UITextureRenderer(m_HardEffectContoroller);
	//m_HardEffect->Initialize();
	//m_HardEffect->SetActive(false);
	//m_HardEffect->SetTexture(TexturePool::GetInstance()->GetResource("file:DefaultTexture-Assets/Texture/gra_effect_lightR.png"));

	m_Transform = std::make_shared<TransformObject>(pos, Vector3(WIDTH, HEIGHT, 50.f));

	m_Renderer->SetTransform(m_Transform);

	m_Collision = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), WIDTH, HEIGHT, 50.f);
	m_RingEffect = NEW Util::RingWaveEffect();
	m_RingEffect->SetActive(false);
	Material* RingMaterial = NEW Material(*(Material*)BlockStrengthMaterial[m_BlockLevel].GetSharedObject());
	m_RingEffect->SetMaterial(RefCountedObjectPtr(RingMaterial));
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Block::~Block()
{
	SAFE_DELETE(m_RingEffect);
	//SAFE_DELETE(m_Effect);
	//SAFE_DELETE(m_HardEffect);
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
	switch(m_DeadStep)
	{
	case DeadStep::StopedStep:
		break;
	case DeadStep::StartDeadStep:
		StartDeadStep();
		break;
	case DeadStep::UpdateEffectStep:
		UpdateEffectStep();
		break;
	case DeadStep::EndDeadStep:
		EndDeadStep();
		break;
	default:
		break;
	}
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
	if (--m_LifeCount > 0)
	{
		switch(m_HardEffectStep)
		{
		case HardBlockStep::StopedHardEffectStep:
			break;
		case HardBlockStep::StartHardEffectStep:
			break;
		case HardBlockStep::UpdateHardEffectStep:
			break;
		case HardBlockStep::EndHardEffectStep:
			break;
		}
		return false;
	}
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
	m_DeadStep = DeadStep::StartDeadStep;
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 死んだときになるSEのハンドルをセット
//-------------------------------------------------------------
void Block::SetSEHandle(const U32 handle)
{
	m_SEHandle = handle;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
Util::RingWaveEffect*	Block::GetRingRenderer() const
{
	return m_RingEffect;
}
////-------------------------------------------------------------
////!	@brief		: 
////-------------------------------------------------------------
//UITextureRenderer* Block::GetEffectRenderer() const
//{
//	return m_Effect;
//}
////-------------------------------------------------------------
////!	@brief		: 
////-------------------------------------------------------------
//UITextureRenderer* Block::GetHardEffectRenderer() const
//{
//	return m_HardEffect;
//}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Block::StartDeadStep()
{
	m_Renderer->SetActive(false);
	m_Collision->SetActive(false);
	//m_Effect->SetActive(true);
	//m_Effect->SetTransform(std::make_shared<TransformObject>(GetTransformTo2D()));
	
	m_RingEffect->SetTransform(m_Transform);
	m_RingEffect->SetActive(true);

	m_DeadStep = DeadStep::UpdateEffectStep;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Block::UpdateEffectStep()
{
	//if (m_EffectContoroller->IsEnd())
	//{
	//	m_Effect->SetActive(false);
	//	m_DeadStep = DeadStep::EndDeadStep;
	//}
	if (m_RingEffect->IsEnd())
	{
		m_DeadStep = DeadStep::EndDeadStep;
	}
	if (m_RingEffect)
		m_RingEffect->Update(0.016f);
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Block::EndDeadStep()
{
	m_RingEffect->SetActive(false);
	SetActive(false);
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void Block::StopedHardEffectStep()
{
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void	Block::StartHardEffectStep()
{
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void	Block::UpdateHardEffectStep()
{
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
void	Block::EndHardEffectStep()
{
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
TransformObject Block::GetTransformTo2D()
{
	TransformObject transform2D;
	Vector3 effectPos = m_Transform->GetTranslation();
	static const Vector2 Offset = Vector2(50, 50); 
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