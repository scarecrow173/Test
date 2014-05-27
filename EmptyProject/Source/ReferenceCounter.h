//=======================================================================================
//!	@file	:	ReferenceCounter.h
//!	@author	:	小山 瑛圭
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
//!	@brief		: コンストラクタ
//---------------------------------------------------------------------------------------
inline ReferenceCounter::ReferenceCounter()
	:	m_RefCount	(NEW U32(0))
{}
//---------------------------------------------------------------------------------------
//!	@brief		: コピーコンストラクタ。srcと参照カウントを共有する
//---------------------------------------------------------------------------------------
inline ReferenceCounter::ReferenceCounter(const ReferenceCounter& src)
{
	Release();
	m_RefCount	= src.m_RefCount;
	AddRef();
}
//---------------------------------------------------------------------------------------
//!	@brief		: srcと参照カウントを共有する
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
//!	@brief		: 参照カウントを減少し、参照カウントが0以下だった場合のみ削除
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