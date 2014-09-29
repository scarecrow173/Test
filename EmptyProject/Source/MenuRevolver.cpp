//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "MenuRevolver.h"
#include "EventTracker.h"
#include "TriangleRenderer.h"
#include "MaterialPool.h"
#include "PrimitivePool.h"

using namespace AK;
using namespace Graphics;
using namespace Util;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
MenuRevolver::MenuRevolver()
	:	m_Selected			(0)
	,	m_Renderer			(nullptr)
	,	m_Shader			(nullptr)
	,	m_CaluvuStep		(CalculateStep_End)
	,	m_CarrentDirection	(NonDirection)
	,	m_NextTarget		(0, 0, 0)
	,	m_CalculationFactor	(0.f)
{
	Event::KeyDownTriggerTracker::GetInstance()->EntryListener(this);
	Event::KeyUPTriggerTracker::GetInstance()->EntryListener(this);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:RING-Revolv"));
	m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/Revolver.csv"));
	m_Renderer->SetTransform(std::make_shared<TransformObject>(Vector3(500,-400,0), Vector3(500, 500, 1.f)));

	m_Shader = NEW DefaultShader();
	m_Shader->Initilize();
	m_Shader->SetShaderTechniqueByName("SimpleColor");

	m_Shader->AddRenderer(m_Renderer);

	m_Shader->SetActive(true);
	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
MenuRevolver::~MenuRevolver()
{
	Event::KeyDownTriggerTracker::GetInstance()->ExitListener(this);
	Event::KeyUPTriggerTracker::GetInstance()->ExitListener(this);

	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);

	SAFE_DELETE(m_Shader);
	SAFE_DELETE(m_Renderer);
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::Notify(Event::EventTrackerBase* _sender)
{
	if (m_CaluvuStep != CalculateStep_End)
		return;

	Event::KeyDownTriggerTracker*	down	= dynamic_cast<Event::KeyDownTriggerTracker*>(_sender);
	Event::KeyUPTriggerTracker*		up		= dynamic_cast<Event::KeyUPTriggerTracker*>(_sender);
	
	if (down)
		m_CarrentDirection = DirectionDown;
	if (up)
		m_CarrentDirection = DirectionUp;
	
	m_CaluvuStep = CalculateStep_Entry;
	//CalculationElementPosition(m_CarrentDirection);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool MenuRevolver::IsActive()	const
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::Update(F32 _dt)
{
	if (m_CaluvuStep != CalculateStep_End)
		CalculationElementPosition(m_CarrentDirection);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::SetElement(UIElement* _elem)
{
	//if (!m_menuList.empty())
	//{
	//	const Vector3	rootRotation = m_Renderer->GetTransform()->GetRotation();
	//	const F32		rotateFactar = (360.f / m_menuList.size() + 1);
	//	const Vector3	rotate = Vector3(0, 0, D3DXToRadian(rotateFactar));
	//
	//	m_Renderer->GetTransform()->SetRotation(rootRotation + rotate);
	//}

	m_menuList.push_back(_elem);
	CalculationElementPosition(NonDirection);
	
	//CalculationElementPosition(DirectionUp);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
U32 MenuRevolver::SelectedElementID()
{
	return 0;
}
//-------------------------------------------------------------
//!	@brief		: 押された瞬間
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationElementPosition(RevolverDirection _dir)
{
	
	switch (m_CaluvuStep)
	{
	case AK::Graphics::Util::CalculateStep_End:
		break;
	case AK::Graphics::Util::CalculateStep_Entry:
		{
			m_CalculationFactor = 0.f;
			switch(_dir)
			{
			case DirectionUp:
				CalculationUp();
				break;
			case DirectionDown:
				CalculationDown();
				break;
			default:
				break;
			}
			m_CaluvuStep = CalculateStep_Update;
		}
		break;
	case AK::Graphics::Util::CalculateStep_Update:
		CalculationUpdate();
		break;
	case AK::Graphics::Util::CalculateStep_Exit:
		CalculationExit();
		break;
	default:
		break;
	}

	const auto		root = m_Renderer->GetTransform();
	Vector3			rootTranslation = root->GetTranslation();
	const Vector3	rootRotation = root->GetRotation();
	Matrix			transMat, rotationMat, scaleMat, rootTransform;
	Matrix			rotX,rotY,rotZ;
	// フォントとリングの座標系が違うので無理やり補正あかんやり方
	//auto tmp = Math::WorldToScreen(rootTranslation, WINDOW_WIDTH, WINDOW_HEIGHT, 
	//	GraphicsManager::GetInstance()->GetView() * GraphicsManager::GetInstance()->GetProjection()); 

	//rootTranslation.x = tmp.x;
	//rootTranslation.y = 250 + -(rootTranslation.y / 2);

	D3DXMatrixIdentity(&rootTransform);
	D3DXMatrixTranslation(&transMat, rootTranslation.x, rootTranslation.y, rootTranslation.z);
	D3DXMatrixRotationX(&rotX, rootRotation.x);
	D3DXMatrixRotationY(&rotY, rootRotation.y);
	D3DXMatrixRotationZ(&rotZ, rootRotation.z);
	rotationMat = rotX * rotY * rotZ;
	D3DXMatrixScaling(&scaleMat, 1.f, 1.f, 1.f);

	D3DXMatrixMultiply(&rootTransform, &scaleMat, &rotationMat);
	D3DXMatrixMultiply(&rootTransform, &rootTransform, &transMat);

	for (auto child = m_menuList.begin(); child != m_menuList.end(); ++child)
	{
		const Matrix childReletive = (*child)->GetReletiveTransform();
		Matrix out;
		D3DXMatrixMultiply(&out, &childReletive, &rootTransform);
		//out._42 = -out._42;
		(*child)->SetTransform(out);
	}
	//m_CaluvuStep = CalculateStep_End;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationUp()
{
	const Vector3			rootRotation = m_Renderer->GetTransform()->GetRotation();
	const F32		rotateFactar = (360.f / m_menuList.size());
	const Vector3	rotate = Vector3(0, 0, D3DXToRadian(rotateFactar));

	m_NextTarget = rootRotation + rotate;

	//m_Renderer->GetTransform()->SetRotation(rootRotation + rotate);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationDown()
{
	const Vector3	rootRotation = m_Renderer->GetTransform()->GetRotation();
	const F32		rotateFactar = -(360.f / m_menuList.size());
	const Vector3	rotate = Vector3(0, 0, D3DXToRadian(rotateFactar));
	
	m_NextTarget = rootRotation + rotate;

	//m_Renderer->GetTransform()->SetRotation(rootRotation + rotate);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationUpdate()
{
	Vector3	rootRotation = m_Renderer->GetTransform()->GetRotation();

	m_CalculationFactor = m_CalculationFactor >= 1.f ? 1.f : m_CalculationFactor + 0.1f;

	D3DXVec3Lerp(&rootRotation, &rootRotation, &m_NextTarget, m_CalculationFactor);
	m_Renderer->GetTransform()->SetRotation(rootRotation);

	if (m_CalculationFactor >= 1.f)
		m_CaluvuStep = CalculateStep_Exit;
	
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationExit()
{
	m_CaluvuStep = CalculateStep_End;
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
