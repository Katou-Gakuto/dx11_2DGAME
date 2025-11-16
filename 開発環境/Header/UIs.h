#pragma once
#include <vector>

#include "ObjectBases.h"

#include "TemplateData.h"

class PlayerControllerUI;
class FSM_SelectUI;
class DataManager;

/*--------------------------------------------------------------------------------------------------------------
* 【タイトルUI】
*/
class TitleUI : public UIBase
{
private:
    // リソースID
    int mnResourceID;

    // 文字の透明度設定用
    float mfFontColorAlpha;
    
    // 透明度設定用に足すフラグ(falseなら引く)
    bool mbFontColorAlphaPlusFlag;

public:
    /*コンストラクタ*/
    TitleUI();
    /*デストラクタ*/
    ~TitleUI();

    /*UI初期化*/
    void UIInitilize() override;
    /*UI終了*/
    void UIFinalize() override;
    /*UI更新*/
    void UIUpdate() override;
    /*UI描画*/
    void UIDraw() override;

private:
    /*選択決定時処理*/
    void DecisionProcess() override;
};

/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーデータ設定UI】
*/
class SetPlayerDataUI : public UIBase
{
private:
    // プレイヤー数
    int mnPlayerCount;
    // 選択中プレイヤーナンバー
    int mnSelectPlayerNumber;

    // 現在処理ナンバー
    int mnProcessNumber;

    // コントローラー設定用
    PlayerControllerUI* mpSetPlayerController;

    // 有限状態マシン
    FSM_SelectUI* mpFSM;

    // リソースID
    int mnResourceID;

public:
    /*コンストラクタ*/
    SetPlayerDataUI();
    /*デストラクタ*/
    ~SetPlayerDataUI();

    /*UI初期化*/
    void UIInitilize() override;
    /*UI終了*/
    void UIFinalize() override;
    /*UI更新*/
    void UIUpdate() override;
    /*UI描画*/
    void UIDraw() override;

private:
    /*選択決定時処理*/
    void DecisionProcess() override;


    /*マウスが反応した時に実行する*/
    void MouseProcess()override;

    /*キーボードが反応した時に実行する*/
    void KeyboardProcess()override;

    /*コントローラーが反応した時に実行する*/
    void ControllerProcess() override;

    /*キーボードかコントローラーが反応した時に実行する*/
    void Keyboard_ControllerProcess() override;

    /*--------------------------------------------------
    * 【ステート用関数】
    */
public:
    /*-------------------------
    * 【処理】
    */
    /*選択肢上変更(マイナス)*/
    void Up() { Decrease(); }
    /*選択肢下変更(プラス)*/
    void Down() { Increase(); }
    /*選択変更フレーム確認*/
    bool CheckChangeFrame() { return CheckFrame(0); }
    /*決定時処理*/
    void Decision() { DecisionProcess(); }

    /*-------------------------
    * 【取得】
    */
    ///*プレイヤー数*/
    //int GetPlayerCount() { return mnPlayerCount; }
    /*選択中プレイヤーナンバー*/
    int GetSelectPlayerNumber() { return mnSelectPlayerNumber; }
    /*コントローラー設定用*/
    PlayerControllerUI* GetSetPlayerControllerUI() { return mpSetPlayerController; }

    /*選択中数*/
    int GetSelectNumber() { return mnSelectNumber; }

    /*キーステート取得*/
    KeyState* GetKey() { return mpKeyState; }

    /*-------------------------
    * 【設定】
    */
    ///*プレイヤー数*/
    //void SetPlayerCount(int setCount) { mnPlayerCount = setCount; }
    /*選択中プレイヤーナンバー*/
    void SetSelectPlayerNumber(int setPlayerNumber) { mnSelectPlayerNumber = setPlayerNumber; }

    /*選択中数*/
    void SetSelectNumber(int setNumber) { mnSelectNumber = setNumber; }
    /*最大選択数*/
    void SetSelectMaxNumber(int setSelectMax) { mnMaxSelectNumber = setSelectMax; }
};

/*----------------------------------------------------------------------------------------------------
* 【リザルトUI】
*/
class ResultUI : public UIBase
{
private:
    // リソースID
    std::vector<int> mnResourceIDs;

    // データマネージャー
    DataManager* mpDataManager;

    // ゲーム時間
    int mnGameTime;

public:
    /*コンストラクタ*/
	ResultUI();
    /*デストラクタ*/
	~ResultUI();

    /*UI初期化*/
    void UIInitilize() override;
    /*UI終了*/
    void UIFinalize() override;
    /*UI更新*/
    void UIUpdate() override;
    /*UI描画*/
    void UIDraw() override;

private:
    /*選択決定時処理*/
    void DecisionProcess() override;
};

/*--------------------------------------------------------------------------------------------------------------
* 【プレイヤーコントローラー設定用UI】
*/
class PlayerControllerUI : public UIBase
{
private:
    // プレイヤー操作キーナンバー変更用
    int mnSetPlayerKey[5/*(int)CONTROLLER_KEY_NUMBER::MAX_CONTROLLER*/];

    // コントローラー設定が開始しているかのフラグ
    bool mbStartFlag;

    // データマネージャー
    DataManager* mpDataManager;

    // リソースID
    std::vector<int> mnResourceIDs;

    // 点滅時間
    int mnBlinkTime;

    // 終了キー押しフラグ
    bool mbEndFlag;

public:
    /*コンストラクタ*/
    PlayerControllerUI();
    /*デストラクタ*/
	~PlayerControllerUI();

    /*UI初期化*/
    void UIInitilize() override;
    /*UI終了*/
    void UIFinalize() override;
    /*UI更新*/
    void UIUpdate() override;
    /*UI描画*/
    void UIDraw() override;

    /*最終描画*/
    void LastDraw() override;

    /*プレイヤーキー設定開始*/
    void SetControllerStart();

    /*プレイヤー設定中かどうかを取得(設定中なら「true」)*/
    bool GetSettingUpFlag() { return mbStartFlag; }

private:
    /*選択決定時処理*/
    void DecisionProcess() override;

    /*コントローラー描画*/
    void ControllerDraw(int number, int resourceID, int keyBoardResourceID = -1, bool keyBoardFlag = false);
};