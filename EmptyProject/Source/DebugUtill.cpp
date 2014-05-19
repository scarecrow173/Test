//=======================================================================================
//!	@file	:	DebugUtil.cpp
//!	@brief	:	デバッグ用のユーティリティ
//!	@author	:	小山 瑛圭
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
//!	@brief		: コンソールウィンドウ作成(デバッグ時のみ)
//-------------------------------------------------------------
void CreateDebugConsole()
{
#if defined(DEBUG) || defined(_DEBUG)
	if (!isConsole)
	{
		isConsole = true;
		::AllocConsole();
		freopen( "CON", "r", stdin  );  // 標準入力を割り当てる
		freopen( "CON", "w", stdout );  // 標準出力を割り当てる
	}
#endif
}
//-------------------------------------------------------------
//!	@brief		: コンソールウィンドウ削除(デバッグ時のみ)
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
//!	@brief		: コンソール画面のクリア(デバッグ時のみ)
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