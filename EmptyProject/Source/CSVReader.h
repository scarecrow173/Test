//=======================================================================================
//!	@file	:	CSVReader.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
namespace AK
{
template <typename T>
struct CSVData
{
	U32 column;
	U32 row;
	std::vector<T> Data;
};
//=======================================================================================
//!	@class	:	CSVReader
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class CSVReader
{
public:
	static CSVData<S32>			ReadInteger(std::string filePath);
	static CSVData<F32>			ReadFloat(std::string filePath);
	static CSVData<std::string>	ReadString(std::string filePath);

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================