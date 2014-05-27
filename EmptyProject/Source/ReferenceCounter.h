//=======================================================================================
//!	@file	:	ReferenceCounter.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

namespace AK
{
//=======================================================================================
//!	@class	:	ReferenceCounter
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class ReferenceCounter
{
public:
	ReferenceCounter();
	ReferenceCounter(const ReferenceCounter& src);

	void	AddRef();
	void	Release();
	U32		GetRefCount();

	ReferenceCounter& operator =(const ReferenceCounter& src);

private:
	void	SubRef();

	U32*	m_RefCount;

};
//=======================================================================================
//		inline method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//---------------------------------------------------------------------------------------
inline ReferenceCounter::ReferenceCounter()
	:	m_RefCount	(NEW U32(0))
{}
//---------------------------------------------------------------------------------------
//!	@brief		: �R�s�[�R���X�g���N�^�Bsrc�ƎQ�ƃJ�E���g�����L����
//---------------------------------------------------------------------------------------
inline ReferenceCounter::ReferenceCounter(const ReferenceCounter& src)
{
	Release();
	m_RefCount	= src.m_RefCount;
	AddRef();
}
//---------------------------------------------------------------------------------------
//!	@brief		: src�ƎQ�ƃJ�E���g�����L����
//---------------------------------------------------------------------------------------
inline ReferenceCounter& ReferenceCounter::operator =(const ReferenceCounter& src)
{
	Release();
	m_RefCount	= src.m_RefCount;
	AddRef();
	return *this;
}

//-------------------------------------------------------------
//!	@brief		: example
//-------------------------------------------------------------
inline void ReferenceCounter::AddRef()
{
	assert(m_RefCount);
	++(*m_RefCount);
}
//-------------------------------------------------------------
//!	@brief		: �Q�ƃJ�E���g���������A�Q�ƃJ�E���g��0�ȉ��������ꍇ�̂ݍ폜
//-------------------------------------------------------------
inline void ReferenceCounter::Release()
{
	assert(m_RefCount);

	SubRef();
	if ((*m_RefCount) > 0)
		return;
	SAFE_DELETE(m_RefCount);
}
//-------------------------------------------------------------
//!	@brief		: example
//-------------------------------------------------------------
inline U32	ReferenceCounter::GetRefCount()
{
	assert(m_RefCount);
	return (*m_RefCount);
}
//-------------------------------------------------------------
//!	@brief		: example
//-------------------------------------------------------------
inline void ReferenceCounter::SubRef()
{
	assert(m_RefCount);
	--(*m_RefCount);
}
};
//===============================================================
//	End of File
//===============================================================