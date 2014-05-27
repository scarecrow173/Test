//=======================================================================================
//!	@file	:	IRenderer.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "IndexData.h"
#include "MyMath.h"
#include "IResource.h"
#include "BufferResource.h"
#include "RefCountedObjectPtr.h"
#include "TransformObject.h"
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
class IRenderer : public IResource
{
public:
	IRenderer() : m_BufferResource	(NULL), m_Transform (NEW TransformObject()),  m_IsActive (true) { /*m_IndexData.start = UINT_MAX; m_IndexData.face = 0;*/ };
	virtual ~IRenderer() {  };

	bool		Initialize();

	bool		IsActive() const;
	void		SetActive(const bool active);

	void		SetBufferResource(RefCountedObjectPtr resource);
	void		SetTransform(std::shared_ptr<TransformObject> transform);
	std::shared_ptr<TransformObject> GetTransform() const;




	virtual void	Draw() PURE;

protected:
	virtual bool	InnerInitialize() { return true; };


	std::shared_ptr<TransformObject>	m_Transform;
	bool								m_IsActive;
	RefCountedObjectPtr					m_BufferResource;
	


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
inline void IRenderer::SetBufferResource(RefCountedObjectPtr resource)
{
	m_BufferResource = resource;
}
inline void IRenderer::SetTransform(std::shared_ptr<TransformObject> transform)
{
	assert(transform);
	m_Transform = transform;
}
inline std::shared_ptr<TransformObject> IRenderer::GetTransform() const
{
	return m_Transform;
}

};
};
//===============================================================
//	End of File
//===============================================================