#pragma once

#include <windows.h>

class TimeManager
{
private:

    // フレームカウント
    int mnFrameCount;
    // スタートタイム
    int mnStartTime;
    // 一つ前の時間
    int mnPreviousTime;
    // ストップタイム
    int mnStopTime;
    // ストップフラグ
    bool mbStopFlag;
    // 1フレームの秒数
    int mnOneFrame;     

    // 新しいシーンに移っている処理をしたフラグ
    bool mbNewSceneTimeFlag;    

public:
    /*コンストラクタ*/
    TimeManager(int oneFrameTime = 17); 
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
    int GetFrame() { return mnFrameCount; }
    
    /// <summary>
    /// ゲーム時間取得
    /// </summary>
    /// <returns>ゲームの経過時間</returns>
    int GetGameTime() { return timeGetTime() - (mnStartTime + (mbNewSceneTimeFlag ? (mnStopTime + (timeGetTime() - mnPreviousTime)) : mnStopTime)); }

    /// <summary>
    /// スタートからの経過時間
    /// </summary>
    /// <returns>経過時間</returns>
    int GetTime() { return timeGetTime() - mnStartTime; }

    /// <summary>
    /// 一つ前の更新時間
    /// </summary>
    /// <returns>更新時間</returns>
    int GetPreviousTime() { return mnPreviousTime; }

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
    int GetOneFrame() { return mnOneFrame; }
    
    /// <summary>
    /// 1フレームの秒数設定(ミリ秒)
    /// </summary>
    /// <param name="time">1フレームの秒数(ミリ秒)</param>
    void SetOneFrame(int time) { mnOneFrame = time; }

    /// <summary>
    /// シーン変更中に経ったゲーム時間を一定化するフラグを設定
    /// </summary>
    /// <param name="flag">新しいシーン移動中かどうか</param>
    void SetNewSceneTimeFlag(bool flag) { mbNewSceneTimeFlag = flag; }
};