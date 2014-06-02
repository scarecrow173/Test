//=======================================================================================
//!	@file	:	BufferResource.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "RefCountedObject.h"
#include <vector>
#include "IndexData.h"
namespace AK
{

//=======================================================================================
//!	@class	:	BufferResource
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class BufferResource	: public RefCountedObject
{
public:
	BufferResource();
	virtual ~BufferResource();

	RTTI_IS_A(BufferResource);
	void					AddIndex(std::vector<U32>& add);
	void					PopIndex(const U32 start, const U32 end);
	void					ReCreateIndexBuffer();
	void					UpdateIndexData(const Graphics::IndexData data);
	Graphics::IndexData		GetIndexData() const;
	IDirect3DIndexBuffer9*	GetIndexBuffer() const;


private:
	std::vector<U32>		m_Index;
	IDirect3DIndexBuffer9*	m_IndexBuffer;
	Graphics::IndexData		m_IndexData;


};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline BufferResource::BufferResource()
	:	m_IndexBuffer	(NULL)
{
	m_IndexData.start		= UINT_MAX; 
	m_IndexData.face		= 0;
	m_IndexData.vertexNum	= 0;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline BufferResource::~BufferResource()
{
	SAFE_RELEASE(m_IndexBuffer);
}
//-------------------------------------------------------------
//!	@brief		: インデックスの追加
//!	@param[in]	: 追加したいインデックス
//-------------------------------------------------------------
inline void	BufferResource::AddIndex(std::vector<U32>& add)
{
	m_Index.insert(m_Index.end(), add.begin(), add.end());
}
//-------------------------------------------------------------
//!	@brief		: 外したいインデックス(同じインデックスが複数あると全て外す)
//!	@param[in]	: 外したい初めの値
//!	@param[in]	: 外したい終わりの値
//-------------------------------------------------------------
inline void	BufferResource::PopIndex(const U32 start, const U32 end)
{
	auto it		= m_Index.begin();
	auto eIt	= m_Index.end();
	while (it != eIt)
	{
		if ((*it) >= start && (*it) <= end)
		{
			it = m_Index.erase(it);
			continue;
		}
		 ++it;
	}
}
//-------------------------------------------------------------
//!	@brief		: インデックスバッファ再作成
//-------------------------------------------------------------
inline void BufferResource::ReCreateIndexBuffer()
{
	
	SAFE_RELEASE(m_IndexBuffer);

	DXUTGetD3D9Device()->CreateIndexBuffer((UINT)(sizeof(U32) * m_Index.size()), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_IndexBuffer, 0);

	U32* index;
	m_IndexBuffer->Lock(0, (UINT)(sizeof(U32) * m_Index.size()), (void**)&index, 0);
	memcpy(index, &m_Index[0], sizeof(U32) * m_Index.size());
	m_IndexBuffer->Unlock();
}
//-------------------------------------------------------------
//!	@brief		: インデックスデータ更新
//!	@param[in]	: インデックスデータ
//-------------------------------------------------------------
inline void BufferResource::UpdateIndexData(const Graphics::IndexData data)
{
	m_IndexData.start		= min(m_IndexData.start, data.start);
	m_IndexData.face		+= data.face;
	m_IndexData.vertexNum	+= data.vertexNum;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline 	Graphics::IndexData BufferResource::GetIndexData() const
{
	return m_IndexData;
}
//-------------------------------------------------------------
//!	@brief		: 
//-------------------------------------------------------------
inline IDirect3DIndexBuffer9*	BufferResource::GetIndexBuffer() const
{
	return m_IndexBuffer;
}

};
//===============================================================
//	End of File
//===============================================================