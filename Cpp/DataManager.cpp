#include "../Header/DataManager.h"
#include "../Header/TemplateData.h"

// コンストラクタ
DataManager::DataManager()
: mstDisplaySize(VECTOR_2D::Zero())
{
	mstPlayerDatas.clear();
}

// デストラクタ
DataManager::~DataManager()
{
}

// 初期化
void DataManager::Initilize(HWND hwnd)
{
	RECT rc;
	GetClientRect(hwnd, &rc);   // ウィンドの黒い領域の大きさを返してくれる
	//GetWindowRect(); // ウィンドの大きさ
	// 基本はいらない　ツールを作る時とかに必要
	mstDisplaySize.X = rc.right - rc.left;
	mstDisplaySize.Y = rc.bottom - rc.top;
}

// プレイヤーキーナンバー設定
bool DataManager::SetPlayerKeyNumber(int* keyNumbers)
{
	for (int i = 0; i < mstPlayerDatas.size(); i++)
	{
		if (*(keyNumbers + i) == -1)
		{
			return false;
		}
		mstPlayerDatas[i].keyNumber = *(keyNumbers + i);
	}

	return true;
}