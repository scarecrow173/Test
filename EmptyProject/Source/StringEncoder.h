//=======================================================================================
//!	@file	:	StringEncoder.h
//!	@author	:	���R �l�\
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
//TODO : ����͋󔒕����̍폜�ƕ�����̐؂蕪�������Ȃ��̂ŕK�v���o����g������
class StringEncoder
{
public:
	StringEncoder(){};
	virtual ~StringEncoder(){};


public:
	//�󔒕����폜
	void DeleteSpace(std::string& buf)
	{
		size_t pos;
		while((pos = buf.find_first_of(" �@\t")) != std::string::npos)
		{
			buf.erase(pos, 1);
		}
	}
	//	�؂蕪���̃L�[�ƂȂ镶��������̕����񂩂�폜����ׂ����H
	//	string�̃R�s�[�͂��傤���Ȃ��H
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