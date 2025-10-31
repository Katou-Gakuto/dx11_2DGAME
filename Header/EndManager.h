#pragma once
#include <windows.h>

class EndManager
{
private:

public:
	/*コンストラクタ*/
	EndManager();
	/*デストラクタ*/
	~EndManager();

	/*終了フラグ取得*/
	bool GetEndFlag(MSG msg);

	/*終了フラグ取得*/
	bool GetEndFlag();
};