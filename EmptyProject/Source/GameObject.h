//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "INode.h"
#include "MyMath.h"
#include "ICollisonObject.h"
#include "IRenderer.h"
namespace AK
{

//=======================================================================================
//!	@class	:	Sample
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class GameObject : public INode
{
public:
	GameObject(INode* parent, Vector3 pos);
	virtual ~GameObject();

	GameObject*						FindGameObject(Collision::ICollisonObject* collison);
	Vector3							GetPosition() const;
	Collision::ICollisonObject*		GetCollison() const;
	Graphics::IRenderer*			GetRenderer() const;
	

protected:

	Vector3							m_Position;
	Collision::ICollisonObject*		m_Collison;
	Graphics::IRenderer*			m_Renderer;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
inline GameObject::GameObject(INode* parent, Vector3 pos)
	:	INode		(parent)
	,	m_Position (pos)
	,	m_Collison (NULL)
	,	m_Renderer (NULL)
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------	
inline GameObject::~GameObject()
{
	if (m_Collison)
		SAFE_DELETE(m_Collison);

	if (m_Renderer)
		SAFE_DELETE(m_Renderer);
}
//-------------------------------------------------------------
//!	@brief		: Collisonから検索
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline GameObject*	GameObject::FindGameObject(Collision::ICollisonObject* collison)
{
	if (m_Collison == collison)
		return this;
	for (auto it = m_Children.begin(); it != m_Children.end(); ++it)
	{
		auto obj = dynamic_cast<GameObject*>(*it);
		if (!obj)
			continue;
		if (obj->GetCollison() == collison)
			return (obj);
	}
	return NULL;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Vector3	GameObject::GetPosition() const
{
	return m_Position;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Collision::ICollisonObject*	GameObject::GetCollison() const
{
	return m_Collison;
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

};
//===============================================================
//	End of File
//===============================================================