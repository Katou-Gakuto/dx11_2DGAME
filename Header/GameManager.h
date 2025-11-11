#pragma once

class Camera;
class MapManager;
class ObjectManager;
class TargetDatas;

class GameManager
{
private:
	// 終了フラグ
	bool mbEndFlag;

	// カメラ
	Camera* mpCamera;

	// マップマネージャー
	MapManager* mpMapManager;

	// オブジェクトマネジャー
	ObjectManager* mpObjectManager;

	// ターゲットデータ
	TargetDatas* mpTargetDatas;

public:
	/*コンストラクタ*/
	GameManager();
	/*デストラクタ*/
	~GameManager();

	/*初期化*/
	void Initilize();
	/*終了処理*/
	void Finailize();

	/*更新*/
	void Update();
	/*描画*/
	void Draw();

	/*終了フラグ設定*/
	void SetEndFlag(bool endFlag) { mbEndFlag = endFlag; }

	/*終了フラグ取得*/
	bool GetEndFlag() { return mbEndFlag; }

	/*カメラ取得*/
	Camera* GetCamera() { return mpCamera; }

	/*マップマネジャー取得*/
	MapManager* GetMapManager() { return mpMapManager; }

	/*オブジェクトマネジャー取得*/
	ObjectManager* GetObjectManager() { return mpObjectManager; }

	/*ターゲットデータ取得取得*/
	TargetDatas* GetTargetDatas() { return mpTargetDatas; }
};