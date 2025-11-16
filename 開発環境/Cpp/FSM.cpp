#include "../Header/FSM.h"
#include "../Header/UIs.h"

FSM_SelectUI::FSM_SelectUI()
{
	mmStateMap.clear();
	mnCurrentState = 0;
	mnNextState = 0;
}

FSM_SelectUI::~FSM_SelectUI()
{
	for (auto& pair : mmStateMap)
	{
		delete pair.second;
	}

	mmStateMap.clear();
}

void FSM_SelectUI::RegisterState(int id, IState_SetPlayerDataUI* state)
{
	mmStateMap[id] = state;
}

// 実行中状態をセットする
void FSM_SelectUI::SetCurrentState(int id, SetPlayerDataUI* parent)
{
	mnNextState = id;
	int checkNumber =  mmStateMap[mnNextState]->OnEnter(parent);
	if (checkNumber != -1)
	{
		SetCurrentState(checkNumber, parent);
	}
}

// 初期化
void FSM_SelectUI::Init()
{
	mnCurrentState = mnNextState;
}

// 共通更新
void FSM_SelectUI::Update(int state, SetPlayerDataUI* parent)
{
	if (mnCurrentState != state)
	{
		mmStateMap[mnCurrentState]->OnExit(parent);
		SetCurrentState(state, parent);
	}
}

// マウス更新
void FSM_SelectUI::MouseUpdate(SetPlayerDataUI* parent)
{
	if (mnCurrentState == mnNextState)
	{
		Update(mmStateMap[mnCurrentState]->MouseUpdate(parent), parent);
	}
}

// キーボード更新
void FSM_SelectUI::KeyboardUpdate(SetPlayerDataUI* parent)
{
	if (mnCurrentState == mnNextState)
	{
		Update(mmStateMap[mnCurrentState]->KeyboardUpdate(parent), parent);
	}
}

// コントローラー更新
void FSM_SelectUI::ControllerUpdate(SetPlayerDataUI* parent)
{
	if (mnCurrentState == mnNextState)
	{
		Update(mmStateMap[mnCurrentState]->ControllerUpdate(parent), parent);
	}
}

// キーボードとコントローラー更新
void FSM_SelectUI::Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent)
{
	if (mnCurrentState == mnNextState)
	{
		Update(mmStateMap[mnCurrentState]->Keyboard_And_ControllerUpdate(parent), parent);
	}
}

// 描画
void FSM_SelectUI::Draw(SetPlayerDataUI* parent)
{
	if (mnCurrentState == mnNextState)
	{
		mmStateMap[mnCurrentState]->Draw(parent);
	}
}