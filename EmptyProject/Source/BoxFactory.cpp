//=======================================================================================
//!	@file	:	BoxFactory.cpp
//!	@brief	:	BoxFactoryクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/05/01
//!	@par	:	
//!	@note	:	
//=======================================================================================
#include "BoxFactory.h"
#include "TriangleRenderer.h"
#include "BufferResource.h"


using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
BoxFactory*	BoxFactory::m_Instance = NULL;


//---------------------------------------------------------------------------------------
//!	@brief		: コンストラクタ
//---------------------------------------------------------------------------------------
BoxFactory::BoxFactory()
	:	m_BoxCount	(0)
{
}
//---------------------------------------------------------------------------------------
//!	@brief		: デストラクタ
//---------------------------------------------------------------------------------------
BoxFactory::~BoxFactory()
{

}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: BOX作成
//!	@param[in]	: 中心位置
//!	@param[in]	: 大きさ
//!	@param[in]	: 色
//!	@param[in]	: インデックス格納先
//!	@return		: インデックスデータ
//---------------------------------------------------------------------------------------
BufferResource*	BoxFactory::CreatePrimitive()
{
	assert(GraphicsManager::BOX_NUM > m_BoxCount);	
		
	const F32 halfX = 0.5f;
	const F32 halfY = 0.5f;
	const F32 halfZ = 0.5f;
	const Vector3 vCenter(0.f, 0.f, 0.f);
	U32 offset = (m_BoxCount * GraphicsManager::ONE_BOX_VERTEX_NUM);

	//	正面:右下
	GraphicsManager::m_VertexBase[offset + 0].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 0].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 0].position.z = vCenter.z - halfZ;
	GraphicsManager::m_VertexUV[offset	 + 0].u			 = 0;
	GraphicsManager::m_VertexUV[offset	 + 0].v			 = 1;
	
	//	正面:右上
	GraphicsManager::m_VertexBase[offset + 1].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 1].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 1].position.z = vCenter.z - halfZ;
	GraphicsManager::m_VertexUV[offset	 + 1].u			 = 0;
	GraphicsManager::m_VertexUV[offset	 + 1].v			 = 0;

	//	正面:左下
	GraphicsManager::m_VertexBase[offset + 2].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 2].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 2].position.z = vCenter.z - halfZ;
	GraphicsManager::m_VertexUV[offset	 + 2].u			 = 0;
	GraphicsManager::m_VertexUV[offset	 + 2].v			 = 1;

	//	正面:左上
	GraphicsManager::m_VertexBase[offset + 3].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 3].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 3].position.z = vCenter.z - halfZ;
	GraphicsManager::m_VertexUV[offset	 + 3].u			 = 0;
	GraphicsManager::m_VertexUV[offset	 + 3].v			 = 0;

	//	左面:左下
	GraphicsManager::m_VertexBase[offset + 4].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 4].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 4].position.z = vCenter.z + halfZ;
	GraphicsManager::m_VertexUV[offset	 + 4].u			 = 1;
	GraphicsManager::m_VertexUV[offset	 + 4].v			 = 1;

	//	左面:左上
	GraphicsManager::m_VertexBase[offset + 5].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 5].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 5].position.z = vCenter.z + halfZ;
	GraphicsManager::m_VertexUV[offset	 + 5].u			 = 1;
	GraphicsManager::m_VertexUV[offset	 + 5].v			 = 0;

	//	裏面:左下
	GraphicsManager::m_VertexBase[offset + 6].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 6].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 6].position.z = vCenter.z + halfZ;
	GraphicsManager::m_VertexUV[offset	 + 6].u			 = 0;
	GraphicsManager::m_VertexUV[offset	 + 6].v			 = 1;

	//	裏面:左上
	GraphicsManager::m_VertexBase[offset + 7].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 7].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 7].position.z = vCenter.z + halfZ;
	GraphicsManager::m_VertexUV[offset	 + 7].u			 = 0;
	GraphicsManager::m_VertexUV[offset	 + 7].v			 = 0;

	//	法線
	for (S32 iVertex = 0; iVertex < 8; ++iVertex)
	{
		Vector3 normal;
		normal.x = GraphicsManager::m_VertexBase[offset + iVertex].position.x - vCenter.x;
		normal.y = GraphicsManager::m_VertexBase[offset + iVertex].position.y - vCenter.y;
		normal.z = GraphicsManager::m_VertexBase[offset + iVertex].position.z - vCenter.z;
		D3DXVec3Normalize(&normal, &normal);

		GraphicsManager::m_VertexBase[offset + iVertex].normal.x = normal.x;
		GraphicsManager::m_VertexBase[offset + iVertex].normal.y = normal.y;
		GraphicsManager::m_VertexBase[offset + iVertex].normal.z = normal.z;
		GraphicsManager::m_VertexColor[offset + iVertex] = 0x00ffffff;
		GraphicsManager::m_VertexInstance[offset + iVertex] = (F32)m_BoxCount;
	}

	std::vector<U32> indexArray;

	// 正面
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 3);

	//左
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 5);
							  
	//裏					
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 5);
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 5);
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 7);

	// 右
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 1);
							  
	//上
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 5);

	//下
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 6);


	IndexData indexData;
	indexData.start			= offset;
	indexData.vertexNum		= 36;
	indexData.face			= GraphicsManager::ONE_BOX_FACE_NUM;


	BufferResource* newResouce = NEW BufferResource();
	newResouce->AddIndex(indexArray);
	newResouce->ReCreateIndexBuffer();
	newResouce->UpdateIndexData(indexData);

	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();

	return newResouce;
}
////---------------------------------------------------------------------------------------
////!	@brief		: BOX作成
////!	@param[in]	: 中心位置
////!	@param[in]	: 大きさ
////!	@param[in]	: 色
////!	@param[in]	: インデックス格納先
////!	@return		: インデックスデータ
////---------------------------------------------------------------------------------------
//void BoxFactory::AllClear()
//{
//	m_BoxCount = 0;
//}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//=======================================================================================
//	End of File
//=======================================================================================