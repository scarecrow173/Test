//=======================================================================================
//!	@file	:	Sample.cpp
//!	@brief	:	Sampleクラスのメンバ関数宣言
//!	@author	:	小山 瑛圭
//!	@date	:	2014/5/01
//!	@par	:	example
//!	@note	:	example
//=======================================================================================

#include "PrimitivePool.h"
#include "StringEncoder.h"
using namespace AK;
using namespace Graphics;
//=======================================================================================
//		Constants Definitions
//=======================================================================================

//-------------------------------------------------------------
//!	@brief		: コンストラクタ
//-------------------------------------------------------------
PrimitivePool::PrimitivePool()
{
	//	ファクトリの名前はファイルから読み込むべき？
	m_PrimitiveCreator["BOX"]		= NEW BoxFactory();
	m_PrimitiveCreator["SHPERE"]	= NEW SphereFactory();
}
//-------------------------------------------------------------
//!	@brief		: デストラクタ
//-------------------------------------------------------------
PrimitivePool::~PrimitivePool()
{
	auto it = m_PrimitiveCreator.begin(); 
	while (it != m_PrimitiveCreator.end())
	{
		SAFE_DELETE(it->second);
		it = m_PrimitiveCreator.erase(it);
	}
}
//=======================================================================================
//		public method
//=======================================================================================
//---------------------------------------------------------------------------------------
//!	@brief		: 形状ごとの共有リソースを取得(file読み込み未実装)
//							タイプ(dataかfile)		　形状指定	　　名前
//!	@param[in]	: 例: dataCode = "data				:	BOX		-	Box01"
//!	@return		: 
//---------------------------------------------------------------------------------------
RefCountedObjectPtr PrimitivePool::GetPrimitive(const std::string& dataCode)
{
	std::string dataType, primiveType;
	SplitDataPath(dataCode, dataType, primiveType/*, name*/);

	auto iCreator = m_PrimitiveCreator.find(primiveType);
	//	ファイル読み込みは未実装なのでアサートしてNULLのオブジェクトを返す
	//	ファクトリがm_PrimitiveCreatorに登録されていなければアサートしてNULLのオブジェクト返す
	if (dataType != "data" || iCreator == m_PrimitiveCreator.end())
	{
		assert(0);	
		return RefCountedObjectPtr(NULL);
	}

	auto it = m_ManagedResouce.find(dataCode);
	if (it != m_ManagedResouce.end())
		return RefCountedObjectPtr(it->second);

	m_ManagedResouce[dataCode] = m_PrimitiveCreator[primiveType]->CreatePrimitive();
	return RefCountedObjectPtr(m_ManagedResouce[dataCode]);
}
//---------------------------------------------------------------------------------------
//!	@brief		: 
//!	@param[in]	: 
//!	@return		: 
//---------------------------------------------------------------------------------------
void PrimitivePool::SplitDataPath(std::string src, std::string& dataType, std::string& primitiveType/*, std::string& name*/)
{
	static StringEncoder encoder;

	encoder.DeleteSpace(src);
	dataType		= encoder.SplitFront(src, ":");
	primitiveType	= encoder.SplitFront(src, "-");
	//name			= src;

	assert(dataType			!= "");
	assert(primitiveType	!= "");
	//assert(name				!= "");
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