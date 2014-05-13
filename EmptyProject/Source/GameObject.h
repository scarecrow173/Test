//=======================================================================================
//!	@file	:	Sample.h
//!	@author	:	���R �l�\
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

	Vector3							GetPosition();
	Collision::ICollisonObject*		GetCollison();
	Graphics::IRenderer*			GetRenderer();
	

protected:

	Vector3							m_Position;
	Collision::ICollisonObject*		m_Collison;
	Graphics::IRenderer*			m_Renderer;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
inline GameObject::GameObject(INode* parent, Vector3 pos)
	:	INode		(parent)
	,	m_Position (pos)
	,	m_Collison (NULL)
	,	m_Renderer (NULL)
{}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------	
inline GameObject::~GameObject()
{
	if (m_Collison)
		SAFE_DELETE(m_Collison);

	if (m_Renderer)
		SAFE_DELETE(m_Renderer);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Vector3	GameObject::GetPosition()
{
	return m_Position;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Collision::ICollisonObject*	GameObject::GetCollison()
{
	return m_Collison;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
inline Graphics::IRenderer* GameObject::GetRenderer()
{
	return m_Renderer;
}

};
//===============================================================
//	End of File
//===============================================================