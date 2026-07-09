#pragma once

#include <windows.h>

class TimeManager
{
private:

    // フレームカウント
    unsigned long mnFrameCount;
    // スタートタイム
    unsigned long mnStartTime;
    // 一つ前の時間
    unsigned long mnPreviousTime;
    // ストップタイム
    unsigned long mnStopTime;
    // ストップフラグ
    bool mbStopFlag;
    // 1フレームの秒数
    unsigned long mnOneFrame;

    // 新しいシーンに移っている処理をしたフラグ
    bool mbNewSceneTimeFlag;    

public:
    /*コンストラクタ*/
    TimeManager(unsigned long oneFrameTime = 17);
    /*デストラクタ*/
    ~TimeManager();  

    /*初期化*/
    void Initilize();
    
    /*更新処理をやるかを返す*/
    bool GetNextUpdateFlag();      


    /// <summary>
    /// フレーム数取得
    /// </summary>
    /// <returns>経過フレーム数</returns>
    unsigned long GetFrame() { return mnFrameCount; }
    
    /// <summary>
    /// ゲーム時間取得
    /// </summary>
    /// <returns>ゲームの経過時間</returns>
    unsigned long GetGameTime() { return timeGetTime() - (mnStartTime + (mbNewSceneTimeFlag ? (mnStopTime + (timeGetTime() - mnPreviousTime)) : mnStopTime)); }

    /// <summary>
    /// スタートからの経過時間
    /// </summary>
    /// <returns>経過時間</returns>
    unsigned long GetTime() { return timeGetTime() - mnStartTime; }

    /// <summary>
    /// 一つ前の更新時間
    /// </summary>
    /// <returns>更新時間</returns>
    unsigned long GetPreviousTime() { return mnPreviousTime; }

    /// <summary>
    /// ゲーム停止フラグ取得
    /// </summary>
    /// <returns>フラグ</returns>
    bool GetStopFlag() { return mbStopFlag; }

    /// <summary>
    /// ゲーム停止フラグ設定
    /// </summary>
    /// <param name="flag">停止するかどうか trueで止まる</param>
    void SetStopFlag(bool flag) { mbStopFlag = flag; }

    /// <summary>
    /// 1フレームの秒数取得(ミリ秒)
    /// </summary>
    /// <returns>1フレームの秒数(ミリ秒)</returns>
    unsigned long GetOneFrame() { return mnOneFrame; }
    
    /// <summary>
    /// 1フレームの秒数設定(ミリ秒)
    /// </summary>
    /// <param name="time">1フレームの秒数(ミリ秒)</param>
    void SetOneFrame(unsigned long time) { mnOneFrame = time; }

    /// <summary>
    /// シーン変更中に経ったゲーム時間を一定化するフラグを設定
    /// </summary>
    /// <param name="flag">新しいシーン移動中かどうか</param>
    void SetNewSceneTimeFlag(bool flag) { mbNewSceneTimeFlag = flag; }
};