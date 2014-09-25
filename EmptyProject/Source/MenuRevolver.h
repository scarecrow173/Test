//=======================================================================================
//!	@file	:	MenuRevolver.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include <memory>
#include <vector>
#include <IEventListener.h>
#include "UIElement.h"
#include "AbsRenderer.h"
#include "DefaultShader.h"

namespace AK
{
namespace Graphics
{

namespace Util
{
enum RevolverDirection
{ 
	DirectionUp = 0,
	DirectionDown,
	NonDirection,
};
enum CalculateStep
{
	CalculateStep_End = 0,
	CalculateStep_Entry,
	CalculateStep_Update,
	CalculateStep_Exit,
};
//=======================================================================================
//!	@class	:	MenuRevolver
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class MenuRevolver : public Event::IEventListener
{
public:
	MenuRevolver();
	~MenuRevolver();

	virtual void Notify(Event::EventTrackerBase* _sender);
	virtual bool IsActive()	const;

	void Update(F32 _dt);

	void SetElement(UIElement* _elem);
	U32 SelectedElementID();

private:
	void CalculationElementPosition(RevolverDirection _dir);
	void CalculationUp();
	void CalculationDown();
	void CalculationUpdate();
	void CalculationExit();

	std::vector<UIElement*>	m_menuList;
	U32						m_Selected;
	AbsRenderer*			m_Renderer;
	DefaultShader*			m_Shader;
	CalculateStep			m_CaluvuStep;
	RevolverDirection		m_CarrentDirection;
	Vector3					m_NextTarget;
	F32						m_CalculationFactor;
};
//=======================================================================================
//		inline method
//=======================================================================================
};
};
};
//===============================================================
//	End of File
//===============================================================