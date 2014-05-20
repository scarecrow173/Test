//=======================================================================================
//!	@file	:	Item.cpp
//!	@brief	:	Item�N���X�̃����o�֐��錾
//!	@author	:	���R �l�\
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "Item.h"
#include "BoxFactory.h"
#include "TriangleRenderer.h"
#include "CollisionBox.h"
#include "Colors.h"


using namespace AK;
using namespace Graphics;
using namespace Collision;

//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �R���X�g���N�^
//-------------------------------------------------------------
Item::Item(INode* parent, Vector3 pos, ITEM_TYPE type)
	:	GameObject(parent, pos)
	,	m_Type	(type)
{
	static const F32 WIDTH	= 100.f;
	static const F32 HEIGHT	= 50.f;
	std::vector<U32> indexSrc;
	IndexData indexData;
	indexData = BoxFactory::GetInstance()->CreateBox(Vector3(0, 0, 0), Vector3(WIDTH, HEIGHT, 50.f), ARGBColors::Magenta, indexSrc);

	m_Renderer = NEW TriangleRenderer();
	m_Renderer->Initialize(DXUTGetD3D9Device());
	m_Renderer->AddIndex(indexSrc);
	m_Renderer->ReCreateIndexBuffer();
	m_Renderer->UpdateIndexData(indexData);

	Matrix mat;
	D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);

	m_Renderer->SetWorld(mat);

	m_Collision = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), WIDTH, HEIGHT, 50.f);
	m_Collision->SetGravity(true);
}
//-------------------------------------------------------------
//!	@brief		: �f�X�g���N�^
//-------------------------------------------------------------
Item::~Item()
{}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: �X�V�i�Փ˂��Ă�������ʔ����j
//-------------------------------------------------------------
void Item::Update()
{
	TRACE(1,"Item::Update");
	std::vector<ICollisionObject*> l_list;
	
	m_Collision->Update(l_list);

	for (auto it = l_list.begin(); it != l_list.end(); ++it)
		ItemAffect(m_Parent->GetParent()->FindNode(*it));
	Move();

}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Item::Start()
{
}
//-------------------------------------------------------------
//!	@brief		: �A�C�e�������������
//-------------------------------------------------------------
void Item::AddCollision(ICollisionObject* collison)
{
	TRACE(1,"Item::AddCollision");
	m_Collision->PushCollisionList(collison);
}

//-------------------------------------------------------------
//!	@brief		: �A�C�e���^�C�v���擾�i����Ō��ʂ𔻒f����j
//-------------------------------------------------------------
ITEM_TYPE Item::GetType() const
{
	return m_Type;
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: ���ʔ���
//!	@param[in]	: ��������
//-------------------------------------------------------------
void Item::ItemAffect(GameObject* obj)
{
	TRACE(1,"Item::ItemAffect");
	if (!obj)
		return;

	obj->Affect(this);
	m_Renderer->SetActive(false);
	SetActive(false);
}
//-------------------------------------------------------------
//!	@brief		: �ړ��̂�
//-------------------------------------------------------------
void Item::Move()
{
	m_Position = m_Collision->GetPosition();
	Matrix t;
	D3DXMatrixTranslation(&t, m_Position.x, m_Position.y, m_Position.z);
	m_Renderer->SetWorld(t);
}
//===============================================================
//	End of File
//===============================================================
