//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "SoundManager.h"

#include "CSVReader.h"

#ifdef _USE_MIDI_SE_
#pragma comment(lib, "MIDIIO.lib")
#pragma comment(lib, "MIDIStatus.lib")
#include "MIDIClock.h"
#include "MIDIIO.h"
#include "MIDIStatus.h"
static MIDIOut* pMIDIOut = nullptr;
static MIDIStatus* pMIDIStatus = nullptr;
#endif

using namespace AK;
using namespace Sound;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
SoundManager*	SoundManager::m_Instance = NULL;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
SoundManager::SoundManager()
	:	m_BGMNum	(0)
	,	m_SENum		(0)
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
SoundManager::~SoundManager()
{
	BASS_Free();
}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: インスタンス生成
//!	@return		: インスタンス
//-------------------------------------------------------------
SoundManager* SoundManager::Create()
{
	if (!m_Instance)
		m_Instance = NEW SoundManager();
	return m_Instance;
}
//-------------------------------------------------------------
//!	@brief		: インスタンス削除
//-------------------------------------------------------------
void SoundManager::Destroy()
{
	SAFE_DELETE(m_Instance);
}
//-------------------------------------------------------------
//!	@brief		: インスタンス削除
//-------------------------------------------------------------
bool SoundManager::Initalize()
{
	BASS_Init(-1, 44100, 0, DXUTGetHWND(), 0);
#ifdef _USE_MIDI_SE_
	pMIDIOut = MIDIOut_OpenA("Microsoft GS Wavetable Synth");
	pMIDIStatus = MIDIStatus_Create(MIDISTATUS_MODENATIVE, 0, 0);
	unsigned char cMIDIMessage[] = { 0xF0, 0x7F, 0x7F, 0x04, 0x01, 0x00, 0x7F, 0xF7 };
	MIDIStatus_PutMIDIMessage(pMIDIStatus, cMIDIMessage, 8);
#endif
	return LoadSEList() && LoadBGMList();
}
//-------------------------------------------------------------
//!	@brief		: SE再生
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PlaySE(U32 streamNum, BOOL restart)
{
	assert(m_SEList.size() > streamNum);
	m_SENum = streamNum;
	m_PlaySE.push_back(SEHandle(streamNum, restart));
	//BASS_ChannelPlay(m_SEList[streamNum], restart);
}
//-------------------------------------------------------------
//!	@brief		: BGM再生
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PlayBGM(U32 streamNum, BOOL restart)
{
	assert(m_BGMList.size() > streamNum);
	PauseBGM(m_BGMNum);
	m_BGMNum = streamNum;
	m_BGMList[streamNum]->Play(restart);
	//BASS_ChannelPlay(m_BGMList[streamNum], restart);
}
//-------------------------------------------------------------
//!	@brief		: 停止
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PauseSE(U32 streamNum)
{
	assert(m_SEList.size() > streamNum);
	BASS_ChannelPause(m_SEList[streamNum]);
}
//-------------------------------------------------------------
//!	@brief		: 停止
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::PauseBGM(U32 streamNum)
{
	assert(m_BGMList.size() > streamNum);
	m_BGMList[streamNum]->Pause();
}
//-------------------------------------------------------------
//!	@brief		: ボリューム変更
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::SetVolumeSE(U32 streamNum, F32 volume)
{
	assert(m_SEList.size() > streamNum);
	BASS_ChannelSetAttribute(m_SEList[streamNum], BASS_ATTRIB_VOL, volume);
}
//-------------------------------------------------------------
//!	@brief		: ボリューム変更
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::SetVolumeBGM(U32 streamNum, F32 volume)
{
	assert(m_BGMList.size() > streamNum);
	
	m_BGMList[streamNum]->SetVolume(volume);
	//BASS_ChannelSetAttribute(m_BGMList[streamNum], BASS_ATTRIB_VOL, volume);
}					
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool SoundManager::IsActiveSE(U32 streamNum)
{
	assert(m_SEList.size() > streamNum);
	return BASS_ChannelIsActive(m_SEList[streamNum]) != 0;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool SoundManager::IsActiveBGM(U32 streamNum)
{
	assert(m_BGMList.size() > streamNum);

	return BASS_ChannelIsActive(m_BGMList[streamNum]->GetHandle()) != 0;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void SoundManager::Update(F32 _dt)
{
#ifdef _USE_MIDI_SE_
	static unsigned char byMIDIMessage1[3] = { 0x90, 0x3C, 0x64 };  /* NoteOn Ch=0 Key=60 Vel=100 */
	static unsigned char byMIDIMessage2[3] = { 0x90, 0x3C, 0x00 };  /* NoteOn Ch=0 Key=60 Vel=0 */
	static unsigned char byMIDIMessage3[3] = { 0xB0, 0x07, 0x7F };
	static		 F32 stop = 0.f;
	static const F32 stopcount = 3.f;
	static bool      isPlaySE = false;

	MIDIOut_PutMIDIMessage(pMIDIOut, byMIDIMessage3, 3); /* ボリューム変更 */

#endif
	m_delta.Update(_dt);
	static const F32 bpm = ((60.f / (149.f * 16.f)));
	auto tmp = m_BGMList[m_BGMNum]->GetBPM() * 4;
	const long t_bpm = 60000 / tmp;
	long current = m_BGMList[m_BGMNum]->GetMillSec() / t_bpm;
	static U32 beforeCount = 0;
	if (current > beforeCount)
	{
		m_delta.Reset();
		m_delta.Update(m_delta.GetTime() - bpm);

		for (auto it = m_PlaySE.begin(); it != m_PlaySE.end(); ++it)
		{
#ifdef _USE_MIDI_SE_
			MIDIOut_PutMIDIMessage(pMIDIOut, byMIDIMessage1, 3); /* ドの音を押す */
			isPlaySE = true;
#else
			BASS_ChannelPlay(m_SEList[it->m_SEHandle], it->m_Restart);
#endif
		}
			
		m_PlaySE.clear();
	}
	beforeCount = current;
#ifdef _USE_MIDI_SE_
	if (isPlaySE)
		stop += _dt;
	if (stop >= stopcount)
	{
		isPlaySE = false;
		stop = 0.f;
 		MIDIOut_PutMIDIMessage(pMIDIOut, byMIDIMessage2, 3); /* ドの音を離す */
	}
#endif
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

	CSVReader SEList;
	SEList.Load("Assets/CSV/SoundList/SEList.csv");	
	for (U32 i = 0; i < SEList.column * SEList.row; ++i)
	{
		auto handle = BASS_StreamCreateFile(FALSE, SEList[i].GetString(), 0, 0, BASS_SAMPLE_FLOAT);
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
	CSVReader BGMList;
	BGMList.Load("Assets/CSV/SoundList/BGMList.csv");	
	for (U32 i = 0; i < BGMList.column * BGMList.row; i += 2)
	{
		auto handle = NEW BGMHandle(BGMList[i].GetString());
		handle->SetBPM(BGMList[i + 1].GetInteger());
		m_BGMList.push_back(handle);
		//auto handle = BASS_StreamCreateFile(FALSE, BGMList[i].GetString(), 0, 0, BASS_SAMPLE_FLOAT | BASS_SAMPLE_LOOP);
		//assert(handle);
		//m_BGMList.push_back(handle);
		
	}
	return true;
}
//===============================================================
//	End of File
//===============================================================
