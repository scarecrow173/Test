//=======================================================================================
//!	@file	:	CSVReader.cpp
//!	@brief	:	CSVReader�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "CSVReader.h"
using namespace AK;

//=======================================================================================
//		Constants Definitions
//=======================================================================================


//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: CSV�𐮐��Ƃ��ēǂݍ���
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
CSVData<S32> CSVReader::ReadInteger(std::string filePath)
{
	CSVData<S32> out;
	std::string str;
	std::ifstream ifs(filePath);
	S32 num;
	U32 rowCount	= 0;
	out.column		= 0;
	out.row			= 0;

	if( !ifs ) 
	{
		std::cout << "Error:Input data file not found" << std::endl; 
		return out;
	}
	while( std::getline( ifs, str ) )
	{
		++out.column;
		std::string token;
 
		std::istringstream stream( str );
 
		while( std::getline( stream, token, ',' ) ) 
		{
			std::stringstream ss;
			ss << token;
			ss >> num;
			out.Data.push_back(num);
			++rowCount;
		}
		out.row = out.row < rowCount ? rowCount : out.row;
		rowCount = 0;
	}
	return out;

}
//-------------------------------------------------------------
//!	@brief		: CSV�𕂓������Ƃ��ēǂݍ���
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
CSVData<F32> CSVReader::ReadFloat(std::string filePath)
{
	CSVData<F32> out;
	std::string str;
	std::ifstream ifs(filePath);
	F32 num;
	U32 rowCount	= 0;
	out.column		= 0;
	out.row			= 0;

	if( !ifs ) 
	{
		std::cout << "Error:Input data file not found" << std::endl; 
		return out;
	}
	while( std::getline( ifs, str ) )
	{
		++out.column;
		std::string token;
 
		std::istringstream stream( str );
 
		while( std::getline( stream, token, ',' ) ) 
		{
			std::stringstream ss;
			ss << token;
			ss >> num;
			out.Data.push_back(num);
			++rowCount;
		}
		out.row = out.row < rowCount ? rowCount : out.row;
		rowCount = 0;
	}
	return out;
}
//-------------------------------------------------------------
//!	@brief		: CSV�𕶎���Ƃ��ēǂݍ���
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
CSVData<std::string> CSVReader::ReadString(std::string filePath)
{
	CSVData<std::string> out;
	std::string str;
	std::ifstream ifs(filePath);
	U32 rowCount	= 0;
	out.column		= 0;
	out.row			= 0;

	if( !ifs ) 
	{
		std::cout << "Error:Input data file not found" << std::endl; 
		return out;
	}
	while( std::getline( ifs, str ) )
	{
		++out.column;
		std::string token;
 
		std::istringstream stream( str );
 
		while( std::getline( stream, token, ',' ) ) 
		{
			out.Data.push_back(token);
			++rowCount;
		}
		out.row = out.row < rowCount ? rowCount : out.row;
		rowCount = 0;
	}
	return out;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================
