//=======================================================================================
//!	@file	:	AutoPerformance.h
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//=======================================================================================
#ifndef _INCLUDE_AUTOPERFORMANCE_H_
#define _INCLUDE_AUTOPERFORMANCE_H_
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "Kernel32.lib")
#include <Windows.h>
#include <unordered_map>
#include <mmsystem.h>
namespace AK
{
namespace Debug
{
#define AUTOPROFILE(NUM) AK::Debug::AutoPerformance AutoProfile(NUM)
//=======================================================================================
//!	@class	:	AutoPerformance
//!	@brief	:	�����ő��x�v������N���X
//!	@par	:	AUTOPROFILE(NAME)�}�N���ō��ږ�������
//!	@note	:	�X�R�[�v���ł����������Ԃ��v��
//=======================================================================================
class AutoPerformance
{
public:
	AutoPerformance(U32 handle);
	~AutoPerformance();
#ifdef _DEBUG
	static std::unordered_map<U32, DWORD>	m_ProfileList;
#endif
private:
#ifdef _DEBUG
	LARGE_INTEGER						m_Frequency;
	LARGE_INTEGER						m_Before;
	LARGE_INTEGER						m_After;
	U32									m_Handle;
#endif
};
//=======================================================================================
//	inline Method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//!	@param[in]	: handle
//-------------------------------------------------------------
inline AutoPerformance::AutoPerformance(U32 handle)
{
#ifdef _DEBUG
	memset(&m_Frequency, 0x00, sizeof m_Frequency);
	memset(&m_Before, 0x00, sizeof m_Before);
	memset(&m_After, 0x00, sizeof m_After);
	
	m_Handle = handle;
	QueryPerformanceFrequency(&m_Frequency);
	QueryPerformanceCounter(&m_Before);
#endif
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
inline AutoPerformance::~AutoPerformance()
{
#ifdef _DEBUG
	QueryPerformanceCounter(&m_After);
	m_ProfileList[m_Handle] += (DWORD)((m_After.QuadPart - m_Before.QuadPart) * 1000000 / m_Frequency.QuadPart);
	m_ProfileList[m_Handle] /= 2;
#endif
}
}
}
#endif
//=======================================================================================
//		End Of File
//=======================================================================================