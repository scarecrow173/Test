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
	m_PrimitiveCreator["RING"]		= NEW RingFactory();
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
RefCountedObjectPtr PrimitivePool::GetResource(const std::string& dataCode)
{
	std::string dataType, primiveType, name;
	SplitDataPath(dataCode, dataType, primiveType, name);

	auto iCreator = m_PrimitiveCreator.find(primiveType);
	//	�t�@�C���ǂݍ��݂͖������Ȃ̂ŃA�T�[�g����NULL�̃I�u�W�F�N�g��Ԃ�
	//	�t�@�N�g����m_PrimitiveCreator�ɓo�^����Ă��Ȃ���΃A�T�[�g����NULL�̃I�u�W�F�N�g�Ԃ�
	if (dataType != "data" || iCreator == m_PrimitiveCreator.end())
	{
		assert(0);	
		return RefCountedObjectPtr(NULL);
	}

	auto it = m_ManagedResource.find(dataCode);
	if (it != m_ManagedResource.end())
		return it->second;

	m_ManagedResource[dataCode] = RefCountedObjectPtr(m_PrimitiveCreator[primiveType]->CreatePrimitive());
	
	return m_ManagedResource[dataCode];
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