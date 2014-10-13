//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "BGMHandle.h"
using namespace AK;
using namespace Sound;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
BGMHandle::BGMHandle(const std::string& _filename)
:	m_handle	(0)
,	m_isPlaying	(false)
,	m_time		(0.f)
,	m_clockImp	(nullptr)
,	m_bpm		(0)
{
	m_handle = BASS_StreamCreateFile(FALSE, _filename.c_str(), 0, 0, BASS_SAMPLE_FLOAT | BASS_SAMPLE_LOOP);
	m_clockImp = MIDIClock_Create(MIDICLOCK_MASTERTPQNBASE, 120, 60000000 / 100);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
BGMHandle::~BGMHandle()
{
	MIDIClock_Delete(m_clockImp);
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BGMHandle::Play(bool _restart)
{
	if (m_isPlaying)
		return;
	MIDIClock_Start(m_clockImp);
	BASS_ChannelPlay(m_handle, _restart);
	m_isPlaying = true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BGMHandle::Stop()
{
	if (!m_isPlaying)
		return;
	MIDIClock_Stop(m_clockImp);
	BASS_ChannelPause(m_handle);
	m_isPlaying = false;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BGMHandle::Pause()
{
	Stop();
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
bool BGMHandle::IsPlaying()
{
	return m_isPlaying;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void BGMHandle::SetVolume(F32 _volume)
{
	BASS_ChannelSetAttribute(m_handle, BASS_ATTRIB_VOL, _volume);

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
