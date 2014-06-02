//=======================================================================================
//!	@file	:	MaterialFactory.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "MaterialFactory.h"
#include "CSVReader.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
MaterialFactory::MaterialFactory()
{}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
MaterialFactory::~MaterialFactory()
{}
//=======================================================================================
//		public method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Material* MaterialFactory::CreateMaterial()
{
	Material* out = NEW  Material();

	out->m_Ambient.a = 1.f;
	out->m_Ambient.r = 1.f;
	out->m_Ambient.g = 1.f;
	out->m_Ambient.b = 1.f;

	out->m_Diffuse.a = 1.f;
	out->m_Diffuse.r = 1.f;
	out->m_Diffuse.g = 1.f;
	out->m_Diffuse.b = 1.f;

	out->m_Emissive.a = 0.3f;
	out->m_Emissive.r = 0.3f;
	out->m_Emissive.g = 0.3f;
	out->m_Emissive.b = 0.3f;

	out->m_Specular.a = 0.3f;
	out->m_Specular.r = 0.3f;
	out->m_Specular.g = 0.3f;
	out->m_Specular.b = 0.3f;

	out->m_SpecularPower = 0.3f;

	return out;
}
//-------------------------------------------------------------
//!	@brief		: example
//!	@param[in]	: example
//!	@return		: example
//-------------------------------------------------------------
Material* MaterialFactory::CreateMaterialFromFile(const std::string& filePath)
{
	Material* out = NEW  Material();
	CSVReader data;
	data.Load(filePath.c_str());
	out->m_Ambient.a = data[0].GetDecimal();
	out->m_Ambient.r = data[1].GetDecimal();
	out->m_Ambient.g = data[2].GetDecimal();
	out->m_Ambient.b = data[3].GetDecimal();

	out->m_Diffuse.a = data[4].GetDecimal();
	out->m_Diffuse.r = data[5].GetDecimal();
	out->m_Diffuse.g = data[6].GetDecimal();
	out->m_Diffuse.b = data[7].GetDecimal();

	out->m_Emissive.a = data[8].GetDecimal();
	out->m_Emissive.r = data[9].GetDecimal();
	out->m_Emissive.g = data[10].GetDecimal();
	out->m_Emissive.b = data[11].GetDecimal();

	out->m_Specular.a = data[12].GetDecimal();
	out->m_Specular.r = data[13].GetDecimal();
	out->m_Specular.g = data[14].GetDecimal();
	out->m_Specular.b = data[15].GetDecimal();

	out->m_SpecularPower = data[16].GetDecimal();

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