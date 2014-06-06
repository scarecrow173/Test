//=======================================================================================
//!	@file	:	IRenderer.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "IndexData.h"
#include "MyMath.h"
#include "BufferResource.h"
#include "RefCountedObjectPtr.h"
#include "TransformObject.h"
#include "Material.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	IRenderer
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class IRenderer
{
public:
	IRenderer() 
		: m_BufferResource	(NULL)
		, m_Texture			(NULL)
		, m_Material		(NULL)
		, m_Transform		(NEW TransformObject())
		,  m_IsActive		(true) 
	{};
	virtual ~IRenderer() { };

	bool		Initialize();

	bool		IsActive() const;
	void		SetActive(const bool active);

	void		SetBufferResource(const RefCountedObjectPtr resource);
	void		SetMaterial(const RefCountedObjectPtr material);
	void		SetTransform(std::shared_ptr<TransformObject> transform);
	
	std::shared_ptr<TransformObject>	GetTransform() const;
	Material*							GetMaterial() const;



	virtual void	Draw() PURE;

protected:
	virtual bool	InnerInitialize() { return true; };


	std::shared_ptr<TransformObject>	m_Transform;
	bool								m_IsActive;
	RefCountedObjectPtr					m_BufferResource;
	RefCountedObjectPtr					m_Texture;
	RefCountedObjectPtr					m_Material;
	


};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: èâä˙âª
//!	@param[in]	: ÉfÉoÉCÉX
//!	@return		: ê¨å˜(true),é∏îs(false)
//-------------------------------------------------------------
inline bool IRenderer::Initialize()
{
	return InnerInitialize();
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
inline bool IRenderer::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void IRenderer::SetActive(const bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void IRenderer::SetBufferResource(const  RefCountedObjectPtr resource)
{
	m_BufferResource = resource;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void	IRenderer::SetMaterial(const RefCountedObjectPtr material)
{
	m_Material = material;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void IRenderer::SetTransform(std::shared_ptr<TransformObject> transform)
{
	assert(transform);
	m_Transform = transform;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline std::shared_ptr<TransformObject> IRenderer::GetTransform() const
{
	return m_Transform;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline Material* IRenderer::GetMaterial() const
{
	return (Material*)m_Material.GetSharedObject();
}

};
};
//===============================================================
//	End of File
//===============================================================