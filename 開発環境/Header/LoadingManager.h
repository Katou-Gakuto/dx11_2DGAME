#pragma once

enum class LOADING_FLAG : unsigned int
{
	SCENE_CHANGE = 0b1,
};

class LoadingManager
{
private:
	// ローディングフラグ
	unsigned int mnLoadingFlag;

public:
	/*コンストラクタ*/
	LoadingManager();
	/*デストラクタ*/
	~LoadingManager();

	/*初期化*/
	void Initilize();

	/*ローディング処理*/
	void LoadingProcess();

	/*ローディングフラグナンバー設定*/
	void SetLoadingFlag(unsigned int flagNumber) { mnLoadingFlag ^= flagNumber; }
	/*ローディングフラグナンバー設定*/
	void SetLoadingFlag(LOADING_FLAG flagNumber) { SetLoadingFlag((unsigned int)flagNumber); }
	/* ローディングフラグナンバー取得*/
	unsigned int GetLoadingFlag() { return mnLoadingFlag; }
};