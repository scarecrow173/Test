//=======================================================================================
//!	@file	:	RingFactory.cpp
//!	@brief	:	RingFactoryクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/05/01
//!	@par	:	
//!	@note	:	
//=======================================================================================
#include "SquareFactory.h"
#include "TriangleRenderer.h"
#include "BufferResource.h"

using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
SquareFactory*	SquareFactory::m_Instance = NULL;

//---------------------------------------------------------------------------------------
//!	@brief		: コンストラクタ
//---------------------------------------------------------------------------------------
SquareFactory::SquareFactory()
	:	m_SquareCount	(0)
{

}
//---------------------------------------------------------------------------------------
//!	@brief		: デストラクタ
//---------------------------------------------------------------------------------------
SquareFactory::~SquareFactory()
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
BufferResource* SquareFactory::CreatePrimitive()
{
	assert(GraphicsManager::SQUARE_NUM > m_SquareCount);
	
	const Vector3	vCenter			= Vector3(0, 0, 1.f);
	static U32		boxOffset		= (GraphicsManager::ONE_BOX_VERTEX_NUM * GraphicsManager::BOX_NUM);
	static U32		sphereOffset	= (GraphicsManager::ONE_SPHERE_VERTEX_NUM * GraphicsManager::SPHERE_NUM);
	static U32		ringOffset		= (GraphicsManager::ONE_RING_VERTEX_NUM * GraphicsManager::RING_NUM);
	const U32		offset			= boxOffset + sphereOffset + ringOffset + (m_SquareCount * GraphicsManager::ONE_SQUARE_VERTEX_NUM);		
	
	
	
	for (int i = 0; i < GraphicsManager::ONE_SQUARE_VERTEX_NUM; ++i)
	{
		const Vector3 vPos = GetVertexPosition(i);

		GraphicsManager::m_VertexBase[offset + i].position.x	= vPos.x;
		GraphicsManager::m_VertexBase[offset + i].position.y	= vPos.y;
		GraphicsManager::m_VertexBase[offset + i].position.z	= 1.f;

		GraphicsManager::m_VertexBase[offset + i].normal.x		= vCenter.x - vPos.x;
		GraphicsManager::m_VertexBase[offset + i].normal.y		= vCenter.y - vPos.y;
		GraphicsManager::m_VertexBase[offset + i].normal.z		= vCenter.z - 1.f;

		const Vector2 vUV = GetVertexUV(i);

		GraphicsManager::m_VertexUV[offset	 + i].u			 = vUV.x;
		GraphicsManager::m_VertexUV[offset	 + i].v			 = vUV.y;

		GraphicsManager::m_VertexColor[offset + i]				= 0x00FFFFFF;
	}

	++m_SquareCount;

	std::vector<U32> indexArray;

	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 2);
	
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 2);

	IndexData indexData;
	indexData.start			= offset;
	indexData.vertexNum		= GraphicsManager::ONE_SQUARE_VERTEX_NUM;
	indexData.face			= GraphicsManager::ONE_SQUARE_FACE_NUM;


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
Vector3 SquareFactory::GetVertexPosition(U32 _n)
{
	assert(_n < 4);
	Vector3 result(0.f, 0.f, 1.f);
	switch (_n)
	{
	case 0:
		result.x = -0.5f;
		result.y = -0.5f;
		break;
	case 1:
		result.x = 0.5f;
		result.y = -0.5f;
		break;
	case 2:
		result.x = -0.5f;
		result.y = 0.5f;
		break;
	case 3:
		result.x = 0.5f;
		result.y = 0.5f;
		break;
	default:
		break;
	}
	return result;
}

Vector2 SquareFactory::GetVertexUV(U32 _n)
{
	assert(_n < 4);
	Vector2 result(0.f, 0.f);
	switch (_n)
	{
	case 0:
		result.x = 1;
		result.y = 1;
		break;
	case 1:
		result.x = 0;
		result.y = 1;
		break;
	case 2:
		result.x = 1;
		result.y = 0;
		break;
	case 3:
		result.x = 0;
		result.y = 0;
		break;
	default:
		break;
	}
	return result;
}
//=======================================================================================
//	End of File
//=======================================================================================