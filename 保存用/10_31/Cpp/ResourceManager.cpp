#include <d3d11.h>
#include <DirectXMath.h>
#include <tuple>
#include <vector>
#include <dwrite.h>
#include <d2d1.h>
#include <string>
#include <DirectXMath.h>
#include "../DirectXTex.h"

#pragma comment(lib,"d2d1.lib")    
#pragma comment(lib,"dwrite.lib")

#pragma comment(lib, "d3d11.lib")

#ifdef _DEBUG
#pragma comment(lib, "DirectXTexd.lib")
#else
#pragma comment(lib, "DirectXTex.lib")
#endif

#include "../Header/Camera.h"
#include "../Header/DirectX_Structs.h"
#include "../Header/GameManager.h"
#include "../Header/Macro.h"
#include "../Header/Master.h"
#include "../Header/ResourceManager.h"

struct SimpleVertex; // 頂点のフォーマット

using namespace DirectX;

// コンストラクタ
ResourceManager::ResourceManager()
// 画像
: mdxsDevice(NULL)
, mdxpImage()
, mdxsMetadata()
, mdxsVertexBuffer(NULL)
, mdxsImmediateContext(NULL)
, mdxsVertexShader(NULL)
, mdxsCBNeverChanges(NULL)
, mdxsCBChangeOnResize(NULL)
, mdxsCBChangesEveryFrame(NULL)
, mdxsPixelShader(NULL)
, mdxsSamplerLinear(NULL)
, mdxsRenderTargetView(NULL)
, mdxsDepthStencilView(NULL)

// フォント
, mdxsD2DFactory(NULL)
, mdxsDWriteFactory(NULL)
, mdxsTextFormat(NULL)
, mdxsTextLayout(NULL)
, mdxsRT(NULL)
, mdxsSolidBrush(NULL)
, mdxsBackBuffer(NULL)
, mdxsFontData(nullptr)

// 共用・その他
, mdxsSwapChain(NULL)
, mpCamera(nullptr)
, mbEndFlag(false)
{
	mvdxsImageResourceViews.clear();
	mvnImageResourceDatas.clear();
}

// デストラクタ
ResourceManager::~ResourceManager()
{
}

// 初期化
void ResourceManager::Initilize()
{
	mpCamera = Master::mpGameManager->GetCamera();

	// デフォルト設定
	mdxsFontData = new FontData();
	mdxsFontData->fontSize = 60;
	mdxsFontData->fontWeight = DWRITE_FONT_WEIGHT_BOLD;


	// Direct2D,DirectWriteの初期化
	D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &mdxsD2DFactory);

	// バックバッファの取得
	// 型：IDXGISwapChain
	mdxsSwapChain->GetBuffer(0, IID_PPV_ARGS(&mdxsBackBuffer));

	// dpiの設定
	/*
	HDC screen = GetDC(nullptr); // Get the screen's device context
	int dpiX = GetDeviceCaps(screen, LOGPIXELSX); // Horizontal DPI
	int dpiY = GetDeviceCaps(screen, LOGPIXELSY); // Vertical DPI
	ReleaseDC(nullptr, screen);//*/
	/*
	FLOAT dpiX = 0.0f;
	FLOAT dpiY = 0.0f;
	pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);//*/
	///*
	UINT dpiX = 0U;
	UINT dpiY = 0U;
	dpiX = dpiY = GetDpiForWindow(mdxHwnd);//*/

	// レンダーターゲットの作成
	D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	// サーフェスに描画するレンダーターゲットを作成
	mdxsD2DFactory->CreateDxgiSurfaceRenderTarget(mdxsBackBuffer, &props, &mdxsRT);

	// アンチエイリアシングモード
	mdxsRT->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE);

	// IDWriteFactoryの作成
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), reinterpret_cast<IUnknown**>(&mdxsDWriteFactory));

	//関数CreateTextFormat()
	//第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
	//第2引数：フォントコレクション（nullptr）
	//第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
	//第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
	//第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
	//第6引数：フォントサイズ（20, 30等）
	//第7引数：ロケール名（L""）
	//第8引数：テキストフォーマット（&g_pTextFormat）
	mdxsDWriteFactory->CreateTextFormat(FontList[(int)mdxsFontData->font],
		mdxsFontData->fontCollection,
		mdxsFontData->fontWeight,
		mdxsFontData->fontStyle,
		mdxsFontData->fontStretch,
		mdxsFontData->fontSize,
		mdxsFontData->localeName,
		&mdxsTextFormat);

	//関数SetTextAlignment()
	//第1引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, DWRITE_TEXT_ALIGNMENT_TRAILING：後, DWRITE_TEXT_ALIGNMENT_CENTER：中央,
	//                         DWRITE_TEXT_ALIGNMENT_JUSTIFIED：行いっぱい）
	mdxsTextFormat->SetTextAlignment(mdxsFontData->textAlignment);

	//関数CreateSolidColorBrush()
	//第1引数：フォント色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定）
	mdxsRT->CreateSolidColorBrush(mdxsFontData->Color, &mdxsSolidBrush);
}
// 終了処理
void ResourceManager::Finailize()
{
	for (int i = 0; i < mvdxsImageResourceViews.size(); i++)
	{
		if (mvdxsImageResourceViews[i]) mvdxsImageResourceViews[i]->Release();
	}
	mvdxsImageResourceViews.clear();
	mvnImageResourceDatas.clear();

	// 文字描画関連のアンロード
	if (mdxsBackBuffer) mdxsBackBuffer->Release();
	if (mdxsSolidBrush) mdxsSolidBrush->Release();
	if (mdxsRT) mdxsRT->Release();
	if (mdxsTextFormat) mdxsTextFormat->Release();
	if (mdxsDWriteFactory) mdxsDWriteFactory->Release();
	if (mdxsD2DFactory) mdxsD2DFactory->Release();
	if (mdxsTextLayout) mdxsTextLayout->Release();
}

// 描画開始
void ResourceManager::StartDraw()
{
	mdxsImmediateContext->VSSetShader(mdxsVertexShader, NULL, 0);
	//                                       /*スロット番号が決まっている 一つ目*/
	mdxsImmediateContext->VSSetConstantBuffers(0, 1, &mdxsCBNeverChanges);
	mdxsImmediateContext->VSSetConstantBuffers(1, 1, &mdxsCBChangeOnResize);
	mdxsImmediateContext->VSSetConstantBuffers(2, 1, &mdxsCBChangesEveryFrame);
	mdxsImmediateContext->PSSetShader(mdxsPixelShader, NULL, 0);
	// シェーダーごとに決めてる?  
	mdxsImmediateContext->PSSetConstantBuffers(2, 1, &mdxsCBChangesEveryFrame);
	//    g_pImmediateContext->PSSetShaderResources(0, 1, &g_pBGTextureRV);
		// テクセル
	mdxsImmediateContext->PSSetSamplers(0, 1, &mdxsSamplerLinear);

	// Rotate cube around the origin 回転するやつが元はあった
	XMMATRIX g_World;    // 4*4 16のfloat　行列
	// 初期値を入れてる
	g_World = XMMatrixIdentity();

	//
	// Clear the back buffer
	//
	// 背景色
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f }; // red, green, blue, alpha
	mdxsImmediateContext->ClearRenderTargetView(mdxsRenderTargetView, ClearColor);

	//
	// Clear the depth buffer to 1.0 (max depth)
	//
	mdxsImmediateContext->ClearDepthStencilView(mdxsDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
	
	// コンスタントバッファの更新　回転が入っていた
	CBChangesEveryFrame cb;
	cb.mWorld = XMMatrixTranspose(g_World);
	mdxsImmediateContext->UpdateSubresource(mdxsCBChangesEveryFrame, 0, NULL, &cb, 0, 0);
}

// 描画終了
void ResourceManager::EndDraw()
{
	// 裏と表を切り替える プレゼント(読み)　ウィンドモードだと切り替えられないから仮想に保存後切り替える(多分)
	mdxsSwapChain->Present(0, 0);
}

/*--------------------------------------------------------------------------------------------------------------
* 【画像描画用】
*/
// リソースを足す
int ResourceManager::AddResource(const wchar_t* fileName)
{
	for (int i = 0; i < mvnImageResourceDatas.size(); i++)
	{
		if (std::get<2>(mvnImageResourceDatas[i]) == fileName)
		{
			std::get<1>(mvnImageResourceDatas[i]) += 1;
			return std::get<0>(mvnImageResourceDatas[i]);
		}
	}

	HRESULT hr = S_OK;

	ID3D11ShaderResourceView* addResourceView = NULL;//(ID3D11ShaderResourceView*)malloc(sizeof(ID3D11ShaderResourceView*));
	//memset(addResourceView, NULL, sizeof(ID3D11ShaderResourceView*));

	// ファイル開く?
	hr = LoadFromWICFile(fileName, DirectX::WIC_FLAGS_NONE, &mdxsMetadata, mdxpImage);
	if (FAILED(hr))
	{
		mbEndFlag = true;
		return -1;
	}

	//プレイヤーテクスチャの作成
	hr = DirectX::CreateShaderResourceView(
		mdxsDevice,
		mdxpImage.GetImages(),
		mdxpImage.GetImageCount(),
		mdxsMetadata,
		&addResourceView);

	mvdxsImageResourceViews.push_back(addResourceView);
	int setNumber = 0;
	if (mvnImageResourceDatas.size() != 0)
	{
		setNumber = std::get<0>(mvnImageResourceDatas[mvnImageResourceDatas.size() - 1]) + 1;
	}
	mvnImageResourceDatas.push_back(std::tuple<int, int, const wchar_t*>(setNumber, 1, fileName));
	
	return std::get<0>(mvnImageResourceDatas[mvnImageResourceDatas.size() - 1]);
}

// リソースを引く
void ResourceManager::SubResource(int resourceId)
{
	if (resourceId == -1)
	{
		return;
	}

	for (int i = 0; i < mvnImageResourceDatas.size(); i++)
	{
		if (std::get<0>(mvnImageResourceDatas[i]) == resourceId)
		{
			std::get<1>(mvnImageResourceDatas[i]) -= 1;
			if (std::get<1>(mvnImageResourceDatas[i]) <= 0)
			{
				mvnImageResourceDatas.erase(mvnImageResourceDatas.begin() + i);

				if (mvdxsImageResourceViews[i]) mvdxsImageResourceViews[i]->Release();
				mvdxsImageResourceViews.erase(mvdxsImageResourceViews.begin() + i);
			}
			break;
		}
	}
}

// リソース作成に必要データを設定
void ResourceManager::SetResourceDatas(ID3D11Device* device, ID3D11DeviceContext* immediateContext, ID3D11Buffer* vertexBuffer, ID3D11VertexShader* vertexShader, 
									   ID3D11Buffer* CBNeverChanges, ID3D11Buffer* CBChangeOnResize, ID3D11Buffer* CBChangesEveryFrame, ID3D11PixelShader* pixelShader, 
									   ID3D11SamplerState* samplerLinear, ID3D11RenderTargetView* renderTargetView, ID3D11DepthStencilView* depthStencilView, IDXGISwapChain* swapChain, HWND hwnd)
{
	mdxsDevice = device;
	mdxsImmediateContext = immediateContext;
	mdxsVertexBuffer = vertexBuffer;
	mdxsVertexShader = vertexShader;
	mdxsCBNeverChanges = CBNeverChanges;
	mdxsCBChangeOnResize = CBChangeOnResize;
	mdxsCBChangesEveryFrame = CBChangesEveryFrame;
	mdxsPixelShader = pixelShader;
	mdxsSamplerLinear = samplerLinear;
	mdxsRenderTargetView = renderTargetView;
	mdxsDepthStencilView = depthStencilView;
	mdxsSwapChain = swapChain;

	mdxHwnd = hwnd;
}

// リソースを取得
ID3D11ShaderResourceView* ResourceManager::GetResourceView(int resourceId)
{
	if (resourceId == -1)
	{
		return nullptr;
	}

	for (int i = 0; i < mvnImageResourceDatas.size(); i++)
	{
		if (std::get<0>(mvnImageResourceDatas[i]) == resourceId)
		{
			return mvdxsImageResourceViews[i];
		}
	}

	return nullptr;
}

// 描画処理
void ResourceManager::DrawSprite(float x, float y, float width, float height, float left, float right, float up, float down, int resourceId, unsigned int intFlag)
{
	ID3D11ShaderResourceView* set = GetResourceView(resourceId);
	mdxsImmediateContext->PSSetShaderResources(0, 1, &set);

	// 描画一
	// 位置操作
	{
		// マップのサブリソース
		D3D11_MAPPED_SUBRESOURCE ms;
		mdxsImmediateContext->Map(mdxsVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &ms);

		SimpleVertex* pVertex = (SimpleVertex*)ms.pData;

		if ((intFlag & CAMERA_VIEW_FLAG) != 0)
		{
			VECTOR_2D setOneLength = mpCamera->GetNowOneLength() * MAP_ONE_SQUARE_SIZE;			
			x -= mpCamera->GetCameraPos().X;
			y -= mpCamera->GetCameraPos().Y;

			x *= setOneLength.X;
			y *= setOneLength.Y;
			
			//0.5f がカメラが中心である事を示している
			x += (mpCamera->GetDisplayDistance().X * 0.5f * setOneLength.X);
			y += (mpCamera->GetDisplayDistance().Y * 0.5f * setOneLength.Y);


			width = width * setOneLength.X;
			height = height * setOneLength.Y;
		}

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

		mdxsImmediateContext->Unmap(mdxsVertexBuffer, 0);
	}

	mdxsImmediateContext->Draw(6, 0);
}


/*--------------------------------------------------------------------------------------------------------------
* 【文字描画用】
*/
/*フォント設定*/
int ResourceManager::SetFontData(FontData* set)
{
	mdxsDWriteFactory->CreateTextFormat(FontList[(int)set->font], set->fontCollection, set->fontWeight, set->fontStyle, set->fontStretch, set->fontSize, set->localeName, &mdxsTextFormat);
	mdxsTextFormat->SetTextAlignment(set->textAlignment);
	mdxsRT->CreateSolidColorBrush(set->Color, &mdxsSolidBrush);

	return -1;
}

/*フォント設定*/
int ResourceManager::SetFontData(Font font, IDWriteFontCollection* fontCollection, DWRITE_FONT_WEIGHT fontWeight, DWRITE_FONT_STYLE fontStyle, DWRITE_FONT_STRETCH fontStretch, FLOAT fontSize, WCHAR const* localeName, DWRITE_TEXT_ALIGNMENT textAlignment, D2D1_COLOR_F Color)
{
	mdxsDWriteFactory->CreateTextFormat(FontList[(int)font], fontCollection, fontWeight, fontStyle, fontStretch, fontSize, localeName, &mdxsTextFormat);
	mdxsTextFormat->SetTextAlignment(textAlignment);
	mdxsRT->CreateSolidColorBrush(Color, &mdxsSolidBrush);

	return -1;
}

// 文字描画, string：文字列, pos：描画ポジション, options：テキストの整形
void ResourceManager::DrawString(std::string str, DirectX::XMFLOAT2 pos, D2D1_DRAW_TEXT_OPTIONS options)
{
	// 文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	// ターゲットサイズの取得
	D2D1_SIZE_F TargetSize = mdxsRT->GetSize();

	// テキストレイアウトを作成
	mdxsDWriteFactory->CreateTextLayout(wstr.c_str(), wstr.size(), mdxsTextFormat, TargetSize.width, TargetSize.height, &mdxsTextLayout);

	// 描画位置の確定
	D2D1_POINT_2F pounts;
	pounts.x = pos.x;
	pounts.y = pos.y;

	// 描画の開始
	mdxsRT->BeginDraw();

	// 描画処理
	mdxsRT->DrawTextLayout(pounts, mdxsTextLayout, mdxsSolidBrush, options);

	// 描画の終了
	mdxsRT->EndDraw();
}

// 文字描画, string：文字列, rect：領域指定, options：テキストの整形
void ResourceManager::DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options)
{
	// 文字列の変換
	std::wstring wstr = StringToWString(str.c_str());

	// 描画の開始
	mdxsRT->BeginDraw();

	// 描画処理
	mdxsRT->DrawText(wstr.c_str(), wstr.size(), mdxsTextFormat, rect, mdxsSolidBrush, options);

	// 描画の終了
	mdxsRT->EndDraw();
}

// stringをwstringへ変換する
std::wstring ResourceManager::StringToWString(std::string oString)
{
	// SJIS → wstring
	int iBufferSize = MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, (wchar_t*)NULL, 0);

	// バッファの取得
	wchar_t* cpUCS2 = new wchar_t[iBufferSize];

	// SJIS → wstring
	MultiByteToWideChar(CP_ACP, 0, oString.c_str(), -1, cpUCS2, iBufferSize);

	// stringの生成
	std::wstring oRet(cpUCS2, cpUCS2 + iBufferSize - 1);

	// バッファの破棄
	delete[] cpUCS2;

	// 変換結果を返す
	return(oRet);
}