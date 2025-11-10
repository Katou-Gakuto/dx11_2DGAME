#pragma once
#include <vector>
#include <string>

#include "TemplateData.h"

class DataManager
{
private:
	// プレイヤーデータ
	std::vector<PlayerData> mstPlayerDatas;

	// 画面サイズ
	VECTOR_2D mstDisplaySize;

public:
	/*コンストラクタ*/
	DataManager();
	/*デストラクタ*/
	~DataManager();

	/*初期化*/
	void Initilize(HWND hwnd);

	/*プレイヤーデータクリア*/
	void ClearPlayerData() { mstPlayerDatas.clear(); }

	/*プレイヤーデータ追加*/
	int AddPlayrData(PlayerData playerData) { mstPlayerDatas.push_back(playerData); }

	/*--------------------------------------------------------------------------------------------------------------
	* 【取得】
	*/
	/*リザルト取得*/
	std::vector<Result> GetResult() { std::vector<Result>result; result.clear(); for (int i = 0; i < mstPlayerDatas.size(); i++) { result.push_back(mstPlayerDatas[i].result); } return result; }

	/*プレイヤー操作ナンバー取得*/
	int GetPlayerKeyNumber(int playerNumber) { return mstPlayerDatas[playerNumber].keyNumber; }

	/*プレイヤー名取得*/
	std::string GetPlayerName(int playerNumber) { return mstPlayerDatas[playerNumber].name; }

	/*プレイヤー数取得*/
	int GetPlayerCount() { return (int)mstPlayerDatas.size(); }

	/*プレイヤーデータ取得*/
	PlayerData GetPlayerData(int playerNumber) { return mstPlayerDatas[playerNumber]; }

	/*プレイヤーデータ全取得*/
	std::vector<PlayerData> GetPlayerData() { return mstPlayerDatas; }

	/*画面サイズ取得*/
	VECTOR_2D GetDisplaySize() { return mstDisplaySize; }

	/*--------------------------------------------------------------------------------------------------------------
	* 【設定】
	*/
	/*リザルト設定*/
	void SetResult(int playerNumber, Result result) { mstPlayerDatas[playerNumber].result = result; }

	/*プレイヤー情報設定*/
	void SetPlayerData(std::vector<PlayerData> playerDatas) { mstPlayerDatas = playerDatas; }

	/*プレイヤーキーナンバー設定*/
	bool SetPlayerKeyNumber(int *keyNumbers);

	/*プレイヤー名設定*/
	void SetPlayerName(int playerNumber, std::string playerName) { mstPlayerDatas[playerNumber].name = playerName; }

	/*プレイヤー種類設定*/
	void SetPlayerType(int playerNumber, int playerType) { mstPlayerDatas[playerNumber].charcterType = playerType; }
};