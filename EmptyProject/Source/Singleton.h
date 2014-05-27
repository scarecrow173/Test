//=======================================================================================
//!	@file	:	Singleton.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

namespace AK
{
//=======================================================================================
//!	@class	:	Singleton
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
template <class T>
class Singleton
{
public:

	static T*		CreateSingleton();
	static void		DestroySingleton();

	static T*		GetInstance();

protected:

	Singleton(){};
	virtual ~Singleton(){};

private:
	Singleton(const Singleton&){}
	const Singleton& operator = (const Singleton&){};

	static T* m_Instance;

};
//=======================================================================================
//		Constants Definitions
//=======================================================================================
template <class T>
T* Singleton<T>::m_Instance	= NULL;
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
template <class T>
T* Singleton<T>::CreateSingleton()
{
	if (!m_Instance)
		m_Instance = NEW T();
	return m_Instance;
}
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
template <class T>
void Singleton<T>::DestroySingleton()
{
	SAFE_DELETE(m_Instance);
}
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�̎擾(���ۂɂ�CreateSingleton���C���X�^���X�𐶐��ς݂����f���Ă����)
//-------------------------------------------------------------
template <class T>
T* Singleton<T>::GetInstance()
{
	return CreateSingleton();
}

};
//===============================================================
//	End of File
//===============================================================