#pragma once
#include <iostream>
#include <string>
#include <vector>

#include "IState.h"
#include "TemplateData.h"

class SetPlayerDataUI;

enum SET_PLAYER_DATA_UI_STATE
{
	SET_PLAYER_DATA_UI_STATE_PLAYER_NUMBER,
	SET_PLAYER_DATA_UI_STATE_CONTROLLER_SELECT,
	SET_PLAYER_DATA_UI_STATE_CHARACTER_SELECT,
	SET_PLAYER_DATA_UI_STATE_NAME_SET,
};


/*----------------------------------------------------------------------------------------------------*/
/*　【プレイヤー数選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
class SPDUIPlayerNumber : public IState_SetPlayerDataUI
{
private:
	// 設定最大プレイヤー数
	static constexpr int PLAYER_MAX = 5;

	// プレイヤーデータ
	std::vector<PlayerData> mstPlayerDatas;

public:
	SPDUIPlayerNumber();
	virtual ~SPDUIPlayerNumber() = default;

	/*この状態に入った時の処理*/
	int OnEnter(SetPlayerDataUI* parent) override;
	/*この状態を出る時の処理*/
	void OnExit(SetPlayerDataUI* parent) override;
	/*マウス更新*/
	int MouseUpdate(SetPlayerDataUI* parent) override;
	/*キーボード更新*/
	int KeyboardUpdate(SetPlayerDataUI* parent) override;
	/*コントローラー更新*/
	int ControllerUpdate(SetPlayerDataUI* parent) override;
	/*キーボードとコントローラー更新*/
	int Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent) override;

	/*描画*/
	void Draw(SetPlayerDataUI* parent) override;
};


/*----------------------------------------------------------------------------------------------------*/
/*　【コントローラー選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
class SPDUIControllerSelect : public IState_SetPlayerDataUI
{
public:
	SPDUIControllerSelect();
	virtual ~SPDUIControllerSelect() = default;

	/*この状態に入った時の処理*/
	int OnEnter(SetPlayerDataUI* parent) override;
	/*この状態を出る時の処理*/
	void OnExit(SetPlayerDataUI* parent) override;
	/*マウス更新*/
	int MouseUpdate(SetPlayerDataUI* parent) override;
	/*キーボード更新*/
	int KeyboardUpdate(SetPlayerDataUI* parent) override;
	/*コントローラー更新*/
	int ControllerUpdate(SetPlayerDataUI* parent) override;
	/*キーボードとコントローラー更新*/
	int Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent) override;

	/*描画*/
	void Draw(SetPlayerDataUI* parent) override;
};


/*----------------------------------------------------------------------------------------------------*/
/*　【キャラクター選択状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
class SPDUICharacterSelect : public IState_SetPlayerDataUI
{
public:
	SPDUICharacterSelect();
	virtual ~SPDUICharacterSelect() = default;

	/*この状態に入った時の処理*/
	int OnEnter(SetPlayerDataUI* parent) override;
	/*この状態を出る時の処理*/
	void OnExit(SetPlayerDataUI* parent) override;
	/*マウス更新*/
	int MouseUpdate(SetPlayerDataUI* parent) override;
	/*キーボード更新*/
	int KeyboardUpdate(SetPlayerDataUI* parent) override;
	/*コントローラー更新*/
	int ControllerUpdate(SetPlayerDataUI* parent) override;
	/*キーボードとコントローラー更新*/
	int Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent) override;

	/*描画*/
	void Draw(SetPlayerDataUI* parent) override;
};


/*----------------------------------------------------------------------------------------------------*/
/*　【名前設定状態】　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　*/
/*----------------------------------------------------------------------------------------------------*/
class SPDUINameSet : public IState_SetPlayerDataUI
{
private:
	// 設定用 名前
	std::wstring msSetName;
	// 追加文字
	std::wstring msAddWord;
	// 選択文字
	std::wstring msSelectWord;
	// 設定用名前 選択中箇所
	int mnSetNameSelectNumber;
	// 追加文字 選択中箇所
	int mnAddWordSelectNumber;
	// 選択中文字 選択中箇所
	int mnSelectWordSelectNumber;

	// 追加文字の変更種類設定用
	int mnAddWordChangeNumber;

	// 最大文字数
	const int NAME_MAX = 10;

	// 選択数X
	int mnSelectNumberX;
	// 選択数Y
	int mnSelectNumberY;

	// 全文字数
	static constexpr int WORD_MAX = 49;
	// 半角文字
	static constexpr wchar_t HARF_WORD[49] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ':', ';', ',', '-', '.', '/', '@','[','\\',']', '^','\\', ' ' };
	static constexpr wchar_t HARF_CAPITAL_WORD[49] = { NULL, '!', '"', '#', '$', '%', '&', '\'', '(', ')', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '*', '+', '<', '=', '>', '?', '`', '{', '|', '}', '~', '_' , ' ' };
	// 全角文字
	static constexpr wchar_t FULL_WORD[49][2] = { L"０", L"１", L"２", L"３", L"４", L"５", L"６", L"７", L"８", L"９", L"ａ", L"ｂ", L"ｃ", L"ｄ", L"ｅ", L"ｆ", L"ｇ", L"ｈ", L"ｉ", L"ｊ", L"ｋ", L"ｌ", L"ｍ", L"ｎ", L"ｏ", L"ｐ", L"ｑ", L"ｒ", L"ｓ", L"ｔ", L"ｕ", L"ｖ", L"ｗ", L"ｘ", L"ｙ", L"ｚ", L"：", L"；", L"、", L"ー", L"。", L"・", L"＠", L"「" ,L"￥", L"」", L"＾", L"￥", L"　" };
	static constexpr wchar_t FULL_CAPITAL_WORD[49][2] = { {(const wchar_t)NULL, (const wchar_t)NULL}, L"！", L"”", L"＃", L"＄", L"％", L"＆", L"’", L"（", L"）", L"Ａ", L"Ｂ", L"Ｃ", L"Ｄ", L"Ｅ", L"Ｆ", L"Ｇ", L"Ｈ", L"Ｉ", L"Ｊ", L"Ｋ", L"Ｌ", L"Ｍ", L"Ｎ", L"Ｏ", L"Ｐ", L"Ｑ", L"Ｒ", L"Ｓ", L"Ｔ", L"Ｕ", L"Ｖ", L"Ｗ", L"Ｘ", L"Ｙ", L"Ｚ", L"＊", L"＋", L"＜", L"＝", L"＞", L"？", L"‘", L"｛", L"｜", L"｝", L"～", L"＿", L" "
};
	
	//[49 + 半角/全角 + tab + capslock + shift + backspae + enter + left(シフト) + right(シフト) + home + end + insert + delete + alt] = [62]
	static constexpr int KEY_POS_NUMBER_WIDTH = 17;
	static constexpr int KEY_POS_NUMBER_HEIGHT = 5;
	// プロセスナンバー
	enum class PROCESS_NUMBER : char
	{
		KEY_BOARD_FULL_HALF_WIDTH = -18,
		KEY_BOARD_SHIFT = -17,
		KEY_BOARD_CAPSLOCK = -16,
		KEY_BOARD_INSERT = -15,
		KEY_BOARD_ALT = -14,
		FULL_HALF_WIDTH = -13,
		BACK_SPAE,
		INSERT,
		HOME,
		TAB,
		DELETE_PROCESS,
		END,
		CAPSLOCK,
		ENTER,
		ALT,// パソコンの押したあと移動なくす、追加文字の入れる場所を左右に移動できるようにする、その他思いつけば
		SHIFT,
		LETF, // パソコンはSHIFTと同時に押すと反応する
		RIGHT, // パソコンはSHIFTと同時に押すと反応する
		_0 = 0,	_1,	_2,	_3,	_4,	_5,	_6,	_7,	_8,	_9,
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		COLON, SENI_COLON, COMMA,          HYPHEN,   PERIOD,
		SLASH, AT_SIGN,    SQUARE_BRACKET, YEN_SIGN, SQUARE_BRACKET_CLOSE,
		CARET, BACK_SLASH, SPACE,
	};
	static constexpr char KEY_POS_NUMBERS[5][17] =
	{
		{/*"半角/全角", '1' ～ '|', backspae, insert, home (キーボード)*/ (char)PROCESS_NUMBER::FULL_HALF_WIDTH/*半角/全角*/, 1,  2,  3,  4,  5,  6, 7,   8,  9,  0, 39, 46,                                   44,                                               (char)PROCESS_NUMBER::BACK_SPAE/*backspae*/,   (char)PROCESS_NUMBER::INSERT/*insert*/,                (char)PROCESS_NUMBER::HOME/*home*/},
		            {/*tab, 'Q' ～ '{', enter, delete, end (キーボード)*/ (char)PROCESS_NUMBER::TAB/*tab*/,                  26, 32, 14, 27, 29, 34, 30, 18, 24, 25, 42, 43,                                   (char)PROCESS_NUMBER::ENTER/*enter*/,             (char)PROCESS_NUMBER::ENTER/*enter*/,          (char)PROCESS_NUMBER::DELETE_PROCESS/*delete*/,        (char)PROCESS_NUMBER::END/*end*/},
		              {/* capslock, 'A' ～ '}', enter, alt (キーボード)*/ (char)PROCESS_NUMBER::CAPSLOCK/*capslock*/,        10, 28, 13, 15, 16, 17, 19, 20, 21, 37, 36, 45,                                   (char)PROCESS_NUMBER::ENTER/*enter*/,             (char)PROCESS_NUMBER::ENTER/*enter*/,          (char)PROCESS_NUMBER::ALT/*alt*/,                    (char)PROCESS_NUMBER::ALT/*alt*/},
		{/* shift, 'Z' ～ '\', left(シフト), right(シフト) (キーボード)*/ (char)PROCESS_NUMBER::SHIFT/*shift*/,              35, 33, 12, 31, 11, 23, 22, 38, 40, 41, 47, (char)PROCESS_NUMBER::SHIFT/*shift*/, (char)PROCESS_NUMBER::SHIFT/*shift*/,             (char)PROCESS_NUMBER::SHIFT/*shift*/,          (char)PROCESS_NUMBER::LETF/*left(シフト)*/,            (char)PROCESS_NUMBER::RIGHT/*right(シフト)*/},
		                                                       {/*space*/ 48,                                                48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48, 48,                                   48,                                               48,                                            48,                                                    48},
	};


	// ワードフラグ enum
	enum class WORD_FLAGS_BIT
	{
		// フォント変換フラグ(「1」全角「0」半角)
		FONT_CONVERSION = (char)1 << 0,
		// シフト
		SHIFT =     (char)1 << 1,
		// キャプスロック
		CAPS_LOCK = (char)1 << 2,
		// インサート
		INSERT =    (char)1 << 3,
		// オルト
		ALT =      (char)1 << 4,
	};
	// ワードフラグ
	unsigned char mucWordFlags;

	// リソースID
	std::vector<int> mnResourceID;

public:
	SPDUINameSet();
	virtual ~SPDUINameSet() = default;

	/*この状態に入った時の処理*/
	int OnEnter(SetPlayerDataUI* parent) override;
	/*この状態を出る時の処理*/
	void OnExit(SetPlayerDataUI* parent) override;
	/*マウス更新*/
	int MouseUpdate(SetPlayerDataUI* parent) override;
	/*キーボード更新*/
	int KeyboardUpdate(SetPlayerDataUI* parent) override;
	/*コントローラー更新*/
	int ControllerUpdate(SetPlayerDataUI* parent) override;
	/*キーボードとコントローラー更新*/
	int Keyboard_And_ControllerUpdate(SetPlayerDataUI* parent) override;

	/*描画*/
	void Draw(SetPlayerDataUI* parent) override;

private:
	/*次のポジションを取得する*/
	void GetNextPos(int* nextXPos, int* nextYPos, int nowXPos, int nowYPos);

	/*範囲外に行っていないかを確認する(X)*/
	int CheckXPos(int xPos);
	/*範囲外に行っていないかを確認する(Y)*/
	int CheckYPos(int yPos);

	/*ナンバーにあった処理をする*/
	void SetNumberProcess(SetPlayerDataUI* parent, PROCESS_NUMBER number, bool flag = true);
	void SetNumberProcess(SetPlayerDataUI* parent, char number, bool flag = true) { SetNumberProcess(parent, (PROCESS_NUMBER)number, flag); }
	void SetNumberProcess(SetPlayerDataUI* parent, int number, bool flag = true) { SetNumberProcess(parent, (PROCESS_NUMBER)number, flag); }

	std::wstring GetWordName(char number, FLOAT* fontSize);

	// 追加文字を変換する
	void ChangeAddWord();

	// ひらがなになるなら「true」を返す
	bool CheckAddWordChangeHiragana();

	// ひらがなにする

};