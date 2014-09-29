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
#include "TexturePool.h"
#include "TriangleRenderer.h"
#include "PrimitivePool.h"
#include <atlbase.h>
#include <atlconv.h>


using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
DrawFonts::DrawFonts(S32 fontSize, S32 fontWeight, const std::string& fontName)
	:	m_hWorld		(NULL)
	,	m_hView			(NULL)
	,	m_hProjection	(NULL)
{
	m_DrawStep	= 10001;
	m_Color		= 0xFFFFFFFF;

	D3DXMatrixIdentity(&m_World);

	LPD3DXBUFFER wError = NULL;
	HRESULT hr = D3DXCreateEffectFromFile(
		GraphicsManager::GetInstance()->GetD3DDevice(),
		L"Source/DefaultShaderPackage.fx",
		NULL,
		NULL,
		D3DXSHADER_DEBUG,
		NULL,
		&m_Effect,
		&wError);
	if (FAILED(hr))
	{
		::MessageBoxA( NULL, (LPCSTR)wError->GetBufferPointer(), "Error", MB_OK );	// 失敗の原因を表示
		wError->Release();
	}
	m_Effect->SetTechnique(m_Effect->GetTechniqueByName("DrawFont"));

	m_hWorld		= m_Effect->GetParameterByName(m_hWorld,		"g_World");
	m_hView			= m_Effect->GetParameterByName(m_hView,			"g_View");
	m_hProjection	= m_Effect->GetParameterByName(m_hProjection,	"g_Projection");

	const Matrix view	= GraphicsManager::GetInstance()->GetView();
	const Matrix proj	= GraphicsManager::GetInstance()->GetProjection();
	m_Effect->SetMatrix(m_hView, &view);
	m_Effect->SetMatrix(m_hProjection, &proj);

	m_Renderer.push_back(NEW TriangleRenderer());
	m_Renderer[0]->SetBufferResource(PrimitivePool::GetInstance()->GetResource("data:SQUARE-Font"));

	
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

	USES_CONVERSION;

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
		m_FontsInfo[cArray[i][0]]		= gms[i];

		auto manegedFontTexturePtr = TexturePool::GetInstance()->GetResource("data:DefaultTexture-" + fontName + W2A(cArray[i]) + std::to_string((_Longlong)m_FontSize));
		auto manegedFontTextureObj = RTTI_PTR_DYNAMIC_CAST(DefaultTexture, manegedFontTexturePtr.GetSharedObject());
		if (manegedFontTextureObj->GetTexture())
		{
			m_FontsTexture[cArray[i][0]] = manegedFontTextureObj->GetTexture();
			SAFE_DELETE_ARRAY(mono);
			continue;
		}
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

		manegedFontTextureObj->SetTexture(&FontTex);


		SAFE_DELETE_ARRAY(mono);
		m_FontsTexture[cArray[i][0]]	= FontTex;
		
	}

	SelectObject(hdc, oldFont);
	ReleaseDC(NULL, hdc);
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
DrawFonts::~DrawFonts()
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
bool DrawFonts::Initilize()
{
	return true;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void DrawFonts::Draw(/*const std::wstring& drawStr, const D3DXMATRIX& world*/)
{
	auto it = m_DrawString.begin();

	F32 offset_x = (F32)m_FontsInfo[*it].gmptGlyphOrigin.x;
	F32 offset_y = (F32)m_FontsInfo[*it].gmptGlyphOrigin.y;

	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	
	//GraphicsManager::GetInstance()->GetSprite()->Begin(0);
	m_Effect->Begin(nullptr, 0);
	m_Effect->BeginPass(0);

	while (it != m_DrawString.end())
	{
		auto findIT = m_FontsInfo.find(*it);
		if (findIT == m_FontsInfo.end())
		{
			assert(0);
			continue;
		}
		
		Matrix FontScal;
		Matrix FontTrans;
		Matrix localMatrix;

		D3DXMatrixScaling(&FontScal, m_FontSize, m_FontSize, 1.f);

		offset_y = (F32)m_FontSize - (F32)findIT->second.gmptGlyphOrigin.y;


		D3DXMatrixTranslation(&FontTrans, -offset_x * 2.f, offset_y, 0.f);
		D3DXMatrixMultiply(&localMatrix, &FontScal, &FontTrans);
		
		offset_x += (F32)findIT->second.gmCellIncX - findIT->second.gmptGlyphOrigin.x;
		(F32)findIT->second.gmCellIncX;

		//GraphicsManager::GetInstance()->GetSprite()->SetTransform(&(localMatrix * m_World));
		
		const Matrix	mat = localMatrix * m_World;
		//const Vector3	vec = Vector3(mat._41, mat._42, mat._43);
		
		m_Effect->SetMatrix(m_hWorld, &mat);
		GraphicsManager::GetInstance()->GetD3DDevice()->SetTexture(1, m_FontsTexture[*it]);
		m_Effect->CommitChanges();
		m_Renderer[0]->Draw();
		//GraphicsManager::GetInstance()->GetSprite()->Draw(m_FontsTexture[*it], NULL , NULL, &vec, m_Color);
		
		++it;
	}
	m_Effect->EndPass();
	m_Effect->End();
	//GraphicsManager::GetInstance()->GetSprite()->End();

	GraphicsManager::GetInstance()->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void DrawFonts::SetDrawString(const std::wstring& drawString)
{
	m_DrawString = drawString;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void DrawFonts::SetWorld(const Matrix& world)
{
	m_World = world;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Matrix DrawFonts::GetWorld() const
{
	return m_World;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
void DrawFonts::SetColor(const DWORD color)
{
	m_Color = color;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
DWORD DrawFonts::GetColor() const
{
	return m_Color;
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