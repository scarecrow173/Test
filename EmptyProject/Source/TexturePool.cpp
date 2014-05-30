//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "TexturePool.h"
#include "StringEncoder.h"
#include "DefaultTexture.h"
#include "CubeTexture.h"
#include "GraphicsManager.h"
#include <string>

#include <atlbase.h>
#include <atlconv.h>

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
TexturePool::TexturePool()
{
	//	�֐��|�C���^�ȊO�̉�����Ƃ��Ă̓N���X�����邮�炢���ȁH�֐��̋K�͓I�ɃN���X�������ɍs��
	m_TextureLoader["DefaultTexture"]	= LoadDefaultTextureFromFile;
	m_TextureLoader["CubeTexture"]		= LoadCubeTextureFromFile;

	m_TextureCreator["DefaultTexture"]	= CreateDefaultTexture;
	m_TextureCreator["CubeTexture"]		= CreateCubeTexture;
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
TexturePool::~TexturePool()
{
//	auto it = m_PrimitiveCreator.begin(); 
	//while (it != m_PrimitiveCreator.end())
	//{
	//	SAFE_DELETE(it->second);
	//	it = m_PrimitiveCreator.erase(it);
	//}
}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �`�󂲂Ƃ̋��L���\�[�X���擾
//							�^�C�v(data��file)		�@�e�N�X�`���^�C�v				���Oor�t�@�C���p�X
//!	@param[in]	: ��: dataCode = "file				:	DefaultTexture		-	Assets/Texture/sample.png"
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr TexturePool::GetTexture(const std::string& dataCode)
{
	std::string dataType, textureType, name;
	SplitDataPath(dataCode, dataType, textureType, name);

	//auto iCreator = m_TextureLoader.find(textureType);

	////	�t�@�N�g����m_TextureLoader�ɓo�^����Ă��Ȃ���΃A�T�[�g����NULL�̃I�u�W�F�N�g�Ԃ�
	//if (iCreator == m_TextureLoader.end())
	//{
	//	assert(0);	
	//	return RefCountedObjectPtr(NULL);
	//}

	auto it = m_ManagedResouce.find(dataCode);
	if (it != m_ManagedResouce.end())
		return RefCountedObjectPtr(it->second);


	
	return RefCountedObjectPtr(CreateTexture(dataCode, dataType, textureType, name));

}
//=======================================================================================
//		protected method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObject* TexturePool::CreateTexture(const std::string& dataCode, const std::string& dataType, const std::string& textureType, const std::string& name)
{
	//�܂����t�@�N�^�����O�ł�����������ƌ��
	if (!(dataType == "file" || dataType == "data"))
		return NULL;

	if (dataType == "file")
	{
		auto iLoader = m_TextureLoader.find(textureType);
		if (iLoader == m_TextureLoader.end())
			return NULL;
		m_ManagedResouce[dataCode] = m_TextureLoader[textureType](name);
	}
	else if (dataType == "data")
	{
		auto iCreator = m_TextureCreator.find(textureType);
		if (iCreator == m_TextureCreator.end())
			return NULL;
		m_ManagedResouce[dataCode] = m_TextureCreator[textureType]();
	}


	return m_ManagedResouce[dataCode];
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
void TexturePool::SplitDataPath(std::string src, std::string& dataType, std::string& primitiveType, std::string& name)
{
	static StringEncoder encoder;

	encoder.DeleteSpace(src);
	dataType		= encoder.SplitFront(src, ":");
	primitiveType	= encoder.SplitFront(src, "-");
	name			= src;

	assert(dataType			!= "");
	assert(primitiveType	!= "");
	assert(name				!= "");
}
//---------------------------------------------------------------------------------------
//!	@brief		: �ϊ����d���\��
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
ITexture* TexturePool::LoadDefaultTextureFromFile(const std::string& filePath)
{
	DefaultTexture* out = NEW DefaultTexture();
	
	IDirect3DTexture9* tex = NULL;

	USES_CONVERSION;

	D3DXCreateTextureFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		A2W(filePath.c_str()),
		&tex);

	out->SetTexture(&tex);
	return out;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
ITexture* TexturePool::LoadCubeTextureFromFile(const std::string& filePath)
{
	CubeTexture* out = NEW CubeTexture();

	IDirect3DCubeTexture9* tex = NULL;

	USES_CONVERSION;

	D3DXCreateCubeTextureFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		A2W(filePath.c_str()),
		&tex);

	out->SetTexture(&tex);
	return out;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
Graphics::ITexture* TexturePool::CreateDefaultTexture()
{
	DefaultTexture* out = NEW DefaultTexture();
	
	IDirect3DTexture9* tex = NULL;

	out->SetTexture(&tex);

	return out;
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
Graphics::ITexture* TexturePool::CreateCubeTexture()
{
	CubeTexture* out = NEW CubeTexture();

	IDirect3DCubeTexture9* tex = NULL;

	out->SetTexture(&tex);

	return out;
}
//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================