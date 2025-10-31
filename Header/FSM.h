#pragma once

#include <map>

#include "IState.h"

class SetPlayerDataUI;

class FSM_SelectUI
{
private:
	// 登録した状態リスト
	std::map<int, IState_SetPlayerDataUI*> mmStateMap;
	// 現在実行中の状態
	int mnCurrentState;
	// 次の実行状態
	int mnNextState;

public:
	FSM_SelectUI();
	~FSM_SelectUI();

	void RegisterState(int id, IState_SetPlayerDataUI* state);
	void SetCurrentState(int id, SetPlayerDataUI* parent);	// 実行中状態をセットする

	/*初期化*/
	void Init();

	/*共通更新*/
	void Update(int state, SetPlayerDataUI* parent);

	/*マウス更新*/
	void MouseUpdate(SetPlayerDataUI* parent);

	/*キーボード更新*/
	void KeyboardUpdate(SetPlayerDataUI* parent);
	/*コントローラー更新*/
	void ControllerUpdate(SetPlayerDataUI* parent);
	/*キーボードとコントローラー更新*/
	void Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent);

	/*実行状態取得*/
	int GetCurrentState() { return mnCurrentState; }
};