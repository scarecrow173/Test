//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "PrimitivePool.h"
#include "StringEncoder.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
PrimitivePool::PrimitivePool()
{
	//	�t�@�N�g���̖��O�̓t�@�C������ǂݍ��ނׂ��H
	m_PrimitiveCreator["BOX"]		= NEW BoxFactory();
	m_PrimitiveCreator["SHPERE"]	= NEW SphereFactory();
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
PrimitivePool::~PrimitivePool()
{
	auto it = m_PrimitiveCreator.begin(); 
	while (it != m_PrimitiveCreator.end())
	{
		SAFE_DELETE(it->second);
		it = m_PrimitiveCreator.erase(it);
	}
	auto iResouce = m_ManagedResouce.begin();
	while (iResouce != m_ManagedResouce.end())
	{
		iResouce = m_ManagedResouce.erase(iResouce);
	}
}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �`�󂲂Ƃ̋��L���\�[�X���擾(file�ǂݍ��ݖ�����)
//							�^�C�v(data��file)		�@�`��w��	�@�@���O
//!	@param[in]	: ��: dataCode = "data				:	BOX		-	Box01"
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr PrimitivePool::GetPrimitive(const std::string& dataCode)
{
	std::string dataType, primiveType;
	SplitDataPath(dataCode, dataType, primiveType/*, name*/);

	auto iCreator = m_PrimitiveCreator.find(primiveType);
	//	�t�@�C���ǂݍ��݂͖������Ȃ̂ŃA�T�[�g����NULL�̃I�u�W�F�N�g��Ԃ�
	//	�t�@�N�g����m_PrimitiveCreator�ɓo�^����Ă��Ȃ���΃A�T�[�g����NULL�̃I�u�W�F�N�g�Ԃ�
	if (dataType != "data" || iCreator == m_PrimitiveCreator.end())
	{
		assert(0);	
		return RefCountedObjectPtr(NULL);
	}

	auto it = m_ManagedResouce.find(dataCode);
	if (it != m_ManagedResouce.end())
		return it->second;

	m_ManagedResouce[dataCode] = RefCountedObjectPtr(m_PrimitiveCreator[primiveType]->CreatePrimitive());
	
	return m_ManagedResouce[dataCode];
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
void PrimitivePool::SplitDataPath(std::string src, std::string& dataType, std::string& primitiveType/*, std::string& name*/)
{
	static StringEncoder encoder;

	encoder.DeleteSpace(src);
	dataType		= encoder.SplitFront(src, ":");
	primitiveType	= encoder.SplitFront(src, "-");
	//name			= src;

	assert(dataType			!= "");
	assert(primitiveType	!= "");
	//assert(name				!= "");
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