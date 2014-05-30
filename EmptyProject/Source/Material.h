//=======================================================================================
//!	@file	:	Material.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "Elements.h"
#include "RefCountedObject.h"
namespace AK
{
namespace Graphics
{
typedef VertexFloat4 F32x4;
//=======================================================================================
//!	@class	:	Material
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Material : public RefCountedObject
{
public:
	Material()
	{
		ZeroMemory(&m_Diffuse,			sizeof(F32x4)	);
		ZeroMemory(&m_Ambient,			sizeof(F32x4)	);
		ZeroMemory(&m_Specular,			sizeof(F32x4)	);
		ZeroMemory(&m_Emissive,			sizeof(F32x4)	);
		ZeroMemory(&m_SpecularPower,	sizeof(F32)		);
	};

	virtual ~Material(){};

	F32x4	m_Diffuse;
	F32x4	m_Ambient;
	F32x4	m_Specular;
	F32x4	m_Emissive;
	F32		m_SpecularPower;

};
//=======================================================================================
//		inline method
//=======================================================================================

};
};
//===============================================================
//	End of File
//===============================================================