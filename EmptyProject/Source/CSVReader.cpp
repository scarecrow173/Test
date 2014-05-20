//=======================================================================================
//!	@file	:	CSVReader.cpp
//!	@brief	:	CSVReaderクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
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
//!	@brief		: CSVを文字列として読み込む
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void CSVReader::Load(const char* filePath)
{
	std::string str;
	std::ifstream ifs(filePath);
	U32 rowCount	= 0;
	column		= 0;
	row			= 0;

	if( !ifs ) 
	{
		std::cout << "Error:Input data file not found" << std::endl; 
		return;
	}
	while( std::getline( ifs, str ) )
	{
		++column;
		std::string token;
 
		std::istringstream stream( str );
 
		while( std::getline( stream, token, ',' ) ) 
		{
			Impl* data = NEW Impl();
			data->SetData(token);
			Data.push_back(data);
			++rowCount;
		}
		row = row < rowCount ? rowCount : row;
		rowCount = 0;
	}
}
//-------------------------------------------------------------
//!	@brief		: CSVを文字列として読み込む
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
CSVReader::Impl::Impl()
	:	m_IsType	(0) 
	,	str			(0)
{}
//-------------------------------------------------------------
//!	@brief		: CSVを文字列として読み込む
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
CSVReader::Impl::~Impl()
{
	if (m_IsType == DataTypeString)
		SAFE_DELETE_ARRAY(str);
}
//-------------------------------------------------------------
//!	@brief		: CSVを文字列として読み込む
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void CSVReader::Impl::SetData(std::string& data)
{

	if(data.find_first_not_of("-0123456789 \t") == std::string::npos)
	{
		m_IsType = DataTypeInteger;
		S32 num;
		std::stringstream ss;
		ss << data;
		ss >> num;
		integer = num;
	}
	else if(data.find_first_not_of("-0123456789. Ee\t") == std::string::npos)
	{
		m_IsType = DataTypeDecimal;
		std::stringstream ss;
		F32 num;
		ss << data;
		ss >> num;
		decimal = num;
	}
	else
	{
		m_IsType = DataTypeString;
		str = NEW char[data.size() + 1];
		memcpy((void*)str, data.c_str(), sizeof(char) * (data.size() + 1));

	}
			
}
//-------------------------------------------------------------
//!	@brief		: CSVを文字列として読み込む
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
S32	CSVReader::Impl::GetInteger() const
{
	assert(m_IsType == DataTypeInteger);
	return integer;
}
//-------------------------------------------------------------
//!	@brief		: CSVを文字列として読み込む
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
F32	CSVReader::Impl::GetDecimal() const
{
	assert(m_IsType == DataTypeDecimal);
	return decimal;
}
//-------------------------------------------------------------
//!	@brief		: CSVを文字列として読み込む
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
const char*	CSVReader::Impl::GetString() const
{
	assert(m_IsType == DataTypeString);
	return str;
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
