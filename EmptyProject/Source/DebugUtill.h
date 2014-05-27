//=======================================================================================
//!	@file	:	DebugUtil.h
//!	@author	:	¬ŽR ‰lŒ\
//!	@date	:	2013/12/25
//=======================================================================================
#pragma once
namespace AK
{
namespace Debug
{

#define TRACE(x,y)		AK::Debug::Trace(x, y, __FILE__, __LINE__)

#if defined(DEBUG) || defined(_DEBUG)
#define DEBUG_PRINT_INT(x)		printf("%d\n", x)
#define DEBUG_PRINT_FLOAT(x)	printf("%f\n", x)
#define DEBUG_PRINT_DOUBLE(x)	printf("%f\n", x)
#define DEBUG_PRINT_CHAR(x)		printf("%s\n", x)

#pragma warning(disable:4996)
#define RANGE_CHACK_MESSAGE(x,y) if (x >= y){std::string err("”ÍˆÍ’´‚¦‚Ä‚é‚æ\n"); err += "FILE : ";err += __FILE__; char numToStr[5]; sprintf(numToStr, "%d", __LINE__); err += "\nLINE : ";err += numToStr; ::MessageBoxA(NULL, err.c_str(), "err", MB_OK);}
#define RANGE_CHACK_MESSAGE_NOT(x,y) if (x != y){std::string err("”ÍˆÍ’´‚¦‚Ä‚é‚æ\n"); err += "FILE : ";err += __FILE__; char numToStr[5]; sprintf(numToStr, "%d", __LINE__); err += "\nLINE : ";err += numToStr; ::MessageBoxA(NULL, err.c_str(), "err", MB_OK);}
#define RANGE_CHACK_ASSERT(x,y) if (x >= y){::assert(0);}
#define RANGE_CHACK_MESSAGE_EX(x,y,z) if (x >= y){std::string err("”ÍˆÍ’´‚¦‚Ä‚é‚æ\n"); err += "FILE : ";err += __FILE__; char numToStr[5]; sprintf(numToStr, "%d", __LINE__); err += "\nLINE : ";err += numToStr; ::MessageBoxA(NULL, err.c_str(), "err", MB_OK);z;}

#else
#define DEBUG_PRINT_INT(x)		
#define DEBUG_PRINT_FLOAT(x)	
#define DEBUG_PRINT_DOUBLE(x)	
#define DEBUG_PRINT_CHAR(x)

#define RANGE_CHACK_MESSAGE(x,y)
#define RANGE_CHACK_ASSERT(x,y)
#define RANGE_CHACK_MESSAGE_EX(x,y,z)
#endif

	void __Trace(const char* str);
	void __Trace(const wchar_t* str);
	template<typename T>
	void Trace(U32 level, T _str, const char* _fileName, S32 _line);
	void TraceEx( LPCSTR pszFormat, ...);
	inline void SetTraceLevel(U32 level);

	void CreateDebugConsole();
	void DestoryDebugConsole();
	void UpdateDebugConsole();


	void __setTraceLevel(U32 level);
	U32	 GetTraceLevel();

//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline	void SetTraceLevel(U32 level)
{
	__setTraceLevel(level);
}
template<typename T>
inline void Trace(U32 level, T _str, const char* _fileName, S32 _line)
{
#if defined(DEBUG) || defined(_DEBUG)
	if (level < GetTraceLevel())
		return;
	char numToStr[5];
	char levelToStr[5];
	sprintf_s(numToStr, "%d", _line);
	sprintf_s(levelToStr, "%d", level);
	OutputDebugStringA("FILENAME : ");
	OutputDebugStringA(_fileName);
	OutputDebugStringA("\nLINE : ");
	OutputDebugStringA(numToStr);
	OutputDebugStringA("\n");
	OutputDebugStringA("LEVEL : ");
	OutputDebugStringA(levelToStr);
	OutputDebugStringA("\n");
	__Trace(_str);
	OutputDebugStringA("\n");

#endif
}

};
};

//=======================================================================================
//		End Of File
//=======================================================================================