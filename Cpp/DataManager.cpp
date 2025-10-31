#include "../Header/DataManager.h"

// コンストラクタ
DataManager::DataManager()
{
	mstPlayerDatas.clear();
}

// デストラクタ
DataManager::~DataManager()
{
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