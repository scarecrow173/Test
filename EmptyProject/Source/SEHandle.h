////=======================================================================================
////!	@file	:	SEHandle.h
////!	@author	:	è¨éR âlå\
////!	@date	:	2014/4/28
////=======================================================================================
//#pragma once
//#include <vector>
//#include "bass.h"
//#include <vector>
//#include "StopWatch.h"
//#pragma comment(lib, "MIDIIO.lib")
//#include "MIDIIO.h"
//#define _USE_MIDI_SE_
//namespace AK
//{
//namespace Sound
//{
////=======================================================================================
////!	@class	:	BGMHandle
////!	@brief	:	example
////!	@par	:	example
////!	@note	:	example
////=======================================================================================
//class SEHandle
//{
//public:
//	SEHandle(const std::string& _filename);
//	virtual ~SEHandle();
//
//	void Play(bool _restart);
//	void Stop();
//	void Pause();
//
//	bool IsPlaying();
//	void SetVolume(F32 _volume);
//
//	HSTREAM GetHandle(){ return m_handle; }
////	long	GetMillSec() { return MIDIClock_GetMillisec(m_clockImp); }
//private:
//#ifdef _USE_MIDI_SE_
//	static MIDIOut* pMIDIOut;
//#endif
//	HSTREAM		m_handle;
//	F32			m_time;
//	bool		m_isPlaying;
////	MIDIClock*	m_clockImp;
//
//};
//
//};
//};
////===============================================================
////	End of File
////===============================================================