//=======================================================================================
//!	@file	:	UseFixed.cpp
//!	@brief	:	UseFixedクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
UseFixed::UseFixed()
{

}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
UseFixed::~UseFixed()
{
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool UseFixed::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: 描画
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
