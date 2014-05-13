//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "InputKeyboard.h"
using namespace AK;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
InputKeyboard::InputKeyboard()
	:	m_KeyState			(0)
	,	m_BeforeKeyState	(0)
{}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
InputKeyboard::~InputKeyboard()
{}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool InputKeyboard::IsTrigger(INPUT_KEY key)
{
	switch(key)
	{
	case KEY_UP:
		return (m_KeyState & 0x01) && ((m_BeforeKeyState & 0x01) == 0x00);
	case KEY_DOWN:
		return (m_KeyState & 0x02) && ((m_BeforeKeyState & 0x02) == 0x00);
	case KEY_LEFT:
		return (m_KeyState & 0x04) && ((m_BeforeKeyState & 0x04) == 0x00);
	case KEY_RIGHT:
		return (m_KeyState & 0x08) && ((m_BeforeKeyState & 0x08) == 0x00);
	case KEY_BUTTON1:
		return (m_KeyState & 0x10) && ((m_BeforeKeyState & 0x10) == 0x00);
	case KEY_BUTTON2:
	case KEY_BUTTON3:
	case KEY_BUTTON4:
	default:
		return false;
	}

}
//-------------------------------------------------------------
//!	@brief		: ������Ă����
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool InputKeyboard::IsKeyDown(INPUT_KEY key)
{
	switch(key)
	{
	case KEY_UP:
		return (m_KeyState & 0x01);
	case KEY_DOWN:
		return (m_KeyState & 0x02);
	case KEY_LEFT:
		return (m_KeyState & 0x04);
	case KEY_RIGHT:
		return (m_KeyState & 0x08);
	case KEY_BUTTON1:
		return (m_KeyState & 0x10);
	case KEY_BUTTON2:
	case KEY_BUTTON3:
	case KEY_BUTTON4:
	default:
		return false;
	}
}
//-------------------------------------------------------------
//!	@brief		: �����ꂽ�u��
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool InputKeyboard::IsKeyRelease(INPUT_KEY key)
{
	switch(key)
	{
	case KEY_UP:
		return ((m_KeyState & 0x01) == 0x00) && (m_BeforeKeyState & 0x01);
	case KEY_DOWN:
		return ((m_KeyState & 0x02) == 0x00) && (m_BeforeKeyState & 0x02);
	case KEY_LEFT:
		return ((m_KeyState & 0x04) == 0x00) && (m_BeforeKeyState & 0x04);
	case KEY_RIGHT:
		return ((m_KeyState & 0x08) == 0x00) && (m_BeforeKeyState & 0x08);
	case KEY_BUTTON1:
		return ((m_KeyState & 0x10) == 0x00) && (m_BeforeKeyState & 0x10);
	case KEY_BUTTON2:
	case KEY_BUTTON3:
	case KEY_BUTTON4:
	default:
		return false;
	}
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void InputKeyboard::Update()
{
	m_BeforeKeyState = m_KeyState;
	m_KeyState &= 0x00;
	m_KeyState |= DXUTIsKeyDown(VK_UP)		? 0x01 : 0x00;
	m_KeyState |= DXUTIsKeyDown(VK_DOWN)	? 0x02 : 0x00;
	m_KeyState |= DXUTIsKeyDown(VK_LEFT)	? 0x04 : 0x00;
	m_KeyState |= DXUTIsKeyDown(VK_RIGHT)	? 0x08 : 0x00;
	m_KeyState |= DXUTIsKeyDown(VK_SPACE)	? 0x10 : 0x00;

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