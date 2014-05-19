//=======================================================================================
//!	@file	:	IRenderer.h
//!	@author	:	���R �l�\
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include <vector>
#include "IndexData.h"
#include "MyMath.h"
namespace AK
{
namespace Graphics
{
//=======================================================================================
//!	@class	:	IRenderer
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class IRenderer
{
public:
	IRenderer() : m_IndexBuffer	(NULL), m_Device (NULL), m_IsActive (true) { m_IndexData.start = UINT_MAX; m_IndexData.face = 0; };
	virtual ~IRenderer() { if (m_Device)	SAFE_RELEASE(m_Device); };

	bool	Initialize(IDirect3DDevice9* device);
	void	AddIndex(std::vector<U32>& add);
	void	PopIndex(const U32 start, const U32 end);
	void	ReCreateIndexBuffer();
	void	UpdateIndexData(const IndexData data);
	
	void	SetWorld(const Matrix& world);
	Matrix	GetWorld() const;

	bool	IsActive() const;
	void	SetActive(const bool active);

	virtual void	Draw() PURE;
	
protected:
	virtual bool	InnerInitialize() { return true; };

	std::vector<U32>		m_Index;
	IDirect3DDevice9*		m_Device;
	IDirect3DIndexBuffer9*	m_IndexBuffer;
	IndexData				m_IndexData;
	Matrix					m_World;
	bool					m_IsActive;
	
	//	Material	: ���͂���Ȃ�
	//	Texture		: ���͂���Ȃ�

};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: ������
//!	@param[in]	: �f�o�C�X
//!	@return		: ����(true),���s(false)
//-------------------------------------------------------------
inline bool IRenderer::Initialize(IDirect3DDevice9* device)
{
	m_Device = device;
	return InnerInitialize();
}
//-------------------------------------------------------------
//!	@brief		: �C���f�b�N�X�̒ǉ�
//!	@param[in]	: �ǉ��������C���f�b�N�X
//-------------------------------------------------------------
inline void	IRenderer::AddIndex(std::vector<U32>& add)
{
	m_Index.insert(m_Index.end(), add.begin(), add.end());
}
//-------------------------------------------------------------
//!	@brief		: �O�������C���f�b�N�X(�����C���f�b�N�X����������ƑS�ĊO��)
//!	@param[in]	: �O���������߂̒l
//!	@param[in]	: �O�������I���̒l
//-------------------------------------------------------------
inline void	IRenderer::PopIndex(const U32 start, const U32 end)
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
//!	@brief		: �C���f�b�N�X�o�b�t�@�č쐬
//-------------------------------------------------------------
inline void IRenderer::ReCreateIndexBuffer()
{
	if(m_IndexBuffer)
		SAFE_RELEASE(m_IndexBuffer);

	DXUTGetD3D9Device()->CreateIndexBuffer(sizeof(U32) * m_Index.size(), 0, D3DFMT_INDEX32, D3DPOOL_MANAGED, &m_IndexBuffer, 0);
	U32* index;
	m_IndexBuffer->Lock(0, sizeof(U32) * m_Index.size(), (void**)&index, 0);
	memcpy(index, &m_Index[0], sizeof(U32) * m_Index.size());
	m_IndexBuffer->Unlock();
}
//-------------------------------------------------------------
//!	@brief		: �C���f�b�N�X�f�[�^�X�V
//!	@param[in]	: �C���f�b�N�X�f�[�^
//-------------------------------------------------------------
inline void IRenderer::UpdateIndexData(const IndexData data)
{
	m_IndexData.start = min(m_IndexData.start, data.start);
	m_IndexData.face += data.face;
}
//-------------------------------------------------------------
//!	@brief		: ���[���h�̃Z�b�g
//!	@param[in]	: ���[���h
//-------------------------------------------------------------
inline void IRenderer::SetWorld(const Matrix& world)
{
	m_World = world;
}
//-------------------------------------------------------------
//!	@brief		: ���[���h�̎擾
//!	@return		: ���[���h
//-------------------------------------------------------------
inline Matrix IRenderer::GetWorld() const
{
	return m_World;
}
//-------------------------------------------------------------
//!	@brief		: ���[���h�̎擾
//!	@return		: ���[���h
//-------------------------------------------------------------
inline bool IRenderer::IsActive() const
{
	return m_IsActive;
}
//-------------------------------------------------------------
//!	@brief		: ���[���h�̎擾
//!	@return		: ���[���h
//-------------------------------------------------------------
inline void IRenderer::SetActive(const bool active)
{
	m_IsActive = active;
}

};
};
//===============================================================
//	End of File
//===============================================================