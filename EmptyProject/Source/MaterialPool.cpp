//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "MaterialPool.h"
#include "StringEncoder.h"
#include "DefaultTexture.h"
#include "CubeTexture.h"
#include "GraphicsManager.h"
#include "CSVReader.h"
#include <string>

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
MaterialPool::MaterialPool()
{
	m_MaterialCreator["Default"] = CreateDefaultMaterial;
	//m_MaterialCreator["Metal"];
	//m_MaterialCreator["sample"];
	//m_MaterialCreator["sample"];
	m_MaterialLoader["Default"] = LoadCSVMaterial;
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
MaterialPool::~MaterialPool()
{
	auto iResouce = m_ManagedResouce.begin();
	while (iResouce != m_ManagedResouce.end())
	{
		iResouce = m_ManagedResouce.erase(iResouce);
	}
}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 形状ごとの共有リソースを取得
//							タイプ(dataかfile)		　マテリアルタイプ			名前
//!	@param[in]	: 例: dataCode = "data				:	Default				-	sample"
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr MaterialPool::GetMaterial(const std::string& dataCode)
{
	std::string dataType, materialType, name;
	SplitDataPath(dataCode, dataType, materialType, name);

	auto it = m_ManagedResouce.find(dataCode);
	if (it != m_ManagedResouce.end())
		return it->second;


	return SelectByDataType(dataCode, dataType, materialType, name);
}
//=======================================================================================
//		protected method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr MaterialPool::SelectByDataType(const std::string& dataCode, const std::string& dataType, const std::string& materialType, const std::string& name)
{
	if (dataType == "file")
	{
		m_ManagedResouce[dataCode] = RefCountedObjectPtr(m_MaterialLoader["Default"](name));
	}
	else if (dataType == "data")
	{
		auto iCreator = m_MaterialCreator.find(materialType);
		if (iCreator == m_MaterialCreator.end())
			return RefCountedObjectPtr(NULL);
		m_ManagedResouce[dataCode] = RefCountedObjectPtr(m_MaterialCreator[materialType]());
	}
	else
	{
		assert(0);
		return RefCountedObjectPtr(NULL);
	}

	return m_ManagedResouce[dataCode];
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
void MaterialPool::SplitDataPath(std::string src, std::string& dataType, std::string& materialType, std::string& name)
{
	static StringEncoder encoder;

	encoder.DeleteSpace(src);
	dataType		= encoder.SplitFront(src, ":");
	materialType	= encoder.SplitFront(src, "-");
	name			= src;

	assert(dataType			!= "");
	assert(materialType		!= "");
	assert(name				!= "");
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
Material* MaterialPool::CreateDefaultMaterial()
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
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
Material* MaterialPool::LoadCSVMaterial(const std::string& filePath)
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
//		private method
//=======================================================================================

//===============================================================
//	End of File
//===============================================================