#pragma once

class DataManager;
class EndManager;
class GameManager;
class KeyState;
class LoadingManager;
class ResourceManager;
class SceneManager;
class TimeManager;
class UIManager;

class Master
{
public:
	static DataManager* mpDataManager;	// データマネージャー

	static EndManager* mpEndManager;	// エンドマネージャー

	static GameManager* mpGameManager;	// ゲームマネージャー
	
	static LoadingManager* mpLoadingManager;	// ローディングマネージャー

	static ResourceManager* mpResourceManager;	// リソースマネージャー

	static SceneManager* mpSceneManager;	// シーンマネージャー

	static TimeManager* mpTimeManager;	// タイムマネージャー

	static UIManager* mpUIManager;	// UIマネージャー

	static KeyState* mpKeyState;	// キー状態

	/*マスター所持物全削除処理*/
	static void AllDelete();
};