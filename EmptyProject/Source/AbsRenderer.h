//=======================================================================================
//!	@file	:	AbsRenderer.h
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
#include "DefaultTexture.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	AbsRenderer
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class AbsRenderer
{
public:
	AbsRenderer() 
		: m_BufferResource	(NULL)
		, m_Texture			(NULL)
		, m_Material		(NULL)
		, m_Transform		(NEW TransformObject())
		,  m_IsActive		(true) 
	{};
	virtual ~AbsRenderer() { };

	bool		Initialize();

	bool		IsActive() const;
	void		SetActive(const bool active);

	void		SetBufferResource(const RefCountedObjectPtr resource);
	void		SetMaterial(const RefCountedObjectPtr material);
	void		SetTexture(const RefCountedObjectPtr texture);
	void		SetTransform(std::shared_ptr<TransformObject> transform);
	
	std::shared_ptr<TransformObject>	GetTransform()	const;
	Material*							GetMaterial()	const;
	DefaultTexture*						GetTexture()	const;



	virtual void	Draw() = 0;

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
inline bool AbsRenderer::Initialize()
{
	return InnerInitialize();
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@return		: 
//-------------------------------------------------------------
inline bool AbsRenderer::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void AbsRenderer::SetActive(const bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void AbsRenderer::SetBufferResource(const  RefCountedObjectPtr resource)
{
	m_BufferResource = resource;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void	AbsRenderer::SetMaterial(const RefCountedObjectPtr material)
{
	m_Material = material;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void	AbsRenderer::SetTexture(const RefCountedObjectPtr texture)
{
	m_Texture = texture;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline void AbsRenderer::SetTransform(std::shared_ptr<TransformObject> transform)
{
	assert(transform);
	m_Transform = transform;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline std::shared_ptr<TransformObject> AbsRenderer::GetTransform() const
{
	return m_Transform;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline Material* AbsRenderer::GetMaterial() const
{
	return (Material*)m_Material.GetSharedObject();
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline DefaultTexture* AbsRenderer::GetTexture() const
{

	return (DefaultTexture*)m_Texture.GetSharedObject();
}
};
};
//===============================================================
//	End of File
//===============================================================