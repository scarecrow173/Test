//=======================================================================================
//!	@file	:	IShaderObject.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "IRenderer.h"
#include <algorithm>
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	IShaderObject
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class IShaderObject
{
public:
	IShaderObject() : m_Effect (NULL), m_DrawStep (0){};
	virtual ~IShaderObject(){ if (m_Effect) SAFE_RELEASE(m_Effect); m_Renderer.clear(); };

	void AddRenderer(IRenderer* renderer);
	void EraseRenderer(IRenderer* renderer);

	virtual bool Initilize()PURE;
	virtual void Draw()PURE;



protected:
	ID3DXEffect*			m_Effect;
	std::vector<IRenderer*>	m_Renderer;
	U32						m_DrawStep;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: �����_���[�ǉ�
//!	@param[in]	: �ǉ������������_���[
//-------------------------------------------------------------
inline void IShaderObject::AddRenderer(IRenderer* renderer)
{
	auto it = std::find(m_Renderer.begin(), m_Renderer.end(), renderer);

	if (it == m_Renderer.end())
		m_Renderer.push_back(renderer);
}
//-------------------------------------------------------------
//!	@brief		: �����_���[�폜
//!	@param[in]	: �폜�����������_���[
//-------------------------------------------------------------
inline void IShaderObject::EraseRenderer(IRenderer* renderer)
{
	auto it = std::find(m_Renderer.begin(), m_Renderer.end(), renderer);

	if (it == m_Renderer.end())
		return;

	m_Renderer.erase(it);
}


};
};
//===============================================================
//	End of File
//===============================================================