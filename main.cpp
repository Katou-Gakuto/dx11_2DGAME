//--------------------------------------------------------------------------------------
// File: Tutorial07.cpp
//
// This application demonstrates texturing
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//--------------------------------------------------------------------------------------

// ゲームパット　Xinput
// 音　          Xオーディオ2

/*
* マップの自動生成
* プレイヤー　複数
* カメラ
* 一画面
* レベル制　敵も少しずつステータスが上がる
* 4人までプレイできる
* メニューあり
* 遠のみ、中まで、近のみ、設置のみ 4種類のキャラ
* エフェクト
* 名前
*/
#include <windows.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include "DirectXTex.h"

#include <iostream>
//#include <cstdlib>?
//#include <cmath>?

#include "Header/Camera.h"
#include "Header/DataManager.h"
#include "Header/DirectX_Structs.h"
#include "Header/EndManager.h"
#include "Header/GameManager.h"
#include "Header/KeyState.h"
#include "Header/LoadingManager.h"
#include "Header/Macro.h"
#include "Header/Master.h"
#include "Header/ObjectManager.h"
#include "Header/ResourceManager.h"
#include "Header/SceneManager.h"
#include "Header/TimeManager.h"
#include "Header/UIManager.h"

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "imm32.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTexd.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

#define PLAYER_NUMBER 1
#define PLAYER_SIZE XMFLOAT2(32,64)
#define PLAYER_DRAW_MOVE_SPEED 30

#define PLUS_POS_FLAG 0b100

using namespace DirectX;


//--------------------------------------------------------------------------------------
// Structures(構造体宣言)
//--------------------------------------------------------------------------------------


struct Character
{
    XMFLOAT2 pos;

    float size;

    bool LiveFlag;

    int moveAnimeNumber;

    int characterType;
};

struct Player : Character
{

    XMFLOAT2 dir;
    float speed;

    int vecAnimeNumber;

    int moveAnimePlusNumber;
};

//--------------------------------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------------------------------
// 理解不足　理解しに行かないと間に合わない　多分間違ってる部分ある
HINSTANCE                           g_hInst = NULL;
HWND                                g_hWnd = NULL;
D3D_DRIVER_TYPE                     g_driverType = D3D_DRIVER_TYPE_NULL;
D3D_FEATURE_LEVEL                   g_featureLevel = D3D_FEATURE_LEVEL_11_0; // チップのバージョン
ID3D11Device*                       g_pd3dDevice = NULL;            // 抽象化したデバイス
ID3D11DeviceContext*                g_pImmediateContext = NULL;     // デバイスコンテキスト 
IDXGISwapChain*                     g_pSwapChain = NULL;            // ダブルバッファを使うための物　複数枚できるようになる　(フレームレートが安定するが入力遅延が起きる)
ID3D11RenderTargetView*             g_pRenderTargetView = NULL;     // メモリ領域　眼鏡と言われたりしてる
ID3D11Texture2D*                    g_pDepthStencil = NULL;         // 
ID3D11DepthStencilView*             g_pDepthStencilView = NULL;     // 
ID3D11VertexShader*                 g_pVertexShader = NULL;         // 
ID3D11PixelShader*                  g_pPixelShader = NULL;          // 
ID3D11InputLayout*                  g_pVertexLayout = NULL;         // 頂点フォーマットの設定情報
/*メモリ領域*/
ID3D11Buffer*                       g_pVertexBuffer = NULL;         // 頂点バッファ
ID3D11Buffer*                       g_pCBNeverChanges = NULL;       // 
ID3D11Buffer*                       g_pCBChangeOnResize = NULL;     // 
ID3D11Buffer*                       g_pCBChangesEveryFrame = NULL;  // 
// コンスタンスメモリ領域?
/*           */

//ID3D11ShaderResourceView*           g_pTextureRV = NULL;            // テクスチャをシェーダーに送るための眼鏡
//ID3D11ShaderResourceView*           g_pBGTextureRV = NULL;          // 
//ID3D11ShaderResourceView*           g_pMapchipRV = NULL;          // 
//ID3D11ShaderResourceView*           g_pCatRV = NULL;          // 

ID3D11SamplerState*                 g_pSamplerLinear = NULL;        // サンプリングの設定
ID3D11RasterizerState*              g_pRasterState = NULL;          // どういう仕事をしてほしいかを設定 ピクセルを塗る判断をする設定 塗るのをピクセルシェーダでやる
ID3D11DepthStencilState*            g_pDepthStencilState = NULL;    // ピクセル上書きする設定
ID3D11BlendState*                   g_pBlendState = NULL;   // ブレンド用
ID3D11BlendState*                   g_pBlendStateAdd = NULL;   // 加算合成
ID3D11BlendState*                   g_pBlendStateSub = NULL;   // 減算合成
XMMATRIX                            g_World;    // 4*4 16のfloat　行列
XMMATRIX                            g_View;
XMMATRIX                            g_Projection;
XMFLOAT4                            g_vMeshColor( 1.0f, 1.0f, 1.0f, 1.0f );

Player g_Players[PLAYER_NUMBER];
Character g_Cat;
XMFLOAT2 g_DrawMoveSpeed;
std::vector<XMUINT2> g_MapHitObjectPoss;

/*
// 0 草原
// 1 砂利
int g_MapData[12][20] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {3,0,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0},
    {3,0,0,0,0,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0},
    {3,3,3,3,3,3,3,3,0,3,0,0,0,0,0,0,0,0,0,0},
};


int g_MapDataObj[12][20] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};*/

//--------------------------------------------------------------------------------------
// Master (後でマスターヘッダーの中に移動)
//--------------------------------------------------------------------------------------
DataManager* Master::mpDataManager = new DataManager();
EndManager* Master::mpEndManager = new EndManager();
GameManager* Master::mpGameManager = new GameManager();
KeyState* Master::mpKeyState = new KeyState();
LoadingManager* Master::mpLoadingManager = new LoadingManager();
ResourceManager* Master::mpResourceManager = new ResourceManager();
SceneManager* Master::mpSceneManager = new SceneManager();
TimeManager* Master::mpTimeManager = new TimeManager((int)(1000.0f / 60.0f));
UIManager* Master::mpUIManager = new UIManager();
//int testNumber[4] = { -1, -1, -1, -1 };
//--------------------------------------------------------------------------------------
// Forward declarations
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow );
HRESULT InitDevice();
void CleanupDevice();
LRESULT CALLBACK    WndProc( HWND, UINT, WPARAM, LPARAM );
void Render();


//void DrawSprite(float x, float y, float width, float height, float left, float right, float up, float down, ID3D11ShaderResourceView* resourceView, int middleSetFlag = 0);
//void DrawSprite(float x, float y, float width, float height, float left, float right, float up, float down, ID3D11ShaderResourceView* resourceView, ID3D11DeviceContext* immediateContext, ID3D11Buffer* vertexBuffer, int intFlag = 0);
void InitGame();
void SetPlayer(Player* playerData, XMFLOAT2 pos, XMFLOAT2 dir, float speed, int type, float size);
void SetDirNormalize(XMFLOAT2* dir);
void PlayersMove();
void SetDrawMap(XMFLOAT2 sizeRatio, XMFLOAT2 drawPosMin, XMFLOAT2 drawPosMax, XMFLOAT2 uvMin, XMFLOAT2 uvMax, int resourceId, int intFlag);
XMFLOAT2 XMVSub(XMFLOAT2 src, XMFLOAT2 dst);
float XMVSize(XMFLOAT2 src);
float XMVSizeSq(XMFLOAT2 src);
bool HitCheckBC(XMFLOAT2 srcPos, float srcR, XMFLOAT2 dstPos, float dstR);
bool CheckWithin(float srcPos, float srcSize, float dstPos, float dstSize);
bool HitCheckBB(XMFLOAT2 srcPos, float srcSize, XMFLOAT2 dstPos, float dstSize);
bool HitCheckBB(XMFLOAT2 srcPos, float srcW, float srcH, XMFLOAT2 dstPos, float dstW, float dstH);

//--------------------------------------------------------------------------------------
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//--------------------------------------------------------------------------------------
// コールバック関数 ウィンドーズに動かしてもらう
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    // 無効化　-1にしてる
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    if( FAILED( InitWindow( hInstance, nCmdShow ) ) )
        return 0;

    if( FAILED( InitDevice() ) )
    {
        CleanupDevice();
        return 0;
    }

    InitGame();

    Master::mpGameManager->Initilize();
    /*timeBeginPeriod(1); // タイマーの分解量の設定を1msにする (1ミリ秒/1000秒)にする

    // DWORD = unsigned int
    DWORD currentTime = timeGetTime();  // 現在時刻
    DWORD lastTime = currentTime;       // 前回更新時刻
    */

    // Main message loop
    MSG msg = {0};
    Master::mpKeyState->Initilize(&msg);
    while (!Master::mpEndManager->GetEndFlag(msg))
    {
        // ツールを作るときはGetMessage(軽くするために)
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            // 文字コードに変換する
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            if (Master::mpLoadingManager->GetLoadingFlag() == 0)
            {
                // 1フレーム分の時間待つ
                if (Master::mpTimeManager->GetNextUpdateFlag())
                {
                    // 更新
                    Master::mpGameManager->Update();

                    // 削除フラグが有効な物は削除する
                    Master::mpGameManager->GetObjectManager()->DeleteAllIfNeeded();

                    // 描画
                    Master::mpGameManager->Draw();

                    // シーン移動確認
                    Master::mpSceneManager->CheckNextScene();

                    //currentTime = timeGetTime(); //現在時刻を更新

                    // 現在時刻と前回更新時刻の差分が16.66msより大きければゲームを実行する
                    //if ((currentTime - lastTime) > (1000.0f / 60.0f))
                }
            }
            else
            {
                // ローディング処理
                Master::mpLoadingManager->LoadingProcess();
            }
        }
    }

    CleanupDevice();

    timeBeginPeriod(0); // タイマーの分解設定をデフォルトに戻す

    return ( int )msg.wParam;
}


//--------------------------------------------------------------------------------------
// Register class and create window
//--------------------------------------------------------------------------------------
HRESULT InitWindow( HINSTANCE hInstance, int nCmdShow )
{
    // Register class
    // 登録情報を設定 動いても怪しくない
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof( WNDCLASSEX );
    wcex.style = CS_CLASSDC;
    wcex.lpfnWndProc = WndProc;// ウィンドープロシージャーの登録　関数を入れてる
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = NULL;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW); // カーソルを変える ハードウェアカーソル　速いけど絵とかにできない　　無効化して絵　ソフトウェアカーソル
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;   // ツールとか作るときに　オプションとかプロパティとかを選択するときのやつ
    wcex.lpszClassName = "TutorialWindowClass"; // 名前を付けたやつ 二重起動をさせないなどで使える 名刺
    wcex.hIconSm = NULL; // 左上のアイコン　タスクバーにカーソルあわせてやつとか
    // ウィンドウズAPI
    if( !RegisterClassEx( &wcex ) )
        return E_FAIL;

    // Create window
    g_hInst = hInstance;
    RECT rc = { 0, 0, 1280, 720 };  // 矩形を設定する
    // ウィンドウズAPI     /*ウィンドウズの形*/
    AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );    // ウィンドウズの大きさをいい感じにそろえてくれる
    // ウィンドウズAPI
    g_hWnd = CreateWindow(  "TutorialWindowClass",  // 上の名刺と合わせる
                            "Team Battle", // ウィンドタイトル
                            WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,    // ウィンドタイプ 最小化や最大化などを追加できる
                            CW_USEDEFAULT,
                            CW_USEDEFAULT,
                            rc.right - rc.left,
                            rc.bottom - rc.top,
                            NULL,
                            NULL,
                            hInstance,
                            NULL );

    if( !g_hWnd )
        return E_FAIL;

    ShowWindow( g_hWnd, nCmdShow ); // ウィンドウズの表示

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Helper for compiling shaders with D3DX11
//--------------------------------------------------------------------------------------
HRESULT CompileShaderFromFile(LPCWSTR szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut )
{
    HRESULT hr = S_OK;

    DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    // Set the D3DCOMPILE_DEBUG flag to embed debug information in the shaders.
    // Setting this flag improves the shader debugging experience, but still allows 
    // the shaders to be optimized and to run exactly the way they will run in 
    // the release configuration of this program.
    dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob* pErrorBlob;
    hr = D3DCompileFromFile( szFileName, NULL, NULL, szEntryPoint, szShaderModel,
        dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
    if( FAILED(hr) )
    {
        if( pErrorBlob != NULL )
            OutputDebugStringA( (char*)pErrorBlob->GetBufferPointer() );
        if( pErrorBlob ) pErrorBlob->Release();
        return hr;
    }
    if( pErrorBlob ) pErrorBlob->Release();

    return S_OK;
}


//--------------------------------------------------------------------------------------
// Create Direct3D device and swap chain
//--------------------------------------------------------------------------------------
HRESULT InitDevice()
{
    // Hリザルト　エラーを見るために リザルトのハンドル
    HRESULT hr = S_OK;

    RECT rc;
    /*ウィンドウズ API*/
    GetClientRect(g_hWnd, &rc);   // ウィンドの黒い領域の大きさを返してくれる
    //GetWindowRect(); // ウィンドの大きさ
    // 基本はいらない　ツールを作る時とかに必要
    UINT width = rc.right - rc.left;
    UINT height = rc.bottom - rc.top;

    UINT createDeviceFlags = 0;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    createDeviceFlags |= D3D11_CREATE_DEVICE_BGRA_SUPPORT;

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,  // GPUにレンたタリングを任せる
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE, // CPUがGPUのふりをする　確実に思いが動かせる
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes); //配列数を取得できる

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0, // 対応しているか確かめる　11が動くかを試すだけでいい
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1; // バックバッファ
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60; //60ヘルツ
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = g_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
    sd.Windowed = TRUE; // falseにするとフルスクリーン

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        g_driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDeviceAndSwapChain(NULL, g_driverType, NULL, createDeviceFlags, featureLevels, numFeatureLevels,   // スワップとデバイスの作成してる
            D3D11_SDK_VERSION, &sd, &g_pSwapChain, &g_pd3dDevice, &g_featureLevel, &g_pImmediateContext);
        if (SUCCEEDED(hr))
            break;
    }
    if (FAILED(hr))
        return hr;

    // Create a render target view
    ID3D11Texture2D* pBackBuffer = NULL;
    hr = g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);// スワップチェインのバックバッファを取得
    if (FAILED(hr))
        return hr;

    hr = g_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
    pBackBuffer->Release();// 参照を一つ減らしてる
    if (FAILED(hr))
        return hr;

    //スペンシルバッファで穴あけとかも出来る
    // やらなくていい処理をやらない　手の奥側とか

    /*パソコン　32ビット　* 4 の128ビットの計算が得意*/

    // Zバッファ(デプスバッファ) の作成
    // テクスチャ作成
    // Create depth stencil texture
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));// メモリ領域を0で初期化
    descDepth.Width = width;    // バックバッファと同じサイズ
    descDepth.Height = height;  // バックバッファと同じサイズ
    descDepth.MipLevels = 1; // LOD(レベルオブディティール)処理の一つ　0だと限界まで作る  1半分　1の半分　2の半分
    descDepth.ArraySize = 1; // キューブマップで使える 6面分のテクスチャを入れれる用にするとき使う
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;   // 分割数　形式　 (アンインドノーマライズ)   D24_UNORM(デプス24ビット)   S8_UINT(スペンシル8ビット)
    descDepth.SampleDesc.Count = 1;// サンプリング回数  2とかにするとマルチサンプリングができる 　周りからピクセルを取得して平均化する　輪郭がぼやけたりする MSAA(マルチサンプリングエイリアス)
    descDepth.SampleDesc.Quality = 0;// 基本GPUに任せる　会社にノウハウがあればそっち
    descDepth.Usage = D3D11_USAGE_DEFAULT; // 0(GPUからRead,Write) 1(GPUからRead) 2(CPUからWrite,GPUからRead) 3(CPUからRead,Write)
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;//D3D11_CPU_ACCESS_READ これ系らしい
    descDepth.MiscFlags = 0;// 特殊な設定
    hr = g_pd3dDevice->CreateTexture2D(&descDepth, NULL, &g_pDepthStencil);
    if (FAILED(hr))
        return hr;

    // Create the depth stencil view
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    // *---* 基本この形 *---*//
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D; // テクスチャ設定 これしか使わない
    descDSV.Texture2D.MipSlice = 0;// 一つもいらない
    //*---*             *---*//
    hr = g_pd3dDevice->CreateDepthStencilView(g_pDepthStencil, &descDSV, &g_pDepthStencilView);
    if (FAILED(hr))
        return hr;
    /*MRTの設定もできる*/
    g_pImmediateContext->OMSetRenderTargets(1, &g_pRenderTargetView, g_pDepthStencilView);// バックバッファとZバッファをレンダリングターゲットを設定

    // レンダリングターゲットのどこに絵を書くのか
    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    g_pImmediateContext->RSSetViewports(1, &vp);


    // Create rasterizer state
    D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
    rd.FillMode = D3D11_FILL_SOLID;// 塗るつぶしのモード
    rd.CullMode = D3D11_CULL_BACK;//(CCW)// 描画するポリゴン裏
    rd.DepthClipEnable = TRUE;
    rd.MultisampleEnable = FALSE;// マルチサンプリングの配慮(1ドットの線など)をするかどうか
    g_pd3dDevice->CreateRasterizerState(&rd, &g_pRasterState);
    g_pImmediateContext->RSSetState(g_pRasterState);// レンダリングステートのセット

    // Create depth stencil state
    D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
    ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
    depthStencilDesc.DepthEnable = TRUE;// 震度を有効にするか DepthWriteMaskで設定できるからTRUEから変える理由がない
    depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;// 0(Z(depth)Test OFF 後に書いたほうで上書き) 1(Z(depth)Test ON 手前)
    depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;// <  特殊なことをしなければこのまま　小さければ勝つ
    depthStencilDesc.StencilEnable = FALSE;
    g_pd3dDevice->CreateDepthStencilState(&depthStencilDesc, &g_pDepthStencilState);
    g_pImmediateContext->OMSetDepthStencilState(g_pDepthStencilState, NULL);

    // Compile the vertex shader
    ID3DBlob* pVSBlob = NULL;// バイナリラージオブジェクト
    hr = CompileShaderFromFile(L"Tutorial07.fx", "VS", "vs_4_0", &pVSBlob);
    if (FAILED(hr))
    {
        MessageBox(NULL,
            "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        return hr;
    }

    // Create the vertex shader
    hr = g_pd3dDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &g_pVertexShader);
    if (FAILED(hr))
    {
        pVSBlob->Release();
        return hr;
    }

    //--* 頂点の情報のレイアウトをシェーダーに教えてる *--//
    // Define the input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
    UINT numElements = ARRAYSIZE(layout);

    // Create the input layout
    hr = g_pd3dDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(), &g_pVertexLayout);
    pVSBlob->Release();
    if (FAILED(hr))
        return hr;

    // Set the input layout
    g_pImmediateContext->IASetInputLayout(g_pVertexLayout);
    //--*                                              *--//

    // Compile the pixel shader
    ID3DBlob* pPSBlob = NULL;
    hr = CompileShaderFromFile(L"Tutorial07.fx", "PS", "ps_4_0", &pPSBlob);
    if (FAILED(hr))
    {
        MessageBox(NULL,
            "The FX file cannot be compiled.  Please run this executable from the directory that contains the FX file.", "Error", MB_OK);
        return hr;
    }

    // Create the pixel shader
    hr = g_pd3dDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &g_pPixelShader);
    pPSBlob->Release();
    if (FAILED(hr))
        return hr;

    // ポリゴンの頂点を設定
    // Create vertex buffer
    SimpleVertex vertices[] =
    {
        { XMFLOAT3(0.0f,  0.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
        { XMFLOAT3(34.0f,  0.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(0.0f, 64.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },


        { XMFLOAT3(34.0f,  0.0f, 0.0f),  XMFLOAT2(1.0f, 0.0f) },
        { XMFLOAT3(34.0f, 64.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
        { XMFLOAT3(0.0f, 64.0f, 0.0f),  XMFLOAT2(0.0f, 1.0f) },
    };

    // 画像描画の設定
    {
        D3D11_BUFFER_DESC bd;
        ZeroMemory(&bd, sizeof(bd));
        bd.Usage = D3D11_USAGE_DYNAMIC; // 頂点バッファのアクセス方法設定　デフォルトだとGPUに任せるため触れない?
        bd.ByteWidth = sizeof(SimpleVertex) * 6;//どのくらいある　頂点の数
        bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // CPUから書き込みを許可する  デフォルト0
        D3D11_SUBRESOURCE_DATA InitData;
        ZeroMemory(&InitData, sizeof(InitData));
        InitData.pSysMem = vertices;
        // 頂点バッファを作ってとお願いしている
        hr = g_pd3dDevice->CreateBuffer(&bd, &InitData, &g_pVertexBuffer);
        if (FAILED(hr))
            return hr;

        // Set vertex buffer
        UINT stride = sizeof(SimpleVertex); // データ1つの大きさ
        UINT offset = 0;
        // 頂点バッファを指定
        g_pImmediateContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

        // Set primitive topology
        // 頂点の組み合わせ方
        g_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        // ByteWidthぐらいしかいじらない
        {
            // Create the constant buffers
            bd.Usage = D3D11_USAGE_DEFAULT;
            bd.ByteWidth = sizeof(CBNeverChanges);
            bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
            bd.CPUAccessFlags = 0;
            hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBNeverChanges);
            if (FAILED(hr))
                return hr;

            bd.ByteWidth = sizeof(CBChangeOnResize);
            hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBChangeOnResize);
            if (FAILED(hr))
                return hr;

            bd.ByteWidth = sizeof(CBChangesEveryFrame);
            hr = g_pd3dDevice->CreateBuffer(&bd, NULL, &g_pCBChangesEveryFrame);
            if (FAILED(hr))
                return hr;
        }
    }

    // Load the Texture
//    TexMetadata metadata;
    ScratchImage image;

    // ウィンドウズイメージコンポーネント
    /*hr = LoadFromWICFile(L"Resource/pipo-charachip001.png", WIC_FLAGS_NONE, &metadata, image);
    if (FAILED(hr))
        return hr;

    //プレイヤーテクスチャの作成
    hr = CreateShaderResourceView(
        g_pd3dDevice,
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        &g_pTextureRV);
        */
/*
    hr = LoadFromWICFile(L"Resource/Astro_Bot_Logo.png", WIC_FLAGS_NONE, &metadata, image);
    if (FAILED(hr))
        return hr;

    //アストロロボットの背景テクスチャの作成
    hr = CreateShaderResourceView(
        g_pd3dDevice,
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        &g_pBGTextureRV);

    hr = LoadFromWICFile(L"Resource/mapchip.png", WIC_FLAGS_NONE, &metadata, image);
    if (FAILED(hr))
        return hr;

    //マップテクスチャの作成
    hr = CreateShaderResourceView(
        g_pd3dDevice,
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        &g_pMapchipRV);

    hr = LoadFromWICFile(L"Resource/pipo-charachip010.png", WIC_FLAGS_NONE, &metadata, image);
    if (FAILED(hr))
        return hr;

    //猫テクスチャの作成
    hr = CreateShaderResourceView(
        g_pd3dDevice,
        image.GetImages(),
        image.GetImageCount(),
        metadata,
        &g_pCatRV);*/



    // Create the sample state
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory( &sampDesc, sizeof(sampDesc) );
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;// フィルタ POINT(指定色持ってくる)   LINEAR(ぼやける 周りから色を持ってくる) ANISOTROPIC(3D用 異方性フィルタ)斜めの調整みたいな感じ(昔は重かったから使うところを考えられたらしい)
    // 0.0 1.0 から外れた時の設定 //
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;//RAP(繰り返し) MIRROR(鏡面繰り返し)　CLAMP(画像の端を繰り返す)　BORDER(こちらで指定)　MIRROR_ONCE(一回だけ反転して取る 対応してないのがある)
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    //                            //
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
/*    sampDesc.BorderColor[0] = 0.0f;
    sampDesc.BorderColor[1] = 0.0f;
    sampDesc.BorderColor[2] = 1.0f;
    sampDesc.BorderColor[3] = 1.0f;*/
    hr = g_pd3dDevice->CreateSamplerState( &sampDesc, &g_pSamplerLinear );
    if( FAILED( hr ) )
        return hr;

    D3D11_BLEND_DESC blendDesc;
    ZeroMemory(&blendDesc, sizeof(blendDesc));
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.IndependentBlendEnable = FALSE;
    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    // アルファブレンド
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;// どれくらい裏に色を使っているか　// 上か下の話もしくは両方かも
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;

    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO; 
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;

    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
    float blendFacter[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    // ブレンド
    hr = g_pd3dDevice->CreateBlendState(&blendDesc, &g_pBlendState);
    if (FAILED(hr))
        return hr;

    //加算合成
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    hr = g_pd3dDevice->CreateBlendState(&blendDesc, &g_pBlendStateAdd);
    if (FAILED(hr))
        return hr;

    // 減算合成
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_SUBTRACT;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    hr = g_pd3dDevice->CreateBlendState(&blendDesc, &g_pBlendStateSub);
    if (FAILED(hr))
        return hr;

    g_pImmediateContext->OMSetBlendState(g_pBlendState, blendFacter, 0xFFFFFFFF);

    // Initialize the world matrices
    // 初期化 単位行列　行列の1
    g_World = XMMatrixIdentity();

    // Initialize the view matrix
    // 初期化
    g_View = XMMatrixIdentity();

    CBNeverChanges cbNeverChanges;
    // 切り替え　行優先とか ?
    cbNeverChanges.mView = XMMatrixTranspose( g_View );
    g_pImmediateContext->UpdateSubresource( g_pCBNeverChanges, 0, NULL, &cbNeverChanges, 0, 0 );

    // Initialize the projection matrix
    // 平行投影
    g_Projection = XMMatrixOrthographicOffCenterLH(0.0f, (float)width, (float)height, 0.0f, 0.0f, 1.0f);
    
    CBChangeOnResize cbChangesOnResize;
    cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );
    g_pImmediateContext->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );

    Master::mpResourceManager->SetResourceDatas(g_pd3dDevice, g_pImmediateContext, g_pVertexBuffer, g_pVertexShader, g_pCBNeverChanges, g_pCBChangeOnResize, g_pCBChangesEveryFrame, g_pPixelShader, g_pSamplerLinear, g_pRenderTargetView, g_pDepthStencilView, g_pSwapChain, g_hWnd);
    //testNumber[0] = Master::mpResourceManager->AddResource(L"Resource/pipo-charachip001.png");
    //testNumber[1] = Master::mpResourceManager->AddResource(L"Resource/Astro_Bot_Logo.png");
    //testNumber[2] = Master::mpResourceManager->AddResource(L"Resource/mapchip.png");
    //testNumber[3] = Master::mpResourceManager->AddResource(L"Resource/pipo-charachip010.png");
    return S_OK;
}


//--------------------------------------------------------------------------------------
// Clean up the objects we've created
//--------------------------------------------------------------------------------------
void CleanupDevice()
{
    Master::AllDelete();

    if( g_pImmediateContext ) g_pImmediateContext->ClearState();
    if(g_pBlendState) g_pBlendState->Release();
    if(g_pBlendStateAdd) g_pBlendStateAdd->Release();
    if(g_pBlendStateSub) g_pBlendStateSub->Release();
    if (g_pRasterState) g_pRasterState->Release();
    if (g_pDepthStencilState) g_pDepthStencilState->Release();
    if( g_pSamplerLinear ) g_pSamplerLinear->Release();
    //if( g_pTextureRV ) g_pTextureRV->Release();
    //if (g_pBGTextureRV) g_pBGTextureRV->Release();
    //if (g_pMapchipRV) g_pMapchipRV->Release();
    //if (g_pCatRV) g_pCatRV->Release();
    if( g_pCBNeverChanges ) g_pCBNeverChanges->Release();
    if( g_pCBChangeOnResize ) g_pCBChangeOnResize->Release();
    if( g_pCBChangesEveryFrame ) g_pCBChangesEveryFrame->Release();
    if( g_pVertexBuffer ) g_pVertexBuffer->Release();
    if( g_pVertexLayout ) g_pVertexLayout->Release();
    if( g_pVertexShader ) g_pVertexShader->Release();
    if( g_pPixelShader ) g_pPixelShader->Release();
    if( g_pDepthStencil ) g_pDepthStencil->Release();
    if( g_pDepthStencilView ) g_pDepthStencilView->Release();
    if( g_pRenderTargetView ) g_pRenderTargetView->Release();
    if( g_pSwapChain ) g_pSwapChain->Release();
    if( g_pImmediateContext ) g_pImmediateContext->Release();
    if( g_pd3dDevice ) g_pd3dDevice->Release();
}


//--------------------------------------------------------------------------------------
// Called every time the application receives a message
//--------------------------------------------------------------------------------------
// 複数のウィンドウ
LRESULT CALLBACK WndProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
{
    // CPUに絵を書かせるときに使う
    PAINTSTRUCT ps;
    HDC hdc;

    switch( message )
    {
        case WM_PAINT:
            // 描画
            hdc = BeginPaint( hWnd, &ps );
            EndPaint( hWnd, &ps );
            break;
        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            return DefWindowProc( hWnd, message, wParam, lParam );
    }

    return 0;
}


//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    Camera* setCamera = Master::mpGameManager->GetCamera();
//    if ((Master::mpKeyState->GetNowKeyFlags(KEY_PLAYER_NUMBER::PLAYER_1) & (KeyState::FlagPos(KEY_TYPE::B) | KeyState::FlagPos(KEY_TYPE::X) | KeyState::FlagPos(KEY_TYPE::A) | KeyState::FlagPos(KEY_TYPE::Y))) != 0)
//    {
//        VECTOR_2D setPos = VECTOR_2D::Zero();
//        if (Master::mpKeyState->GetKey(KEY_TYPE::B, KEY_PLAYER_NUMBER::PLAYER_1))
//        {
//            setPos.X += 0.05f;
//        }
//        if (Master::mpKeyState->GetKey(KEY_TYPE::X, KEY_PLAYER_NUMBER::PLAYER_1))
//        {
//            setPos.X -= 0.05f;
//        }
//        if (Master::mpKeyState->GetKey(KEY_TYPE::A, KEY_PLAYER_NUMBER::PLAYER_1))
//        {
//            setPos.Y += 0.05f;
//        }
//        if (Master::mpKeyState->GetKey(KEY_TYPE::Y, KEY_PLAYER_NUMBER::PLAYER_1))
//        {
//            setPos.Y -= 0.05f;
//        }
//        setCamera->SetCameraTargetPos(setCamera->GetCameraPos() + setPos);
//    }
//
    if ((Master::mpKeyState->GetNowKeyFlags_Controller(CONTROLLER_KEY_NUMBER::CONTROLLER_1) & (KeyState::FlagPos_Controller(CONTROLLER_KEY_TYPE::R) | KeyState::FlagPos_Controller(CONTROLLER_KEY_TYPE::RT) | KeyState::FlagPos_Controller(CONTROLLER_KEY_TYPE::L) | KeyState::FlagPos_Controller(CONTROLLER_KEY_TYPE::LT))) != 0)
    {
        VECTOR_2D setSize = VECTOR_2D::Zero();
        if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::RT, CONTROLLER_KEY_NUMBER::CONTROLLER_1))
        {
            setSize.X += 0.01f;
        }
        if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::R, CONTROLLER_KEY_NUMBER::CONTROLLER_1))
        {
            setSize.Y += 0.01f;
        }
        if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::LT, CONTROLLER_KEY_NUMBER::CONTROLLER_1))
        {
            setSize.X -= 0.01f;
        }
        if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::L, CONTROLLER_KEY_NUMBER::CONTROLLER_1))
        {
            setSize.Y -= 0.01f;
        }
        setCamera->SetCameraTargetSize(setCamera->GetCameraSize() + setSize);
    }
//    /*
//    g_pImmediateContext->VSSetShader(g_pVertexShader, NULL, 0);
//    //                                       /*スロット番号が決まっている 一つ目
//    g_pImmediateContext->VSSetConstantBuffers(0, 1, &g_pCBNeverChanges);
//    g_pImmediateContext->VSSetConstantBuffers(1, 1, &g_pCBChangeOnResize);
//    g_pImmediateContext->VSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
//    g_pImmediateContext->PSSetShader(g_pPixelShader, NULL, 0);
//    // シェーダーごとに決めてる?  
//    g_pImmediateContext->PSSetConstantBuffers(2, 1, &g_pCBChangesEveryFrame);
//    //    g_pImmediateContext->PSSetShaderResources(0, 1, &g_pBGTextureRV);
//        // テクセル
//    g_pImmediateContext->PSSetSamplers(0, 1, &g_pSamplerLinear);
//
//    // Rotate cube around the origin 回転するやつが元はあった
//    // 初期値を入れてる
//    g_World = XMMatrixIdentity();
//    //
//    // Clear the back buffer
//    //
//    // 背景色
//    float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // red, green, blue, alpha
//    g_pImmediateContext->ClearRenderTargetView(g_pRenderTargetView, ClearColor);
//
//    //
//    // Clear the depth buffer to 1.0 (max depth)
//    //
//    g_pImmediateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
//
//    // コンスタントバッファの更新　回転が入っていた
//    CBChangesEveryFrame cb;
//    cb.mWorld = XMMatrixTranspose(g_World);
//    g_pImmediateContext->UpdateSubresource(g_pCBChangesEveryFrame, 0, NULL, &cb, 0, 0);*/
//
//    /*
//    // 絵の操作1
//
//        // マップのサブリソース
//        D3D11_MAPPED_SUBRESOURCE ms;
//        g_pImmediateContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
//
//        SimpleVertex* pVertex = (SimpleVertex*)ms.pData;
//
//        // 左上
//        (pVertex)->Pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
//        (pVertex)->Tex = XMFLOAT2(0.0f, 0.0f);
//
//        // 右上
//        (pVertex + 1)->Pos = XMFLOAT3(1280.0f, 0.0f, 0.0f);
//        (pVertex + 1)->Tex = XMFLOAT2(1.0f, 0.0f);
//
//        // 左下
//        (pVertex + 2)->Pos = XMFLOAT3(0.0f, 720.0f, 0.0f);
//        (pVertex + 2)->Tex = XMFLOAT2(0.0f, 1.0f);
//
//        // 右上
//        (pVertex + 3)->Pos = XMFLOAT3(1280.0f, 0.0f, 0.0f);
//        (pVertex + 3)->Tex = XMFLOAT2(1.0f, 0.0f);
//
//        // 右下
//        (pVertex + 4)->Pos = XMFLOAT3(1280.0f, 720.0f, 0.0f);
//        (pVertex + 4)->Tex = XMFLOAT2(1.0f, 1.0f);
//
//        // 左下
//        (pVertex + 5)->Pos = XMFLOAT3(0.0f, 720.0f, 0.0f);
//        (pVertex + 5)->Tex = XMFLOAT2(0.0f, 1.0f);
//
//        g_pImmediateContext->Unmap(g_pVertexBuffer, 0);
//
//
//    //
//    // Update variables that change once per frame
//    //
//
//    //
//    // Render the Polygons
//    //
//    g_pImmediateContext->Draw(6, 0);*/
//
//    /* g_pImmediateContext->PSSetShaderResources(0, 1, &g_pTextureRV);
//     // 絵の操作2
//
//         // マップのサブリソース
//         ZeroMemory(&ms, sizeof(ms));
//         g_pImmediateContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
//
//         pVertex = (SimpleVertex*)ms.pData;
//
//         // 左上
//         (pVertex)->Pos = XMFLOAT3(0.0f + 640.0f, 0.0f + 360.0f, 0.0f);
//         (pVertex)->Tex = XMFLOAT2(0.0f, 0.0f);
//
//         // 右上
//         (pVertex + 1)->Pos = XMFLOAT3(32.0f + 640.0f, 0.0f + 360.0f, 0.0f);
//         (pVertex + 1)->Tex = XMFLOAT2(1.0f, 0.0f);
//
//         // 左下
//         (pVertex + 2)->Pos = XMFLOAT3(0.0f + 640.0f, 64.0f + 360.0f, 0.0f);
//         (pVertex + 2)->Tex = XMFLOAT2(0.0f, 1.0f);
//
//         // 右上
//         (pVertex + 3)->Pos = XMFLOAT3(32.0f + 640.0f, 0.0f + 360.0f, 0.0f);
//         (pVertex + 3)->Tex = XMFLOAT2(1.0f, 0.0f);
//
//         // 右下
//         (pVertex + 4)->Pos = XMFLOAT3(32.0f + 640.0f, 64.0f + 360.0f, 0.0f);
//         (pVertex + 4)->Tex = XMFLOAT2(1.0f, 1.0f);
//
//         // 左下
//         (pVertex + 5)->Pos = XMFLOAT3(0.0f + 640.0f, 64.0f + 360.0f, 0.0f);
//         (pVertex + 5)->Tex = XMFLOAT2(0.0f, 1.0f);
//
//         g_pImmediateContext->Unmap(g_pVertexBuffer, 0);
//
//         //g_pImmediateContext->Map(g_pVertexBufferTest, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);
//         //
//         //// 左上
//         //(pVertex)->Pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
//         //(pVertex)->Tex = XMFLOAT2(0.0f, 0.0f);
//
//         //// 右上
//         //(pVertex + 1)->Pos = XMFLOAT3(1280.0f, 0.0f, 0.0f);
//         //(pVertex + 1)->Tex = XMFLOAT2(1.0f, 0.0f);
//
//         //// 左下
//         //(pVertex + 2)->Pos = XMFLOAT3(0.0f, 720.0f, 0.0f);
//         //(pVertex + 2)->Tex = XMFLOAT2(0.0f, 1.0f);
//
//         //// 右上
//         //(pVertex + 3)->Pos = XMFLOAT3(1280.0f, 0.0f, 0.0f);
//         //(pVertex + 3)->Tex = XMFLOAT2(1.0f, 0.0f);
//
//         //// 右下
//         //(pVertex + 4)->Pos = XMFLOAT3(1280.0f, 720.0f, 0.0f);
//         //(pVertex + 4)->Tex = XMFLOAT2(1.0f, 1.0f);
//
//         //// 左下
//         //(pVertex + 5)->Pos = XMFLOAT3(0.0f, 720.0f, 0.0f);
//         //(pVertex + 5)->Tex = XMFLOAT2(0.0f, 1.0f);
//
//         ////g_pImmediateContext->Unmap(g_pVertexBuffer, 0);
//
//     //
//     // Render the Polygons
//     //
//     g_pImmediateContext->Draw(6, 0);*/
//
//
//     //DrawSprite(0.0f, 0.0f, 1280.0f, 720.0f, 0.2f, 0.8f, 0.2f, 0.8f, g_pBGTextureRV);
//
//    if (false)
//    {
//        XMUINT2 setNumber = XMUINT2(7, 0);
//        SetDrawMap(XMFLOAT2(32.0f, 32.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1280.0f, 720.0f), XMFLOAT2(((0.125f/*1.0f / 8.0f*/) * setNumber.x) + 0.00f, ((0.125f/*1.0f / 8.0f*/) * setNumber.y) + 0.00f), XMFLOAT2((0.125f/*1.0f / 8.0f*/) * (setNumber.x + 1), (0.125f/*1.0f / 8.0f*/) * (setNumber.y + 1)), testNumber[2], PLUS_POS_FLAG);
//        setNumber = XMUINT2(4, 0);
//        SetDrawMap(XMFLOAT2(32.0f, 32.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1280.0f, 1.0f), XMFLOAT2(((0.125f/*1.0f / 8.0f*/) * setNumber.x) + 0.00f, ((0.125f/*1.0f / 8.0f*/) * setNumber.y) + 0.00f), XMFLOAT2((0.125f/*1.0f / 8.0f*/) * (setNumber.x + 1), (0.125f/*1.0f / 8.0f*/) * (setNumber.y + 1)), testNumber[2], PLUS_POS_FLAG);
//        
//        //SetDrawMap(XMFLOAT2(32.0f, 32.0f), XMFLOAT2(10.0f, 20.0f), XMFLOAT2(156.0f, 79.0f), XMFLOAT2(((0.125f/*1.0f / 8.0f*/) * 0.0f), ((0.125f/*1.0f / 8.0f*/) * 0.0f) + 0.002f), XMFLOAT2((0.125f/*1.0f / 8.0f*/) * 1.0f, (0.125f/*1.0f / 8.0f*/) * 1.0f), Master::mpResourceManager->GetResourceView(testNumber[2]), PLUS_POS_FLAG);
//        //SetDrawMap(XMFLOAT2(32.0f, 32.0f), XMFLOAT2(10.0f, 20.0f), XMFLOAT2(156.0f, 79.0f), XMFLOAT2(((0.125f/*1.0f / 8.0f*/) * 0.0f), ((0.125f/*1.0f / 8.0f*/) * 0.0f) + 0.002f), XMFLOAT2((0.125f/*1.0f / 8.0f*/) * 1.0f, (0.125f/*1.0f / 8.0f*/) * 1.0f), Master::mpResourceManager->GetResourceView(testNumber[2]), PLUS_POS_FLAG);
////        SetDrawMap(XMFLOAT2(32.0f, 32.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1280.0f, 720.0f), XMFLOAT2(((0.125f/*1.0f / 8.0f*/) * 0.0f), ((0.125f/*1.0f / 8.0f*/) * 0.0f) + 0.002f), XMFLOAT2((0.125f/*1.0f / 8.0f*/) * 1.0f, (0.125f/*1.0f / 8.0f*/) * 1.0f), Master::mpResourceManager->GetResourceView(testNumber[2]), 0);
//        //SetDrawMap(XMFLOAT2(5.0f, 5.0f), XMFLOAT2(0.0f, 0.0f), XMFLOAT2(1280.0f, 720.0f), XMFLOAT2((1.0f / 8.0f) * 0.0f, (1.0f / 8.0f) * 0.0f), XMFLOAT2((1.0f / 8.0f) * 1.0f, (1.0f / 8.0f) * 1.0f), Master::mpResourceManager->GetResourceView(testNumber[2]), ULTRAVIOLET_PLUS_FLAG);
////        g_DrawMoveSpeed.x += 0.00001f;
////        g_DrawMoveSpeed.y += 0.00001f;
//    }
//    else
//    {/*
//        for (int y = 0; y < 12; y++)
//        {
//            for (int x = 0; x < 20; x++)
//            {
//                switch (g_MapData[y][x])
//                {
//                case 0:
//                    Master::mpResourceManager->DrawSprite(32.0f + (x * 64.0f), 32.0f + (y * 64.0f), 64.0f, 64.0f, 0.125f * 0, 0.125f, 0.0f, 0.125f, testNumber[2], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//                    break;
//
//                case 1:
//                    Master::mpResourceManager->DrawSprite(32.0f + (x * 64.0f), 32.0f + (y * 64.0f), 64.0f, 64.0f, 0.125f * 7, 0.125f, 0.0f, 0.125f, testNumber[2], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//                    break;
//
//                case 2:
//                    Master::mpResourceManager->DrawSprite(32.0f + (x * 64.0f), 32.0f + (y * 64.0f), 64.0f, 64.0f, 0.125f * 6, 0.125f, 0.0f, 0.125f, testNumber[2], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//                    break;
//
//                case 3:
//                    Master::mpResourceManager->DrawSprite(32.0f + (x * 64.0f), 32.0f + (y * 64.0f), 64.0f, 64.0f, 0.125f * 5, 0.125f, 0.0f, 0.125f, testNumber[2], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//                    break;
//                }
//            }
//        }
//
//        for (int y = 0; y < 12; y++)
//        {
//            for (int x = 0; x < 20; x++)
//            {
//                switch (g_MapDataObj[y][x])
//                {
//                case 1:
//                    Master::mpResourceManager->DrawSprite(32.0f + (x * 64.0f), 32.0f + (y * 64.0f), 64.0f, 64.0f, 0.125f * 4, 0.125f, 0.125f * 6, 0.125f, testNumber[2], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//                    break;
//
//                case 2:
//                    Master::mpResourceManager->DrawSprite(32.0f + (x * 64.0f), 32.0f + (y * 64.0f), 64.0f, 64.0f, 0.125f * 2, 0.125f, 0.125f * 5, 0.125f, testNumber[2], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//                    break;
//                }
//            }
//        }*/
//    }
//
//    Master::mpResourceManager->DrawSprite(32.0f, 32.0f, 64.0f, 64.0f, 0.625f, 0.125f, 0.625f, 0.125f, testNumber[2], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//
//    PlayersMove();
//
//    for (int i = 0; i < PLAYER_NUMBER; i++)
//    {
//        if (g_Players[i].LiveFlag)
//        {
//            switch (g_Players[i].characterType)
//            {
//            case 0:
//                Master::mpResourceManager->DrawSprite(g_Players[i].pos.x, g_Players[i].pos.y, 32.0f, 64.0f, 0.0f, 1.0f, 0.0f, 1.0f, testNumber[0], MIDDLE_FLAG);
//                break;
//
//            case 1:
//            {
//                int setNumber = -1;
//                if (g_Players[i].dir.x < 0.0f)
//                {
//                    setNumber = 1;
//                }
//                else if (g_Players[i].dir.x > 0.0f)
//                {
//                    setNumber = 2;
//                }
//                else if (g_Players[i].dir.y > 0.0f)
//                {
//                    setNumber = 0;
//                }
//                else if (g_Players[i].dir.y < 0.0f)
//                {
//                    setNumber = 3;
//                }
//
//                if (setNumber != -1)
//                {
//                    if (g_Players[i].vecAnimeNumber == setNumber)
//                    {
//                        g_Players[i].moveAnimeNumber += g_Players[i].moveAnimePlusNumber;
//                        if ((g_Players[i].moveAnimeNumber >= PLAYER_DRAW_MOVE_SPEED) || (g_Players[i].moveAnimeNumber <= 0))
//                        {
//                            g_Players[i].moveAnimePlusNumber *= -1;
//                            g_Players[i].moveAnimeNumber += g_Players[i].moveAnimePlusNumber * (PLAYER_DRAW_MOVE_SPEED / 3);
//                        }
//                    }
//                    else
//                    {
//                        g_Players[i].moveAnimeNumber = 0;
//                        g_Players[i].moveAnimePlusNumber = 1;
//                        g_Players[i].vecAnimeNumber = setNumber;
//                    }
//                }
//                else
//                {
//                    g_Players[i].moveAnimeNumber = (PLAYER_DRAW_MOVE_SPEED / 3);
//                    g_Players[i].moveAnimePlusNumber = 1;
//                }
//
//                Master::mpResourceManager->DrawSprite(g_Players[i].pos.x, g_Players[i].pos.y, 64.0f, 64.0f, (int)((float)g_Players[i].moveAnimeNumber * (3.0f / (float)PLAYER_DRAW_MOVE_SPEED)) * 0.33333f, 0.33333f,
//                    0.25f * g_Players[i].vecAnimeNumber, 0.25f,
//                    testNumber[0], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//            }
//            break;
//            }
//
//            if (HitCheckBC(g_Players[i].pos, g_Players[i].size, g_Cat.pos, g_Cat.size))
//            {
//                g_Cat.LiveFlag = false;
//            }
//        }
//    }
//
//    if (g_Cat.LiveFlag)
//    {
//        switch (g_Cat.characterType)
//        {
//        case 0:
//            Master::mpResourceManager->DrawSprite(g_Cat.pos.x, g_Cat.pos.y, 64.0f, 64.0f, (int)((float)g_Cat.moveAnimeNumber * (3.0f / (float)PLAYER_DRAW_MOVE_SPEED)) * 0.33333f, 0.33333f, 0.0f, 0.25f, testNumber[3], MIDDLE_FLAG | ULTRAVIOLET_PLUS_FLAG);
//            break;
//        }
//    }
    //
    // Present our back buffer to our front buffer
    //
    // 裏と表を切り替える プレゼント(読み)　ウィンドモードだと切り替えられないから仮想に保存後切り替える(多分)
    //g_pSwapChain->Present(0, 0);
}
// 1280, 720
/*
void DrawSprite(float x, float y, float width, float height, float left, float right, float up, float down, ID3D11ShaderResourceView* resourceView, ID3D11DeviceContext* immediateContext, ID3D11Buffer* vertexBuffer, int intFlag)
{
    immediateContext->PSSetShaderResources(0, 1, &resourceView);

    // 描画一
    // 位置操作
    {
        // マップのサブリソース
        D3D11_MAPPED_SUBRESOURCE ms;
        immediateContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

        SimpleVertex* pVertex = (SimpleVertex*)ms.pData;

        if ((intFlag & MIDDLE_FLAG) != 0)
        {
            x -= width / 2.0f;
            y -= height / 2.0f;
        }

        if ((intFlag & ULTRAVIOLET_PLUS_FLAG) != 0)
        {
            down += up;
            right += left;
        }

        // 左上
        (pVertex)->Pos = XMFLOAT3(0.0f + x, 0.0f + y, 0.0f);
        (pVertex)->Tex = XMFLOAT2(left, up);

        // 右上
        (pVertex + 1)->Pos = XMFLOAT3(width + x, 0.0f + y, 0.0f);
        (pVertex + 1)->Tex = XMFLOAT2(right, up);

        // 左下
        (pVertex + 2)->Pos = XMFLOAT3(0.0f + x, height + y, 0.0f);
        (pVertex + 2)->Tex = XMFLOAT2(left, down);

        // 右上
        (pVertex + 3)->Pos = XMFLOAT3(width + x, 0.0f + y, 0.0f);
        (pVertex + 3)->Tex = XMFLOAT2(right, up);

        // 右下
        (pVertex + 4)->Pos = XMFLOAT3(width + x, height + y, 0.0f);
        (pVertex + 4)->Tex = XMFLOAT2(right, down);

        // 左下
        (pVertex + 5)->Pos = XMFLOAT3(0.0f + x, height + y, 0.0f);
        (pVertex + 5)->Tex = XMFLOAT2(left, down);

        immediateContext->Unmap(vertexBuffer, 0);
    }

    immediateContext->Draw(6, 0);
}*/

void InitGame()
{
    srand((unsigned int)time(NULL));
    int type = 0;

    switch (type)
    {
    case 0:
        for (int i = 0; i < PLAYER_NUMBER; i++)
        {
            SetPlayer(&g_Players[i], XMFLOAT2(640.0f, 360.0f), XMFLOAT2((500.0f / ((rand() % 500) - 250.0f)) * 0.1f, (500.0f / ((rand() % 500) - 250.0f)) * 0.1f), 20.0f, 1, 32.0f);
        }
        g_DrawMoveSpeed.x = 0.0f;
        g_DrawMoveSpeed.y = 0.0f;
        break;
    }

    g_Cat.characterType = 0;
    g_Cat.pos = XMFLOAT2(60.0f, 60.0f);
    g_Cat.moveAnimeNumber = 0;
    g_Cat.size = 32.0f;
    g_Cat.LiveFlag = true;

    g_MapHitObjectPoss.clear();/*
    for (int y = 0; y < 12; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            if (g_MapData[y][x] == 3)
            {
                g_MapHitObjectPoss.push_back(XMUINT2(x, y));
            }
        }
    }
    */
}

void SetPlayer(Player* playerData, XMFLOAT2 pos, XMFLOAT2 dir, float speed, int type, float size)
{
    playerData->pos = pos;
    if ((dir.x == 0.0f) && (dir.y == 0.0f))
    {
        dir = XMFLOAT2(1.0f, 1.0f);
    }
    playerData->dir = dir;
    SetDirNormalize(&playerData->dir);

    playerData->speed = speed;
    playerData->characterType = type;
    playerData->vecAnimeNumber = 0;
    playerData->moveAnimeNumber = 0;
    playerData->moveAnimePlusNumber = 1;
    
    playerData->size = size;

    playerData->LiveFlag = true;
}

void SetDirNormalize(XMFLOAT2* dir)
{
    XMFLOAT2 setDir = *dir;
    float length = sqrtf((dir->x * dir->x) + (dir->y * dir->y));
    *dir = XMFLOAT2(setDir.x / length, setDir.y / length);
}

void PlayersMove()
{
    for (int i = 0; i < PLAYER_NUMBER; i++)
    {
        bool xHitFlag = false;
        switch (g_Players[i].characterType)
        {
        case 0:
            g_Players[i].pos.x += (g_Players[i].dir.x * g_Players[i].speed);
            g_Players[i].pos.y += (g_Players[i].dir.y * g_Players[i].speed);

            if ((0.0f + (PLAYER_SIZE.x / 2)) > g_Players[i].pos.x)
            {
                g_Players[i].dir.x = (1 * std::abs(g_Players[i].dir.x));
            }
            else if (g_Players[i].pos.x > 1280.0f - (PLAYER_SIZE.x / 2))
            {
                g_Players[i].dir.x = (-1 * std::abs(g_Players[i].dir.x));
            }

            if (0.0f + (PLAYER_SIZE.y / 2) > g_Players[i].pos.y)
            {
                g_Players[i].dir.y = (1 * std::abs(g_Players[i].dir.y));
            }
            else if (g_Players[i].pos.y > 720.0f - (PLAYER_SIZE.y / 2))
            {
                g_Players[i].dir.y = (-1 * std::abs(g_Players[i].dir.y));
            }
            break;

        case 1:
            g_Players[i].dir = XMFLOAT2(0.0f, 0.0f);

            if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::RIGHT, CONTROLLER_KEY_NUMBER::CONTROLLER_1))//(getKey['D'] & 0x80) || (GetAsyncKeyState(VK_RIGHT) & 0x8000))
            {
                g_Players[i].pos.x += g_Players[i].speed;
                g_Players[i].dir.x += g_Players[i].speed;
            }
            if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::LEFT, CONTROLLER_KEY_NUMBER::CONTROLLER_1))//(getKey['A'] & 0x80) || (GetAsyncKeyState(VK_LEFT) & 0x8000))
            {
                g_Players[i].pos.x -= g_Players[i].speed;
                g_Players[i].dir.x -= g_Players[i].speed;
            }
            if (g_Players[i].dir.x != 0.0f)
            {
                for (int j = 0; j < g_MapHitObjectPoss.size(); j++)
                {
                    if (HitCheckBB(g_Players[i].pos, g_Players[i].size, XMFLOAT2(32.0f + (g_MapHitObjectPoss[j].x * 64.0f), 32.0f + (g_MapHitObjectPoss[j].y * 64.0f)), 32.0f))
                    {
                        if (g_Players[i].dir.x < 0.0f)
                        {
                            g_Players[i].pos.x = (32.0f + (g_MapHitObjectPoss[j].x * 64.0f)) + 32.0f + g_Players[i].size;
                        }
                        else if (g_Players[i].dir.x > 0.0f)
                        {
                            g_Players[i].pos.x = (32.0f + (g_MapHitObjectPoss[j].x * 64.0f)) - 32.0f - g_Players[i].size;
                        }
                        xHitFlag = true;
                    }
                }
            }

            if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::DOWN, CONTROLLER_KEY_NUMBER::CONTROLLER_1))//(getKey['S'] & 0x80) || (GetAsyncKeyState(VK_DOWN) & 0x8000))
            {
                g_Players[i].pos.y += g_Players[i].speed;
                g_Players[i].dir.y += g_Players[i].speed;
            }
            if (Master::mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::UP, CONTROLLER_KEY_NUMBER::CONTROLLER_1))//(getKey['W'] & 0x80) || (GetAsyncKeyState(VK_UP) & 0x8000))
            {
                g_Players[i].pos.y -= g_Players[i].speed;
                g_Players[i].dir.y -= g_Players[i].speed;
            }
            if (g_Players[i].dir.y != 0.0f)
            {
                for (int j = 0; j < g_MapHitObjectPoss.size(); j++)
                {
                    if (HitCheckBB(g_Players[i].pos, g_Players[i].size, XMFLOAT2(32.0f + (g_MapHitObjectPoss[j].x * 64.0f), 32.0f + (g_MapHitObjectPoss[j].y * 64.0f)), 32.0f))
                    {
                        if (g_Players[i].dir.y > 0.0f)
                        {
                            g_Players[i].pos.y = (32.0f + (g_MapHitObjectPoss[j].y * 64.0f)) - 32.0f - g_Players[i].size;
                            if ((g_Players[i].vecAnimeNumber == 0) || (g_Players[i].dir.x != 0.0f))
                            {
                                g_Players[i].dir.y -= g_Players[i].speed;
                            }
                        }
                        else if (g_Players[i].dir.y < 0.0f)
                        {
                            g_Players[i].pos.y = (32.0f + (g_MapHitObjectPoss[j].y * 64.0f)) + 32.0f + g_Players[i].size;
                            if ((g_Players[i].vecAnimeNumber == 3) || (g_Players[i].dir.x != 0.0f))
                            {
                                g_Players[i].dir.y += g_Players[i].speed;
                            }
                        }
                    }
                }
            }

            if (xHitFlag)
            {
                if (g_Players[i].dir.x < 0.0f)
                {
                    if ((g_Players[i].vecAnimeNumber == 1) || (g_Players[i].dir.y != 0.0f))
                    {
                        g_Players[i].dir.x += g_Players[i].speed;
                    }
                }
                else if (g_Players[i].dir.x > 0.0f)
                {
                    if ((g_Players[i].vecAnimeNumber == 2) || (g_Players[i].dir.y != 0.0f))
                    {
                        g_Players[i].dir.x -= g_Players[i].speed;
                    }
                }
            }


            if ((0.0f + (PLAYER_SIZE.x / 2)) > g_Players[i].pos.x)
            {
                g_Players[i].pos.x = (0.0f + (PLAYER_SIZE.x / 2));
                g_Players[i].dir.x = 0.0f;
            }
            else if (g_Players[i].pos.x > 1280.0f - (PLAYER_SIZE.x / 2))
            {
                g_Players[i].pos.x = 1280.0f - (PLAYER_SIZE.x / 2);
                g_Players[i].dir.x = 0.0f;
            }

            if (0.0f + (PLAYER_SIZE.y / 2) > g_Players[i].pos.y)
            {
                g_Players[i].pos.y = 0.0f + (PLAYER_SIZE.y / 2);
                g_Players[i].dir.y = 0.0f;
            }
            else if (g_Players[i].pos.y > 720.0f - (PLAYER_SIZE.y / 2))
            {
                g_Players[i].pos.y = 720.0f - (PLAYER_SIZE.y / 2);
                g_Players[i].dir.y = 0.0f;
            }

            /*for (int y = 0; y < 12; y++)
            {
                for (int x = 0; x < 20; x++)
                {
                    if (g_MapData[y][x] == 3)
                    {
                        if (HitCheckBB(g_Players[i].pos, g_Players[i].size, XMFLOAT2(32.0f + (x * 64.0f), 32.0f + (y * 64.0f)), 32.0f))
                        {
                            if (g_Players[i].dir.x < 0.0f)
                            {
                                g_Players[i].pos.x += g_Players[i].speed;
                                g_Players[i].dir.x += g_Players[i].speed;
                            }
                            else if (g_Players[i].dir.x > 0.0f)
                            {
                                g_Players[i].pos.x -= g_Players[i].speed;
                                g_Players[i].dir.x -= g_Players[i].speed;
                            }
                            if (g_Players[i].dir.y > 0.0f)
                            {
                                g_Players[i].pos.y -= g_Players[i].speed;
                                g_Players[i].dir.y -= g_Players[i].speed;
                            }
                            else if (g_Players[i].dir.y < 0.0f)
                            {
                                g_Players[i].pos.y += g_Players[i].speed;
                                g_Players[i].dir.y += g_Players[i].speed;
                            }
                        }
                    }
                }
            }*/
            break;
        }
    }
}

void SetDrawMap(XMFLOAT2 sizeRatio, XMFLOAT2 drawPosMin, XMFLOAT2 drawPosMax, XMFLOAT2 uvMin, XMFLOAT2 uvMax, int resourceId, int intFlag)
{

    XMFLOAT2 oneSize = XMFLOAT2(1280.0f / sizeRatio.x, 720.0f / sizeRatio.y);
    for (int y = 0; y < ((((PLUS_POS_FLAG & intFlag) != 0) ? drawPosMax.y : (drawPosMin.y + drawPosMax.y)) / oneSize.y); y++)
    {
        for (int x = 0; x < ((((PLUS_POS_FLAG & intFlag) != 0) ? drawPosMax.x : (drawPosMin.x + drawPosMax.x)) / oneSize.x); x++)
        {
            Master::mpResourceManager->DrawSprite((x * oneSize.x) + drawPosMin.x,
                (y * oneSize.y) + drawPosMin.y,
                oneSize.x,
                oneSize.y,
                uvMin.x,
                uvMax.x,
                uvMin.y,
                uvMax.y,
                resourceId,
                intFlag);
        }
    }
}

XMFLOAT2 XMVSub(XMFLOAT2 src, XMFLOAT2 dst)
{
    return XMFLOAT2(src.x - dst.x, src.y - dst.y);
}

float XMVSize(XMFLOAT2 src)
{
    return sqrt((src.x * src.x) + (src.y * src.y));
}

// 一番速い(割り算などを使ってないから) 当たっているかもしれないからこの後に詳しく見るみたいな使い方
float XMVSizeSq(XMFLOAT2 src)
{
    return ((src.x * src.x) + (src.y * src.y));
}

// bounding circle:境界円
bool HitCheckBC(XMFLOAT2 srcPos, float srcR, XMFLOAT2 dstPos, float dstR)
{
    XMFLOAT2 setVec = XMVSub(dstPos, srcPos);

    float r = (srcR + dstR);

    return ((r * r) >= XMVSizeSq(setVec));
}

//　大きさ半分想定
bool CheckWithin(float srcPos, float srcSize, float dstPos, float dstSize)
{
    if ((srcPos - srcSize) >= (dstPos + dstSize))
    {
        return false;
    }
    if ((srcPos + srcSize) <= (dstPos - dstSize))
    {
        return false;
    }

    return true;
}

//　大きさ半分想定
bool HitCheckBB(XMFLOAT2 srcPos, float srcSize, XMFLOAT2 dstPos, float dstSize)
{
    return (CheckWithin(srcPos.x, srcSize, dstPos.x, dstSize) &&
            CheckWithin(srcPos.y, srcSize, dstPos.y, dstSize));
}
// bounding box:境界箱 aabb→ axis aligned bounding box 軸平行境界箱
bool HitCheckBB(XMFLOAT2 srcPos, float srcW, float srcH, XMFLOAT2 dstPos, float dstW, float dstH)
{
    return (CheckWithin(srcPos.x, srcW, dstPos.x, dstW) &&
            CheckWithin(srcPos.y, srcH, dstPos.y, dstH));
}

/*
// DirectInputの初期化とデバイス列挙
void EnumerateControllers() {
    
    IDirectInput8* directInput = nullptr;
    if (FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr))) {
        return;
    }

    // デバイス列挙
    directInput->EnumDevices(DI8DEVCLASS_GAMECTRL, [](const DIDEVICEINSTANCE* instance, void* context) -> BOOL {
        std::wcout << L"コントローラー発見: " << instance->tszProductName << std::endl;
        return DIENUM_CONTINUE; // 継続
        }, nullptr, DIEDFL_ATTACHEDONLY);

    directInput->Release();
}



void Test()
{
    DWORD dwResult;
    for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));

        // Simply get the state of the controller from XInput.
        dwResult = XInputGetState(i, &state);

        if (dwResult == ERROR_SUCCESS)
        {
            // Controller is connected
        }
        else
        {
            // Controller is not connected
        }
    }
}
//*/