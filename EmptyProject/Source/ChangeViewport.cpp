//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "ChangeViewport.h"
#include "GraphicsManager.h"

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
ChangeViewport::ChangeViewport()
{
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
ChangeViewport::~ChangeViewport()
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
void ChangeViewport::Draw()
{
	ChangeViewprot();
	GraphicsManager::GetInstance()->GetD3DDevice()->Clear(
		0, 
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_ARGB( 0, 45, 50, 170 ), 
		1.0f, 
		0);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool ChangeViewport::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void ChangeViewport::ChangeViewprot()
{
	GraphicsManager::GetInstance()->GetD3DDevice()->SetViewport(&m_Viewprot);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void ChangeViewport::SetViewport(const D3DVIEWPORT9& viewport)
{
	m_Viewprot = viewport;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
D3DVIEWPORT9 ChangeViewport::GetViewport() const
{
	return m_Viewprot;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void ChangeViewport::SetDrawStep(const U32 drawstep)
{
	m_DrawStep = drawstep;
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
