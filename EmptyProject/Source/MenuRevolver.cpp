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
	:	m_Selected		(0)
	,	m_Renderer		(nullptr)
	,	m_Shader		(nullptr)
{
	Event::KeyDownTriggerTracker::GetInstance()->EntryListener(this);
	Event::KeyUPTriggerTracker::GetInstance()->EntryListener(this);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:RING-Revolv"));
	m_Renderer->SetMaterial(MaterialPool::GetInstance()->GetResource("file:Default-Assets/CSV/Material/Revolver.csv"));
	m_Renderer->SetTransform(std::make_shared<TransformObject>(Vector3(0,0,0), Vector3(30, 30, 1.f)));

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
	Event::KeyDownTriggerTracker*	down	= static_cast<Event::KeyDownTriggerTracker*>(_sender);
	Event::KeyUPTriggerTracker*		up		= static_cast<Event::KeyUPTriggerTracker*>(_sender);
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
	m_menuList.push_back(_elem);
	CalculationElementPosition(DirectionUp);
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
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationUp()
{

}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void MenuRevolver::CalculationDown()
{

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
