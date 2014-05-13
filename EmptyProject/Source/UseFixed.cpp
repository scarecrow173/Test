//=======================================================================================
//!	@file	:	UseFixed.cpp
//!	@brief	:	UseFixed�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "UseFixed.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
UseFixed::UseFixed()
{

}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
UseFixed::~UseFixed()
{
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: ������
//!	@return		: ����(true),���s(false)
//-------------------------------------------------------------
bool UseFixed::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: �`��
//-------------------------------------------------------------
void UseFixed::Draw()
{
	for (auto it = m_Renderer.begin(); it != m_Renderer.end(); ++it)
	{
		(*it)->Draw();
	}
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