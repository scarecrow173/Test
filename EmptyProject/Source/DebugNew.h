#pragma once
#include <new>
// ���������[�N���o�p��NEW

#ifdef _DEBUG
#define NEW			new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define MALLOC(s)	_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)




#else
#define NEW			new
#define MALLOC(s)	malloc(s)




#endif
