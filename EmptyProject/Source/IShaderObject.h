//=======================================================================================
//!	@file	:	IShaderObject.h
//!	@author	:	小山 瑛圭
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
	IShaderObject() : m_Effect (NULL), m_DrawStep (0), m_IsActive (true) {};
	virtual ~IShaderObject()
	{ 
		SAFE_RELEASE(m_Effect); 
		if (!m_Renderer.empty())
		{
			std::vector<IRenderer*> clear;
			m_Renderer.swap(clear);
		}
	};
	RTTI_IS_A_BASE(IShaderObject);
	void AddRenderer(IRenderer* renderer);
	void EraseRenderer(const IRenderer* renderer);
	bool IsActive() const;
	void SetActive(const bool active);


	virtual bool Initilize()PURE;
	virtual void Draw()PURE;

	bool operator <(const IShaderObject& obj);
	bool operator >(const IShaderObject& obj);


	U32						m_DrawStep;
protected:
	ID3DXEffect*			m_Effect;
	std::vector<IRenderer*>	m_Renderer;

	bool					m_IsActive;
};
//=======================================================================================
//		inline method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: レンダラー追加
//!	@param[in]	: 追加したいレンダラー
//-------------------------------------------------------------
inline void IShaderObject::AddRenderer(IRenderer* renderer)
{
	auto it = std::find(m_Renderer.begin(), m_Renderer.end(), renderer);

	if (it == m_Renderer.end())
		m_Renderer.push_back(renderer);
}
//-------------------------------------------------------------
//!	@brief		: レンダラー削除
//!	@param[in]	: 削除したいレンダラー
//-------------------------------------------------------------
inline void IShaderObject::EraseRenderer(const IRenderer* renderer)
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
inline bool IShaderObject::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//-------------------------------------------------------------
inline void IShaderObject::SetActive(const bool active)
{
	m_IsActive = active;
}
//-------------------------------------------------------------
//!	@brief		: ソートのため<演算子オーバーロード
//-------------------------------------------------------------
inline	bool IShaderObject::operator <(const IShaderObject& obj)
{
	return m_DrawStep < obj.m_DrawStep;
}
//-------------------------------------------------------------
//!	@brief		: ソートのため>演算子オーバーロード
//-------------------------------------------------------------
inline	bool IShaderObject::operator >(const IShaderObject& obj)
{
	return m_DrawStep > obj.m_DrawStep;
}

};
};
//===============================================================
//	End of File
//===============================================================