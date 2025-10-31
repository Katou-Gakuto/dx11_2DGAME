#pragma once
#include <Windows.h>
#include "TemplateData.h"

/*--------------------------------------------------------------------------------------------------------------
* フラグの種類(使ってないのもある)
*/
enum class FLAG_TYPE
{
	/*現在の状態*/
	NOW,
	/*押した始めた*/
	DOWN,
	/*離した*/
	UP,

	/*最大*/
	MAX
};


/*--------------------------------------------------------------------------------------------------------------
* コントローラーキーの種類
*/
enum class CONTROLLER_KEY_TYPE
{
	/*有無*/
	EXISTENCE = 0,

	/*Aボタン*/
	A,
	/*Bボタン*/
	B,
	/*Xボタン*/
	X,
	/*Yボタン*/
	Y,

	/*Lボタン(左トリガー)*/
	L,
	/*LTボタン(左奥トリガー)*/
	LT,
	/*Rボタン(右トリガー)*/
	R,
	/*RTボタン(右奥トリガー)*/
	RT,

	/*左ボタン*/
	LEFT,
	/*右ボタン*/
	RIGHT,
	/*上ボタン*/
	UP,
	/*下ボタン*/
	DOWN,

	/*左(左スティック)*/
	LEFT_STICK_LEFT,
	/*右(左スティック)*/
	LEFT_STICK_RIGHT,
	/*上(左スティック)*/
	LEFT_STICK_UP,
	/*下(左スティック)*/
	LEFT_STICK_DOWN,
	/*押し込み(左スティック)*/
	LEFT_STICK_PUSH,

	/*左(右スティック)*/
	RIGHT_STICK_LEFT,
	/*右(右スティック)*/
	RIGHT_STICK_RIGHT,
	/*上(右スティック)*/
	RIGHT_STICK_UP,
	/*下(右スティック)*/
	RIGHT_STICK_DOWN,
	/*押し込み(右スティック)*/
	RIGHT_STICK_PUSH,

	/*スタート*/
	START,
	/*バック*/
	BACK,

	/*最大キー数*/
	KEY_MAX
};
/*--------------------------------------------------------------------------------------------------------------
* 変動するコントローラーキーナンバー
*/
enum class CONTROLLER_KEY_VARIABLE_NUMBER
{
	/*右スティック(X軸)*/
	STICK_RIGHT_X = 0,
	/*右スティック(Y軸)*/
	STICK_RIGHT_Y,
	/*左スティック(X軸)*/
	STICK_LEFT_X,
	/*左スティック(Y軸)*/
	STICK_LEFT_Y,
	/*右奥トリガー*/
	RIGHT_TRIGGER,
	/*左奥トリガー*/
	LEFT_TRIGGER
};
/*--------------------------------------------------------------------------------------------------------------
* コントローラーナンバー
*/
enum class CONTROLLER_KEY_NUMBER
{
	/*キーボード*/
	KEY_BOARD = 0,
	/*コントローラー(1)*/
	CONTROLLER_1,
	/*コントローラー(2)*/
	CONTROLLER_2,
	/*コントローラー(3)*/
	CONTROLLER_3,
	/*コントローラー(4)*/
	CONTROLLER_4,

	/*コントローラー最大数*/
	MAX_CONTROLLER
};

/*
* フラグ設定用
*/
namespace KEY_BOARD_SET_NUMBER
{
	/*--------------------------------------------------------------------------------------------------------------
	* キーボードのキー種類
	*/
	enum class BOARD_KEY_TYPE 
	{// 137個
		// 数字キー
		_0 = '0',
		_1,
		_2,
		_3,
		_4,
		_5,
		_6,
		_7,
		_8,
		_9,

		// 文字キー
		A = 'A',
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z,

		// 記号文字
		COLON = 186,				// コロン
		SENI_COLON,					// セミコロン
		COMMA,						// カンマ
		HYPHEN,						// ハイフン
		PERIOD,						// ピリオド
		SLASH,						// スラッシュ
		AT_SIGN,					// アットマーク
		SQUARE_BRACKET = 219,		// 角括弧
		YEN_SIGN,					// 円マーク
		SQUARE_BRACKET_CLOSE,		// 角括弧
		CARET,						// キャレット(^)
		BACK_SLASH = 226,			// バックスラッシュ
		
		// 移動キー
		PG_UP = 33,					// ページアップ
		PG_DN,						// ページダウン
		END,						// 行末まで飛ぶ
		HOME,						// 行頭まで飛ぶ
		ARROW_LEFT,					// 左移動
		ARROW_UP,					// 上移動
		ARROW_RIGHT,				// 右移動
		ARROW_DOEN,					// 下移動
		
		// 特殊キー
		BACK_SPACE = 8,				// バックスペース
		TAB,						// タブ
		ENTER = 13,					// エンター
		SPACE = 32,					// スペース
		INSERT = 45,				// インサート
		_DELETE,					// デリート
		APPLICATION_KEY = 93,		// アプリケーションキー(ノートみたいな絵の奴)
		
		// 修飾キー
		SHIFT_LEFT_AND_RIGHT = 16,	// 両シフト
		SIFT_LEFT = 160,			// 左シフト
		SIFT_RIGHT,					// 右シフト
		CTRL_LEFT_AND_RIGHT = 17,	// 両コントロール
		CTRL_LEFT = 162,			// 左コントロール
		CTRL_RIGHT,					// 右コントロール
		ALT_LEFT_AND_RIGHT = 18,	// 両オルト
		ALT_LEFT = 164,				// 左オルト
		ALT_RIGHT,					// 右オルト
		ESC = 27,					// エスケープ
		WINDOWS = 91,				// ウィンドーズ
		
		// 半角・全角
		HALF_WIDTH = 240,			// 半角
		FULL_WIDTH = 242,			// 全角
		
		
		// F数字
		F1 = 112,
		F2, 
		F3, 
		F4, 
		F5,
		F6, 
		F7, 
		F8, 
		F9, 
		F10,
		F11,
		F12,
		
		// トグルキー
		NUM_LOCK = 144,				// num(ナム)ロック
		CAPS_LOCK,					// caps(キャプチャー)ロック
		SCROLL_LOCK = 20,			// Scroll(スクロール)ロック

		// NumPad
		NUMPAD_0_NUM_ON = 96,		// 0
		NUMPAD_1_NUM_ON,			// 1
		NUMPAD_2_NUM_ON,			// 2
		NUMPAD_3_NUM_ON,			// 3
		NUMPAD_4_NUM_ON,			// 4
		NUMPAD_5_NUM_ON,			// 5
		NUMPAD_6_NUM_ON,			// 6
		NUMPAD_7_NUM_ON,			// 7
		NUMPAD_8_NUM_ON,			// 8
		NUMPAD_9_NUM_ON,			// 9
		NUMPAD_ASTERISK,			// アスタリスク(掛け算)
		NUMPAD_PLUS,				// プラス(足し算)
		NUMPAD_MINUS = 109,			// マイナス(引き算)
		NUMPAD_SLASH = 111,			// スラッシュ(割り算)
		NUMPAD_5_NUM_OFF = 12,		// 何も文字をかけない取得出来るだけ



		// 音量キー(使わない予定、取得もしない)
		VOLUME_DELETE = 173,		// 音量削除
		VOLUME_DOWN,				// 音量下げる
		VOLUME_UP,					// 音量上げる


		// マウス
		MOUSE_LEFT = 1,				// 左マウス
		MOUSE_RIGHT,				// 右マウス
		MOUSE_WHEEL_BUTTON = 4,		// マウスホイール
	};
}
/*--------------------------------------------------------------------------------------------------------------
* キーボード 文字操作種類
*/
enum class KEY_BOARD_WORD
{
	// 数字キー
	_0 = 0,
	_1,
	_2,
	_3,
	_4,
	_5,
	_6,
	_7,
	_8,
	_9,

	// 文字キー
	A,
	B,
	C,
	D,
	E,
	F,
	G,
	H,
	I,
	J,
	K,
	L,
	M,
	N,
	O,
	P,
	Q,
	R,
	S,
	T,
	U,
	V,
	W,
	X,
	Y,
	Z,

	// 記号文字
	COLON,					// コロン
	SENI_COLON,				// セミコロン
	COMMA,					// カンマ
	HYPHEN,					// ハイフン
	PERIOD,					// ピリオド
	SLASH,					// スラッシュ
	AT_SIGN,				// アットマーク
	SQUARE_BRACKET,			// 角括弧
	YEN_SIGN,				// 円マーク
	SQUARE_BRACKET_CLOSE,	// 角括弧
	CARET,					// キャレット(^)
	BACK_SLASH,				// バックスラッシュ
	
	// 移動キー
	PG_UP,					// ページアップ
	PG_DN,					// ページダウン
	END,					// 行末まで飛ぶ
	HOME,					// 行頭まで飛ぶ
	ARROW_LEFT,				// 左移動
	ARROW_UP,				// 上移動
	ARROW_RIGHT,			// 右移動
	ARROW_DOEN,				// 下移動
};
/*--------------------------------------------------------------------------------------------------------------
* キーボード 特殊
*/
enum class KEY_BOARD_SPECIAL
{
	// 特殊キー
	BACK_SPACE = 0,			// バックスペース
	TAB,					// タブ
	ENTER,					// エンター
	SPACE,					// スペース
	INSERT,					// インサート
	_DELETE,				// デリート
	APPLICATION_KEY,		// アプリケーションキー(ノートみたいな絵の奴)

	// 修飾キー
	SHIFT_LEFT_AND_RIGHT,	// 両シフト
	SIFT_LEFT,				// 左シフト
	SIFT_RIGHT,				// 右シフト
	CTRL_LEFT_AND_RIGHT,	// 両コントロール
	CTRL_LEFT,				// 左コントロール
	CTRL_RIGHT,				// 右コントロール
	ALT_LEFT_AND_RIGHT,		// 両オルト
	ALT_LEFT,				// 左オルト
	ALT_RIGHT,				// 右オルト
	ESC,					// エスケープ
	WINDOWS,				// ウィンドーズ

	// 半角・全角
	HALF_WIDTH,				// 半角
	FULL_WIDTH,				// 全角


	// F数字
	F1,
	F2,
	F3,
	F4,
	F5,
	F6,
	F7,
	F8,
	F9,
	F10,
	F11,
	F12,
};
/*--------------------------------------------------------------------------------------------------------------
* キーボード テンキー操作
*/
enum class KEY_BOARD_NUM_PAD
{
	// トグルキー
	NUM_LOCK = 0,				// num(ナム)ロック
	// NumPad
	NUMPAD_0_NUM_ON,			// 0
	NUMPAD_1_NUM_ON,			// 1
	NUMPAD_2_NUM_ON,			// 2
	NUMPAD_3_NUM_ON,			// 3
	NUMPAD_4_NUM_ON,			// 4
	NUMPAD_5_NUM_ON,			// 5
	NUMPAD_6_NUM_ON,			// 6
	NUMPAD_7_NUM_ON,			// 7
	NUMPAD_8_NUM_ON,			// 8
	NUMPAD_9_NUM_ON,			// 9
	NUMPAD_ASTERISK,			// アスタリスク(掛け算)
	NUMPAD_PLUS,				// プラス(足し算)
	NUMPAD_MINUS,				// マイナス(引き算)
	NUMPAD_SLASH,				// スラッシュ(割り算)
	NUMPAD_5_NUM_OFF,			// 何も文字をかけない取得出来るだけ
};
/*--------------------------------------------------------------------------------------------------------------
* キーボード　トグルの状態
*/
enum class KEY_BOARD_TOGGLE
{
	NUM_LOCK = 0,	// num(ナム)ロック
	CAPS_LOCK,		// caps(キャプチャー)ロック
	SCROLL_LOCK,	// Scroll(スクロール)ロック
};

/*--------------------------------------------------------------------------------------------------------------
* マウスのフラグ種類
*/
enum class MOUSE_TYPE
{
	/*右ボタン*/
	RIGHT_BUTTON = 0,
	/*左ボタン*/
	LEFT_BUTTON,
	/*ホイールボタン*/
	WHEEL_BUTTON,
	/*ホイール前方向回転*/
	WHEEL_FRONT,
	/*ホイール後ろ方向回転*/
	WHEEL_BACK,
	/*マウス右移動*/
	MOVE_RIGHT,
	/*マウス左移動*/
	MOVE_LEFT,
	/*マウス前移動*/
	MOVE_FRONT,
	/*マウス後ろ移動*/
	MOVE_BACK,

	/*マウスのフラグ種類最大数*/
	MAX
};
/*--------------------------------------------------------------------------------------------------------------
* カーソルのポジションデータ種類
*/
enum class CURSOR_POSITION_TYPE
{
	/*現在移動している方向に進み始めたポジション*/
	START = 0,
	/*一つ前*/
	PREV,
	/*現在*/
	NOW,

	/*カーソルのポジションデータ種類最大数*/
	MAX
};


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* キー状態
*/
class KeyState
{
/*----------------------------------------------------------------------------------------------------
* 【共通】
*/
public:

	/*コンストラクタ*/
	KeyState();
	/*デストラクタ*/
	~KeyState();

	void Initilize(MSG* msg) { mdxsMsg = msg; }

	/*更新*/
	void Update();

	/*フラグのポジションを取得*/
	static unsigned int FlagPos(int keyNumber) { return 1U << keyNumber; }
	/*フラグのポジションを取得(コントローラー)*/
	static unsigned int FlagPos_Controller(CONTROLLER_KEY_TYPE keyNumber) { return FlagPos((int)keyNumber); }
	/*フラグのポジションを取得(キーボード文字系)*/
	static unsigned long long FlagPos_Board(KEY_BOARD_WORD keyNumber) { return FlagPos((int)keyNumber); }
	/*フラグのポジションを取得(キーボード特殊)*/
	static unsigned long FlagPos_Board(KEY_BOARD_SPECIAL keyNumber) { return FlagPos((int)keyNumber); }
	/*フラグのポジションを取得(キーボードNumLock)*/
	static unsigned short FlagPos_Board(KEY_BOARD_NUM_PAD keyNumber) { return FlagPos((int)keyNumber); }
	/*フラグのポジションを取得(マウス)*/
	static unsigned int FlagPos_Mouse(MOUSE_TYPE keyNumber) { return FlagPos((int)keyNumber); }

private:
	/*キーフラグを設定(コントローラーは現在のキーのみ設定)*/
	void SetKey();

/*----------------------------------------------------------------------------------------------------
* 【コントローラー(キーボードのコントローラー準拠も)】
*/
private:
	/*コントローラーフラグズ*/
	unsigned int munControllerKeyFlags[(int)FLAG_TYPE::MAX][(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER];

	/*右スティック横*/
	short mshNowRightStickX[(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER];
	/*右スティック縦*/
	short mshNowRightStickY[(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER];

	/*左スティック横*/
	short mshNowLeftStickX[(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER];
	/*左スティック縦*/
	short mshNowLeftStickY[(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER];

	/*左奥トリガー押し込み度合*/
	short mshNowLeftTrigger[(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER];
	/*右奥トリガー押し込み度合*/
	short mshNowRightTrigger[(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER];

	/*コントローラー最大数*/
	static constexpr int CONTROLLER_MAX = (const int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER;

public:
	/*押し始めたキーフラグを全取得(コントローラー)*/
	unsigned int GetDownKeyFlags_Controller(int controllerNumber) { return munControllerKeyFlags[(int)FLAG_TYPE::DOWN][controllerNumber]; }
	/*押し始めたキーフラグを全取得(コントローラー)*/
	unsigned int GetDownKeyFlags_Controller(CONTROLLER_KEY_NUMBER controllerNumber) { return GetDownKeyFlags_Controller((int)controllerNumber); }
	/*押し始めたキーフラグを全コントローラー分全取得(コントローラー)*/
	unsigned int GetAllDownKeyFlags_Controller(bool keyBoardFlag = true);

	/*押しているキーフラグを全取得(コントローラー)*/
	unsigned int GetNowKeyFlags_Controller(int controllerNumber) { return munControllerKeyFlags[(int)FLAG_TYPE::NOW][controllerNumber]; }
	/*押しているキーフラグを全取得(コントローラー)*/
	unsigned int GetNowKeyFlags_Controller(CONTROLLER_KEY_NUMBER controllerNumber) { return GetNowKeyFlags_Controller((int)controllerNumber); }
	/*押しているキーフラグを全コントローラー分全取得(コントローラー)*/
	unsigned int GetAllNowKeyFlags_Controller(bool keyBoardFlag = true);

	/*離したキーフラグを全取得(コントローラー)*/
	unsigned int GetUpKeyFlags_Controller(int controllerNumber) { return munControllerKeyFlags[(int)FLAG_TYPE::UP][controllerNumber]; }
	/*離したキーフラグを全取得(コントローラー)*/
	unsigned int GetUpKeyFlags_Controller(CONTROLLER_KEY_NUMBER controllerNumber) { return GetUpKeyFlags_Controller((int)controllerNumber); }
	/*離したキーフラグを全コントローラー分全取得(コントローラー)*/
	unsigned int GetAllUpKeyFlags_Controller(bool keyBoardFlag = true);


	/*キーナンバーに応じたキーの押しているなら「true」を返す(コントローラー)*/
	bool GetKey_Controller(int keyNumber, int controllerNumber);
	/*キーナンバーに応じたキーの押しているなら「true」を返す(コントローラー)*/
	bool GetKey_Controller(CONTROLLER_KEY_TYPE keyNumber) { return GetKey_Controller((int)keyNumber, 0); }
	/*キーナンバーに応じたキーの押しているなら「true」を返す(コントローラー)*/
	bool GetKey_Controller(CONTROLLER_KEY_TYPE keyNumber, int controllerNumber) { return GetKey_Controller((int)keyNumber, controllerNumber); }
	/*キーナンバーに応じたキーの押しているなら「true」を返す(コントローラー)*/
	bool GetKey_Controller(CONTROLLER_KEY_TYPE keyNumber, CONTROLLER_KEY_NUMBER controllerNumber) { return GetKey_Controller((int)keyNumber, (int)controllerNumber); }
	/*全コントローラーのキーナンバーに応じたキーを誰かが押しているなら「true」を返す(コントローラー)*/
	bool GetKeyAllController(int keyNumber, bool keyBoard = true) { for (int i = (keyBoard ? 0 : 1); i < (int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER; i++) { if (GetKey_Controller(keyNumber, i)) { return true; } } return false; }
	/*全コントローラーのキーナンバーに応じたキーを誰かが押しているなら「true」を返す(コントローラー)*/
	bool GetKeyAllController(CONTROLLER_KEY_TYPE keyNumber, bool keyBoard = true) { return GetKeyAllController((int)keyNumber, keyBoard); }

	/*キーナンバーに応じたキーが押された瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyDown_Controller(int keyNumber, int controllerNumber);
	/*キーナンバーに応じたキーが押された瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyDown_Controller(CONTROLLER_KEY_TYPE keyNumber) { return GetKeyDown_Controller((int)keyNumber, 0); }
	/*キーナンバーに応じたキーが押された瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyDown_Controller(CONTROLLER_KEY_TYPE keyNumber, int controllerNumber) { return GetKeyDown_Controller((int)keyNumber, controllerNumber); }
	/*キーナンバーに応じたキーが押された瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyDown_Controller(CONTROLLER_KEY_TYPE keyNumber, CONTROLLER_KEY_NUMBER controllerNumber) { return GetKeyDown_Controller((int)keyNumber, (int)controllerNumber); }
	/*全コントローラーのキーナンバーに応じたキーを誰かが押した瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyDownAllController(int keyNumber, bool keyBoard = true) { for (int i = (keyBoard ? 0 : 1); i < (int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER; i++) { if (GetKeyDown_Controller(keyNumber, i)) { return true; } } return false; }
	/*全コントローラーのキーナンバーに応じたキーを誰かが押した瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyDownAllController(CONTROLLER_KEY_TYPE keyNumber, bool keyBoard = true) { return GetKeyDownAllController((int)keyNumber, keyBoard); }

	/*キーナンバーに応じたキーが押されなくなった瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyUp_Controller(int keyNumber, int controllerNumber);
	/*キーナンバーに応じたキーが押されなくなった瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyUp_Controller(CONTROLLER_KEY_TYPE keyNumber) { return GetKeyUp_Controller((int)keyNumber, 0); }
	/*キーナンバーに応じたキーが押されなくなった瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyUp_Controller(CONTROLLER_KEY_TYPE keyNumber, int controllerNumber) { return GetKeyUp_Controller((int)keyNumber, controllerNumber); }
	/*キーナンバーに応じたキーが押されなくなった瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyUp_Controller(CONTROLLER_KEY_TYPE keyNumber, CONTROLLER_KEY_NUMBER controllerNumber) { return GetKeyUp_Controller((int)keyNumber, (int)controllerNumber); }
	/*全コントローラーのキーナンバーに応じたキーを誰かが離した瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyUpAllController(int keyNumber, bool keyBoard = true) { for (int i = (keyBoard ? 0 : 1); i < (int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER; i++) { if (GetKeyUp_Controller(keyNumber, i)) { return true; } } return false; }
	/*全コントローラーのキーナンバーに応じたキーを誰かが押した瞬間なら「true」を返す(コントローラー)*/
	bool GetKeyUpAllController(CONTROLLER_KEY_TYPE keyNumber, bool keyBoard = true) { return GetKeyUpAllController((int)keyNumber, keyBoard); }


	/*キーの変動値取得(コントローラー)*/
	short GetKeyVariable_Controller(CONTROLLER_KEY_VARIABLE_NUMBER getNumber, int controllerNumber);
	/*キーの変動値取得(コントローラー)*/
	short GetKeyVariable_Controller(CONTROLLER_KEY_VARIABLE_NUMBER getNumber, CONTROLLER_KEY_NUMBER controllerNumber = CONTROLLER_KEY_NUMBER::MAX_CONTROLLER) { return GetKeyVariable_Controller(getNumber, (int)controllerNumber); }

private:

	/*フラグを現在のキーに反映させる(コントローラー)*/
	void SetNowKey_Controller(bool flag, CONTROLLER_KEY_TYPE number, int controllerNumber = 0);

/*----------------------------------------------------------------------------------------------------
* 【キーボード】
*/
private:
	// 文字操作系キーフラグズ
	unsigned long long mullWordFlags[(int)FLAG_TYPE::MAX];

	// 特殊キーフラグズ
	unsigned long mulSpecialFlags[(int)FLAG_TYPE::MAX];

	// テンキーフラグズ
	unsigned short mushNumpadFlags[(int)FLAG_TYPE::MAX];

	// トグル状態
	unsigned char mucToggleFlag;

	// キーボードを取得するフラグ
	unsigned int munKeyBoardFlag;

public:
	/*キーボード状態を取得するかを設定する*/
	void SetKeyBoardFlag(bool flag);
	
	/*押し始めた文字操作系キーフラグを全取得(キーボード)*/
	unsigned long long GetDownWordKeyFlags_Board() { return mullWordFlags[(int)FLAG_TYPE::DOWN]; }
	/*押している文字操作系キーフラグを全取得(キーボード)*/
	unsigned long long GetNowWordKeyFlags_Board() { return mullWordFlags[(int)FLAG_TYPE::NOW]; }
	/*離した文字操作系キーフラグを全取得(キーボード)*/
	unsigned long long GetUpWordKeyFlags_Board() { return mullWordFlags[(int)FLAG_TYPE::UP]; }
	/*指定の文字操作系キーが押しているなら「true」を返す(キーボード)*/
	bool GetWordKey_Board(int keyNumber);
	/*指定の文字操作系キーが押しているなら「true」を返す(キーボード)*/
	bool GetWordKey_Board(KEY_BOARD_WORD keyNumber) { return GetWordKey_Board((int)keyNumber); }
	/*指定の文字操作系キーが押し始めた瞬間なら「true」を返す(キーボード)*/
	bool GetWordKeyDown_Board(int keyNumber);
	/*指定の文字操作系キーが押し始めた瞬間なら「true」を返す(キーボード)*/
	bool GetWordKeyDown_Board(KEY_BOARD_WORD keyNumber) { return GetWordKeyDown_Board((int)keyNumber); }
	/*指定の文字操作系キーが離した瞬間なら「true」を返す(キーボード)*/
	bool GetWordKeyUp_Board(int keyNumber);
	/*指定の文字操作系キーが離した瞬間なら「true」を返す(キーボード)*/
	bool GetWordKeyUp_Board(KEY_BOARD_WORD keyNumber) { return GetWordKeyUp_Board((int)keyNumber); }
	
	/*押し始めた特殊キーフラグを全取得(キーボード)*/
	unsigned long GetDownSpecialKeyFlags_Board() { return mulSpecialFlags[(int)FLAG_TYPE::DOWN]; }
	/*押している特殊キーフラグを全取得(キーボード)*/
	unsigned long GetNowSpecialKeyFlags_Board() { return mulSpecialFlags[(int)FLAG_TYPE::NOW]; }
	/*離した特殊キーフラグを全取得(キーボード)*/
	unsigned long GetUpSpecialKeyFlags_Board() { return mulSpecialFlags[(int)FLAG_TYPE::UP]; }
	/*指定の特殊キーが押しているなら「true」を返す(キーボード)*/
	bool GetSpecialKey_Board(int keyNumber);
	/*指定の特殊キーが押しているなら「true」を返す(キーボード)*/
	bool GetSpecialKey_Board(KEY_BOARD_SPECIAL keyNumber) { return GetSpecialKey_Board((int)keyNumber); }
	/*指定の特殊キーが押し始めた瞬間なら「true」を返す(キーボード)*/
	bool GetSpecialKeyDown_Board(int keyNumber);
	/*指定の特殊キーが押し始めた瞬間なら「true」を返す(キーボード)*/
	bool GetSpecialKeyDown_Board(KEY_BOARD_SPECIAL keyNumber) { return GetSpecialKeyDown_Board((int)keyNumber); }
	/*指定の特殊キーが離した瞬間なら「true」を返す(キーボード)*/
	bool GetSpecialKeyUp_Board(int keyNumber);
	/*指定の特殊キーが離した瞬間なら「true」を返す(キーボード)*/
	bool GetSpecialKeyUp_Board(KEY_BOARD_SPECIAL keyNumber) { return GetSpecialKeyUp_Board((int)keyNumber); }
	
	/*押し始めたテンキーキーフラグを全取得(キーボード)*/
	unsigned short GetDownNumpadKeyFlags_Board() { return mushNumpadFlags[(int)FLAG_TYPE::DOWN]; }
	/*押しているテンキーキーフラグを全取得(キーボード)*/
	unsigned short GetNowNumpadKeyFlags_Board() { return mushNumpadFlags[(int)FLAG_TYPE::NOW]; }
	/*離したテンキーキーフラグを全取得(キーボード)*/
	unsigned short GetUpNumpadKeyFlags_Board() { return mushNumpadFlags[(int)FLAG_TYPE::UP]; }
	/*指定のテンキーキーが押しているなら「true」を返す(キーボード)*/
	bool GetNumpadKey_Board(int keyNumber);
	/*指定のテンキーキーが押しているなら「true」を返す(キーボード)*/
	bool GetNumpadKey_Board(KEY_BOARD_NUM_PAD keyNumber) { return GetNumpadKey_Board((int)keyNumber); }
	/*指定のテンキーキーが押し始めた瞬間なら「true」を返す(キーボード)*/
	bool GetNumpadKeyDown_Board(int keyNumber);
	/*指定のテンキーキーが押し始めた瞬間なら「true」を返す(キーボード)*/
	bool GetNumpadKeyDown_Board(KEY_BOARD_NUM_PAD keyNumber) { return GetNumpadKeyDown_Board((int)keyNumber); }
	/*指定のテンキーキーが離した瞬間なら「true」を返す(キーボード)*/
	bool GetNumpadKeyUp_Board(int keyNumber);
	/*指定のテンキーキーが離した瞬間なら「true」を返す(キーボード)*/
	bool GetNumpadKeyUp_Board(KEY_BOARD_NUM_PAD keyNumber) { return GetNumpadKeyUp_Board((int)keyNumber); }

	/*トグル状態全取得(キーボード)*/
	unsigned char GetAllToggleState() { return mucToggleFlag; }
	/*指定のトグル状態が有効なら「true」を返す(キーボード)*/
	bool GetToggleState(int keyNumber);
	/*指定のトグル状態が有効なら「true」を返す(キーボード)*/
	bool GetToggleState(KEY_BOARD_TOGGLE keyNumber) { return GetToggleState((int)keyNumber); }

private:
	/*キーフラグを設定する(キーボード)*/
	void SetKey_Board(unsigned char* key);
	
	/*フラグを現在のキーに反映させる(文字操作系キーボードキー)*/
	void SetNowWordKey_Board(bool flag, KEY_BOARD_WORD keyNumber);
	/*フラグを現在のキーに反映させる(特殊キーボードキー)*/
	void SetNowSpecialKey_Board(bool flag, KEY_BOARD_SPECIAL keyNumber);
	/*フラグを現在のキーに反映させる(テンキーキー　キーボードキー)*/
	void SetNowNumpadKey_Board(bool flag, KEY_BOARD_NUM_PAD keyNumber);

/*----------------------------------------------------------------------------------------------------
* 【マウス】
*/
private:
	// マウスフラグズ(現在の反応している/反応し始めた/反応していた)
	unsigned int munMouseFlags;

	// マウスのポジション
	VECTOR_2D mstCursorPos[(int)CURSOR_POSITION_TYPE::MAX];

	// マウスホイールの回転量
	short mshWheelVolume;

	// マウスホイール取得用メッセージ
	MSG* mdxsMsg;

public:
	/*マウスフラグを全取得*/
	unsigned int GetMouseFlags() { return munMouseFlags; }

	/*指定のフラグが反応しているなら「true」を返す*/
	bool GetMouse(int number);
	/*指定のフラグが反応しているなら「true」を返す*/
	bool GetMouse(MOUSE_TYPE number) { return GetMouse((int)number); }

	/*指定のフラグが反応し始めたなら「true」を返す*/
	bool GetDownMouse(int number);
	/*指定のフラグが反応し始めたなら「true」を返す*/
	bool GetDownMouse(MOUSE_TYPE number) { return GetDownMouse((int)number); }

	/*指定のフラグが反応していたなら「true」を返す*/
	bool GetUpMouse(int number);
	/*指定のフラグが反応していたなら「true」を返す*/
	bool GetUpMouse(MOUSE_TYPE number) { return GetUpMouse((int)number); }

	/*指定タイミングのカーソルポジション取得*/
	VECTOR_2D GetCursorPosition(int number) { return mstCursorPos[number]; }
	/*指定タイミングのカーソルポジション取得*/
	VECTOR_2D GetCursorPosition(CURSOR_POSITION_TYPE number) { return GetCursorPosition((int)number); }

	/*マウスホイール回転取得(他の入力があるまで反応し続ける(キーボードも含めた))*/
	short GetWheelVolume() { return mshWheelVolume; }

private:
	/*マウスフラグを設定*/
	void SetMouseFlag(bool flag, MOUSE_TYPE number);
};