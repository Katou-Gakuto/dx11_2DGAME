#pragma once
#include <vector>

class DataManager;
class KeyState;
class ResourceManager;
class SetPlayerDataUI;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【選択UI】
*/
class IState_SetPlayerDataUI
{
protected:
	// データマネージャー
	DataManager* mpDataManager;

	// キーステート
	KeyState* mpKeyState;

	// リソースマネージャー
	ResourceManager* mpResourceManager;

	// リソースID達
	std::vector<int> mnResourceIDs;

public:
	IState_SetPlayerDataUI();
	virtual ~IState_SetPlayerDataUI() = default;

	/*この状態に入った時の処理*/
	virtual int OnEnter(SetPlayerDataUI* parent) = 0;
	/*この状態を出る時の処理*/
	virtual void OnExit(SetPlayerDataUI* parent) = 0;

	/*マウス更新*/
	virtual int MouseUpdate(SetPlayerDataUI* parent) = 0;
	/*キーボード更新*/
	virtual int KeyboardUpdate(SetPlayerDataUI* parent) = 0;
	/*コントローラー更新*/
	virtual int ControllerUpdate(SetPlayerDataUI* parent) = 0;
	/*キーボードとコントローラー更新*/
	virtual int Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent) = 0;

	/*描画*/
	virtual void Draw(SetPlayerDataUI* parent) = 0;
};