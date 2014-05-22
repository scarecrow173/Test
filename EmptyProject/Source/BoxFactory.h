//=======================================================================================
//!	@file	:	BoxFactory.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//=======================================================================================
#pragma once
#include "GraphicsManager.h"
#include "IndexData.h"
#include <vector>
#include <hash_map>
#include <string>
#include <iostream>

namespace AK
{
namespace Graphics
{
//class GraphicsManager;
//=======================================================================================
//!	@class	:	BoxFactory
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BoxFactory
{
public:
	static BoxFactory*	Create();
	static void			Destroy();
	static BoxFactory*	GetInstance();
	
	IndexData			CreateBox(const Vector3 vCenter, const Vector3 size, const VertexARGB color, std::vector<U32>& indexArray);
	IRenderer*			CreateBox(const std::string& name, const VertexARGB color);
	void				AllClear();
private:
	BoxFactory();
	virtual ~BoxFactory();

	static BoxFactory*	m_Instance;
	U32					m_BoxCount;

	std::hash_map<const std::string, IRenderer*>	m_BoxResouce;
};
//=======================================================================================
//	inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: インスタンス取得
//!	@return		: インスタンス
//-------------------------------------------------------------
inline BoxFactory* BoxFactory::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}
};
};
//===============================================================
//	End of File
//===============================================================