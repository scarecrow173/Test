//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "AbsNode.h"
#include "MyMath.h"
#include "AbsCollisionObject.h"
#include "AbsRenderer.h"
#include "RefCountedObjectPtr.h"
#include "TransformObject.h"
namespace AK
{

//=======================================================================================
//!	@class	:	GameObject
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class GameObject : public AbsNode
{
public:
	GameObject(AbsNode* parent, Vector3 pos);
	virtual ~GameObject();

	std::shared_ptr<TransformObject>	GetTransform() const;
	Collision::AbsCollisionObject*		GetCollision() const;
	Graphics::AbsRenderer*				GetRenderer() const;

	RTTI_IS_A(GameObject);
	virtual	void					Affect(GameObject* obj);

protected:

	Collision::AbsCollisionObject*		m_Collision;
	Graphics::AbsRenderer*				m_Renderer;
	std::shared_ptr<TransformObject>	m_Transform;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
inline GameObject::GameObject(AbsNode* parent, Vector3 pos)
	:	AbsNode		(parent)
	,	m_Collision (NULL)
	,	m_Renderer	(NULL)
	,	m_Transform	(std::make_shared<TransformObject>(pos))
{
	
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------	
inline GameObject::~GameObject()
{
	SAFE_DELETE(m_Collision);

	
	SAFE_DELETE(m_Renderer);
}

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline std::shared_ptr<TransformObject> GameObject::GetTransform() const
{
	return m_Transform;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Collision::AbsCollisionObject*	GameObject::GetCollision() const
{
	return m_Collision;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Graphics::AbsRenderer* GameObject::GetRenderer() const
{
	return m_Renderer;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline void GameObject::Affect(GameObject* obj)
{}
};
//===============================================================
//	End of File
//===============================================================