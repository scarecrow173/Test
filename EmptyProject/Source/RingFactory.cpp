//=======================================================================================
//!	@file	:	RingFactory.cpp
//!	@brief	:	RingFactoryクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/05/01
//!	@par	:	
//!	@note	:	
//=======================================================================================
#include "RingFactory.h"
#include "TriangleRenderer.h"
#include "BufferResource.h"

using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
RingFactory*	RingFactory::m_Instance = NULL;

//---------------------------------------------------------------------------------------
//!	@brief		: コンストラクタ
//---------------------------------------------------------------------------------------
RingFactory::RingFactory()
	:	m_RingCount	(0)
{

}
//---------------------------------------------------------------------------------------
//!	@brief		: デストラクタ
//---------------------------------------------------------------------------------------
RingFactory::~RingFactory()
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
BufferResource* RingFactory::CreatePrimitive()
{
	assert(GraphicsManager::RING_NUM > m_RingCount);
	
	
	const F32		halfRad			= 1.f;
	const Vector3	vCenter			= Vector3(0, 0, 0);
	static U32		boxOffset		= (GraphicsManager::ONE_BOX_VERTEX_NUM * GraphicsManager::BOX_NUM);
	static U32		sphereOffset	= (GraphicsManager::ONE_SPHERE_VERTEX_NUM * GraphicsManager::SPHERE_NUM);
	const U32		offset			= boxOffset + sphereOffset + (m_RingCount * GraphicsManager::ONE_RING_VERTEX_NUM);
	U32				count			= 0;
	const U32		Belt			= 1;
		
	
	std::vector<U32> indexArray;

	for (U32 iOutCricle = 0; iOutCricle < (GraphicsManager::ONE_RING_VERTEX_NUM / 2); ++iOutCricle)
	{
		F32 rad = Math::PI2 * iOutCricle / (GraphicsManager::ONE_RING_VERTEX_NUM / 2);
		
		
		F32 x	= Math::Cos(rad) * halfRad;
		F32 y	= Math::Sin(rad) * halfRad;
		

		GraphicsManager::m_VertexBase[offset + count].position.x	= x;
		GraphicsManager::m_VertexBase[offset + count].position.y	= y;
		GraphicsManager::m_VertexBase[offset + count].position.z	= 1.f;

		GraphicsManager::m_VertexBase[offset + count].normal.x		= vCenter.x - x;
		GraphicsManager::m_VertexBase[offset + count].normal.y		= vCenter.y - y;
		GraphicsManager::m_VertexBase[offset + count].normal.z		= vCenter.z - 1.f;

		GraphicsManager::m_VertexColor[offset + count]	= 0x00FFFFFF;
		++count;
	}
	for (U32 iInCricle = 0; iInCricle < (GraphicsManager::ONE_RING_VERTEX_NUM / 2); ++iInCricle)
	{
		F32 rad = Math::PI2 * iInCricle / (GraphicsManager::ONE_RING_VERTEX_NUM / 2);
		
		
		F32 x	= Math::Cos(rad) * (halfRad * 0.5f);
		F32 y	= Math::Sin(rad) * (halfRad * 0.5f);
		

		GraphicsManager::m_VertexBase[offset + count].position.x	= x;
		GraphicsManager::m_VertexBase[offset + count].position.y	= y;
		GraphicsManager::m_VertexBase[offset + count].position.z	= 1.f;

		GraphicsManager::m_VertexBase[offset + count].normal.x		= vCenter.x - x;
		GraphicsManager::m_VertexBase[offset + count].normal.y		= vCenter.y - y;
		GraphicsManager::m_VertexBase[offset + count].normal.z		= vCenter.z - 1.f;

		GraphicsManager::m_VertexColor[offset + count]	= 0x00FFFFFF;
		++count;
	}

	static const U32 ringSize = GraphicsManager::ONE_RING_VERTEX_NUM / 2;
	for (U32 iIndex = 0; iIndex < ringSize - 1; ++iIndex)
	{

		indexArray.push_back(offset + iIndex);
		indexArray.push_back(offset + iIndex + 1);
		indexArray.push_back(offset + iIndex + ringSize);
		
		
		indexArray.push_back(offset + iIndex + ringSize);
		indexArray.push_back(offset + iIndex + 1);
		indexArray.push_back(offset + iIndex + 1 + ringSize);
	}

	indexArray.push_back(offset + (ringSize - 1));
	indexArray.push_back(offset);
	indexArray.push_back(offset + ringSize);
	
	indexArray.push_back(offset + ringSize);
	indexArray.push_back(offset + ringSize + (ringSize - 1));
	indexArray.push_back(offset + ringSize-1);


	++m_RingCount;

	IndexData indexData;
	indexData.start	= offset;
	indexData.vertexNum		= GraphicsManager::ONE_RING_VERTEX_NUM;
	indexData.face	= GraphicsManager::ONE_RING_FACE_NUM + 1;


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