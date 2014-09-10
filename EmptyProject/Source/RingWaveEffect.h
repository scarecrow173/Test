//=======================================================================================
//!	@file	:	RingWaveEffect.h
//!	@author	:	è¨éR âlå\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once

#include <memory>
#include "RefCountedObjectPtr.h"
#include "TransformObject.h"
namespace AK
{
namespace Graphics
{
class	AbsRenderer;
class	DefaultShader;
namespace Util
{
//=======================================================================================
//!	@class	:	RingWaveEffect
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class RingWaveEffect
{
public:
	RingWaveEffect(F32 _speed = 0.001f, Vector3 _limit3d = Vector3(500, 500, 0));
	virtual ~RingWaveEffect();

	void Update(F32 _deltaTime);

	void SetMaterial(const RefCountedObjectPtr material);
	void SetTexture(const RefCountedObjectPtr texture);
	void SetTransform(std::shared_ptr<TransformObject> transform);
private:
	AbsRenderer*						m_Renderer;
	DefaultShader*						m_Shader;
	std::shared_ptr<TransformObject>	m_Transform;

	Vector3								m_Position;
	Vector3								m_Size;
	F32									m_ScalingSpeedFactor;
	F32									m_CurrentFactor;
	F32									m_Alpha;
	Vector3								m_LimitSize;
};
//=======================================================================================
//		inline method
//=======================================================================================
};
};
};
//===============================================================
//	End of File
//===============================================================