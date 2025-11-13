#include <iostream>
#include <fstream>
#include <vector>

#include "../Header/DataManager.h"
#include "../Header/EndManager.h"
#include "../Header/TemplateData.h"

// コンストラクタ
DataManager::DataManager()
: mstDisplaySize(VECTOR_2D::Zero())
, mdxsWnd()
, mnGameStartTime(0)
, mstBitMapData(BitMapData())
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

	mdxsWnd = hwnd;
}

// プレイヤーキーナンバー設定
bool DataManager::SetPlayerKeyNumber(int* keyNumbers)
{
	for (int i = 0; i < mstPlayerDatas.size(); i++)
	{
		if (*(keyNumbers + i) == -2)
		{
			return false;
		}
		mstPlayerDatas[i].keyNumber = *(keyNumbers + i);
	}

	return true;
}

// ビットマップデータ設定
void DataManager::SetBitMapData(std::string fileName)
{
	std::ifstream file(fileName, std::ios::binary);

	if (!file) {
		Master::mpEndManager->SetEndFlag(true);
		return;
	}

	file.read(reinterpret_cast<char*>(&mstBitMapData.bmpHeaderData), sizeof(mstBitMapData.bmpHeaderData));

	if (mstBitMapData.bmpHeaderData.bfType != 0x4D42) {
		return;
	}

	mstBitMapData.maxYPos = mstBitMapData.bmpHeaderData.biHeight;
	mstBitMapData.onePixelData.resize(mstBitMapData.bmpHeaderData.biHeight * mstBitMapData.bmpHeaderData.biWidth);

	file.seekg(mstBitMapData.bmpHeaderData.bfOffBits, std::ios::beg);

	file.read(mstBitMapData[0], mstBitMapData.onePixelData.size() * 4);
	file.close();
}