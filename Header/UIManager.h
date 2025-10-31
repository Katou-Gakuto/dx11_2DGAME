#pragma once
#include <vector>

#include "ObjectBases.h"

class UIManager
{
private:
    // メニューナンバー
    int mnNowUINumber;
    
    // メニューベースズ
    std::vector<UIBase*> mpUIBases;

public:
    UIManager();  // コンストラクタ
    ~UIManager(); // デストラクタ

    int IncreaseUINumber(UIBase* uiBase);  // メニューナンバー増加
    void DecreaseUINumber();  // メニューナンバー減少
    int GetNowUINumber() { return mnNowUINumber; }  // メニューナンバー取得
};