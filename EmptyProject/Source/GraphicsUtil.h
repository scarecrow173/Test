//=======================================================================================
//!	@file	:	GraphicsUtil.h
//!	@author	:	¬ŽR ‰lŒ\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "RefCountedObjectPtr.h"
#include "TexturePool.h"
#include "GraphicsManager.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
//================================================================
//	Utility
//================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void CreateRenderTargetPtr(RefCountedObjectPtr& resource, D3DFORMAT textureFormat)
{
	DefaultTexture* textureObj = RTTI_PTR_DYNAMIC_CAST(DefaultTexture, resource.GetSharedObject());
	
	if (textureObj->GetTexture() == NULL)
	{
		LPDIRECT3DTEXTURE9 tex;
		D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
			1024, 
			1024,
			1,
			D3DUSAGE_RENDERTARGET,
			textureFormat,
			D3DPOOL_DEFAULT,
			&tex);
		textureObj->SetTexture(&tex);
	}
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
RefCountedObjectPtr GetVelocityMap()
{
	RefCountedObjectPtr ObjPtr = TexturePool::GetInstance()->GetResource("data:DefaultTexture-VelocityMap");

	CreateRenderTargetPtr(ObjPtr, D3DFMT_A32B32G32R32F);

	return ObjPtr;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
RefCountedObjectPtr GetBlueringTexture()
{
	RefCountedObjectPtr ObjPtr = TexturePool::GetInstance()->GetResource("data:DefaultTexture-BlueringTexture");

	CreateRenderTargetPtr(ObjPtr, D3DFMT_A32B32G32R32F);

	return ObjPtr;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
RefCountedObjectPtr GetDefaultTarget()
{
	RefCountedObjectPtr ObjPtr = TexturePool::GetInstance()->GetResource("data:DefaultTexture-DefaultTarget");

	CreateRenderTargetPtr(ObjPtr, D3DFMT_A32B32G32R32F);

	return ObjPtr;
}


//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================
