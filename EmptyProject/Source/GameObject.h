//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "INode.h"
#include "MyMath.h"
#include "ICollisionObject.h"
#include "IRenderer.h"
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
class GameObject : public INode
{
public:
	GameObject(INode* parent, Vector3 pos);
	virtual ~GameObject();

	std::shared_ptr<TransformObject>	GetTransform() const;
	Collision::ICollisionObject*		GetCollision() const;
	Graphics::IRenderer*				GetRenderer() const;

	RTTI_IS_A(GameObject);
	virtual	void					Affect(GameObject* obj);

protected:

	Collision::ICollisionObject*		m_Collision;
	Graphics::IRenderer*				m_Renderer;
	std::shared_ptr<TransformObject>	m_Transform;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
inline GameObject::GameObject(INode* parent, Vector3 pos)
	:	INode		(parent)
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
inline Collision::ICollisionObject*	GameObject::GetCollision() const
{
	return m_Collision;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Graphics::IRenderer* GameObject::GetRenderer() const
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