#include <windows.h>

#include "../Header/TimeManager.h"

// コンストラクタ
TimeManager::TimeManager(unsigned long oneFrameTime)
: mnFrameCount(0)
, mnStartTime(0)
, mnPreviousTime(0)
, mnStopTime(0)
, mbStopFlag(false)
, mnOneFrame(oneFrameTime)
, mbNewSceneTimeFlag(false)
{
}
// デストラクタ
TimeManager::~TimeManager()
{
}
// 初期化
void TimeManager::Initilize()
{
    timeBeginPeriod(1); // タイマーの分解量の設定を1msにする (1ミリ秒/1000秒)にする
    mnStartTime = timeGetTime();
}

// 更新
bool TimeManager::GetNextUpdateFlag()
{
    unsigned long nowTime = timeGetTime();
    if ((mnPreviousTime + mnOneFrame) <= nowTime)
    {
        mnFrameCount += 1;

        if (mbStopFlag) {
            mnStopTime += (nowTime - mnPreviousTime);
            if (mbNewSceneTimeFlag) {
                mbNewSceneTimeFlag = false;
            }
        }
        else if (mbNewSceneTimeFlag) {
            mnStopTime += ((nowTime - mnPreviousTime) - mnOneFrame);
            mbNewSceneTimeFlag = false;
        }

        mnPreviousTime = nowTime;
        
        return true;

    }

    return false;
}