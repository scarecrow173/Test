//=======================================================================================
//!	@file	:	SoundManager.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "bass.h"
#include <vector>
#include "StopWatch.h"

namespace AK
{
namespace Sound
{
//enum SOUND_EFFECT_TYPE
//{
//	EFFECT_NONE		= 0x000000000,
//	EFFECT_FADE_OUT	= 0x000000001,
//	EFFECT_FADE_IN	= 0x000000002,
//	EFFECT_ROTATE	= 0x000000004,
//	EFFECT_FLANGER	= 0x000000008,
//	EFFECT_ECHO		= 0x000000010
//};
//=======================================================================================
//!	@class	:	SoundManager
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class SoundManager
{
public:
	static SoundManager*	Create();
	static void				Destroy();
	static SoundManager*	GetInstance();

	bool	Initalize();
	
	void	PlaySE(U32 streamNum, BOOL restart);
	void	PlayBGM(U32 streamNum, BOOL restart);

	void	PauseSE(U32 streamNum);
	void	PauseBGM(U32 streamNum);

	void	SetVolumeSE(U32 streamNum, F32 volume);
	void	SetVolumeBGM(U32 streamNum, F32 volume);

	void	Update(F32 _dt);

	//void	StopSE(U32 streamNum);
	//void	StopBGM(U32 streamNum);

	bool	IsActiveSE(U32 streamNum);
	bool	IsActiveBGM(U32 streamNum);

	HSTREAM GetStreamHandle(U32 streamNum) { return m_BGMList[streamNum]; }
	HSTREAM GetStreamHandleSE(U32 streamNum) { return m_SEList[streamNum]; }
	U32						m_BGMNum;
	U32						m_SENum;
	StopWatch				m_delta;
protected:

private:
	SoundManager();
	virtual ~SoundManager();

	bool	LoadSEList();
	bool	LoadBGMList();



	static SoundManager*	m_Instance;



	std::vector<HSTREAM>	m_SEList;
	std::vector<HSTREAM>	m_BGMList;
	struct SEHandle
	{
		SEHandle(U32 _handle, bool _restart) : m_SEHandle(_handle), m_Restart(_restart){}
		U32		m_SEHandle;
		bool	m_Restart;
	};
	std::vector<SEHandle>		m_PlaySE;

};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline SoundManager* SoundManager::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}
};
};
//===============================================================
//	End of File
//===============================================================