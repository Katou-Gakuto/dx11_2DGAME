#pragma once
#include <vector>

#include "TemplateData.h"

class CharacterBase;

class TargetDatas
{
private:

	// 標的プレイヤー達
	std::vector<CharacterBase*> mpPlayers;

	// 標的エネミー達
	std::vector<CharacterBase*> mpEnemys;

public:
	/*コンストラクタ*/
	TargetDatas();
	/*デストラクタ*/
	~TargetDatas();

	/*プレイヤーを追加*/
	void AddPlayer(CharacterBase* player) { mpPlayers.push_back(player); }
	/*プレイヤーを削除*/
	void SubPlayer(CharacterBase* player);
	/*プレイヤーを取得*/
	std::vector<CharacterBase*> GetPlayers() { return mpPlayers; }
	/*一番近いプレイヤーを取得*/
	VECTOR_2D GetNearPlayerVec(VECTOR_2D pos);


	/*エネミーを追加*/
	void AddEnemy(CharacterBase* enemy) { mpEnemys.push_back(enemy); }
	/*エネミーを削除*/
	void SubEnemy(CharacterBase* enemy);
	/*エネミーを取得*/
	std::vector<CharacterBase*> GetEnemys() { return mpEnemys; }
};