//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
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
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
MenuRevolver::MenuRevolver()
	:	m_Selected		(0)
	,	m_Renderer		(nullptr)
	,	m_Shader		(nullptr)
{
	Event::KeyDownTriggerTracker::GetInstance()->EntryListener(this);
	Event::KeyUPTriggerTracker::GetInstance()->EntryListener(this);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:RING-Revolv"));
	m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/Revolver.csv"));
	m_Renderer->SetTransform(std::make_shared<TransformObject>(Vector3(0,0,0), Vector3(500, 570, 1.f)));

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
//!	@brief		: �f�X�g���N�^
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
	Event::KeyDownTriggerTracker*	down	= dynamic_cast<Event::KeyDownTriggerTracker*>(_sender);
	Event::KeyUPTriggerTracker*		up		= dynamic_cast<Event::KeyUPTriggerTracker*>(_sender);
	RevolverDirection dir = (RevolverDirection)0;
	
	if (down)
		dir = DirectionDown;
	if (up)
		dir = DirectionUp;
	
	CalculationElementPosition(dir);
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
	CalculationElementPosition((RevolverDirection)3);
	
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
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationElementPosition(RevolverDirection _dir)
{
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

	const auto		root = m_Renderer->GetTransform();
	Vector3			rootTranslation = root->GetTranslation();
	const Vector3	rootRotation = root->GetRotation();
	Matrix			transMat, rotationMat, scaleMat, rootTransform;
	Matrix			rotX,rotY,rotZ;
	// �t�H���g�ƃ����O�̍��W�n���Ⴄ�̂Ŗ������␳���������
	auto tmp = Math::WorldToScreen(rootTranslation, WINDOW_WIDTH, WINDOW_HEIGHT, 
		GraphicsManager::GetInstance()->GetView() * GraphicsManager::GetInstance()->GetProjection()); 

	rootTranslation.x = tmp.x;
	rootTranslation.y = 250 + -(rootTranslation.y / 2);

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
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationUp()
{
	const Vector3	rootRotation = m_Renderer->GetTransform()->GetRotation();
	const F32		rotateFactar = (360.f / m_menuList.size());
	const Vector3	rotate = Vector3(0, 0, D3DXToRadian(rotateFactar));
	
	m_Renderer->GetTransform()->SetRotation(rootRotation + rotate);
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
	
	m_Renderer->GetTransform()->SetRotation(rootRotation + rotate);
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
