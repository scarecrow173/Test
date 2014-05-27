//=======================================================================================
//!	@file	:	TransformObject.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "MyMath.h"
namespace AK
{

//=======================================================================================
//!	@class	:	TransformObject
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class TransformObject
{
public:
	TransformObject();
	TransformObject(Vector3 trans, Vector3 scale = Vector3(1.f, 1.f, 1.f), Vector3 rot = Vector3(0.f, 0.f, 0.f));
	virtual ~TransformObject();

	void UpdateTransform();

	void SetTranslation(const Vector3& trans);
	void SetScaling(const Vector3& scale);
	void SetRotation(const Vector3& rot);
	void SetTransform(const Matrix& transform);

	Vector3 GetTranslation() const; 
	Vector3 GetScaling()	 const;
	Vector3 GetRotation()	 const;
	Matrix	GetTransform()	 const;

private:

	Matrix		m_Transform;

	Vector3		m_Translation;
	Vector3		m_Scaling;
	Vector3		m_Rotation;

};
//=======================================================================================
//		inline method
//=======================================================================================
inline TransformObject::TransformObject()
	:	m_Translation	(0, 0, 0)
	,	m_Scaling		(1, 1, 1)
	,	m_Rotation		(0, 0, 0)
{
	D3DXMatrixIdentity(&m_Transform);
}
inline TransformObject::TransformObject(Vector3 trans, Vector3 scale, Vector3 rot)
	:	m_Translation	(trans)
	,	m_Scaling		(scale)
	,	m_Rotation		(rot)
{
	Matrix matTrans, matScale, matRot;

	D3DXMatrixTranslation(&matTrans, m_Translation.x, m_Translation.y, m_Translation.z);
	D3DXMatrixScaling(&matScale, m_Scaling.x, m_Scaling.y, m_Scaling.z);
	D3DXMatrixRotationYawPitchRoll(&matRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	m_Transform = matRot * matScale * matTrans;
}
inline TransformObject::~TransformObject()
{
}
inline void TransformObject::UpdateTransform()
{
	Matrix matTrans, matScale, matRot;

	D3DXMatrixTranslation(&matTrans, m_Translation.x, m_Translation.y, m_Translation.z);
	D3DXMatrixScaling(&matScale, m_Scaling.x, m_Scaling.y, m_Scaling.z);
	D3DXMatrixRotationYawPitchRoll(&matRot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

	m_Transform = matRot * matScale * matTrans;
}

inline void TransformObject::SetTranslation(const Vector3& trans)
{
	m_Translation = trans;
}

inline void TransformObject::SetScaling(const Vector3& scale)
{
	m_Scaling = scale;
}

inline void TransformObject::SetRotation(const Vector3& rot)
{
	m_Rotation = rot;
}
inline void TransformObject::SetTransform(const Matrix& transform)
{
	m_Transform = transform;
}

inline Vector3 TransformObject::GetTranslation() const
{
	return m_Translation;
}
inline Vector3 TransformObject::GetScaling()	 const
{
	return m_Scaling;
}
inline Vector3 TransformObject::GetRotation()	 const
{
	return m_Rotation;
}
inline Matrix TransformObject::GetTransform()	 const
{
	return m_Transform;
}

};
//===============================================================
//	End of File
//===============================================================