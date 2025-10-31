#pragma once

/// <summary>シーン名</summary>
enum class SCENE_NAME
{
	/// <summary>開始</summary>
	START = 0,
	/// <summary>タイトル</summary>
	TITLE,
	/// <summary>選択</summary>
	SELECT,
	/// <summary>ゲーム</summary>
	GAME,
	/// <summary>リザルト</summary>
	RESULT
};

class LoadingManager;

class SceneManager
{
private:
	// 現在のシーン
	SCENE_NAME meNowScene;
	// 次のシーン
	SCENE_NAME meNextScene;

	// ローディングマネージャー
	LoadingManager* mpLoadingManager;

public:
	/*コンストラクタ*/
	SceneManager();
	/*デストラクタ*/
	~SceneManager();

	/*初期化*/
	void Initilize();

	/*シーン移動するかを確認する*/
	void CheckNextScene();

	/*次のシーンに移動する*/
	void NewSceneProcess();

	/*次のシーンを設定*/
	void SetNextScene(SCENE_NAME nextScene) { meNextScene = nextScene; }

	SCENE_NAME GetNowScene() { return meNowScene; }
};