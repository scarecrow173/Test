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
namespace Collision{ class ICollisionObject; }
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

	
	virtual void Update();
	virtual void Start();

	void SetBlockSystem(BlockSystem* system);
	void SetBottomLine(Collision::ICollisionObject* bottomLine);
	void AddDeathCount();
	void SubDeathCount();
	U32	 GetDeathCount() const;
	void SetShader(Graphics::IShaderObject* shader);
	void SetPowerup(const bool powerup);
	bool IsPowerup() const;



private:
	bool Death(Collision::ICollisionObject* obj);
	void Respawn();
	void Launch();
	void Move();
	void Powerup();
	
	U32								m_DeathCount;
	BlockSystem*					m_BlockSystem;
	Collision::ICollisionObject*	m_BottomLine;
	Paddle*							m_Paddle;
	InputKeyboard					m_Keyboard;
	Graphics::IShaderObject*		m_Shader;

	bool							m_IsRespawn;
	bool							m_IsPowerup;
	U32								m_PowerupCount;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================