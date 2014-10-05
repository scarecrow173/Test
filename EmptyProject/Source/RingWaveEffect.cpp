//=======================================================================================
//!	@file	:	RingWaveEffect.cpp
//!	@brief	:	RingWaveEffectクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "RingWaveEffect.h"
#include "TriangleRenderer.h"
#include "PrimitivePool.h"
#include "MaterialPool.h"
#include "DefaultShader.h"
#include "GraphicsManager.h"

using namespace AK;
using namespace Graphics;
using namespace Util;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
RingWaveEffect::RingWaveEffect(F32 _speed, Vector3 _limit3d )
	:	m_Renderer			(nullptr)
	,	m_Shader			(nullptr)
	,	m_Position			(0,0,0)
	,	m_Size				(0,0,1)
	,	m_ScalingSpeedFactor(_speed)
	,	m_CurrentFactor		(0)
	,	m_LimitSize			(_limit3d)
	,	m_Alpha				(1.f)
	,	m_IsActive			(true)
	,	m_IsEnd				(false)
{
	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:RING-WaveRing"));
	Material* RingMaterial = NEW Material(*(Material*)MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/DefaultBall.csv").GetSharedObject());
	m_Renderer->SetMaterial(RefCountedObjectPtr(RingMaterial));
	//m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/DefaultBall.csv"));
	m_Renderer->SetTransform(std::make_shared<TransformObject>(Vector3(0,0,0), Vector3(30, 30, 1.f)));
	
	//m_Shader = NEW DefaultShader();
	//m_Shader->Initilize();
	//m_Shader->SetShaderTechniqueByName("SimpleColor");
	
	//m_Shader->AddRenderer(m_Renderer);

	//m_Shader->SetActive(m_IsActive);
	//GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
	
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
RingWaveEffect::~RingWaveEffect()
{
//	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);

//	SAFE_DELETE(m_Shader);
	SAFE_DELETE(m_Renderer);

}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void RingWaveEffect::Update(F32 _deltaTime)
{
	if (!m_IsActive)
		return;
	if (m_CurrentFactor >= 1.f)
	{
		m_IsEnd = true;
		return;
	}
	m_CurrentFactor += m_ScalingSpeedFactor;

	Math::LinearInterpolation(&m_Size.x,	m_Size.x,	m_LimitSize.x,	m_CurrentFactor);
	Math::LinearInterpolation(&m_Size.y,	m_Size.y,	m_LimitSize.y,	m_CurrentFactor);
	Math::LinearInterpolation(&m_Renderer->GetMaterial()->m_Diffuse.a,	m_Renderer->GetMaterial()->m_Diffuse.a,	0.f, m_CurrentFactor);

	if (m_LimitSize.x <= m_Size.x)
		m_Size.x = m_LimitSize.x;
	if (m_LimitSize.y <= m_Size.y)
		m_Size.y = m_LimitSize.y;	

	m_Renderer->GetTransform()->SetScaling(m_Size);
	m_Renderer->GetTransform()->UpdateTransform();
	//m_Renderer->GetMaterial()->m_Diffuse.a = m_Alpha;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void RingWaveEffect::SetMaterial(const RefCountedObjectPtr material)
{
	assert(m_Renderer);
	m_Renderer->SetMaterial(material);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void RingWaveEffect::SetTexture(const RefCountedObjectPtr texture)
{
	assert(m_Renderer);
	m_Renderer->SetTexture(texture);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void RingWaveEffect::SetTransform(std::shared_ptr<TransformObject> transform)
{
	assert(m_Renderer);
	m_Renderer->SetTransform(transform);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
AbsRenderer* RingWaveEffect::GetRenderer() const
{
	return m_Renderer;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void RingWaveEffect::SetActive(const bool _active)
{
	m_IsActive = _active;
	m_Renderer->SetActive(_active);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool RingWaveEffect::IsActivce() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool RingWaveEffect::IsEnd() const
{
	return m_IsEnd;
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