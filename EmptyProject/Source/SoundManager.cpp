//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sample�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "SoundManager.h"
#include "CSVReader.h"
using namespace AK;
using namespace Sound;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
SoundManager*	SoundManager::m_Instance = NULL;
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
SoundManager::SoundManager()
	:	m_BGMNum	(0)
	,	m_SENum		(0)
{}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
SoundManager::~SoundManager()
{
	BASS_Free();
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �C���X�^���X����
//!	@return		: �C���X�^���X
//-------------------------------------------------------------
SoundManager* SoundManager::Create()
{
	if (m_Instance)
		return m_Instance;

	m_Instance = NEW SoundManager();
	return m_Instance;
}
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�폜
//-------------------------------------------------------------
void SoundManager::Destroy()
{
	SAFE_DELETE(m_Instance);
}
//-------------------------------------------------------------
//!	@brief		: �C���X�^���X�폜
//-------------------------------------------------------------
bool SoundManager::Initalize()
{
	BASS_Init(-1, 44100, 0, DXUTGetHWND(), 0);
	return LoadSEList() && LoadBGMList();
}
//-------------------------------------------------------------
//!	@brief		: SE�Đ�
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PlaySE(U32 streamNum, BOOL restart)
{
	assert(m_SEList.size() > streamNum);
	m_SENum = streamNum;
	BASS_ChannelPlay(m_SEList[streamNum], restart);
}
//-------------------------------------------------------------
//!	@brief		: BGM�Đ�
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PlayBGM(U32 streamNum, BOOL restart)
{
	assert(m_BGMList.size() > streamNum);
	PauseBGM(m_BGMNum);
	m_BGMNum = streamNum;
	BASS_ChannelPlay(m_BGMList[streamNum], restart);
}
//-------------------------------------------------------------
//!	@brief		: ��~
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PauseSE(U32 streamNum)
{
	assert(m_SEList.size() > streamNum);
	BASS_ChannelPause(m_SEList[streamNum]);
}
//-------------------------------------------------------------
//!	@brief		: ��~
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PauseBGM(U32 streamNum)
{
	assert(m_BGMList.size() > streamNum);
	BASS_ChannelPause(m_BGMList[streamNum]);
}
//-------------------------------------------------------------
//!	@brief		: �{�����[���ύX
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::SetVolumeSE(U32 streamNum, F32 volume)
{
	assert(m_SEList.size() > streamNum);
	BASS_ChannelSetAttribute(m_BGMList[streamNum], BASS_ATTRIB_VOL, volume);
}
//-------------------------------------------------------------
//!	@brief		: �{�����[���ύX
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::SetVolumeBGM(U32 streamNum, F32 volume)
{
	assert(m_BGMList.size() > streamNum);
	
	BASS_ChannelSetAttribute(m_BGMList[streamNum], BASS_ATTRIB_VOL, volume);
}					
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool SoundManager::IsActiveSE(U32 streamNum)
{
	assert(m_SEList.size() > streamNum);
	return BASS_ChannelIsActive(m_SEList[streamNum]);	
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool SoundManager::IsActiveBGM(U32 streamNum)
{
	assert(m_BGMList.size() > streamNum);

	return BASS_ChannelIsActive(m_BGMList[streamNum]);
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool SoundManager::LoadSEList()
{
	auto SEList = CSVReader::ReadString("Assets/CSV/SoundList/SEList.csv");
	
	for (auto it = SEList.Data.begin(); it != SEList.Data.end(); ++it)
	{
		auto handle = BASS_StreamCreateFile(FALSE, (*it).c_str(), 0, 0, BASS_SAMPLE_FLOAT);
		assert(handle);
		m_SEList.push_back(handle);
	}
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool SoundManager::LoadBGMList()
{
	auto BGMList = CSVReader::ReadString("Assets/CSV/SoundList/BGMList.csv");
	
	for (auto it = BGMList.Data.begin(); it != BGMList.Data.end(); ++it)
	{
		auto handle = BASS_StreamCreateFile(FALSE, (*it).c_str(), 0, 0, BASS_SAMPLE_FLOAT | BASS_SAMPLE_LOOP);
		assert(handle);
		m_BGMList.push_back(handle);
	}
	return true;
}
//===============================================================
//	End of File
//===============================================================
