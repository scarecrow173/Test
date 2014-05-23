//=======================================================================================
//!	@file	:	ReferCountType.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

namespace AK
{
//=======================================================================================
//!	@class	:	ReferCountType
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ReferCountType
{
public:
	ReferCountType();
	ReferCountType(const ReferCountType& src);

	void	AddRef();
	void	SubRef();
	void	Release();
	U32		GetRefCount();

	ReferCountType& operator =(const ReferCountType& src);

private:
	U32*	m_RefCount;

};
//=======================================================================================
//		inline method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//---------------------------------------------------------------------------------------
//template <typename T>
inline ReferCountType::ReferCountType()
	:	m_RefCount	(NEW U32(0))
{}
//---------------------------------------------------------------------------------------
//!	@brief		: �R�s�[�R���X�g���N�^
//---------------------------------------------------------------------------------------
inline ReferCountType::ReferCountType(const ReferCountType& src)
{
	Release();
	m_RefCount	= src.m_RefCount;
	AddRef();
}
//---------------------------------------------------------------------------------------
//!	@brief		: ������Z�q
//---------------------------------------------------------------------------------------
inline ReferCountType& ReferCountType::operator =(const ReferCountType& src)
{
	Release();
	m_RefCount	= src.m_RefCount;
	AddRef();
	return *this;
}

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline void ReferCountType::AddRef()
{
	assert(m_RefCount);
	++(*m_RefCount);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline void ReferCountType::SubRef()
{
	assert(m_RefCount);
	--(*m_RefCount);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline void ReferCountType::Release()
{
	assert(m_RefCount);

	SubRef();
	if ((*m_RefCount) > 0)
		return;
	SAFE_DELETE(m_RefCount);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline U32	ReferCountType::GetRefCount()
{
	assert(m_RefCount);
	return (*m_RefCount);
}
};
//===============================================================
//	End of File
//===============================================================