#include <iostream>
#include <string>

//#include <imm.h>


#include "../Header/DataManager.h"
#include "../Header/KeyState.h"
#include "../Header/Master.h"
#include "../Header/State_SetPlayerDataUI.h"
#include "../Header/TemplateData.h"
#include "../Header/UIs.h"

//#pragma comment(lib, "imm32.lib")

/*----------------------------------------------------------------------------------------------------*/
/*　【プレイヤー数選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
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
	Master::mpDataManager->SetPlayerData(mstPlayerDatas);
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
int SPDUIPlayerNumber::ControllerUpdate(SetPlayerDataUI* parent){ return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER; }
// キーボードとコントローラー更新
int SPDUIPlayerNumber::Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent)
{
	if (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::UP))
	{
		parent->Up();
	}
	if (mpKeyState->GetKeyAllController(CONTROLLER_KEY_TYPE::DOWN))
	{
		parent->Down();
	}

	if (mpKeyState->GetKeyDownAllController(CONTROLLER_KEY_TYPE::A, false))
	{
		return SET_PLAYER_DATA_UI_STATE_CONTROLLER_SELECT;
	}
	return SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER;
}


/*----------------------------------------------------------------------------------------------------*/
/*　【コントローラー選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
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


/*----------------------------------------------------------------------------------------------------*/
/*　【キャラクター選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
// この状態に入った時の処理
int SPDUICharacterSelect::OnEnter(SetPlayerDataUI* parent)
{
	parent->SetSelectMaxNumber((int)CHARACTER_TYPE::MAX);
	parent->SetSelectNumber(0);

	return -1;
}
// この状態を出る時の処理
void SPDUICharacterSelect::OnExit(SetPlayerDataUI* parent)
{
	Master::mpDataManager->SetPlayerType(parent->GetSelectPlayerNumber(), parent->GetSelectNumber());
}
// マウス更新
int SPDUICharacterSelect::MouseUpdate(SetPlayerDataUI* parent)
{
	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;
}
// キーボード更新
int SPDUICharacterSelect::KeyboardUpdate(SetPlayerDataUI* parent){	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;}
// コントローラー更新
int SPDUICharacterSelect::ControllerUpdate(SetPlayerDataUI* parent){ return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT; }
// キーボードとコントローラー更新
int SPDUICharacterSelect::Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent)
{
	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::UP, parent->GetSelectPlayerNumber()))
	{
		parent->Up();
	}
	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::DOWN, parent->GetSelectPlayerNumber()))
	{
		parent->Down();
	}

	if (mpKeyState->GetKeyDown_Controller(CONTROLLER_KEY_TYPE::A, parent->GetSelectPlayerNumber()))
	{
		return SET_PLAYER_DATA_UI_STATE_NAME_SET;
	}

	return SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT;
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
	if (Master::mpDataManager->GetPlayerKeyNumber(parent->GetSelectPlayerNumber()) == (int)CONTROLLER_KEY_NUMBER::KEY_BOARD)
	{
		unsigned long long keyBoradFlags = (mpKeyState->GetDownWordKeyFlags_Board() & 0xfffffffff);
		// 押してるワードに反応する
		if (keyBoradFlags != 0)
		{
			for (int i = 0; i < WORD_MAX; i++)
			{
				if (mpKeyState->GetWordKeyDown_Board(i))
				{
					// 位置を設定


					SetNumberProcess(i);
				}
			}
		}
	}

	return SET_PLAYER_DATA_UI_STATE_NAME_SET;
}
// コントローラー更新
int SPDUINameSet::ControllerUpdate(SetPlayerDataUI* parent)
{
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
void SPDUINameSet::SetNumberProcess(PROCESS_NUMBER number, bool flag)
{
	if ((char)number >= 0)
	{
		if ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION)) != 0)
		{
			if (msAddWord.size() > 0)
			{
				switch (number)
				{
				case PROCESS_NUMBER::SPACE:
					// msAddWord 変換処理
					break;

				case PROCESS_NUMBER::A:
				case PROCESS_NUMBER::I:
				case PROCESS_NUMBER::U:
				case PROCESS_NUMBER::E:
				case PROCESS_NUMBER::O:
					// ひらがな生成処理
					break;
				}
			}
		}
		else
		{
			if ((int)number <= (int)PROCESS_NUMBER::SPACE)
			{
				if (((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::CAPS_LOCK)) != 0) || ((mucWordFlags & ((unsigned char)1 << (int)WORD_FLAGS_BIT::SHIFT)) != 0))
				{
					if (HARF_CAPITAL_WORD[(int)number] != NULL)
					{
						if (msAddWord.size() > 0)
						{
							msAddWord.insert(mnAddWordSelectNumber, 1, HARF_CAPITAL_WORD[(int)number]);
							mnAddWordSelectNumber += 1;
							mnAddWordChangeNumber = 0;
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
							msAddWord.insert(mnAddWordSelectNumber, 1, HARF_WORD[(int)number]);
							mnAddWordSelectNumber += 1;
							mnAddWordChangeNumber = 0;
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
			mucWordFlags &= ~((unsigned char)(flag ? 1 : 0) << (int)WORD_FLAGS_BIT::FONT_CONVERSION);
			break;
		case PROCESS_NUMBER::FULL_HALF_WIDTH:
			mucWordFlags ^= ((unsigned char)1 << (int)WORD_FLAGS_BIT::FONT_CONVERSION);
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
			mucWordFlags &= ~((unsigned char)(flag ? 1 : 0) << (int)WORD_FLAGS_BIT::INSERT);
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
				SetNumberProcess(PROCESS_NUMBER::SPACE, false);
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
			mucWordFlags &= ~((unsigned char)(flag ? 1 : 0) << (int)WORD_FLAGS_BIT::CAPS_LOCK);
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
				// 次に移動
			}
			break;

		case PROCESS_NUMBER::KEY_BOARD_ALT:
			mucWordFlags &= ~((unsigned char)(flag ? 1 : 0) << (int)WORD_FLAGS_BIT::ALT);
			break;
		case PROCESS_NUMBER::ALT:
			mucWordFlags ^= ((unsigned char)1 << (int)WORD_FLAGS_BIT::ALT);
			break;

		case PROCESS_NUMBER::KEY_BOARD_SHIFT:
			mucWordFlags &= ~((unsigned char)(flag ? 1 : 0) << (int)WORD_FLAGS_BIT::SHIFT);
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