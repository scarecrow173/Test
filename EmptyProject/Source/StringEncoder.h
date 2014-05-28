//=======================================================================================
//!	@file	:	StringEncoder.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <string>
namespace AK
{

//=======================================================================================
//!	@class	:	StringEncoder
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
//TODO : 現状は空白文字の削除と文字列の切り分けしかないので必要が出たら拡張する
class StringEncoder
{
public:
	StringEncoder(){};
	virtual ~StringEncoder(){};


public:
	//空白文字削除
	void DeleteSpace(std::string& buf)
	{
		size_t pos;
		while((pos = buf.find_first_of(" 　\t")) != std::string::npos)
		{
			buf.erase(pos, 1);
		}
	}
	//	切り分けのキーとなる文字列を元の文字列から削除するべきか？
	//	stringのコピーはしょうがない？
	std::string SplitFront(std::string& buf, const std::string& spritKey)
	{
		size_t pos;
		std::string out;
		if ((pos = buf.find_first_of(spritKey)) != std::string::npos)
		{
			 out = buf.substr(0, pos);
			 buf.erase(0, pos + 1);
		}
		return out;
	}
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================