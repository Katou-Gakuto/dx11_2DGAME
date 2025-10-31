#include "../Header/Master.h"
#include "../Header/TimeManager.h"
#include "../Header/UIManager.h"

/*コンストラクタ*/
UIManager::UIManager()
: mnNowUINumber(0)
{
    mpUIBases.clear();
}

/*デストラクタ*/
UIManager::~UIManager()
{
}

/*
* @fn IncreaseUINumber
* @drief メニューナンバー増加
*/
int UIManager::IncreaseUINumber(UIBase* uiBase)
{
    // 一番後ろに追加
    mpUIBases.push_back(uiBase);

    mnNowUINumber += 1;
    if (mnNowUINumber == 1) {
        // 時間を止める
        Master::mpTimeManager->SetStopFlag(true);
    }
    return mnNowUINumber;
}

/*
* @fn DecreaseUINumber
* @drief メニューナンバー減少
*/
void UIManager::DecreaseUINumber()
{
    // 一番後ろを削除
    mpUIBases.pop_back();

    mnNowUINumber -= 1;
    if (mnNowUINumber <= 0) {
        mnNowUINumber = 0;

        // 時間を動かす
        Master::mpTimeManager->SetStopFlag(false);
    }
}