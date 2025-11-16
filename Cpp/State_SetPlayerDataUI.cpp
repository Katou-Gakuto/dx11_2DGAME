#include <iostream>
#include <string>
#include <locale>
#include <codecvt>

#include <dxgi.h>

#include <DirectXMath.h>

//#include <imm.h>


#include "../Header/DataManager.h"
#include "../Header/KeyState.h"
#include "../Header/Master.h"
#include "../Header/SceneManager.h"
#include "../Header/State_SetPlayerDataUI.h"
#include "../Header/TemplateData.h"
#include "../Header/UIs.h"

using namespace DirectX;

//#pragma comment(lib, "imm32.lib")

#pragma comment(lib, "DXGI.lib")

/*----------------------------------------------------------------------------------------------------*/
/*　【プレイヤー数選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
SPDUIPlayerNumber::SPDUIPlayerNumber()
: IState_SetPlayerDataUI()
{
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/ArrowBoxMark.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/WhiteArrowBoxMark.png"));
}

// この状態に入った時の処理
int SPDUIPlayerNumber::OnEnter(SetPlayerDataUI* parent)
{
	mstPlayerDatas.clear();

	parent->SetSelectMaxNumber(PLAYER_MAX);
	parent->SetSelectNumber(0);

	return -1;
}
// この状態を出る時の処理
void SPDUIPlayerNumber::OnExit(SetPlayerDataUI* parent)
{
	mstPlayerDatas.reserve((unsigned long long)(parent->GetSelectNumber() + 1));
	for (int i = 0; i <= parent->GetSelectNumber(); i++)
	{
		mstPlayerDatas.push_back(PlayerData());
	}
	mpDataManager->SetPlayerData(mstPlayerDatas);
}
// マウス更新
int SPDUIPlayerNumber::MouseUpdate(SetPlayerDataUI* parent)
{
	return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER;
}
// キーボード更新
int SPDUIPlayerNumber::KeyboardUpdate(SetPlayerDataUI* parent)
{
	for (int i = 0; i < PLAYER_MAX; i++)
	{
		if (mpKeyState->GetWordKeyDown_Board((int)KEY_BOARD_WORD::_1 + i) || mpKeyState->GetNumpadKeyDown_Board((int)KEY_BOARD_NUM_PAD::NUMPAD_1_NUM_ON + i))
		{
			parent->SetSelectNumber(i);
		}
	}

	if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER))
	{
		return SET_PLAYER_DATA_UI_STATE_CONTROLLER_SELECT;
	}
	return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER;
}
// コントローラー更新
int SPDUIPlayerNumber::ControllerUpdate(SetPlayerDataUI* parent)
{
	if (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::B))
	{
		Master::mpSceneManager->SetNextScene(SCENE_NAME::TITLE);
	}

	return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER;
}

// キーボードとコントローラー更新
int SPDUIPlayerNumber::Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent)
{
	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::DOWN) && parent->CheckChangeFrame())
	{
		parent->Up();
	}
	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::UP) && parent->CheckChangeFrame())
	{
		parent->Down();
	}

	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::A, false))
	{
		return SET_PLAYER_DATA_UI_STATE_CONTROLLER_SELECT;
	}
	return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER;
}

// 描画
void SPDUIPlayerNumber::Draw(SetPlayerDataUI* parent)
{
	if (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::UP))
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.7f, mpDataManager->GetDisplaySize().Y * 0.25f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.5f, 0.875f, 0.0f, 0.5f, mnResourceIDs[0], MIDDLE_FLAG);
	}
	else
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.7f, mpDataManager->GetDisplaySize().Y * 0.25f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.5f, 0.875f, 0.0f, 0.5f, mnResourceIDs[1], MIDDLE_FLAG);
	}

	if (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::DOWN))
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.7f, mpDataManager->GetDisplaySize().Y * 0.7f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.125f, 0.5f, 0.0f, 0.5f, mnResourceIDs[0], MIDDLE_FLAG);
	}
	else
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.7f, mpDataManager->GetDisplaySize().Y * 0.7f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.125f, 0.5f, 0.0f, 0.5f, mnResourceIDs[1], MIDDLE_FLAG);
	}

	for (int i = 0; i < 5; i++)
	{
		mpResourceManager->DrawString(std::to_string(i + 1), XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.2f, mpDataManager->GetDisplaySize().Y * (0.43f - (i * 0.08f) + (parent->GetSelectNumber() * 0.08f))), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}

	mpResourceManager->DrawString("人で遊ぶ", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.23f, mpDataManager->GetDisplaySize().Y * 0.43f), D2D1_DRAW_TEXT_OPTIONS_NONE);

	FontData fontData = FontData();
	fontData.fontSize = 20.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;
	Master::mpResourceManager->SetFontData(&fontData);
	mpResourceManager->DrawString("※5人でやる場合は一名、キーボードでやる事となります。", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.43f, mpDataManager->GetDisplaySize().Y * 0.49f), D2D1_DRAW_TEXT_OPTIONS_NONE);
	fontData = FontData();
	Master::mpResourceManager->SetFontData(&fontData);
}


/*----------------------------------------------------------------------------------------------------*/
/*　【コントローラー選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
SPDUIControllerSelect::SPDUIControllerSelect()
: IState_SetPlayerDataUI()
{
}

// この状態に入った時の処理
int SPDUIControllerSelect::OnEnter(SetPlayerDataUI* parent)
{
	parent->GetSetPlayerControllerUI()->SetControllerStart();

	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;
}
// この状態を出る時の処理
void SPDUIControllerSelect::OnExit(SetPlayerDataUI* parent){}
// マウス更新
int SPDUIControllerSelect::MouseUpdate(SetPlayerDataUI* parent){	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT; }
// キーボード更新
int SPDUIControllerSelect::KeyboardUpdate(SetPlayerDataUI* parent){	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT; }
// コントローラー更新
int SPDUIControllerSelect::ControllerUpdate(SetPlayerDataUI* parent){ return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT; }
// キーボードとコントローラー更新
int SPDUIControllerSelect::Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent){	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT; }

// 描画
void SPDUIControllerSelect::Draw(SetPlayerDataUI* parent){}


/*----------------------------------------------------------------------------------------------------*/
/*　【キャラクター選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
SPDUICharacterSelect::SPDUICharacterSelect()
: IState_SetPlayerDataUI()
{
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018a.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018b.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018c.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018d.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018e.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018f.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Swordsman/pipo-charachip018g.png"));

	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Back.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/ArrowMark.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/WhiteArrowMark.png"));
}

// この状態に入った時の処理
int SPDUICharacterSelect::OnEnter(SetPlayerDataUI* parent)
{
	parent->SetSelectMaxNumber(mnResourceIDs.size() - 3);
	parent->SetSelectNumber(0);

	return -1;
}
// この状態を出る時の処理
void SPDUICharacterSelect::OnExit(SetPlayerDataUI* parent)
{
	mpDataManager->SetPlayerType(parent->GetSelectPlayerNumber(), parent->GetSelectNumber());
}
// マウス更新
int SPDUICharacterSelect::MouseUpdate(SetPlayerDataUI* parent)
{
	for (int i = 0; i < mpDataManager->GetPlayerCount(); i++)
	{
		if (mpDataManager->GetPlayerKeyNumber(i) == -1)
		{
			return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER;
		}
	}
	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;
}
// キーボード更新
int SPDUICharacterSelect::KeyboardUpdate(SetPlayerDataUI* parent){	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;}
// コントローラー更新
int SPDUICharacterSelect::ControllerUpdate(SetPlayerDataUI* parent)
{
	for (int i = 0; i < mpDataManager->GetPlayerCount(); i++)
	{
		if (mpDataManager->GetPlayerKeyNumber(i) == -1)
		{
			return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER;
		}
	}

	if (mpKeyState->GetKeyUpAllController(CONTROLLER_KEY_TYPE::B))
	{
		int nullKeyNumber[5] = {-1, -1, -1, -1, -1};
		mpDataManager->SetPlayerKeyNumber(nullKeyNumber);
		return SET_PLAYER_DATA_UI_STATE_CONTROLLER_SELECT;
	}

	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;
}
// キーボードとコントローラー更新
int SPDUICharacterSelect::Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent)
{

	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::LEFT, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())) && parent->CheckChangeFrame())
	{
		parent->Up();
	}
	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::RIGHT, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())) && parent->CheckChangeFrame())
	{
		parent->Down();
	}

	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::A, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
	{
		return SET_PLAYER_DATA_UI_STATE_NAME_SET;
	}

	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;
}

// 描画
void SPDUICharacterSelect::Draw(SetPlayerDataUI* parent)
{
	for (int i = 0; i < mpDataManager->GetPlayerCount(); i++)
	{
		if (mpDataManager->GetPlayerKeyNumber(i) == -1)
		{
			return;
		}
	}

	Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.1325f, mpDataManager->GetDisplaySize().Y * 0.14f,
		mpDataManager->GetDisplaySize().X * 0.055f, mpDataManager->GetDisplaySize().Y * 0.07f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 3], MIDDLE_FLAG);
	
	FontData fontData = FontData();
	fontData.fontSize = 40.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD;
	Master::mpResourceManager->SetFontData(&fontData);
	Master::mpResourceManager->DrawString(std::to_string(parent->GetSelectPlayerNumber() + 1) + "P", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.13f, mpDataManager->GetDisplaySize().Y * 0.13f), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

	fontData = FontData();
	Master::mpResourceManager->SetFontData(&fontData);

	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::RIGHT, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.75f, mpDataManager->GetDisplaySize().Y * 0.5f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.5f, 0.875f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 2], MIDDLE_FLAG);
	}
	else
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.75f, mpDataManager->GetDisplaySize().Y * 0.5f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.5f, 0.875f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);
	}

	if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::LEFT, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.5f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.125f, 0.5f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 2], MIDDLE_FLAG);
	}
	else
	{
		Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.5f,
			mpDataManager->GetDisplaySize().X * 0.25f, mpDataManager->GetDisplaySize().Y * 0.25f, 0.125f, 0.5f, 0.5f, 1.0f, mnResourceIDs[mnResourceIDs.size() - 1], MIDDLE_FLAG);
	}

	Master::mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.5f, mpDataManager->GetDisplaySize().Y * 0.5f,
		mpDataManager->GetDisplaySize().X * 0.3f, mpDataManager->GetDisplaySize().Y * 0.3f, 1.0f / 3.0f, 2.0f / 3.0f, 0.0f / 4.0f, 1.0f / 4.0f, mnResourceIDs[parent->GetSelectNumber()], MIDDLE_FLAG);

	switch (parent->GetSelectNumber())
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		mpResourceManager->DrawString("キャラクター種類 : 近距離", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.2f, mpDataManager->GetDisplaySize().Y * 0.15f), D2D1_DRAW_TEXT_OPTIONS_NONE);
	}
}

/*----------------------------------------------------------------------------------------------------*/
/*　【名前設定状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
// コンストラクタ
SPDUINameSet::SPDUINameSet()
: IState_SetPlayerDataUI()
, mnSelectNumberX(0)
, mnSelectNumberY(0)
, mucWordFlags((unsigned char)0)
, mnSetNameSelectNumber(0)
, mnAddWordSelectNumber(0)
, mnSelectWordSelectNumber(0)
, mnAddWordChangeNumber(0)
{
	msSetName.clear();
	msAddWord.clear();
	msSelectWord.clear();

	mnResourceIDs.clear();
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/Back.png"));
	mnResourceIDs.push_back(mpResourceManager->AddResource(L"Resource/GrayBack.png"));
}

// この状態に入った時の処理
int SPDUINameSet::OnEnter(SetPlayerDataUI* parent)
{
	msSetName.clear();
	msAddWord.clear();
	msSelectWord.clear();
	mnSetNameSelectNumber = 0;
	mnAddWordSelectNumber = 0;
	mnSelectWordSelectNumber = 0;

	mnAddWordChangeNumber = 0;

	mnSelectNumberX = 0;
	mnSelectNumberY = 0;
	
	mucWordFlags = ((unsigned char)(mpKeyState->GetSpecialKey_Board(KEY_BOARD_SPECIAL::FULL_WIDTH) ? 1 : 0) << (int)WORD_FLAGS_BIT::FONT_CONVERSION) +
		          ((unsigned char)(mpKeyState->GetSpecialKey_Board(KEY_BOARD_SPECIAL::SHIFT_LEFT_AND_RIGHT) ? 1 : 0) << (int)WORD_FLAGS_BIT::SHIFT) +
		          ((unsigned char)(mpKeyState->GetToggleState(KEY_BOARD_TOGGLE::CAPS_LOCK) ? 1 : 0) << (int)WORD_FLAGS_BIT::CAPS_LOCK) +
		          ((unsigned char)(mpKeyState->GetSpecialKey_Board(KEY_BOARD_SPECIAL::INSERT) ? 1 : 0) << (int)WORD_FLAGS_BIT::INSERT) +
		          ((unsigned char)(mpKeyState->GetSpecialKey_Board(KEY_BOARD_SPECIAL::ALT_LEFT_AND_RIGHT) ? 1 : 0) << (int)WORD_FLAGS_BIT::ALT);

	return -1;
}
// この状態を出る時の処理
void SPDUINameSet::OnExit(SetPlayerDataUI* parent)
{
}
// マウス更新
int SPDUINameSet::MouseUpdate(SetPlayerDataUI* parent)
{
	return SET_PLAYER_DATA_UI_STATE_NAME_SET;
}
// キーボード更新
int SPDUINameSet::KeyboardUpdate(SetPlayerDataUI* parent)
{
	if (parent->GetSelectPlayerNumber() < mpDataManager->GetPlayerCount())
	{
		if (mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber()) == (int)CONTROLLER_KEY_NUMBER::KEY_BOARD)
		{
			unsigned long long wordKeyBoradFlags = (mpKeyState->GetDownWordKeyFlags_Board() & 0x1'ffff'ffff'ffff);
			// 押してるワードに反応する
			if (wordKeyBoradFlags != 0)
			{
				for (int i = 0; i < WORD_MAX; i++)
				{
					if ((wordKeyBoradFlags & ((unsigned long long)1 << i)) != 0)
					{
						// 仮想キーボードの位置を設定


						SetNumberProcess(parent, i);
					}
				}

				if (((wordKeyBoradFlags & ((unsigned long long)1 << (int)KEY_BOARD_WORD::ARROW_LEFT)) != 0) &&
					((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::ALT)) != 0))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::LETF);
				}
				if (((wordKeyBoradFlags & ((unsigned long long)1 << (int)KEY_BOARD_WORD::ARROW_RIGHT)) != 0) &&
					((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::ALT)) != 0))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::RIGHT);
				}

				// ホーム
				if ((wordKeyBoradFlags & ((unsigned long long)1 << (int)KEY_BOARD_WORD::HOME)) != 0)
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::HOME);
				}

				// エンド
				if ((wordKeyBoradFlags & ((unsigned long long)1 << (int)KEY_BOARD_WORD::END)) != 0)
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::END);
				}
			}

			{// 特殊キー処理
				// 全角半角 エラー起こる
				if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::FULL_WIDTH))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_FULL_HALF_WIDTH, true);
				}
				else if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::HALF_WIDTH))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_FULL_HALF_WIDTH, false);
				}

				// シフト
				if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::SHIFT_LEFT_AND_RIGHT))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_SHIFT, true);
				}
				else if (mpKeyState->GetSpecialKeyUp_Board(KEY_BOARD_SPECIAL::SHIFT_LEFT_AND_RIGHT))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_SHIFT, false);
				}

				// インサート
				if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::INSERT))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_INSERT, true);
				}
				else if (mpKeyState->GetSpecialKeyUp_Board(KEY_BOARD_SPECIAL::INSERT))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_INSERT, false);
				}

				// オルト
				if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ALT_LEFT_AND_RIGHT))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_ALT, true);
				}
				else if (mpKeyState->GetSpecialKeyUp_Board(KEY_BOARD_SPECIAL::ALT_LEFT_AND_RIGHT))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_ALT, false);
				}

				// バックスペース
				if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::BACK_SPACE))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::BACK_SPAE);
				}

				// タブ
				if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::TAB))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::TAB);
				}

				// デリート
				if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::_DELETE))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::DELETE_PROCESS);
				}

				// コントロール別処理
				if (!mpKeyState->GetSpecialKey_Board(KEY_BOARD_SPECIAL::CTRL_LEFT_AND_RIGHT))
				{
					// エンター
					if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER))
					{
						SetNumberProcess(parent, (int)PROCESS_NUMBER::ENTER);
					}
				}
				else
				{
					// エンター
					if (mpKeyState->GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL::ENTER))
					{
						SetNumberProcess(parent, KEY_POS_NUMBERS[mnSelectNumberY][mnSelectNumberX]);
					}

					// マス移動
					if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_UP))
					{
						mnSelectNumberY = CheckYPos(mnSelectNumberY - 1);
					}
					if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_DOWN))
					{
						mnSelectNumberY = CheckYPos(mnSelectNumberY + 1);
					}

					if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_RIGHT))
					{
						mnSelectNumberX = CheckXPos(mnSelectNumberX + 1);
					}
					if (mpKeyState->GetWordKeyDown_Board(KEY_BOARD_WORD::ARROW_LEFT))
					{
						mnSelectNumberX = CheckXPos(mnSelectNumberX - 1);
					}
				}
			}

			{// 
				// キャプチャーロック
				if (mpKeyState->GetAllToggleState())// トグルキーダウンとアップ作る
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_CAPSLOCK, true);
				}
				else if (mpKeyState->GetSpecialKeyUp_Board(KEY_BOARD_SPECIAL::SHIFT_LEFT_AND_RIGHT))
				{
					SetNumberProcess(parent, (int)PROCESS_NUMBER::KEY_BOARD_CAPSLOCK, false);
				}
			}
		}
	}

	return SET_PLAYER_DATA_UI_STATE_NAME_SET;
}
// コントローラー更新
int SPDUINameSet::ControllerUpdate(SetPlayerDataUI* parent)
{
	if (parent->GetSelectPlayerNumber() < mpDataManager->GetPlayerCount())
	{
		if (mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber()) != 0)
		{
			if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::UP, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
			{
				mnSelectNumberY = CheckYPos(mnSelectNumberY - 1);
			}
			if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::DOWN, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
			{
				mnSelectNumberY = CheckYPos(mnSelectNumberY + 1);
			}

			if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::RIGHT, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
			{
				mnSelectNumberX = CheckXPos(mnSelectNumberX + 1);
			}
			if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::LEFT, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
			{
				mnSelectNumberX = CheckXPos(mnSelectNumberX - 1);
			}

			if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::A, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
			{
				SetNumberProcess(parent, KEY_POS_NUMBERS[mnSelectNumberY][mnSelectNumberX]);
			}

			if (mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::L, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())) &&
				mpKeyState->GetKey_Controller(CONTROLLER_KEY_TYPE::R, mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber())))
			{
				SetNumberProcess(parent, PROCESS_NUMBER::ENTER);
			}
		}
	}

	return SET_PLAYER_DATA_UI_STATE_NAME_SET;
}
// キーボードとコントローラー更新
int SPDUINameSet::Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent){	return SET_PLAYER_DATA_UI_STATE_NAME_SET; }

// 次のポジションを取得する
void SPDUINameSet::GetNextPos(int* nextXPos, int* nextYPos, int nowXPos, int nowYPos)
{
	if ((*nextXPos != nowXPos) || (*nextYPos != nowYPos))
	{
		int xPos = CheckXPos(*nextXPos);
		int yPos = CheckYPos(*nextYPos);
		if (KEY_POS_NUMBERS[yPos][xPos] == KEY_POS_NUMBERS[nowYPos][nowXPos])
		{
			if ((xPos != nowXPos) && (yPos != nowYPos))
			{
				if (KEY_POS_NUMBERS[yPos][nowXPos] != KEY_POS_NUMBERS[nowYPos][nowXPos])
				{
					*nextXPos = nowXPos;
					*nextYPos = yPos;
					return;
				}
				else if (KEY_POS_NUMBERS[nowYPos][xPos] != KEY_POS_NUMBERS[nowYPos][nowXPos])
				{
					*nextXPos = xPos;
					*nextYPos = nowYPos;
					return;
				}

				*nextYPos = yPos;
				nowYPos = yPos;
			}

			if (*nextXPos != nowXPos)
			{
				int sign = ((*nextXPos < nowXPos) ? -1 : 1);
				for (int x = 0; x < KEY_POS_NUMBER_WIDTH; x += sign)
				{
					if (KEY_POS_NUMBERS[*nextYPos][CheckXPos(xPos + x)] != KEY_POS_NUMBERS[nowYPos][nowXPos])
					{
						*nextXPos = CheckXPos(xPos + x);
						return;
					}
				}
			}

			if (*nextYPos != nowYPos)
			{
				int sign = ((*nextYPos < nowYPos) ? -1 : 1);
				for (int y = 0; y < KEY_POS_NUMBER_HEIGHT; y += sign)
				{
					if (KEY_POS_NUMBERS[CheckYPos(yPos + y)][*nextXPos] != KEY_POS_NUMBERS[nowYPos][nowXPos])
					{
						*nextXPos = CheckYPos(xPos + y);
						return;
					}
				}
			}

			assert(false);
		}
		else
		{
			*nextXPos = xPos;
			*nextYPos = yPos;
		}
	}
}

// 範囲外に行っていないかを確認する(X)
int SPDUINameSet::CheckXPos(int xPos)
{
	if (xPos < 0)
	{
		xPos = KEY_POS_NUMBER_WIDTH - 1;
	}
	else if (xPos >= KEY_POS_NUMBER_WIDTH)
	{
		xPos = 0;
	}

	return xPos;
}

// 範囲外に行っていないかを確認する(Y)
int SPDUINameSet::CheckYPos(int yPos)
{
	if (yPos < 0)
	{
		yPos = KEY_POS_NUMBER_HEIGHT - 1;
	}
	else if (yPos >= KEY_POS_NUMBER_HEIGHT)
	{
		yPos = 0;
	}

	return yPos;
}

// ナンバーにあった処理をする
void SPDUINameSet::SetNumberProcess(SetPlayerDataUI* parent, PROCESS_NUMBER number, bool flag)
{
	if ((char)number >= 0)
	{
		if (((int)number <= (int)PROCESS_NUMBER::SPACE) && (GetNameCount() <= 12/*最大文字数*/))
		{
			if ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION)) != 0)
			{
				if (((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK)) != 0) || ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT)) != 0))
				{
					if (FULL_CAPITAL_WORD[(int)number] != NULL)
					{
						if (msAddWord.size() > 0)
						{
							if (mnAddWordChangeNumber != 0)
							{
								mnAddWordChangeNumber = 0;
							}

							msAddWord.insert(mnAddWordSelectNumber, FULL_CAPITAL_WORD[(int)number]);
							mnAddWordSelectNumber += 2;
						}
						else
						{
							msSetName.insert(mnSetNameSelectNumber, FULL_CAPITAL_WORD[(int)number]);
							mnSetNameSelectNumber += 2;
						}
						msSelectWord.clear();
						mnSelectWordSelectNumber = 0;
					}
				}
				else
				{
					if (FULL_WORD[(int)number] != NULL)
					{
						if (msAddWord.size() > 0)
						{
							if (mnAddWordChangeNumber != 0)
							{
								mnAddWordChangeNumber = 0;
							}

							msAddWord.insert(mnAddWordSelectNumber, FULL_WORD[(int)number]);
							mnAddWordSelectNumber += 2;
						}
						else
						{
							msSetName.insert(mnSetNameSelectNumber, FULL_WORD[(int)number]);
							mnSetNameSelectNumber += 2;
						}
						msSelectWord.clear();
						mnSelectWordSelectNumber = 0;
					}
					/*
					switch (number)
					{
					case PROCESS_NUMBER::SPACE:
					case PROCESS_NUMBER::A:
					case PROCESS_NUMBER::I:
					case PROCESS_NUMBER::U:
					case PROCESS_NUMBER::E:
					case PROCESS_NUMBER::O:
						// ひらがな生成処理(もう一つ作るそれを変更中の文字列の代わりに表示する)mnAddWordChangeNumberは関数内で変更
						break;
					}*/
				}
			}
			else
			{
				if (((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK)) != 0) || ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT)) != 0))
				{
					if (HARF_CAPITAL_WORD[(int)number] != NULL)
					{
						if (msAddWord.size() > 0)
						{
							if (mnAddWordChangeNumber != 0)
							{
								mnAddWordChangeNumber = 0;
							}

							msAddWord.insert(mnAddWordSelectNumber, 1, HARF_CAPITAL_WORD[(int)number]);
							mnAddWordSelectNumber += 1;
						}
						else
						{
							msSetName.insert(mnSetNameSelectNumber, 1, HARF_CAPITAL_WORD[(int)number]);
							mnSetNameSelectNumber += 1;
						}
						msSelectWord.clear();
						mnSelectWordSelectNumber = 0;
					}
				}
				else
				{
					if (HARF_WORD[(int)number] != NULL)
					{
						if (msAddWord.size() > 0)
						{
							if (mnAddWordChangeNumber != 0)
							{
								mnAddWordChangeNumber = 0;
							}

							msAddWord.insert(mnAddWordSelectNumber, 1, HARF_WORD[(int)number]);
							mnAddWordSelectNumber += 1;
						}
						else
						{
							msSetName.insert(mnSetNameSelectNumber, 1, HARF_WORD[(int)number]);
							mnSetNameSelectNumber += 1;
						}
						msSelectWord.clear();
						mnSelectWordSelectNumber = 0;
					}
				}
			}
		}
	}
	else
	{
		switch (number)
		{
		case PROCESS_NUMBER::KEY_BOARD_FULL_HALF_WIDTH:
			if (flag)
			{
				//mucWordFlags |= ((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION);
			}
			else
			{
				//mucWordFlags &= ~((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION);
			}
			break;
		case PROCESS_NUMBER::FULL_HALF_WIDTH:
			//mucWordFlags ^= ((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION);
			break;

		case PROCESS_NUMBER::BACK_SPAE:
			if (msSelectWord.size() > 0)
			{
				msSelectWord.clear();
				mnSelectWordSelectNumber = 0;
			}
			else if (msAddWord.size() > 0)
			{
				if (mnAddWordSelectNumber > 0)
				{
					mnAddWordSelectNumber -= 1;
					msAddWord.erase(mnAddWordSelectNumber, 1);
				}
			}
			else if (msSetName.size() > 0)
			{
				if (mnSetNameSelectNumber > 0)
				{
					mnSetNameSelectNumber -= 1;
					msSetName.erase(mnSetNameSelectNumber, 1);
				}
			}
			break;

		case PROCESS_NUMBER::KEY_BOARD_INSERT:
			if (flag)
			{
				mucWordFlags |= ((unsigned char)1 << (int)WORD_FLAGS_BIT::INSERT);
			}
			else
			{
				mucWordFlags &= ~((unsigned char)1 << (int)WORD_FLAGS_BIT::INSERT);
			}
			break;
		case PROCESS_NUMBER::INSERT:
			mucWordFlags ^= ((unsigned char)1 << (int)WORD_FLAGS_BIT::INSERT);
			break;

		case PROCESS_NUMBER::HOME:
			if (msAddWord.size() > 0)
			{
				msAddWord.insert(mnAddWordSelectNumber, msSelectWord);
				mnAddWordSelectNumber = 0;
			}
			else
			{
				msSetName.insert(mnSetNameSelectNumber, msSelectWord);
				mnSetNameSelectNumber = 0;
			}
			msSelectWord.clear();
			mnSelectWordSelectNumber = 0;
			break;

		case PROCESS_NUMBER::TAB:
			for (int i = 0; i < 4; ++i)
			{
				SetNumberProcess(parent, PROCESS_NUMBER::SPACE, false);
			}
			break;

		case PROCESS_NUMBER::DELETE_PROCESS:
			if (msSelectWord.size() > 0)
			{
				msSelectWord.clear();
				mnSelectWordSelectNumber = 0;
			}
			else if (msAddWord.size() > 0)
			{
				if (msAddWord.size() > mnAddWordSelectNumber)
				{
					msAddWord.erase(mnAddWordSelectNumber, 1);
				}
				break;
			}
			else if (msSetName.size() > 0)
			{
				if (msSetName.size() > mnSetNameSelectNumber)
				{
					msSetName.erase(mnSetNameSelectNumber, 1);
				}
			}
			break;

		case PROCESS_NUMBER::END:
			if (msSelectWord.size() > 0)
			{
				if (msAddWord.size() > 0)
				{
					msAddWord.insert(mnAddWordSelectNumber, msSelectWord);
					mnAddWordSelectNumber += msSelectWord.size();
				}
				else
				{
					msSetName.insert(mnSetNameSelectNumber, msSelectWord);
					mnSetNameSelectNumber += msSelectWord.size();
				}
				msSelectWord.clear();
				mnSelectWordSelectNumber = 0;
			}
			else if (msAddWord.size() > 0)
			{
				mnAddWordSelectNumber = msAddWord.size();
			}
			else if (msSetName.size() > 0)
			{
				mnSetNameSelectNumber = msSetName.size();
			}
			break;

		case PROCESS_NUMBER::KEY_BOARD_CAPSLOCK:
			if (flag)
			{
				mucWordFlags |= ((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK);
			}
			else
			{
				mucWordFlags &= ~((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK);
			}
			break;
		case PROCESS_NUMBER::CAPSLOCK:
			mucWordFlags ^= ((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK);
			break;

		case PROCESS_NUMBER::ENTER:
			if (msSelectWord.size() > 0)
			{
				if (msAddWord.size() > 0)
				{
					msAddWord.insert(mnAddWordSelectNumber, msSelectWord);
					mnAddWordSelectNumber += msSelectWord.size();
				}
				else
				{
					msSetName.insert(mnSetNameSelectNumber, msSelectWord);
					mnSetNameSelectNumber += msSelectWord.size();
				}
				msSelectWord.clear();
				mnSelectWordSelectNumber = 0;
			}
			else if (msAddWord.size() > 0)
			{
				msSetName.insert(mnSetNameSelectNumber, msAddWord);
				mnSetNameSelectNumber += msAddWord.size();
				msAddWord.clear();
				mnAddWordSelectNumber = 0;
			}
			else
			{
				if (msSetName.size() > 0)
				{
					{// 名前入力
						std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
						mpDataManager->SetPlayerName(parent->GetSelectPlayerNumber(), msSetName);
					}
					// 次に移動
					parent->Decision();
				}
			}
			break;

		case PROCESS_NUMBER::KEY_BOARD_ALT:
			if (flag)
			{
				mucWordFlags |= ((unsigned char)1 << (int)WORD_FLAGS_BIT::ALT);
			}
			else
			{
				mucWordFlags &= ~((unsigned char)1 << (int)WORD_FLAGS_BIT::ALT);
			}
			break;
		case PROCESS_NUMBER::ALT:
			mucWordFlags ^= ((unsigned char)1 << (int)WORD_FLAGS_BIT::ALT);
			break;

		case PROCESS_NUMBER::KEY_BOARD_SHIFT:
			if (flag)
			{
				mucWordFlags |= ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT);
			}
			else
			{
				mucWordFlags &= ~((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT);
			}
			break;
		case PROCESS_NUMBER::SHIFT:
			mucWordFlags ^= ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT);
			break;

		case PROCESS_NUMBER::LETF:
			if ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT)) != 0)
			{
				if ((msSelectWord.size() == mnSelectWordSelectNumber) && (msSelectWord.size() > 0))
				{
					if (mnSelectWordSelectNumber > 0)
					{
						mnSelectWordSelectNumber -= 1;
						if (msAddWord.size() > 0)
						{
							msAddWord.insert(mnAddWordSelectNumber, 1, msSelectWord[mnSelectWordSelectNumber]);
						}
						else
						{
							msSetName.insert(mnSetNameSelectNumber, 1, msSelectWord[mnSelectWordSelectNumber]);
						}
						msSelectWord.pop_back();
					}
				}
				else
				{
					if (msAddWord.size() > 0)
					{
						if (mnAddWordSelectNumber > 0)
						{
							mnAddWordSelectNumber -= 1;
							msSelectWord.insert(mnSelectWordSelectNumber, 1, msAddWord[mnAddWordSelectNumber]);
							msAddWord.erase(mnAddWordSelectNumber, 1);
						}
					}
					else
					{
						if (mnSetNameSelectNumber > 0)
						{
							mnSetNameSelectNumber -= 1;
							msSelectWord.insert(mnSelectWordSelectNumber, 1, msSetName[mnSetNameSelectNumber]);
							msSetName.erase(mnSetNameSelectNumber, 1);
						}
					}
				}
			}
			else
			{
				if (msSelectWord.size() > 0)
				{
					if (msAddWord.size() > 0)
					{
						msAddWord.insert(mnAddWordSelectNumber, msSelectWord);
					}
					else
					{
						msSetName.insert(mnSetNameSelectNumber, msSelectWord);
					}
					msSelectWord.clear();
					mnSelectWordSelectNumber = 0;
				}
				else
				{
					if (msAddWord.size() > 0)
					{
						if (mnAddWordSelectNumber > 0)
						{
							mnAddWordSelectNumber -= 1;
						}
					}
					else
					{
						if (mnSetNameSelectNumber > 0)
						{
							mnSetNameSelectNumber -= 1;
						}
					}
				}
			}
			break;

		case PROCESS_NUMBER::RIGHT:
			if ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT)) != 0)
			{
				if (msSelectWord.size() == mnSelectWordSelectNumber)
				{
					if (msAddWord.size() > 0)
					{
						if (msAddWord.size() > mnAddWordSelectNumber)
						{
							msSelectWord.insert(mnSelectWordSelectNumber, 1, msAddWord[mnAddWordSelectNumber]);
							mnSelectWordSelectNumber += 1;
						}
					}
					else
					{
						if (msSetName.size() > mnSetNameSelectNumber)
						{
							msSelectWord.insert(mnSelectWordSelectNumber, 1, msSetName[mnSetNameSelectNumber]);
							mnSelectWordSelectNumber += 1;
						}
					}
				}
				else
				{
					if (msAddWord.size() > 0)
					{
						msAddWord.insert(mnAddWordSelectNumber, 1, msSelectWord[mnSelectWordSelectNumber]);
						mnAddWordSelectNumber += 1;
					}
					else
					{
						msSetName.insert(mnSetNameSelectNumber, 1, msSelectWord[mnSelectWordSelectNumber]);
						mnSetNameSelectNumber += 1;
					}
					msSelectWord.erase(mnSelectWordSelectNumber, 1);
				}
			}
			else
			{
				if (msSelectWord.size() > 0)
				{
					if (msAddWord.size() > 0)
					{
						msAddWord.insert(mnAddWordSelectNumber, msSelectWord);
						mnAddWordSelectNumber += msSelectWord.size();
					}
					else
					{
						msSetName.insert(mnSetNameSelectNumber, msSelectWord);
						mnSetNameSelectNumber += msSelectWord.size();
					}
					msSelectWord.clear();
					mnSelectWordSelectNumber = 0;
				}
				else
				{
					if (msAddWord.size() > 0)
					{
						if (msAddWord.size() > mnAddWordSelectNumber)
						{
							mnAddWordSelectNumber += 1;
						}
					}
					else
					{
						if (msSetName.size() > mnSetNameSelectNumber)
						{
							mnSetNameSelectNumber += 1;
						}
					}
				}
			}
			break;

		}
	}
}

// ナンバーにあった処理をする
void SPDUINameSet::SetNumberProcess(SetPlayerDataUI* parent, int number, bool flag)
{
	for (int y = 0; y < (KEY_POS_NUMBER_HEIGHT - 1); y++)
	{
		for (int x = 0; x < KEY_POS_NUMBER_WIDTH; x++)
		{
			if (KEY_POS_NUMBERS[y][x] == (char)number)
			{
				mnSelectNumberY = y;
				mnSelectNumberX = x;
				SetNumberProcess(parent, (PROCESS_NUMBER)number, flag);
				return;
			}
		}
	}

	if ((int)PROCESS_NUMBER::SPACE == number)
	{
		mnSelectNumberY = 4;
		mnSelectNumberX = 0;
		SetNumberProcess(parent, (PROCESS_NUMBER)number, flag);
		return;
	}

	if ((int)PROCESS_NUMBER::KEY_BOARD_FULL_HALF_WIDTH == number)
	{
		mnSelectNumberY = 0;
		mnSelectNumberX = 0;
		SetNumberProcess(parent, (PROCESS_NUMBER)number, flag);
		return;
	}

	if ((int)PROCESS_NUMBER::KEY_BOARD_SHIFT == number)
	{
		mnSelectNumberY = 3;
		mnSelectNumberX = 0;
		SetNumberProcess(parent, (PROCESS_NUMBER)number, flag);
		return;
	}

	if ((int)PROCESS_NUMBER::KEY_BOARD_CAPSLOCK == number)
	{
		mnSelectNumberY = 2;
		mnSelectNumberX = 0;
		SetNumberProcess(parent, (PROCESS_NUMBER)number, flag);
		return;
	}

	if ((int)PROCESS_NUMBER::KEY_BOARD_INSERT == number)
	{
		mnSelectNumberY = 0;
		mnSelectNumberX = 15;
		SetNumberProcess(parent, (PROCESS_NUMBER)number, flag);
		return;
	}

	if ((int)PROCESS_NUMBER::KEY_BOARD_ALT == number)
	{
		mnSelectNumberY = 2;
		mnSelectNumberX = 15;
		SetNumberProcess(parent, (PROCESS_NUMBER)number, flag);
		return;
	}
}


std::wstring SPDUINameSet::GetWordName(char number, FontData* fontData)
{
	std::wstring wordName = L"";

	if (number >= 0)
	{
		if ((int)number < (int)PROCESS_NUMBER::SPACE)
		{
			if ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION)) != 0)
			{
				if (((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK)) != 0) || ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT)) != 0))
				{
					wordName = FULL_CAPITAL_WORD[(int)number];
				}
				else
				{
					wordName = FULL_WORD[(int)number];
				}
			}
			else
			{
				if (((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK)) != 0) || ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT)) != 0))
				{
					wordName = HARF_CAPITAL_WORD[(int)number];
				}
				else
				{
					wordName = HARF_WORD[(int)number];
				}
			}
		}
		else
		{
			wordName = L"SPACE";
		}

		return wordName;
	}

	switch ((PROCESS_NUMBER)number)
	{
	case PROCESS_NUMBER::FULL_HALF_WIDTH:
		fontData->fontSize = 20.0f;
		if ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION)) != 0)
		{
			//wordName = L"HALF";
		}
		else
		{
			//wordName = L"FULL";
		}
		break;

	case PROCESS_NUMBER::BACK_SPAE:
		fontData->fontSize = 10.0f;
		wordName = L"BACK SPAE";
		break;

	case PROCESS_NUMBER::INSERT:
		fontData->fontSize = 15.0f;
		wordName = L"INSERT";
		break;

	case PROCESS_NUMBER::HOME:
		fontData->fontSize = 15.0f;
		wordName = L"HOME";
		break;

	case PROCESS_NUMBER::TAB:
		fontData->fontSize = 20.0f;
		wordName = L"TAB";
		break;

	case PROCESS_NUMBER::DELETE_PROCESS:
		fontData->fontSize = 15.0f;
		wordName = L"DELETE";
		break;

	case PROCESS_NUMBER::END:
		fontData->fontSize = 20.0f;
		wordName = L"END";
		break;

	case PROCESS_NUMBER::CAPSLOCK:
		fontData->fontSize = 10.0f;
		wordName = L"CAPSLOCK";
		break;

	case PROCESS_NUMBER::ENTER:
		fontData->fontSize = 20.0f;
		if ((msAddWord.size() + msSelectWord.size() + msSetName.size()) == 0)
		{
			fontData->Color.a = 0.7f;
		}
		wordName = L"ENTER";
		break;

	case PROCESS_NUMBER::ALT:
		fontData->fontSize = 20.0f;
		wordName = L"ALT";
		break;

	case PROCESS_NUMBER::SHIFT:
		fontData->fontSize = 20.0f;
		wordName = L"SHIFT";
		break;

	case PROCESS_NUMBER::LETF:
		fontData->fontSize = 20.0f;
		wordName = L"←";
		break;

	case PROCESS_NUMBER::RIGHT:
		fontData->fontSize = 20.0f;
		wordName = L"→";
		break;
	}
	mpResourceManager->SetFontData(fontData);

	return wordName;
}

// 描画
void SPDUINameSet::Draw(SetPlayerDataUI* parent)
{
	mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * 0.1325f, mpDataManager->GetDisplaySize().Y * 0.14f,
		mpDataManager->GetDisplaySize().X * 0.055f, mpDataManager->GetDisplaySize().Y * 0.07f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);

	FontData fontData = FontData();
	fontData.fontSize = 40.0f;
	fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_BOLD;
	mpResourceManager->SetFontData(&fontData);
	mpResourceManager->DrawString(std::to_string(parent->GetSelectPlayerNumber() + 1) + "P", XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.13f, mpDataManager->GetDisplaySize().Y * 0.13f), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

	fontData = FontData();
	mpResourceManager->SetFontData(&fontData);

	float setNumberX = 0.05f;
	float setNumberY = 0.1f;

	std::wstring draw;
	for (int y = 0; y < (KEY_POS_NUMBER_HEIGHT - 1); y++)
	{
		for (int x = 0; x < KEY_POS_NUMBER_WIDTH; x++)
		{
			if (
				(((y == 1) || (y == 2)) && ((x == 13) || (x == 14))) ||// エンター
				((y == 3) && ((x == 12) || (x == 13) || (x == 14))) ||// シフト
				((y == 2) && ((x == 15) || (x == 16)))// オルト
				)
			{
				continue;
			}

			if ((mnSelectNumberY == y) && (mnSelectNumberX == x))
			{
				mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (x * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (y * setNumberY)),
					mpDataManager->GetDisplaySize().X * 0.049f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);
			}
			else
			{
				mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (x * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (y * setNumberY)),
					mpDataManager->GetDisplaySize().X * 0.049f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
			}
			

			draw = GetWordName(KEY_POS_NUMBERS[y][x], &fontData);
			mpResourceManager->DrawString(draw, XMFLOAT2(mpDataManager->GetDisplaySize().X * (0.1f + (x * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.35f + (y * setNumberY))), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

			fontData = FontData();
			mpResourceManager->SetFontData(&fontData);
		}
	}

	{// エンター

		if (((mnSelectNumberY == 1) || (mnSelectNumberY == 2)) && ((mnSelectNumberX == 13) || (mnSelectNumberX == 14)))
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (13.5f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (1.5f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.099f, mpDataManager->GetDisplaySize().Y * 0.19f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);
		}
		else
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (13.5f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (1.5f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.099f, mpDataManager->GetDisplaySize().Y * 0.19f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
		}

		fontData = FontData();
		fontData.fontSize = 35.0f;
		fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;
		if (GetNameCount() <= 0)
		{
			fontData.Color.a = 0.5f;
		}
		mpResourceManager->SetFontData(&fontData);

		draw = L"ENTER";
		mpResourceManager->DrawString(draw, XMFLOAT2(mpDataManager->GetDisplaySize().X * (0.1f + (13.45f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.35f + (1.53f * setNumberY))), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

		fontData = FontData();
		mpResourceManager->SetFontData(&fontData);
	}

	{// シフト

		if ((mnSelectNumberY == 3) && ((mnSelectNumberX == 12) || (mnSelectNumberX == 13) || (mnSelectNumberX == 14)))
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (13.0f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (3.0f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.149f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);
		}
		else
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (13.0f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (3.0f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.149f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
		}

		fontData = FontData();
		fontData.fontSize = 45.0f;
		fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;
		mpResourceManager->SetFontData(&fontData);

		draw = L"SHIFT";
		mpResourceManager->DrawString(draw, XMFLOAT2(mpDataManager->GetDisplaySize().X * (0.1f + (13.0f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.35f + (3.01f * setNumberY))), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

		fontData = FontData();
		mpResourceManager->SetFontData(&fontData);
	}

	{// オルト

		if ((mnSelectNumberY == 2) && ((mnSelectNumberX == 15) || (mnSelectNumberX == 16)))
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (15.5f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (2.0f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.099f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);
		}
		else
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (15.5f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (2.0f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.099f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
		}

		fontData = FontData();
		fontData.fontSize = 45.0f;
		fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;
		mpResourceManager->SetFontData(&fontData);

		draw = L"ALT";
		mpResourceManager->DrawString(draw, XMFLOAT2(mpDataManager->GetDisplaySize().X * (0.1f + (15.5f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.35f + (2.01f * setNumberY))), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

		fontData = FontData();
		mpResourceManager->SetFontData(&fontData);
	}

	{// スペース

		if (mnSelectNumberY == 4)
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (8.0f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (4.0f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.849f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[0], MIDDLE_FLAG);
		}
		else
		{
			mpResourceManager->DrawSprite(mpDataManager->GetDisplaySize().X * (0.1f + (8.0f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.37f + (4.0f * setNumberY)),
				mpDataManager->GetDisplaySize().X * 0.849f, mpDataManager->GetDisplaySize().Y * 0.09f, 0.0f, 1.0f, 0.0f, 1.0f, mnResourceIDs[1], MIDDLE_FLAG);
		}

		fontData = FontData();
		fontData.fontSize = 45.0f;
		fontData.fontWeight = DWRITE_FONT_WEIGHT::DWRITE_FONT_WEIGHT_THIN;
		mpResourceManager->SetFontData(&fontData);

		draw = L"SPACE";
		mpResourceManager->DrawString(draw, XMFLOAT2(mpDataManager->GetDisplaySize().X * (0.1f + (8.0f * setNumberX)), mpDataManager->GetDisplaySize().Y * (0.35f + (4.01f * setNumberY))), D2D1_DRAW_TEXT_OPTIONS_NONE, MIDDLE_FLAG, fontData.fontSize);

		fontData = FontData();
		mpResourceManager->SetFontData(&fontData);
	}


	std::wstring drawString = L"Name: " + msSetName.substr(0, mnSetNameSelectNumber) + msAddWord.substr(0, mnAddWordSelectNumber) + msSelectWord + msAddWord.substr(mnAddWordSelectNumber) + msSetName.substr(mnSetNameSelectNumber);

	fontData = FontData();
	fontData.fontSize = 40.0f;
	mpResourceManager->SetFontData(&fontData);
	mpResourceManager->DrawString(drawString, XMFLOAT2(mpDataManager->GetDisplaySize().X * 0.2f, mpDataManager->GetDisplaySize().Y * 0.15f), D2D1_DRAW_TEXT_OPTIONS_NONE);
}