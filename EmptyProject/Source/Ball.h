//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "GameObject.h"
#include "bass.h"
#include "InputKeyboard.h"
#include "IState.h"
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

	//RTTI_GAMEOBJECT_IS_A(Ball);
	RTTI_IS_A(Ball);
	virtual void Update();
	virtual void Start();

	void							SetBlockSystem(BlockSystem* system);
	void							SetBottomLine(Collision::ICollisionObject* bottomLine);
	Collision::ICollisionObject*	GetBottomLine()		const;
	void							AddDeathCount();
	void							SubDeathCount();
	U32								GetDeathCount()		const;
	void							SetShader(Graphics::IShaderObject* shader);
	void							SetPowerup(const bool powerup);
	bool							IsPowerup()			const;
	Paddle*							GetPaddle()			const;
	BlockSystem*					GetBlockSystem()	const;



private:
	bool Death(Collision::ICollisionObject* obj);
	void Respawn();
	void Launch();
	void UpdateMatrix();
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
	F32								m_Radius;

	IState<Ball>*					m_State;
};
//=======================================================================================
//		inline method
//=======================================================================================


};
//===============================================================
//	End of File
//===============================================================