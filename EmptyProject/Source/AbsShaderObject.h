//=======================================================================================
//!	@file	:	AbsShaderObject.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "AbsRenderer.h"
#include "RefCountedObjectPtr.h"
#include "DefaultTexture.h"
#include <algorithm>
namespace AK
{
namespace Graphics
{
//enum DrawStep
//{
//	Default		= 0,
//	PostProcess	= 1000,
//	End			= 2000,
//};
//=======================================================================================
//!	@class	:	AbsShaderObject
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class AbsShaderObject
{
public:
	AbsShaderObject()
		: m_Effect							(NULL)
		, m_DrawStep						(1)
		, m_DefaultRenderTargetDepthSurface	(NULL)
		, m_IsActive (true)
	{}
	virtual ~AbsShaderObject()
	{ 
		SAFE_RELEASE(m_Effect); 
		SAFE_RELEASE(m_DefaultRenderTargetDepthSurface);
		if (!m_Renderer.empty())
		{
			std::vector<AbsRenderer*> clear;
			m_Renderer.swap(clear);
		}
	}
	RTTI_IS_A_BASE(AbsShaderObject);
	void AddRenderer(AbsRenderer* renderer);
	void EraseRenderer(const AbsRenderer* renderer);
	bool IsActive() const;
	void SetActive(const bool active);
	U32	 GetDrawStep() const;
	RefCountedObjectPtr GetRenderTargetPtr() const;


	virtual bool Initilize()= 0;
	virtual void Draw()= 0;

	bool operator <(const AbsShaderObject& obj);
	bool operator >(const AbsShaderObject& obj);


	
protected:
	ID3DXEffect*			m_Effect;
	std::vector<AbsRenderer*>	m_Renderer;

	IDirect3DSurface9*		m_DefaultRenderTargetDepthSurface;

	U32						m_DrawStep;
	bool					m_IsActive;
};
//=======================================================================================
//		inline method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �����_���[�ǉ�
//!	@param[in]	: �ǉ������������_���[
//-------------------------------------------------------------
inline void AbsShaderObject::AddRenderer(AbsRenderer* renderer)
{
	auto it = std::find(m_Renderer.begin(), m_Renderer.end(), renderer);

	if (it == m_Renderer.end())
		m_Renderer.push_back(renderer);
}
//-------------------------------------------------------------
//!	@brief		: �����_���[�폜
//!	@param[in]	: �폜�����������_���[
//-------------------------------------------------------------
inline void AbsShaderObject::EraseRenderer(const AbsRenderer* renderer)
{
	auto it = std::find(m_Renderer.begin(), m_Renderer.end(), renderer);

	if (it == m_Renderer.end())
		return;

	m_Renderer.erase(it);
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
inline bool AbsShaderObject::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
inline void AbsShaderObject::SetActive(const bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
inline U32 AbsShaderObject::GetDrawStep() const
{
	return m_DrawStep;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
//inline RefCountedObjectPtr AbsShaderObject::GetRenderTargetPtr() const
//{
//	return m_DefaultRenderTargetPtr;
//}
//-------------------------------------------------------------
//!	@brief		: �\�[�g�̂���<���Z�q�I�[�o�[���[�h
//-------------------------------------------------------------
inline	bool AbsShaderObject::operator <(const AbsShaderObject& obj)
{
	return m_DrawStep < obj.m_DrawStep;
}
//-------------------------------------------------------------
//!	@brief		: �\�[�g�̂���>���Z�q�I�[�o�[���[�h
//-------------------------------------------------------------
inline bool AbsShaderObject::operator >(const AbsShaderObject& obj)
{
	return m_DrawStep > obj.m_DrawStep;
}

};
};
//===============================================================
//	End of File
//===============================================================