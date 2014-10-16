//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "NumberPlateRenderer.h"
#include "GraphicsManager.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
NumberPlateRenderer::NumberPlateRenderer()
: m_DisplayNumber(0)
, m_DisplayDigit(0)
{
	m_Color = 0xFFFFFFFF;
	m_RenderState = (D3DRENDERSTATETYPE)0;
	SetRectEmpty(&m_Rect);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
NumberPlateRenderer::~NumberPlateRenderer()
{
	
}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void NumberPlateRenderer::Draw()
{
	const Matrix transform = m_Transform->GetTransform();
	const Vector3 rootPositon(transform._41, transform._42, transform._43);
	const U32 digit = max(CalcDigit(m_DisplayNumber), 2);
	Vector3 currentPositon = rootPositon;
	U32 currentnumber = m_DisplayNumber;
	Matrix INIT;
	D3DXMatrixIdentity(&INIT);
	GraphicsManager::GetInstance()->GetSprite()->SetTransform(&INIT);
	for (U32 i = 0; i < digit; ++i)
	{
		U32 num = currentnumber % 10;
		GraphicsManager::GetInstance()->GetSprite()->Draw(GetTexture()->GetTexture(), 
			&CalcRectFromNumber(num),
			NULL, 
			&currentPositon, 
			m_Color);

		currentPositon.x -= 64;
		currentnumber /= 10;
	}
}
//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================
U32 NumberPlateRenderer::CalcDigit(U32 _rawNumber)
{
	return (U32)log10f(_rawNumber) + 1;
}
RECT NumberPlateRenderer::CalcRectFromNumber(U32 _rawNumber)
{
	RECT result;
	const int left	= (_rawNumber % 4) * 128;
	const int top = (_rawNumber / 4) * 128;
	SetRect(&result, left, top, left + 128, top + 128);
	return result;
}
//===============================================================
//	End of File
//===============================================================
