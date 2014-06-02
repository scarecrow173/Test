//=======================================================================================
//!	@file	:	CubeTextureFactory.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "CubeTextureFactory.h"
#include "CubeTexture.h"
#include "GraphicsManager.h"

#include <atlbase.h>
#include <atlconv.h>

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
CubeTextureFactory::CubeTextureFactory()
{}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
CubeTextureFactory::~CubeTextureFactory()
{}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
ITexture* CubeTextureFactory::CreateTexture()
{
	CubeTexture* out = NEW CubeTexture();

	IDirect3DCubeTexture9* tex = NULL;

	out->SetTexture(&tex);

	return out;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
ITexture* CubeTextureFactory::CreateTextureFromFile(const std::string& filePath)
{
	CubeTexture* out = NEW CubeTexture();

	IDirect3DCubeTexture9* tex = NULL;

	USES_CONVERSION;

	D3DXCreateCubeTextureFromFile(
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