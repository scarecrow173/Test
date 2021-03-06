//=======================================================================================
//!	@file	:	HandedOverBox.cpp
//!	@brief	:	HandedOverBoxクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "HandedOverBox.h"
#include "BoxFactory.h"
#include <algorithm>

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
HandedOverBox::HandedOverBox()
{
	m_BoxCreator = NEW BoxFactory();
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
HandedOverBox::~HandedOverBox()
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
RefCountedObjectPtr	HandedOverBox::GetBox(const std::string& name)
{
	auto it = m_ManagedResourceBox.find(name);
	if (it != m_ManagedResourceBox.end())
		return RefCountedObjectPtr(it->second);

	m_ManagedResourceBox[name] = m_BoxCreator->CreateBox();
	return RefCountedObjectPtr(m_ManagedResourceBox[name]);

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