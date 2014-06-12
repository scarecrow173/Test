//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "UIStepDefault.h"
#include "GraphicsManager.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
UIStepDefault::UIStepDefault()
{
	m_DrawStep = 10000;
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
UIStepDefault::~UIStepDefault()
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
bool UIStepDefault::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void UIStepDefault::Draw()
{
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

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
