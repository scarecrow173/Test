//=======================================================================================
//!	@file	:	Paddle.cpp
//!	@brief	:	Paddleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "Paddle.h"
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
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Paddle::Paddle(INode* parent, Vector3 pos)
	:	GameObject	(parent, pos)
	,	m_Item		(NULL)
	,	m_Speed		(3.f)
{
	static const F32 WIDTH	= 400.f;
	static const F32 HEIGHT	= 80.f;

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

	m_Collison = NEW CollisionBox(pos, Vector3(0.f, 0.f, 0.f), Vector3(0.f, 0.f, 0.f), WIDTH, HEIGHT, 50.f);
	m_Collison->SetReflection(true);
	m_Collison->SetAttenuation(true);
	m_Collison->SetAttenuationFactor(0.91f);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Paddle::~Paddle()
{}
//=======================================================================================
//		public method
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Paddle::Update()
{
	m_Keyboard.Update();
	Vector3 speed = m_Collison->GetSpeed();

	if (m_Keyboard.IsKeyDown(KEY_LEFT))
		speed.x += m_Speed;
	if (m_Keyboard.IsKeyDown(KEY_RIGHT))
		speed.x -= m_Speed;

	m_Collison->SetSpeed(speed);

	std::vector<ICollisonObject*> l_list;
	m_Collison->Update(l_list);

	m_Position = m_Collison->GetPosition();
	Matrix t;
	D3DXMatrixTranslation(&t, m_Position.x, m_Position.y, m_Position.z);
	m_Renderer->SetWorld(t);

}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Paddle::Start()
{
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Paddle::PushItem(Item* item)
{
	//if (m_Item)
	//	SAFE_DELETE(m_Item);
	//m_Item = item;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void Paddle::SetSpeed(const F32 speed)
{
	m_Speed = speed;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
F32	Paddle::GetSpeed()
{
	return m_Speed;
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
