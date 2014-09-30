//=======================================================================================
//!	@file	:	SphereFactory.cpp
//!	@brief	:	SphereFactoryクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/05/01
//!	@par	:	
//!	@note	:	
//=======================================================================================
#include "SphereFactory.h"
#include "TriangleRenderer.h"
#include "BufferResource.h"

using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
SphereFactory*	SphereFactory::m_Instance = NULL;

//---------------------------------------------------------------------------------------
//!	@brief		: コンストラクタ
//---------------------------------------------------------------------------------------
SphereFactory::SphereFactory()
	:	m_SphereCount	(0)
{

}
//---------------------------------------------------------------------------------------
//!	@brief		: デストラクタ
//---------------------------------------------------------------------------------------
SphereFactory::~SphereFactory()
{

}
//=======================================================================================
//		public method
//=======================================================================================
//
//---------------------------------------------------------------------------------------
//!	@brief		: 球作成
//!	@param[in]	: 中心位置
//!	@param[in]	: 半径
//!	@param[in]	: 色
//!	@param[in]	: インデックス格納先
//!	@return		: インデックスデータ
//---------------------------------------------------------------------------------------
BufferResource* SphereFactory::CreatePrimitive()
{
	assert(GraphicsManager::SPHERE_NUM > m_SphereCount);
	
	
	const F32		radius		= 1.f;
	const Vector3	vCenter		= Vector3(0, 0, 0);
	static U32		boxOffset	= (GraphicsManager::ONE_BOX_VERTEX_NUM * GraphicsManager::BOX_NUM);
	const U32		offset		= boxOffset + (m_SphereCount * GraphicsManager::ONE_SPHERE_VERTEX_NUM);
	U32 count		= 0;
	


	for (U32 iStack = 0; iStack <= GraphicsManager::SPHERE_STACKS; ++iStack)
	{
		F32 ph	= Math::PI * (F32)iStack / GraphicsManager::SPHERE_STACKS;
		F32 y	= (Math::Cos(ph) * radius) + vCenter.y;
		F32	r	= Math::Sin(ph) * radius;
		for (U32 iSlice = 0; iSlice <= GraphicsManager::SPHERE_SLICES; ++iSlice)
		{
			F32 th	= Math::PI2 * (F32)iSlice / (F32)GraphicsManager::SPHERE_SLICES;
			F32 x	= r * Math::Cos(th) + vCenter.x;
			F32 z	= r * Math::Sin(th) + vCenter.z;
			
			GraphicsManager::m_VertexBase[offset + count].position.x = x;
			GraphicsManager::m_VertexBase[offset + count].position.y = y;
			GraphicsManager::m_VertexBase[offset + count].position.z = z;
			
			Vector3 normal;
			normal.x = vCenter.x - x;
			normal.y = vCenter.y - y;
			normal.z = vCenter.z - z;
			D3DXVec3Normalize(&normal, &normal);
			GraphicsManager::m_VertexBase[offset + count].normal.x = normal.x;
			GraphicsManager::m_VertexBase[offset + count].normal.y = normal.y;
			GraphicsManager::m_VertexBase[offset + count].normal.z = normal.z;

			GraphicsManager::m_VertexColor[offset + count]	= 0x00FFFFFF;

			++count;
		}
	}

	std::vector<U32> indexArray;

	for (U32 iStack = 0; iStack < GraphicsManager::SPHERE_STACKS; ++iStack)
	{
		for (U32 iSlice = 0; iSlice < GraphicsManager::SPHERE_SLICES; ++iSlice)
		{
			U32 index = (GraphicsManager::SPHERE_SLICES + 1) * iStack + iSlice;
			
			indexArray.push_back(offset + index + GraphicsManager::SPHERE_SLICES + 2);
			indexArray.push_back(offset + index + 1);
			indexArray.push_back(offset + index);

			indexArray.push_back(offset + index + GraphicsManager::SPHERE_SLICES + 1);
			indexArray.push_back(offset + index + GraphicsManager::SPHERE_SLICES + 2);
			indexArray.push_back(offset + index);
		}
	}


	++m_SphereCount;

	IndexData indexData;
	indexData.start		= offset;
	indexData.vertexNum	= GraphicsManager::ONE_SPHERE_VERTEX_NUM;
	indexData.face		= GraphicsManager::ONE_SPHERE_FACE_NUM;


	BufferResource* newResouce = NEW BufferResource();
	newResouce->AddIndex(indexArray);
	newResouce->ReCreateIndexBuffer();
	newResouce->UpdateIndexData(indexData);

	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
	

	return newResouce;
}

//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//=======================================================================================
//	End of File
//=======================================================================================