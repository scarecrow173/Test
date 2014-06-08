//=======================================================================================
//!	@file	:	DrawFonts.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "DrawFonts.h"
#include "GraphicsManager.h"
#include "WindowPolygonRenderer.h"
#include <atlbase.h>
#include <atlconv.h>

using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
ID3DXSprite*			g_Sprite	= NULL;
//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
DrawFonts::DrawFonts(S32 fontSize, S32 fontWeight, const std::string& fontName)
{
	if(!g_Sprite)
	{
		D3DXCreateSprite(GraphicsManager::GetInstance()->GetD3DDevice(), &g_Sprite);
	}
	m_FontSize = fontSize;
	const CHAR* font = fontName.c_str();
	LOGFONT lFont = 
	{
		fontSize,
		0,0,0,
		fontWeight,
		0,0,0,
		SHIFTJIS_CHARSET,
		OUT_TT_ONLY_PRECIS,
		CLIP_DEFAULT_PRECIS,
		PROOF_QUALITY, 
		DEFAULT_PITCH | FF_MODERN, 
		font[0]
	};

	HFONT hFont		= CreateFontIndirect(&lFont);
	HDC hdc			= GetDC(NULL);
	HFONT oldFont	= (HFONT)SelectObject(hdc, hFont);

	const S32 FontsNum = 85;

	const wchar_t cArray[FontsNum][2] =
	{
			{L"a"}, {L"b"}, {L"c"}, {L"d"}, {L"e"},
			{L"f"}, {L"g"}, {L"h"}, {L"i"}, {L"j"},
			{L"k"}, {L"l"}, {L"m"}, {L"n"}, {L"o"},
			{L"p"}, {L"q"}, {L"r"}, {L"s"}, {L"t"},
			{L"u"}, {L"w"}, {L"x"}, {L"y"}, {L"z"},
			{L"A"}, {L"B"}, {L"C"}, {L"D"}, {L"E"},
			{L"F"}, {L"G"}, {L"H"}, {L"I"}, {L"J"},
			{L"K"}, {L"L"}, {L"M"}, {L"N"}, {L"O"},
			{L"P"}, {L"Q"}, {L"R"}, {L"S"}, {L"T"},
			{L"U"}, {L"W"}, {L"X"}, {L"Y"}, {L"Z"},
			{L"0"}, {L"1"}, {L"2"}, {L"3"}, {L"4"},
			{L"5"}, {L"6"}, {L"7"}, {L"8"}, {L"9"},
			{L"!"}, {L"#"}, {L"%"}, {L"&"}, {L"'"},
			{L"("}, {L")"}, {L"="}, {L"~"}, {L"|"},
			{L"."}, {L","}, {L"?"}, {L"/"}, {L"_"},
			{L";"}, {L":"}, {L"["}, {L"]"}, {L"<"},
			{L">"}, {L" "}, {L"+"}, {L"*"}, {L"-"},
	};
	UINT			codes[FontsNum];
	TEXTMETRIC		tms;
	GLYPHMETRICS	gms[FontsNum];
	S32				fontWidth;
	S32				fontHeight;
	const S32		gradFlag	= GGO_GRAY4_BITMAP;
	S32				grad		= 0;

	CONST MAT2 mat =
	{
		{0,1}, {0,0},
		{0,0}, {0,1},
	};

	switch(gradFlag)
	{
        case GGO_GRAY2_BITMAP:
			grad =  4;
			break;
        case GGO_GRAY4_BITMAP:
			grad = 16;
			break;
        case GGO_GRAY8_BITMAP:
			grad = 64;
			break;
	}

	for (S32 i = 0; i < FontsNum; ++i)
	{
		codes[i] = (UINT)cArray[i][0];

		GetTextMetrics(hdc, &tms);
		
		IDirect3DTexture9* FontTex = NULL;
		DWORD size = GetGlyphOutlineW(hdc, codes[i], gradFlag, &gms[i], 0, NULL, &mat);
		BYTE* mono = NEW BYTE[size];
		GetGlyphOutlineW(hdc, codes[i], gradFlag, &gms[i], size, mono, &mat);
		
		fontWidth	= (gms[i].gmBlackBoxX + 3) / 4 * 4;
		fontHeight	= gms[i].gmBlackBoxY;

		GraphicsManager::GetInstance()->GetD3DDevice()->CreateTexture(
			fontWidth, fontHeight, 
			1, 0, D3DFMT_A8R8G8B8, 
			D3DPOOL_MANAGED, 
			&FontTex, 
			NULL);
		
		D3DLOCKED_RECT lockedRect;
		FontTex->LockRect(0, &lockedRect, NULL, 0);
		DWORD* fontBuf = (DWORD*)lockedRect.pBits;

		for (S32 y = 0; y < fontHeight; ++y)
		{
			for (S32 x = 0; x < fontWidth; ++x)
			{
				DWORD alpha = mono[y * fontWidth + x] * 255 / grad;
				fontBuf[y * fontWidth + x] = (alpha << 24) | 0x00FFFFFF;
			}
		}

		FontTex->UnlockRect(0);
		SAFE_DELETE_ARRAY(mono);
		USES_CONVERSION;
		m_FontsTexture[cArray[i][0]]	= FontTex;
		m_FontsInfo[cArray[i][0]]		= gms[i];
	}
	SelectObject(hdc, oldFont);
	ReleaseDC(NULL, hdc);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
DrawFonts::~DrawFonts()
{}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void DrawFonts::Draw(const std::wstring& drawStr, const D3DXMATRIX& world)
{
	auto it = drawStr.begin();
	F32 offset_x = (F32)m_FontsInfo[*it].gmptGlyphOrigin.x;
	F32 offset_y = (F32)m_FontsInfo[*it].gmptGlyphOrigin.y;
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	g_Sprite->Begin(0);
	while (it != drawStr.end())
	{
		Matrix FontScal;
		Matrix FontTrans;
		Matrix localMatrix;

		D3DXMatrixScaling(&FontScal, 1.f, 1.f, 1.f);

		offset_y = (F32)m_FontSize - (F32)m_FontsInfo[*it].gmptGlyphOrigin.y;

		D3DXMatrixTranslation(&FontTrans, offset_x, offset_y, 0.f);
		D3DXMatrixMultiply(&localMatrix, &FontScal, &FontTrans);
		offset_x += (F32)m_FontsInfo[*it].gmCellIncX;

		
		g_Sprite->SetTransform(&(localMatrix * world));
		
		g_Sprite->Draw(m_FontsTexture[*it], NULL , NULL, NULL, 0xFFFFFFFF);
		
		++it;
	}
	g_Sprite->End();
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------

//=======================================================================================
//		protected method
//=======================================================================================

//=======================================================================================
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================