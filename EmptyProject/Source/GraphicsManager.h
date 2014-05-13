//=======================================================================================
//!	@file	:	GraphicsManager.h
//!	@author	:	小山 瑛圭
//!	@date	:	2014/4/28
//=======================================================================================
#pragma once
#include "Elements.h"
#include "MyMath.h"
#include "IShaderObject.h"

namespace AK
{
namespace Graphics
{
enum PRIMITIVE_TYPE
{
	PRIMITIVE_BOX = 0,
	PRIMITIVE_SPHERE,
	PRIMITIVE_LINE,
	PRIMITIVE_SQUARE
};
struct VertexBaseData
{
	VertexFloat3 position;
	VertexFloat3 normal;
};

class BoxFactory;
class SphereFactory;
class SquareFactory;

//=======================================================================================
//!	@class	:	GraphicsManager
//!	@brief	:	example
//!	@par	:	example
//!	@note	:	example
//=======================================================================================
class GraphicsManager
{
public:
	static GraphicsManager*	Create();
	static void				Destroy();
	static GraphicsManager*	GetInstance();


	friend BoxFactory;
	friend SphereFactory;
	friend SquareFactory;


	static const U32 ONE_BOX_VERTEX_NUM			= 8;
	static const U32 ONE_BOX_FACE_NUM			= 12;
	static const U32 SPHERE_SLICES				= 10;
	static const U32 SPHERE_STACKS				= 10;
	static const U32 ONE_SPHERE_VERTEX_NUM		= (SPHERE_SLICES + 1) * (SPHERE_STACKS + 1);
	static const U32 ONE_SPHERE_FACE_NUM		= SPHERE_SLICES * SPHERE_STACKS * 2;
	static const U32 LINE_NUM					= 5;
	static const U32 ONE_LINE_VERTEX_NUM		= 20;
	static const U32 SQUARE_VERTEX_NUM			= 4;
	static const U32 SQUARE_NUM					= 10;
	static const U32 BOX_NUM					= 50;
	static const U32 SPHERE_NUM					= 4;
	static const U32 VERTEX_NUM					= (ONE_BOX_VERTEX_NUM * BOX_NUM) + (ONE_SPHERE_VERTEX_NUM * SPHERE_NUM) + (SQUARE_NUM * SQUARE_VERTEX_NUM) + (ONE_LINE_VERTEX_NUM * LINE_NUM);
	static const U32 INSTACE_NUM				= 50;



	void	AddShaderObject(IShaderObject* shader);
	void	EraseShaderObject(IShaderObject* shader);
	bool	ReCreateVertexBuffer();
	void	SetAllStreamSource();

	void	ChangeColor(U32 min, U32 max, VertexARGB color);
	
	void	SetView(Matrix& view);
	void	SetProjection(Matrix& projction);
	Matrix	GetView();
	Matrix	GetProjection();

	bool	Initialize();
	void	Draw();
	IDirect3DDevice9*		m_Device;
private:

	GraphicsManager();
	virtual ~GraphicsManager();

	static GraphicsManager*			m_Instance;
	
	//IDirect3DDevice9*		m_Device;

	static VertexBaseData			m_VertexBase[VERTEX_NUM];
	static VertexARGB				m_VertexColor[VERTEX_NUM];
	static VertexFloat2				m_VertexUV[VERTEX_NUM];
	static F32						m_VertexInstance[VERTEX_NUM];

	Matrix							m_View;
	Matrix							m_Projection;
	Vector3							m_WorldPos[INSTACE_NUM];
	Vector3							m_WorldScale[INSTACE_NUM];


	IDirect3DVertexBuffer9*			m_BaseBuffer;
	IDirect3DVertexBuffer9*			m_ColorBuffer;
	IDirect3DVertexBuffer9*			m_UVBuffer;
	IDirect3DVertexBuffer9*			m_InstanceBuffer;
	U32								m_IndexCount;
	U32								m_VertexCount;


	std::vector<IShaderObject*>		m_ShaderList;
};
//=======================================================================================
//		inline method
//=======================================================================================
//-------------------------------------------------------------
//!	@brief		: インスタンス取得
//!	@return		: インスタンス
//-------------------------------------------------------------
inline GraphicsManager* GraphicsManager::GetInstance()
{
	assert(m_Instance);
	return m_Instance;
}
};
};
//===============================================================
//	End of File
//===============================================================