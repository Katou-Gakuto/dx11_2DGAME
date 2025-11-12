#pragma once

#include <vector>

#include "ObjectBases.h"
#include "TemplateData.h"

class TargetDatas;

/*カメラモード*/
enum class CAMERA_MODE
{
	/*ゲームのステージ(デフォルト)*/
	DEFAULT = 0,
	/*プレイヤーたちの中心座標を基準に移動する*/
	PLAYERS_MIDDLE_MOVE,
	/*強制スクロール*/
	FORCED_SCROLL,
};

class Camera
{
private:
	// カメラポジション
	VECTOR_2D mstCameraPosition;
	// カメラサイズ
	VECTOR_2D mstCameraSize;

	// 目標地点
	VECTOR_2D mstTargetPosition;
	// 目標サイズ
	VECTOR_2D mstTargetSize;

	// カメラ移動速度
	float mfCameraMoveSpeed;
	// カメラサイズ変更速度
	float mfCameraSizeChangeSpeed;

	// 現在の「1」分の長さ
	VECTOR_2D mstNowOneLength;
	// 開始時サイズ
	VECTOR_2D mstStartSize;

	// 開始時描画範囲
	VECTOR_2D mstStartDisplayDistance;

	// カメラモード
	CAMERA_MODE meCameraMode;

	// プレイヤー取得用データ
	TargetDatas* mpPlayerData;

public:
	/*コンストラクタ*/
	Camera();
	/*デストラクタ*/
	~Camera();

	/*初期化*/
	void Initilize();

	/*更新*/
	void Update();

public:
	/*--------------------------------------------------------------------------------------------------------------
	* 【設定】
	*/
	/*カメラ移動目標地点を設定*/
	void SetCameraTargetPos(VECTOR_2D setPos) { mstTargetPosition = setPos; }
	/*カメラ目標サイズ*/
	void SetCameraTargetSize(VECTOR_2D setSize) { mstTargetSize = setSize; }
	/*カメラ移動速度*/
	void SetCameraMoveSpeed(float setSpeed) { mfCameraMoveSpeed = setSpeed; }
	/*カメラサイズ変更速度*/
	void SetCameraChangeSizeSpeed(float setChangeSpeed) { mfCameraSizeChangeSpeed = setChangeSpeed; }

	/*カメラモード設定*/
	void SetCameraMode(CAMERA_MODE mode);

public:
	/*--------------------------------------------------------------------------------------------------------------
	* 【取得】
	*/
	/*現在の「1」分の長さ取得*/
	VECTOR_2D GetNowOneLength() { return mstNowOneLength; }

	/*描画範囲*/
	VECTOR_2D GetDisplayDistance() { return mstStartDisplayDistance * (mstCameraSize / mstStartSize); }

	/*カメラモード取得*/
	CAMERA_MODE GetCameraMode() { return meCameraMode; }

	/// <summary>カメラのポジション</summary>
	/// <returns>初期画面の中央が初期値(x(0.0f), y(0.0f))</returns>
	VECTOR_2D GetCameraPos() { return mstCameraPosition; }
	/// <summary>カメラサイズ</summary>
	/// <returns>初期値(x(1.0f), y(1.0f))</returns>
	VECTOR_2D GetCameraSize() { return mstCameraSize; }
};