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
	DirectionUp,
	DirectionDown,
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

	void SetElement(UIElement* _elem);
	U32 SelectedElementID();

private:
	void CalculationElementPosition(RevolverDirection _dir);
	void CalculationUp();
	void CalculationDown();

	std::vector<UIElement*>	m_menuList;
	U32						m_Selected;
	AbsRenderer*			m_Renderer;
	DefaultShader*			m_Shader;
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