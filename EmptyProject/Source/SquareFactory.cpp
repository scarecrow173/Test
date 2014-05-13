//=======================================================================================
//!	@file	:	SquareFactory.cpp
//!	@brief	:	SquareFactory�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "SquareFactory.h"

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
SquareFactory*	SquareFactory::m_Instance = NULL;
//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
SquareFactory::SquareFactory()
	:	m_SquareCount	(0)
{

}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
SquareFactory::~SquareFactory()
{
}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �C���X�^���X�쐬
//!	@return		: �C���X�^���X
//---------------------------------------------------------------------------------------
SquareFactory* SquareFactory::Create()
{
	if (m_Instance)
		return m_Instance;

	m_Instance = NEW SquareFactory();
	return m_Instance;
}
//---------------------------------------------------------------------------------------
//!	@brief		: �C���X�^���X�쐬
//!	@return		: �C���X�^���X
//---------------------------------------------------------------------------------------
void SquareFactory::Destroy()
{
	SAFE_DELETE(m_Instance);
}
//-------------------------------------------------------------
//!	@brief		: �|���쐬
//!	@param[in]	: ���S�ʒu
//!	@param[in]	: �傫��
//!	@param[in]	: �F
//!	@param[in]	: �C���f�b�N�X�i�[��
//!	@return		: �C���f�b�N�X�f�[�^
//-------------------------------------------------------------
IndexData SquareFactory::CreateSquare(Vector3 vCenter, Vector2 size, VertexARGB color, std::vector<U32>& indexArray)
{
	static const U32 BaseOffset	=	(GraphicsManager::BOX_NUM * GraphicsManager::ONE_BOX_VERTEX_NUM) + (GraphicsManager::SPHERE_NUM * GraphicsManager::ONE_SPHERE_VERTEX_NUM);
	U32	offset	= BaseOffset + (m_SquareCount * 4);

	F32 halfX = size.x * 0.5f;
	F32 halfY = size.y * 0.5f;

	//	�ʒu
	GraphicsManager::m_VertexBase[offset].position.x		= vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset].position.y		= vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset].position.z		= vCenter.z;

	GraphicsManager::m_VertexBase[offset + 1].position.x	= vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 1].position.y	= vCenter.y - halfY;
	GraphicsManager::m_VertexBase[offset + 1].position.z	= vCenter.z;
	

	GraphicsManager::m_VertexBase[offset + 2].position.x	= vCenter.x - halfX;
	GraphicsManager::m_VertexBase[offset + 2].position.y	= vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 2].position.z	= vCenter.z;

	GraphicsManager::m_VertexBase[offset + 3].position.x	= vCenter.x + halfX;
	GraphicsManager::m_VertexBase[offset + 3].position.y	= vCenter.y + halfY;
	GraphicsManager::m_VertexBase[offset + 3].position.z	= vCenter.z;

	//	�@��
	GraphicsManager::m_VertexBase[offset].normal		= GraphicsManager::m_VertexBase[offset].position;
	
	GraphicsManager::m_VertexBase[offset + 1].normal	= GraphicsManager::m_VertexBase[offset + 1].position;

	GraphicsManager::m_VertexBase[offset + 2].normal	= GraphicsManager::m_VertexBase[offset + 2].position;

	GraphicsManager::m_VertexBase[offset + 3].normal	= GraphicsManager::m_VertexBase[offset + 3].position;


	//	UV
	GraphicsManager::m_VertexUV[offset].u		= 0.f;
	GraphicsManager::m_VertexUV[offset].v		= 0.f;
					
	GraphicsManager::m_VertexUV[offset + 1].u	= 1.f;
	GraphicsManager::m_VertexUV[offset + 1].v	= 0.f;

	GraphicsManager::m_VertexUV[offset + 2].u	= 0.f;
	GraphicsManager::m_VertexUV[offset + 2].v	= 1.f;
	
	GraphicsManager::m_VertexUV[offset + 3].u	= 1.f;
	GraphicsManager::m_VertexUV[offset + 3].v	= 1.f;

	//	Color
	GraphicsManager::m_VertexColor[offset]		= color;
					
	GraphicsManager::m_VertexColor[offset + 1]	= color;
	
	GraphicsManager::m_VertexColor[offset + 2]	= color;
	
	GraphicsManager::m_VertexColor[offset + 3]	= color;

	indexArray.push_back(offset + 1);
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 3);

	indexArray.push_back(offset );
	indexArray.push_back(offset + 2);
	indexArray.push_back(offset + 1);

	++m_SquareCount;

	IndexData out;
	out.start	= offset;
	out.vertexNum		= 4;
	out.face	= 2;
	return out;
}

//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================
