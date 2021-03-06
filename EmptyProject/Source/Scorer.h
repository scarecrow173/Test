//=======================================================================================
//!	@file	:	Scorer.h
//!	@author	:	���R �l�\
//!	@date	:	2014/6/12
//=======================================================================================
#pragma once

namespace AK
{
//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Scorer
{
public:
	Scorer();
	virtual ~Scorer();

	void	AddScore(const U32 addScore);
	void	Reset();
	U32		GetScore()	const;
private:
	U32		m_Score;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================