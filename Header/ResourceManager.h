#pragma once
#include <d3d11.h>
#include <vector>
#include <tuple>
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

class Camera;

/*--------------------------------------------------------------------------------------------------------------
* 【フォントリスト】
*/
enum class Font
{
	Meiryo,
	Arial,
	MeiryoUI
};

/*--------------------------------------------------------------------------------------------------------------
* 【フォント名】
*/
namespace
{
	const WCHAR* FontList[]
	{
		L"メイリオ",
		L"Arial",
		L"Meiryo UI"
	};
}

/*--------------------------------------------------------------------------------------------------------------
* 【フォント設定】
*/
struct FontData
{
	Font font;					// フォント名
	IDWriteFontCollection* fontCollection;		// フォントコレクション
	DWRITE_FONT_WEIGHT fontWeight;			// フォントの太さ
	DWRITE_FONT_STYLE fontStyle;			// フォントスタイル
	DWRITE_FONT_STRETCH fontStretch;		// フォントの幅
	FLOAT fontSize;					// フォントサイズ
	WCHAR const* localeName;			// ロケール名
	DWRITE_TEXT_ALIGNMENT textAlignment;		// テキストの配置
	D2D1_COLOR_F Color;				// フォントの色

	// デフォルト設定
	FontData()
	{
		font = Font::Meiryo;
		fontCollection = nullptr;
		fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_NORMAL;
		fontStyle = DWRITE_FONT_STYLE::DWRITE_FONT_STYLE_NORMAL;
		fontStretch = DWRITE_FONT_STRETCH::DWRITE_FONT_STRETCH_NORMAL;
		fontSize = 60.0f;
		localeName = L"ja-jp";
		textAlignment = DWRITE_TEXT_ALIGNMENT::DWRITE_TEXT_ALIGNMENT_LEADING;
		Color = D2D1::ColorF(D2D1::ColorF::White);
	}
};

/*--------------------------------------------------------------------------------------------------------------
* 【リソースマネージャー】
*/
class ResourceManager
{
private:
	/*--------------------------------------------------------------------------------------------------------------
	* 【画像描画用】
	*/
	// 画像リソース
	std::vector<ID3D11ShaderResourceView *> mvdxsImageResourceViews;
	// 画像リソースナンバー<int(ID), int(現在参照している数), const char*(ファイル名)>
	std::vector<std::tuple<int, int, const wchar_t*>> mvnImageResourceDatas;

	// メタデータ
	DirectX::TexMetadata mdxsMetadata;

	// イメージ
	DirectX::ScratchImage mdxpImage;

	// デバイス
	ID3D11Device* mdxsDevice;

	// 頂点バッファ
	ID3D11Buffer* mdxsVertexBuffer;

	// デバイスコンテキスト
	ID3D11DeviceContext* mdxsImmediateContext;

	ID3D11VertexShader* mdxsVertexShader;
	// 頂点バッファ
	ID3D11Buffer* mdxsCBNeverChanges;
	// 頂点バッファ
	ID3D11Buffer* mdxsCBChangeOnResize;
	// 頂点バッファ
	ID3D11Buffer* mdxsCBChangesEveryFrame;
	ID3D11PixelShader* mdxsPixelShader;
	// サンプリングの設定
	ID3D11SamplerState* mdxsSamplerLinear;
	// メモリ領域　眼鏡と言われたりしてる
	ID3D11RenderTargetView* mdxsRenderTargetView;
	ID3D11DepthStencilView* mdxsDepthStencilView;

	/*--------------------------------------------------------------------------------------------------------------
	* 【文字描画用】
	*/
	ID2D1Factory* mdxsD2DFactory;
	IDWriteFactory* mdxsDWriteFactory;
	IDWriteTextFormat* mdxsTextFormat;
	IDWriteTextLayout* mdxsTextLayout;
	ID2D1RenderTarget* mdxsRT;
	ID2D1SolidColorBrush* mdxsSolidBrush;
	IDXGISurface* mdxsBackBuffer;
	
	HWND mdxHwnd;

	// フォントデータ
	FontData* mdxsFontData;

	/*--------------------------------------------------------------------------------------------------------------
	* 【共用・その他】
	*/
	IDXGISwapChain* mdxsSwapChain;

	// カメラ
	Camera* mpCamera;

	// 終了フラグ
	bool mbEndFlag;
public:
	/*コンストラクタ*/
	ResourceManager();
	/*デストラクタ*/
	~ResourceManager();

	/*初期化*/
	void Initilize();
	/*終了処理*/
	void Finailize();
	/*描画開始*/
	void StartDraw();
	/*描画終了*/
	void EndDraw();

	/*--------------------------------------------------------------------------------------------------------------
	* 【画像描画用】
	*/
	/*リソースを足す*/
	int AddResource(const wchar_t* fileName);
	/*リソースを足す*/
	int AddResource(wchar_t* fileName) { return AddResource((const wchar_t*)fileName); };
	/*リソースを引く*/
	void SubResource(int resourceId);

	/*リソース作成に必要データを設定*/
	void SetResourceDatas(ID3D11Device* device, ID3D11DeviceContext* immediateContext, ID3D11Buffer* vertexBuffer, ID3D11VertexShader* vertexShader, ID3D11Buffer* CBNeverChanges, ID3D11Buffer* CBChangeOnResize, ID3D11Buffer* CBChangesEveryFrame, ID3D11PixelShader* pixelShader, ID3D11SamplerState* samplerLinear, ID3D11RenderTargetView* renderTargetView, ID3D11DepthStencilView* depthStencilView, IDXGISwapChain* swapChain, HWND hwnd);

	/*リソースを取得*/
	ID3D11ShaderResourceView* GetResourceView(int resourceId);

	/*描画処理 (x(描画座標X), y(描画座標Y), width(画像横幅), height(画像立幅), left(描画する画像の左座標,UV値), right(描画する画像の右座標,UV値), up(描画する画像の上座標,UV値), down(描画する画像の下座標,UV値), resourceId(リソースID), intFlag(処理変更用フラグ(MIDDLE_FLAG = 座標を中心に画像を描画, ULTRAVIOLET_PLUS_FLAG = UV値の左上座標を基準に右と下の量描画する, CAMERA_VIEW_FLAG = カメラが見ている座標を中心にカメラの描画サイズに合わせて描画する描画する(1.0f = MAP_ONE_SQUARE_SIZE))))*/
	void DrawSprite(float x, float y, float width, float height, float left, float right, float up, float down, int resourceId, unsigned int intFlag = 0U);

	/*--------------------------------------------------------------------------------------------------------------
	* 【文字描画用】
	*/
	/*フォント設定*/
	int SetFontData(FontData* set);

	/*フォント設定
	第1引数：フォント名（L"メイリオ", L"Arial", L"Meiryo UI"等）
	第2引数：フォントコレクション（nullptr）
	第3引数：フォントの太さ（DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_WEIGHT_BOLD等）
	第4引数：フォントスタイル（DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STYLE_OBLIQUE, DWRITE_FONT_STYLE_ITALIC）
	第5引数：フォントの幅（DWRITE_FONT_STRETCH_NORMAL,DWRITE_FONT_STRETCH_EXTRA_EXPANDED等）
	第6引数：フォントサイズ（20, 30等）
	第7引数：ロケール名（L"ja-jp"等）
	第8引数：テキストの配置（DWRITE_TEXT_ALIGNMENT_LEADING：前, 等）
	第9引数：フォントの色（D2D1::ColorF(D2D1::ColorF::Black)：黒, D2D1::ColorF(D2D1::ColorF(0.0f, 0.2f, 0.9f, 1.0f))：RGBA指定等
	*/
	int SetFontData(Font font,					// フォント名
		IDWriteFontCollection* fontCollection,	// フォントコレクション
		DWRITE_FONT_WEIGHT fontWeight,		// フォントの太さ
		DWRITE_FONT_STYLE fontStyle,		// フォントスタイル
		DWRITE_FONT_STRETCH fontStretch,		// フォントの幅
		FLOAT fontSize,				// フォントサイズ
		WCHAR const* localeName,			// ロケール名
		DWRITE_TEXT_ALIGNMENT textAlignment,	// テキストの配置
		D2D1_COLOR_F Color				// フォントの色
		);

	/*文字描画
	* string：文字列
	* pos：描画ポジション
	* options：テキストの整形
	*/
	void DrawString(std::string str, DirectX::XMFLOAT2 pos, D2D1_DRAW_TEXT_OPTIONS options, unsigned int intFlag = 0U, float fontSize = 60.0f);

	/*文字描画
	* string：文字列
	* rect：領域指定
	* options：テキストの整形
	*/
	void DrawString(std::string str, D2D1_RECT_F rect, D2D1_DRAW_TEXT_OPTIONS options);


	/*--------------------------------------------------------------------------------------------------------------
	* 【共用・その他】
	*/
	/*エンドフラグ取得*/
	bool GetEndFlag() { return mbEndFlag; }

private:

	/*--------------------------------------------------------------------------------------------------------------
	* 【文字描画用】
	*/
	/*stringをwstringへ変換する*/
	std::wstring StringToWString(std::string oString);
};