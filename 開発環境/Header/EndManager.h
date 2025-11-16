#pragma once
#include <windows.h>

class EndManager
{
private:
	// エンドフラグ
	bool mbEndFlag;

public:
	/*コンストラクタ*/
	EndManager();
	/*デストラクタ*/
	~EndManager();

	/*終了フラグ取得*/
	bool GetEndFlag(MSG msg);

	/*終了フラグ取得*/
	bool GetEndFlag();

	/*終了フラグ設定*/
	void SetEndFlag(bool flag) { mbEndFlag = flag; }
};