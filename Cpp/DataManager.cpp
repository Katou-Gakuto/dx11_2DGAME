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
{
	mstBitMapData.clear();
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
	BitMapData bitMapData = BitMapData();

	std::ifstream file(fileName, std::ios::binary);

	if (!file) {
		Master::mpEndManager->SetEndFlag(true);
		return;
	}

	file.read(reinterpret_cast<char*>(&bitMapData.bmpHeaderData), sizeof(bitMapData.bmpHeaderData));

	if (bitMapData.bmpHeaderData.bfType != 0x4D42) {
		return;
	}

	bitMapData.maxYPos = bitMapData.bmpHeaderData.biHeight;
	bitMapData.onePixelData.resize(bitMapData.bmpHeaderData.biHeight * bitMapData.bmpHeaderData.biWidth);

	file.seekg(bitMapData.bmpHeaderData.bfOffBits, std::ios::beg);

	file.read(bitMapData[0], bitMapData.onePixelData.size() * 4);
	file.close();

	mstBitMapData.push_back(bitMapData);
}