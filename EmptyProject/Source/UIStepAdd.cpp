//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "UIStepAdd.h"
#include "GraphicsManager.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
UIStepAdd::UIStepAdd()
{
	m_DrawStep = 10000;
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
UIStepAdd::~UIStepAdd()
{
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool UIStepAdd::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIStepAdd::Draw()
{
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);		//�A���t�@�u�����f�B���O�̗L����
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_BLENDOP,  D3DBLENDOP_ADD );	//�u�����f�B���O�I�v�V�������Z
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);		//SRC�̐ݒ�
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);		//DEST�̐ݒ�
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		//�A���t�@�e�X�g�̖�����

	GraphicsManager::GetInstance()->GetSprite()->Begin(0);

	for (auto it = m_Renderer.begin(); it != m_Renderer.end(); ++it)
	{
		if ((*it)->IsActive())
			(*it)->Draw();
	}
	GraphicsManager::GetInstance()->GetSprite()->End();
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
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