//=======================================================================================
//!	@file	:	RefCountedObjectPtr.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "RefCountedObject.h"
namespace AK
{

//=======================================================================================
//!	@class	:	RefCountedObjectPtr
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class RefCountedObjectPtr
{
public:
	RefCountedObjectPtr();
	explicit RefCountedObjectPtr(RefCountedObject* obj);
	RefCountedObjectPtr(const RefCountedObjectPtr& src);
	virtual ~RefCountedObjectPtr();

	RefCountedObjectPtr&	operator =(const RefCountedObjectPtr& src);
	void					operator =(RefCountedObject* obj);

	RefCountedObject&		operator *();
	RefCountedObject*		operator ->();
	//RefCountedObject*		operator ->() const;


	const RefCountedObject* GetSharedObject() const;

private:
	RefCountedObject* m_SharedObject;

};
//=======================================================================================
//		inline method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: コンストラクタ
//---------------------------------------------------------------------------------------
inline RefCountedObjectPtr::RefCountedObjectPtr()
	:	m_SharedObject	(NULL)
{
}
//---------------------------------------------------------------------------------------
//!	@brief		: コンストラクタ
//---------------------------------------------------------------------------------------
inline RefCountedObjectPtr::RefCountedObjectPtr(RefCountedObject* obj)
{
	if( obj )
		obj->AddRef();
	m_SharedObject = obj;
}
//---------------------------------------------------------------------------------------
//!	@brief		: コピー
//---------------------------------------------------------------------------------------
inline RefCountedObjectPtr::RefCountedObjectPtr(const RefCountedObjectPtr& src)
{
	if (src.m_SharedObject)
		src.m_SharedObject->AddRef();

	m_SharedObject = src.m_SharedObject;
}
//---------------------------------------------------------------------------------------
//!	@brief		: デストラクタ
//---------------------------------------------------------------------------------------
inline RefCountedObjectPtr::~RefCountedObjectPtr()
{
	SAFE_RELEASE(m_SharedObject);

}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//---------------------------------------------------------------------------------------
inline RefCountedObjectPtr& RefCountedObjectPtr::operator = (const RefCountedObjectPtr& src)
{
	SAFE_RELEASE(m_SharedObject);

	if (src.m_SharedObject)
		src.m_SharedObject->AddRef();

	m_SharedObject = src.m_SharedObject;

	return *this;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//---------------------------------------------------------------------------------------
inline void RefCountedObjectPtr::operator = (RefCountedObject* obj)
{
	SAFE_RELEASE(m_SharedObject);

	m_SharedObject = obj;

}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//---------------------------------------------------------------------------------------
inline RefCountedObject& RefCountedObjectPtr::operator *()
{
	return *m_SharedObject;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//---------------------------------------------------------------------------------------
inline RefCountedObject* RefCountedObjectPtr::operator ->()
{
	return m_SharedObject;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//---------------------------------------------------------------------------------------
//inline RefCountedObject* RefCountedObjectPtr::operator ->() const
//{
//	return m_SharedObject;
//}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//---------------------------------------------------------------------------------------
inline const RefCountedObject* RefCountedObjectPtr::GetSharedObject() const
{
	return m_SharedObject;
}

};
//===============================================================
//	End of File
//===============================================================