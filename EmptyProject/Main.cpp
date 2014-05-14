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
#include "Elements.h"
#include "Colors.h"
#include "BoxFactory.h"
#include "SphereFactory.h"
#include "SquareFactory.h"

#include "bass.h"





//#define __MY_DEBUG_STR_USE_

AK::RootNode* g_Root		= NULL;
IDirect3DDevice9* g_Device	= NULL;
//=====================================================
//	テストコード
AK::Graphics::GraphicsManager* g_mrg = NULL;
Matrix world,view, projction;

std::vector<U32> indexSrc;

//--------------------------------------------------------------------------------------
// Rejects any D3D9 devices that aren't acceptable to the app by returning false
//--------------------------------------------------------------------------------------
bool CALLBACK IsD3D9DeviceAcceptable( D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat,
                                      bool bWindowed, void* pUserContext )
{
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"IsD3D9DeviceAcceptable\n");
#endif
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
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"ModifyDeviceSettings\n");
#endif
    return true;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that will live through a device reset (D3DPOOL_MANAGED)
// and aren't tied to the back buffer size
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9CreateDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                     void* pUserContext )
{
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"OnD3D9CreateDevice\n");
#endif
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create any D3D9 resources that won't live through a device reset (D3DPOOL_DEFAULT) 
// or that are tied to the back buffer size 
//--------------------------------------------------------------------------------------
HRESULT CALLBACK OnD3D9ResetDevice( IDirect3DDevice9* pd3dDevice, const D3DSURFACE_DESC* pBackBufferSurfaceDesc,
                                    void* pUserContext )
{
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"OnD3D9ResetDevice\n");
#endif
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Handle updates to the scene.  This is called regardless of which D3D API is used
//--------------------------------------------------------------------------------------
void CALLBACK OnFrameMove( double fTime, float fElapsedTime, void* pUserContext )
{
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"OnFrameMove\n");
#endif
	AUTOPROFILE(0);
	AK::Debug::UpdateDebugConsole();


	//	テキトーにライトを設定
	D3DLIGHT9 lLight;
    memset(&lLight, 0, sizeof(D3DLIGHT9));
	static F32 Count = 0;
	Count += 0.02f;
	lLight.Position.x=0;
	lLight.Position.z=10;
	lLight.Direction = D3DXVECTOR3(cosf(fTime), -(sinf(fTime)), tanf(fTime));
    lLight.Type = D3DLIGHT_DIRECTIONAL; 
    lLight.Diffuse.r = 1.0f;
    lLight.Diffuse.g = 1.0f;
    lLight.Diffuse.b = 1.0f;
	DXUTGetD3D9Device()->SetLight(0, &lLight);
	DXUTGetD3D9Device()->LightEnable(0, true);
	
	g_Root->UpdateChild();


	DEBUG_PRINT_INT(AK::Debug::AutoPerformance::m_ProfileList[0]);
	DEBUG_PRINT_CHAR("/μs");
	DEBUG_PRINT_FLOAT(fElapsedTime);
	
}


//--------------------------------------------------------------------------------------
// Render the scene using the D3D9 device
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9FrameRender( IDirect3DDevice9* pd3dDevice, double fTime, float fElapsedTime, void* pUserContext )
{
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"OnD3D9FrameRender\n");
#endif
    HRESULT hr;

    // Clear the render target and the zbuffer 
    V( pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_ARGB( 0, 45, 50, 170 ), 1.0f, 0 ) );

    // Render the scene
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
    {
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
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"OnD3D9LostDevice\n");
#endif
}


//--------------------------------------------------------------------------------------
// Release D3D9 resources created in the OnD3D9CreateDevice callback 
//--------------------------------------------------------------------------------------
void CALLBACK OnD3D9DestroyDevice( void* pUserContext )
{
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"OnD3D9DestroyDevice\n");
#endif

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
) {
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
#ifdef __MY_DEBUG_STR_USE_
	OutputDebugString(L"wWinMain\n");
#endif
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
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
	g_Root = AK::RootNode::Create();
	AK::Graphics::BoxFactory::Create();
	AK::Graphics::SphereFactory::Create();
	AK::Graphics::SquareFactory::Create();
	g_mrg = AK::Graphics::GraphicsManager::Create();
	g_Device = DXUTGetD3D9Device();
	//=====================================================
	//	テストコード
	D3DVIEWPORT9 viewPort;
	g_Device->GetViewport(&viewPort);
	
	D3DXMatrixIdentity(&world);
	D3DXMatrixPerspectiveFovLH( &projction, D3DXToRadian(45), WINDOW_WIDTH/WINDOW_HEIGHT, 1.f, 2001.0f);
	D3DXMatrixLookAtLH( &view, &D3DXVECTOR3( 0, 0, 500), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0) );

	getViewMatrixTakingSphereInCamera(&view, Vector3(0,0,0), 500.f, D3DXToRadian(45), WINDOW_WIDTH/WINDOW_HEIGHT, Vector3(0, 0, -1), Vector3(0, 1, 0));

	g_Device->SetTransform(D3DTS_WORLD, &world);
	g_Device->SetTransform(D3DTS_VIEW, &view);
	g_Device->SetTransform(D3DTS_PROJECTION, &projction);

	g_mrg->m_Device = g_Device;
	g_mrg->Initialize();
	//DXUTGetD3D9Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	//AK::Graphics::IndexData indexdata;
	//0.9005
	//auto vec3 = AK::Math::ScreenToWorld(Vector2( 300, 100), 0.9005, WINDOW_WIDTH, WINDOW_HEIGHT, view, projction);

	//auto vec3 = AK::Math::ScreenToWorld(Vector2( WINDOW_WIDTH *  0.5f, WINDOW_HEIGHT - 50.f), 1000.f, WINDOW_WIDTH, WINDOW_HEIGHT, view, projction);

	g_mrg->SetView(view);
	g_mrg->SetProjection(projction);
	
	BASS_Init(-1, 44100, 0, DXUTGetHWND(), 0);
	HSTREAM streamHndle;
	streamHndle = BASS_StreamCreateFile(FALSE, "Assets/Sound/SE/se_maoudamashii_battle17.mp3", 0, 0, 0);
	BASS_ChannelPlay(streamHndle, FALSE);

	//	テストコード
	//=====================================================

	// Start the render loop
    DXUTMainLoop();
//	U32 count = 0;

	AK::RootNode::Destroy();
	AK::Debug::DestoryDebugConsole();
	AK::Graphics::BoxFactory::Destroy();
	AK::Graphics::SphereFactory::Destroy();
	AK::Graphics::SquareFactory::Destroy();
	AK::Graphics::GraphicsManager::Destroy();
	

    // TODO: Perform any application-level cleanup here

    return DXUTGetExitCode();
}


