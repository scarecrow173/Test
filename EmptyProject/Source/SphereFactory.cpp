//=======================================================================================
//!	@file	:	SphereFactory.cpp
//!	@brief	:	SphereFactory�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/05/01
//!	@par	:	
//!	@note	:	
//=======================================================================================
#include "SphereFactory.h"

using namespace AK;
using namespace Graphics;

//=======================================================================================
//		Constants Definitions
//=======================================================================================
SphereFactory*	SphereFactory::m_Instance = NULL;

//---------------------------------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//---------------------------------------------------------------------------------------
SphereFactory::SphereFactory()
	:	m_SphereCount	(0)
{

}
//---------------------------------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//---------------------------------------------------------------------------------------
SphereFactory::~SphereFactory()
{

}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: �C���X�^���X�쐬
//!	@return		: �C���X�^���X
//---------------------------------------------------------------------------------------
SphereFactory* SphereFactory::Create()
{
	if (m_Instance)
		return m_Instance;

	m_Instance = NEW SphereFactory();
	return m_Instance;
}
//---------------------------------------------------------------------------------------
//!	@brief		: �C���X�^���X�폜
//---------------------------------------------------------------------------------------
void SphereFactory::Destroy()
{
	SAFE_DELETE(m_Instance);
}
//---------------------------------------------------------------------------------------
//!	@brief		: ���쐬
//!	@param[in]	: ���S�ʒu
//!	@param[in]	: ���a
//!	@param[in]	: �F
//!	@param[in]	: �C���f�b�N�X�i�[��
//!	@return		: �C���f�b�N�X�f�[�^
//---------------------------------------------------------------------------------------
IndexData SphereFactory::CreateSphere(Vector3 vCenter, F32 radius, VertexARGB color, std::vector<U32>& indexArray)
{
	static U32 boxOffset		= (GraphicsManager::ONE_BOX_VERTEX_NUM * GraphicsManager::BOX_NUM);
	U32	offset		= boxOffset + (m_SphereCount * GraphicsManager::ONE_SPHERE_VERTEX_NUM);
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
			
			GraphicsManager::m_VertexBase[offset + count].normal.x = x - vCenter.x;
			GraphicsManager::m_VertexBase[offset + count].normal.y = y - vCenter.y;
			GraphicsManager::m_VertexBase[offset + count].normal.z = z - vCenter.z;

			GraphicsManager::m_VertexColor[offset + count]	= color;

			++count;
		}
	}

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

	IndexData out;
	out.start	= offset;
	out.vertexNum		= GraphicsManager::ONE_SPHERE_VERTEX_NUM;
	out.face	= GraphicsManager::ONE_SPHERE_FACE_NUM;

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