//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "GameObject.h"
#include "bass.h"
#include "InputKeyboard.h"
namespace AK
{
namespace Graphics { class IShaderObject;};
class BlockSystem;
class Paddle;

//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class Ball : public GameObject
{
public:
	Ball(INode* parent, Vector3 pos, Paddle* paddle);
	virtual ~Ball();

	
	void Update();
	void Start();

	void SetBlockSystem(BlockSystem* system);
	void SetBottomLine(Collision::ICollisonObject* bottomLine);
	void AddDeathCount();
	void SubDeathCount();
	U32	 GetDeathCount();
	void PopItem(Vector3 pos);
	void SetShader(Graphics::IShaderObject* shader);

private:
	U32							m_DeathCount;
	HSTREAM						m_StreamHndle;
	BlockSystem*				m_BlockSystem;
	Collision::ICollisonObject* m_BottomLine;
	Paddle*						m_Paddle;
	InputKeyboard				m_Keyboard;
	Graphics::IShaderObject*	m_Shader;

	bool						m_IsRespawn;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================