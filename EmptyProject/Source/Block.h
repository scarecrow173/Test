//=======================================================================================
//!	@file	:	Block.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "GameObject.h"
#include "IndexData.h"
#include "Elements.h"
#include "SoundManager.h"
#include "TextureAnimationController.h"
#include "UITextureRenderer.h"
#include "RingWaveEffect.h"
namespace AK
{
enum BlockLevel
{
	BLOCK_WHITE = 0,
	BLOCK_ORANGE,
	BLOCK_AQUA,
	BLOCK_GREEN,
	BLOCK_RED,
	BLOCK_BLUE,
	BLOCK_PINK,
	BLOCK_HARD,
	BLOCK_IMMORTALITY,

	BLOCK_LEVEL_NUM
};
namespace DeadStep
{
	enum DeadStep
	{
		StopedStep	= 0,
		StartDeadStep,
		UpdateEffectStep,
		EndDeadStep,
	};
};
namespace HardBlockStep
{
	enum HardBlockStep
	{
		StopedHardEffectStep	= 0,
		StartHardEffectStep,
		UpdateHardEffectStep,
		EndHardEffectStep,
	};
};
//=======================================================================================
//!	@class	:	Block
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Block : public GameObject
{
public:
	Block(AbsNode* parent, Vector3 pos, U32 lifeCount);
	virtual ~Block();

	RTTI_IS_A(Block);
	virtual void	Update();
	virtual void	Start();

	bool	Death();
	void	SetSEHandle(const U32 handle);
	//Graphics::UITextureRenderer* GetEffectRenderer() const;
	//Graphics::UITextureRenderer* GetHardEffectRenderer() const;
	Graphics::Util::RingWaveEffect*	GetRingRenderer() const;

private:
	void			StartDeadStep();
	void			UpdateEffectStep();
	void			EndDeadStep();

	void	StopedHardEffectStep();
	void	StartHardEffectStep();
	void	UpdateHardEffectStep();
	void	EndHardEffectStep();

	TransformObject GetTransformTo2D();

	U32										m_LifeCount;
	BlockLevel								m_BlockLevel;
	Graphics::IndexData						m_IndexData;
	Graphics::VertexARGB					m_Color;
	U32										m_SEHandle;
	//Graphics::UITextureRenderer*			m_Effect;
	//Graphics::TextureAnimationController*	m_EffectContoroller;
	//Graphics::UITextureRenderer*			m_HardEffect;
	//Graphics::TextureAnimationController*	m_HardEffectContoroller;
	DeadStep::DeadStep						m_DeadStep;
	HardBlockStep::HardBlockStep			m_HardEffectStep;
	Graphics::Util::RingWaveEffect*			m_RingEffect;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================