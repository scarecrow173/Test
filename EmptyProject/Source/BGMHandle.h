//=======================================================================================
//!	@file	:	BGMHandle.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "bass.h"
#include <vector>
#include "StopWatch.h"
#pragma comment(lib, "MIDIClock.lib")
#include "MIDIClock.h"
namespace AK
{
namespace Sound
{
//=======================================================================================
//!	@class	:	BGMHandle
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BGMHandle
{
public:
	BGMHandle(const std::string& _filename);
	virtual ~BGMHandle();

	void Play(bool _restart);
	void Stop();
	void Pause();
	
	bool IsPlaying();
	void SetVolume(F32 _volume);
	
	HSTREAM GetHandle() const { return m_handle; }
	long	GetMillSec() { return MIDIClock_GetMillisec(m_clockImp); }
	void	SetBPM(long _bpm) { m_bpm = _bpm; }
	long	GetBPM() const { return m_bpm; }
private:
	HSTREAM		m_handle;
	F32			m_time;
	bool		m_isPlaying;
	MIDIClock*	m_clockImp;
	long		m_bpm;
	
};

};
};
//===============================================================
//	End of File
//===============================================================