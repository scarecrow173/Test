//=======================================================================================
//!	@file	:	DefaultTextureFactory.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "DefaultTextureFactory.h"

#include "DefaultTexture.h"
#include "GraphicsManager.h"

#include <atlbase.h>
#include <atlconv.h>


using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
DefaultTextureFactory::DefaultTextureFactory()
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
DefaultTextureFactory::~DefaultTextureFactory()
{}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
ITexture* DefaultTextureFactory::CreateTexture()
{
	DefaultTexture* out = NEW DefaultTexture();
	
	IDirect3DTexture9* tex = NULL;

	out->SetTexture(&tex);

	return out;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
ITexture* DefaultTextureFactory::CreateTextureFromFile(const std::string& filePath)
{
	DefaultTexture* out = NEW DefaultTexture();
	
	IDirect3DTexture9* tex = NULL;

	USES_CONVERSION;

	D3DXCreateTextureFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		A2W(filePath.c_str()),
		&tex);

	out->SetTexture(&tex);
	return out;
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