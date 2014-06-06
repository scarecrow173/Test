//--------------------------------------------------------------------------------------
// File: EmptyProject.cpp
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------
#pragma comment (lib, "bass.lib")
#include "DXUT.h"


#include "resource.h"
#include "RootNode.h"
#include "DebugUtill.h"
#include "AutoPerformance.h"
#include "InputKeyboard.h"
#include "SoundManager.h"
#include "bass.h"
#include "Spectrum.h"
#include "PrimitivePool.h"
#include "MaterialPool.h"
#include "TexturePool.h"
#include "DefaultTexture.h"

//#define __MY_DEBUG_STR_USE_
using namespace AK::Graphics;

AK::RootNode* g_Root		= NULL;
IDirect3DDevice9* g_Device	= NULL;

GraphicsManager* g_mrg	= NULL;

Spectrum* spectrum		= NULL;
//BlendMultiTexturesShader* bmts = NULL;
//AK::RefCountedObjectPtr g_spmPtr(NULL);
//DefaultTexture*			g_spmObj	= NULL;
//IDirect3DSurface9*		g_spmSurf	= NULL;
//IDirect3DSurface9*		g_depth		= NULL;

Matrix world,view, projction;



//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
	TRACE(0, "IsD3D9DeviceAcceptable\n");

    // Typically want to skip back buffer formats that don't support alpha blending
    IDirect3D9* pD3D = DXUTGetD3D9Object();
    if( FAILED( pD3D->CheckDeviceFormat( pCaps->AdapterOrdinal, pCaps->DeviceType,
                                         AdapterFormat, D3DUSAGE_QUERY_POSTPIXELSHADER_BLENDING,
                                         D3DRTYPE_TEXTURE, BackBufferFormat ) ) )
        return false;

    return true;
}
//--------------------------------------------------------------------------------------
// Before a device is created, modify the device settings as needed
//--------------------------------------------------------------------------------------
bool CALLBACK ModifyDeviceSettings( DXUTDeviceSettings* pDeviceSettings, void* pUserContext )
{
	TRACE(0, "ModifyDeviceSettings\n");

    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
	TRACE(0,L"OnD3D9CreateDevice\n");
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{

	TRACE(0,L"OnD3D9ResetDevice\n");

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
	

	TRACE(0,L"OnFrameMove\n");

	AUTOPROFILE(0);
	AK::Debug::UpdateDebugConsole();

	

//	keyboard.Update();

	//	テキトーにライトを設定
	//D3DLIGHT9 lLight1,lLight2;
 //   memset(&lLight1, 0, sizeof(D3DLIGHT9));
	static F32 Count	= 0;
	Count				+= 0.02f;
	/*
	//lLight1.Position.x	= 0;
	//lLight1.Position.z	= 1000;
	lLight1.Direction	= D3DXVECTOR3(0, 0.2, -1);
    lLight1.Type		= D3DLIGHT_DIRECTIONAL; 
    lLight1.Diffuse.r	= 1.0f;
    lLight1.Diffuse.g	= 1.0f;
    lLight1.Diffuse.b	= 1.0f;
	DXUTGetD3D9Device()->SetLight(0, &lLight1);
	DXUTGetD3D9Device()->LightEnable(0, true);
	*/
	//memset(&lLight2, 0, sizeof(D3DLIGHT9));
	////lLight2.Position.x	= 0;
	////lLight2.Position.z	= 1;
	////lLight2.Position.y	= 0;
	//lLight2.Direction	= D3DXVECTOR3(0, 0.f, -1);
 //   lLight2.Type		= D3DLIGHT_DIRECTIONAL; 
 //   lLight2.Diffuse.r	= 1.0f;
 //   lLight2.Diffuse.g	= 1.0f;
 //   lLight2.Diffuse.b	= 1.0f;
	//DXUTGetD3D9Device()->SetLight(1, &lLight2);
	//DXUTGetD3D9Device()->LightEnable(1, true);

	DXUTGetD3D9Device()->SetRenderState( D3DRS_LIGHTING, TRUE );   // 発電所を回す！
	DXUTGetD3D9Device()->SetRenderState( D3DRS_AMBIENT, 0xFF2F2F2F);   // 世の中をちょっと白く照らす

	auto handle = AK::Sound::SoundManager::GetInstance()->GetStreamHandle(AK::Sound::SoundManager::GetInstance()->m_BGMNum);

	F32 fft[1024];
	BASS_ChannelGetData(handle, fft, BASS_DATA_FFT2048); // get the FFT data
	for (S32 i = 0; i < 1024; ++i)
	{

		fft[i] = ((sqrt(fft[i]) * 3 * WINDOW_HEIGHT) * 2);
		fft[i] = WINDOW_HEIGHT - (fft[i] > (WINDOW_HEIGHT * 0.9f) ? (WINDOW_HEIGHT * 0.9f) : fft[i]);

	}
	spectrum->Update(fft, 1024);


	g_Root->UpdateNodeTree();


	DEBUG_PRINT_INT(AK::Debug::AutoPerformance::m_ProfileList[0]);
	DEBUG_PRINT_CHAR("/μs");
	DEBUG_PRINT_FLOAT(fElapsedTime);
	
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{

	TRACE(0, L"OnD3D9FrameRender\n");

    HRESULT hr;

    // Clear the render target and the zbuffer										 0, 45, 50, 170
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
		//IDirect3DSurface9* back = NULL;
		//IDirect3DSurface9* bd = NULL;
		//pd3dDevice->GetRenderTarget(0, &back);
		//pd3dDevice->GetDepthStencilSurface(&bd);
		//pd3dDevice->SetRenderTarget(0, g_spmSurf);
		//pd3dDevice->SetDepthStencilSurface(g_depth);
	 //   V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0), 1.0f, 0 ) );

		spectrum->Draw();
		//pd3dDevice->SetRenderTarget(0, back);
		//pd3dDevice->SetDepthStencilSurface(bd);

		//phong->Draw();

		pd3dDevice->Clear( 0, NULL, D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 0, 0, 0 ), 1.0f, 0 );

		g_mrg->Draw();

		

        V( pd3dDevice->EndScene() );
    }
	
}


//--------------------------------------------------------------------------------------
// Handle messages to the application 
//--------------------------------------------------------------------------------------
LRESULT CALLBACK MsgProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam,
                          bool* pbNoFurtherProcessing, void* pUserContext )
{
    return 0;
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9ResetDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9LostDevice( void* pUserContext )
{
	TRACE(0, L"OnD3D9LostDevice\n");

}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{

	OutputDebugString(L"OnD3D9DestroyDevice\n");


}

////////////////////////////////////////
// 境界球をカメラに収めるView行列算出
//
// out    : ビュー行列（出力）
// r      : 境界球半径
// fovY   : 画角Y
// aspect : アスペクト比
// direct : カメラの向きベクトル
// up     : カメラの上ベクトル
// 戻り値 : ビュー行列

D3DXMATRIX *getViewMatrixTakingSphereInCamera(
    D3DXMATRIX* out,
    const D3DXVECTOR3& center,
    float r,
    float fovY,
    float aspect,
    const D3DXVECTOR3& direct,
    const D3DXVECTOR3& up
) 
{
    // fovYとfovXの小さい方をθとして選択
    float theta = (aspect >= 1.0f) ? fovY : fovY * aspect;

    // 引く距離を算出
    float d = r / sin( theta / 2.0f );

    // カメラ位置確定
    D3DXVECTOR3 normDirect;
    D3DXVec3Normalize( &normDirect, &direct );
    D3DXVECTOR3 pos = center - normDirect * d;

    // ビュー行列作成
    return D3DXMatrixLookAtLH( out, &pos, &center, &up );
}
//--------------------------------------------------------------------------------------
// Initialize everything and go into a render loop
//--------------------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE, HINSTANCE, LPWSTR, int )
{
	AK::Debug::SetTraceLevel(2);

	TRACE(0, L"wWinMain\n");

	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//_CrtSetBreakAlloc(642);
#endif

    // Set the callback functions
    DXUTSetCallbackD3D9DeviceAcceptable( IsD3D9DeviceAcceptable );
    DXUTSetCallbackD3D9DeviceCreated( OnD3D9CreateDevice );
    DXUTSetCallbackD3D9DeviceReset( OnD3D9ResetDevice );
    DXUTSetCallbackD3D9FrameRender( OnD3D9FrameRender );
    DXUTSetCallbackD3D9DeviceLost( OnD3D9LostDevice );
    DXUTSetCallbackD3D9DeviceDestroyed( OnD3D9DestroyDevice );
    DXUTSetCallbackDeviceChanging( ModifyDeviceSettings );
    DXUTSetCallbackMsgProc( MsgProc );
    DXUTSetCallbackFrameMove( OnFrameMove );

    // TODO: Perform any application-level initialization here

    // Initialize DXUT and create the desired Win32 window and Direct3D device for the application
    DXUTInit( true, true ); // Parse the command line and show msgboxes
    DXUTSetHotkeyHandling( true, true, true );  // handle the default hotkeys
    DXUTSetCursorSettings( true, true ); // Show the cursor and clip it when in full screen
    DXUTCreateWindow( L"Breakout" );
    DXUTCreateDevice( true, WINDOW_WIDTH, WINDOW_HEIGHT );

	AK::Debug::CreateDebugConsole();
	

	AK::Sound::SoundManager::Create();
	AK::Sound::SoundManager::GetInstance()->Initalize();
	
	g_mrg = AK::Graphics::GraphicsManager::Create();
	g_Device = DXUTGetD3D9Device();
	g_mrg->SetD3DDevice9(&g_Device);
	g_mrg->Initialize();


	

	
	D3DXMatrixIdentity(&world);
	D3DXMatrixPerspectiveFovLH( &projction, D3DXToRadian(45), WINDOW_WIDTH/WINDOW_HEIGHT, 1.f, 2001.0f);

	const Vector3 eye(0.f, 0.f, 500.f);
	const Vector3 at(0.f, 0.f, 0.f);
	const Vector3 up(0.f, 1.f, 0.f);
	D3DXMatrixLookAtLH( &view, &eye, &at, &up );

	getViewMatrixTakingSphereInCamera(&view, Vector3(0,0,0), 500.f, D3DXToRadian(45), WINDOW_WIDTH/WINDOW_HEIGHT, Vector3(0, 0, -1), Vector3(0, 1, 0));



	//g_Device->SetTransform(D3DTS_WORLD, &world);
	//g_Device->SetTransform(D3DTS_VIEW, &view);
	//g_Device->SetTransform(D3DTS_PROJECTION, &projction);
	g_mrg->SetView(view);
	g_mrg->SetProjection(projction);

	g_Root = AK::RootNode::Create();

	//g_Device->SetVertexShaderConstantF(0, world,		4);
	//g_Device->SetVertexShaderConstantF(4, view,			4);
	//g_Device->SetVertexShaderConstantF(8, projction,	4);

	//g_Device->SetVertexShaderConstantF(13, eye,	1);

	//const Vector3 LightDir(0, 0.f, -1);
	//g_Device->SetVertexShaderConstantF(12, LightDir, 1);
	
	//D3DMATERIAL9 material;
	//
	//material.Diffuse.a = 0.0f;
	//material.Diffuse.r = 1.0f;
	//material.Diffuse.g = 1.0f;
	//material.Diffuse.b = 1.0f;

	//material.Ambient.a = 1.0f;
	//material.Ambient.r = 1.0f;
	//material.Ambient.g = 1.0f;
	//material.Ambient.b = 1.0f;

	//material.Specular.a = 1.0f;
	//material.Specular.r = 0.4f;
	//material.Specular.g = 0.4f;
	//material.Specular.b = 0.4f;

	//material.Emissive.a = 0.0f;
	//material.Emissive.r = 0.1f;
	//material.Emissive.g = 0.1f;
	//material.Emissive.b = 0.1f;

	//material.Power = 1000.f;

	//g_Device->SetMaterial(&material);


	//AK::Graphics::Material mymaterial;

	//memcpy(&material, &mymaterial.m_Diffuse, sizeof(D3DMATERIAL9));

	//ZeroMemory(&mymaterial, sizeof(AK::Graphics::Material));

	//blur = NEW AK::Graphics::BlurFilter();
	//blur->Initilize();

	//bmts = NEW AK::Graphics::BlendMultiTexturesShader();
	//bmts->Initilize();
	//bmts->Draw();
	spectrum = NEW AK::Graphics::Spectrum();
	spectrum->CreateSpectrumData();
	
	//phong	= NEW AK::Graphics::DefaultShader();
	//g_spmPtr = AK::Graphics::TexturePool::GetInstance()->GetResource("data:DefaultTexture - spm");
	//g_spmObj = RTTI_PTR_DYNAMIC_CAST(DefaultTexture, g_spmPtr.GetSharedObject());
	//if (g_spmObj->GetTexture() == NULL)
	//{
	//	LPDIRECT3DTEXTURE9 tex;
	//	D3DXCreateTexture(GraphicsManager::GetInstance()->GetD3DDevice(),
	//		1024, 
	//		1024,
	//		1,
	//		D3DUSAGE_RENDERTARGET,
	//		D3DFORMAT::D3DFMT_A8R8G8B8,
	//		D3DPOOL_DEFAULT,
	//		&tex);
	//	g_spmObj->SetTexture(&tex);
	//}
	//g_spmObj->GetTexture()->GetSurfaceLevel(0, &g_spmSurf);
	//g_spmObj->GetTexture()->Release();
	//IDirect3DSurface9 *pSurf;
	//GraphicsManager::GetInstance()->GetD3DDevice()->GetDepthStencilSurface( &pSurf );
	//D3DSURFACE_DESC Desc;
	//pSurf->GetDesc( &Desc );
	//SAFE_RELEASE(pSurf);
	//
	//auto hr = GraphicsManager::GetInstance()->GetD3DDevice()->CreateDepthStencilSurface(
	//	1024,
	//	1024,
	//	Desc.Format,
	//	Desc.MultiSampleType,
	//	Desc.MultiSampleQuality,
	//	FALSE,
	//	&g_depth,
	//	NULL
	//	);

	// Start the render loop
    DXUTMainLoop();

	SAFE_DELETE(spectrum);
	AK::RootNode::Destroy();
	AK::Debug::DestoryDebugConsole();
	AK::Graphics::PrimitivePool::DestroySingleton();
	AK::Graphics::MaterialPool::DestroySingleton();
	AK::Graphics::TexturePool::DestroySingleton();
	AK::Graphics::GraphicsManager::Destroy();
	AK::Sound::SoundManager::Destroy();
	BASS_Free();

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


