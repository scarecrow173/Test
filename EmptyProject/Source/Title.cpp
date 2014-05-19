//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
#include "Title.h"
#include "DebugUtill.h"
#include "Stage1.h"
#include "SoundManager.h"
#include "InputKeyboard.h"
#include "CSVReader.h"
#include "BoxFactory.h"
#include "Colors.h"
#include "TriangleRenderer.h"
#include "UseFixed.h"

using namespace AK;
using namespace Sound;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================
static const U32 TITLE_BGM_NUM = 2;
InputKeyboard keyboard;


//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
Title::Title(INode* parent)
	:	SceneNode		(parent)
	,	m_IsEnd			(false)
	,	m_FadeVolume	(1.f)
	,	m_Shader		(NULL)
	,	m_Floating		(0.0f)
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
Title::~Title()
{
	GraphicsManager::GetInstance()->EraseShaderObject(m_Shader);
	SAFE_DELETE(m_Shader);
	BoxFactory::GetInstance()->AllClear();
	auto it = m_TitleBlock.begin();
	while(it != m_TitleBlock.end())
	{
		SAFE_DELETE(*it);
		it = m_TitleBlock.erase(it);
	}

}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: 更新
//-------------------------------------------------------------
void Title::Update()
{
	DEBUG_PRINT_CHAR("TITLE");
	
	m_Floating += 0.2f;
	F32 value = sin(m_Floating);

	auto it = m_TitleBlock.begin();
	while (it != m_TitleBlock.end())
	{
		Matrix mat = (*it)->GetWorld();
		mat._42 += m_IsEnd ? -15.f : value;
		(*it)->SetWorld(mat);
		++it;
	}
	keyboard.Update();
}
//-------------------------------------------------------------
//!	@brief		: シーン変更
//!	@return		: 変更時なら変更先ポインタ
//-------------------------------------------------------------
SceneNode*	Title::ChangeScene()
{
	if ((!m_IsEnd) && keyboard.IsTrigger(KEY_BUTTON1))
	{
		m_IsEnd = true;
		SoundManager::GetInstance()->PlaySE(11, TRUE);
	}

	m_FadeVolume -= m_IsEnd ? 0.01f : 0.f;
	SoundManager::GetInstance()->SetVolumeBGM(TITLE_BGM_NUM, m_FadeVolume);


	if (m_FadeVolume < 0.f)
	{
		SoundManager::GetInstance()->PauseBGM(TITLE_BGM_NUM);
		return NEW Stage1(m_Parent, 0);
	}
	return this;
}
//-------------------------------------------------------------
//!	@brief		: 初期化
//!	@return		: 成功(true),失敗(false)
//-------------------------------------------------------------
bool Title::Initialize()
{
	SoundManager::GetInstance()->SetVolumeBGM(TITLE_BGM_NUM, 1.f);
	SoundManager::GetInstance()->PlayBGM(TITLE_BGM_NUM, TRUE);

	m_Shader = NEW UseFixed();
	m_Shader->Initilize();

	//CSVData<S32> data;
	//CSVReader::ReadInteger("Assets/CSV/Title/Title.csv", data);
#ifdef _CSVREADER_MODE_01
	CSVReader<S32> data(std::string("Assets/CSV/Title/Title.csv"));
	U32 widthNum	= data.Data[0];
	U32 heightNum	= data.Data[1];
#else
	CSVReader data;
	data.Load("Assets/CSV/Title/Title.csv");
	U32 widthNum	= data[0].GetInteger();
	U32 heightNum	= data[1].GetInteger();
#endif
	F32 blockWhidth	= 1000.f / widthNum;
	F32 blockHeight	= 1000.f / heightNum;

	for (U32 i = 0; i < widthNum * heightNum; ++i)
	{
#ifdef _CSVREADER_MODE_01
		if (data.Data[i+2] == 0)
			continue;
#else
		if (data[i+2].GetInteger() == 0)
			continue;
#endif
		
		VertexARGB color = ARGBColors::Red;
		std::vector<U32>	index;
		IndexData			indexData;
		indexData = BoxFactory::GetInstance()->CreateBox(Vector3(0,0,0), Vector3(blockWhidth, blockHeight, 32.f), color, index);

		TriangleRenderer* render = NEW TriangleRenderer();
		render->Initialize(DXUTGetD3D9Device());
		render->AddIndex(index);
		render->ReCreateIndexBuffer();
		render->UpdateIndexData(indexData);

		m_TitleBlock.push_back(render);

		Matrix mat;
		Vector3 pos;

		pos.x = 500.f - ((i % widthNum) * (blockWhidth) + (blockWhidth * 0.5f));
		pos.y = 500.f - ((i / widthNum) * (blockHeight) + (blockHeight * 0.5f));
		pos.z = 0.f;

		D3DXMatrixTranslation(&mat, pos.x, pos.y, pos.z);
		render->SetWorld(mat);

		m_Shader->AddRenderer(render);
	}

	GraphicsManager::GetInstance()->AddShaderObject(m_Shader);
	GraphicsManager::GetInstance()->ReCreateVertexBuffer();
	GraphicsManager::GetInstance()->SetAllStreamSource();
	return true;
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