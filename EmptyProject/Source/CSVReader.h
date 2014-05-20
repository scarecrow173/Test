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
//#define _CSVREADER_MODE_01
namespace AK
{
class CSVReader
{
	class Impl
	{
	public:
		Impl();
		~Impl();

		void		SetData(std::string& data);
		S32			GetInteger()	const;
		F32			GetDecimal()	const;
		const char*	GetString()		const;

		static const U8 DataTypeInteger	= 0x01;
		static const U8 DataTypeDecimal	= 0x02;
		static const U8 DataTypeString	= 0x04;
		union
		{
			S32			integer;
			F32			decimal;
			const char* str;
		};
		U8 m_IsType;

	};
public:
	void Load(const char* filePath);

	U32 column;
	U32 row;
	Impl& operator [] (S32 num)
	{
		assert(Data.size() > num);
		return *Data[num];
	}
private:

	std::vector<Impl*> Data;

};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================