//=======================================================================================
//!	@file	:	BoxFactory.cpp
//!	@brief	:	BoxFactory�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/05/01
//!	@par	:	
//!	@note	:	
//=======================================================================================
#include "BoxFactory.h"


using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
BoxFactory*	BoxFactory::m_Instance = NULL;

//---------------------------------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//---------------------------------------------------------------------------------------
BoxFactory::BoxFactory()
	:	m_BoxCount	(0)
{

}
//---------------------------------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//---------------------------------------------------------------------------------------
BoxFactory::~BoxFactory()
{

}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �C���X�^���X�쐬
//!	@return		: �C���X�^���X
//---------------------------------------------------------------------------------------
BoxFactory* BoxFactory::Create()
{
	if (m_Instance)
		return m_Instance;

	m_Instance = NEW BoxFactory();
	return m_Instance;
}
//---------------------------------------------------------------------------------------
//!	@brief		: �C���X�^���X�폜
//---------------------------------------------------------------------------------------
void BoxFactory::Destroy()
{
	SAFE_DELETE(m_Instance);
}

//---------------------------------------------------------------------------------------
//!	@brief		: BOX�쐬
//!	@param[in]	: ���S�ʒu
//!	@param[in]	: �傫��
//!	@param[in]	: �F
//!	@param[in]	: �C���f�b�N�X�i�[��
//!	@return		: �C���f�b�N�X�f�[�^
//---------------------------------------------------------------------------------------
IndexData BoxFactory::CreateBox(Vector3 vCenter, Vector3 size, VertexARGB color, std::vector<U32>& indexArray)
{	
	F32 halfX = size.x * 0.5;
	F32 halfY = size.y * 0.5;
	F32 halfZ = size.z * 0.5;
	U32 offset = (m_BoxCount * GraphicsManager::ONE_BOX_VERTEX_NUM);

	//	����:�E��
	GraphicsManager::m_VertexBase[offset + 0].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 0].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 0].position.z = vCenter.z - halfZ;
	
	//	����:�E��
	GraphicsManager::m_VertexBase[offset + 1].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 1].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 1].position.z = vCenter.z - halfZ;
	
	//	����:����
	GraphicsManager::m_VertexBase[offset + 2].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 2].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 2].position.z = vCenter.z - halfZ;
	
	//	����:����
	GraphicsManager::m_VertexBase[offset + 3].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 3].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 3].position.z = vCenter.z - halfZ;
	
	//	����:����
	GraphicsManager::m_VertexBase[offset + 4].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 4].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 4].position.z = vCenter.z + halfZ;
	
	//	����:����
	GraphicsManager::m_VertexBase[offset + 5].position.x = vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 5].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 5].position.z = vCenter.z + halfZ;
	
	//	����:����
	GraphicsManager::m_VertexBase[offset + 6].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 6].position.y = vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 6].position.z = vCenter.z + halfZ;
	
	//	����:����
	GraphicsManager::m_VertexBase[offset + 7].position.x = vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 7].position.y = vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 7].position.z = vCenter.z + halfZ;

	//	�@��
	for (S32 iVertex = 0; iVertex < 8; ++iVertex)
	{
		GraphicsManager::m_VertexBase[offset + iVertex].normal.x = GraphicsManager::m_VertexBase[offset + iVertex].position.x - vCenter.x;
		GraphicsManager::m_VertexBase[offset + iVertex].normal.y = GraphicsManager::m_VertexBase[offset + iVertex].position.y - vCenter.y;
		GraphicsManager::m_VertexBase[offset + iVertex].normal.z = GraphicsManager::m_VertexBase[offset + iVertex].position.z - vCenter.z;
		GraphicsManager::m_VertexColor[offset + iVertex] = color;
		GraphicsManager::m_VertexInstance[offset + iVertex] = m_BoxCount;
	}

	// ����
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 3);

	//��
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 5);
							  
	//��					
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 5);
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 5);
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 7);

	// �E
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 1);
							  
	//��
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 7);
	indexArray.push_back(offset + 3);
	indexArray.push_back(offset + 5);

	//��
	indexArray.push_back(offset + 0);
	indexArray.push_back(offset + 6);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 4);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 6);


	IndexData out;
	out.start	= offset;
	out.vertexNum		= 8;
	out.face	= GraphicsManager::ONE_BOX_FACE_NUM;
	

	++m_BoxCount;

	return out;
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