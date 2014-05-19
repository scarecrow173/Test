//=======================================================================================
//!	@file	:	DebugUtil.cpp
//!	@brief	:	�f�o�b�O�p�̃��[�e�B���e�B
//!	@author	:	���R �l�\
//!	@date	:	2013/12/25
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "DebugUtill.h"
//#include <debugapi.h>
#include <wincon.h>
#include <map>
#if defined(DEBUG) || defined(_DEBUG)
bool	isConsole	= false;
U32		TraceLevel	= 0;
#endif
namespace AK{
namespace Debug
{
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Trace(U32 level, const char* _str, const char* _fileName, S32 _line)
{
#if defined(DEBUG) || defined(_DEBUG)
	if (level < TraceLevel)
		return;
	char numToStr[5];
	char levelToStr[5];
#pragma warning(disable:4996)
	sprintf(numToStr, "%d", _line);
	sprintf(levelToStr, "%d", level);
	OutputDebugStringA("FILENAME : ");
	OutputDebugStringA(_fileName);
	OutputDebugStringA("\nLINE : ");
	OutputDebugStringA(numToStr);
	OutputDebugStringA("\n");
	OutputDebugStringA("LEVEL : ");
	OutputDebugStringA(levelToStr);
	OutputDebugStringA("\n");
	OutputDebugStringA(_str);
	OutputDebugStringA("\n");

#endif
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Trace(U32 level, const wchar_t* _str, const char* _fileName, S32 _line)
{
#if defined(DEBUG) || defined(_DEBUG)
	if (level < TraceLevel)
		return;
	char numToStr[5];
	char levelToStr[5];
#pragma warning(disable:4996)
	sprintf(numToStr, "%d", _line);
	sprintf(levelToStr, "%d", level);
	OutputDebugStringA("FILENAME : ");
	OutputDebugStringA(_fileName);
	OutputDebugStringA("\nLINE : ");
	OutputDebugStringA(numToStr);
	OutputDebugStringA("\n");
	OutputDebugStringA("LEVEL : ");
	OutputDebugStringA(levelToStr);
	OutputDebugStringA("\n");
	OutputDebugStringW(_str);
	OutputDebugStringW(L"\n");
#endif
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//-------------------------------------------------------------
void TraceEx( LPCSTR pszFormat, ...)
{
#if defined(DEBUG) || defined(_DEBUG)
    va_list	argp;
    char pszBuf[ 256];
    va_start(argp, pszFormat);
    vsprintf( pszBuf, pszFormat, argp);
    va_end(argp);
    OutputDebugStringA( pszBuf);
#endif
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//-------------------------------------------------------------
void SetTraceLevel(U32 level)
{
#if defined(DEBUG) || defined(_DEBUG)
	TraceLevel = level;
#endif
}
//-------------------------------------------------------------
//!	@brief		: �R���\�[���E�B���h�E�쐬(�f�o�b�O���̂�)
//-------------------------------------------------------------
void CreateDebugConsole()
{
#if defined(DEBUG) || defined(_DEBUG)
	if (!isConsole)
	{
		isConsole = true;
		::AllocConsole();
		freopen( "CON", "r", stdin  );  // �W�����͂����蓖�Ă�
		freopen( "CON", "w", stdout );  // �W���o�͂����蓖�Ă�
	}
#endif
}
//-------------------------------------------------------------
//!	@brief		: �R���\�[���E�B���h�E�폜(�f�o�b�O���̂�)
//-------------------------------------------------------------
void DestoryDebugConsole()
{
#if defined(DEBUG) || defined(_DEBUG)
	if (isConsole)
	{
		isConsole = false;
		::FreeConsole();
	}
#endif
}
//-------------------------------------------------------------
//!	@brief		: �R���\�[����ʂ̃N���A(�f�o�b�O���̂�)
//-------------------------------------------------------------
void UpdateDebugConsole()
{
#if defined(DEBUG) || defined(_DEBUG)
	if (isConsole)
	{
		system("cls");
	}
#endif
}
};
};

//=======================================================================================
//		End Of File
//=======================================================================================