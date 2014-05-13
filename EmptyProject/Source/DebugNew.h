#pragma once
#include <new>
// メモリリーク検出用のNEW

#ifdef _DEBUG
#define NEW			new (_NORMAL_BLOCK, __FILE__, __LINE__)
#define MALLOC(s)	_malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)




#else
#define NEW			new
#define MALLOC(s)	malloc(s)




#endif
