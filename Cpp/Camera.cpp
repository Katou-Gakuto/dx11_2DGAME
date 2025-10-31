#include "../Header/Calculation.h"
#include "../Header/Camera.h"
#include "../Header/GameManager.h"
#include "../Header/Macro.h"
#include "../Header/Master.h"
#include "../Header/TargetDatas.h"

// コンストラクタ
Camera::Camera()
// カメラ位置
: mstCameraPosition(VECTOR_2D::Zero())
, mstCameraSize(VECTOR_2D::One())

// カメラ変更位置
, mstTargetPosition(VECTOR_2D::Zero())
, mstTargetSize(VECTOR_2D::One())

// カメラ位置変更速度
, mfCameraMoveSpeed(1.0f)
, mfCameraSizeChangeSpeed(1.0f)

// 現在の「1」分の長さ
, mstNowOneLength(VECTOR_2D::One())
, mstStartSize(VECTOR_2D::One())

// 開始時描画範囲
, mstStartDisplayDistance(VECTOR_2D::Zero())

// カメラモード
, meCameraMode(CAMERA_MODE::DEFAULT)

// プレイヤー取得用データ
, mpPlayerData(nullptr)
{
}
// デストラクタ
Camera::~Camera()
{
}

// 初期化
void Camera::Initilize()
{
	// カメラ位置
	mstCameraPosition = VECTOR_2D::Zero();
	mstCameraSize = VECTOR_2D::One();

	// カメラ変更位置
	mstTargetPosition = VECTOR_2D::Zero();
	mstTargetSize = VECTOR_2D::One();

	// カメラ位置変更速度
	mfCameraMoveSpeed = 1.0f;
	mfCameraSizeChangeSpeed = 1.0f;

	// 現在の「1」分の長さ
	mstNowOneLength = VECTOR_2D::One();
	mstStartSize = mstCameraSize;

	// 開始時描画範囲
	mstStartDisplayDistance = VECTOR_2D::GetFloatVec(20.0f, 12.0f);
}

// 更新
void Camera::Update()
{
	switch (meCameraMode)
	{
	case CAMERA_MODE::PLAYERS_MIDDLE_MOVE:
	{
		if (mpPlayerData == nullptr)
		{
			mpPlayerData = Master::mpGameManager->GetTargetDatas();
		}

		VECTOR_2D playerMiddlePos = VECTOR_2D::Zero();
		std::vector<CharacterBase*> players = mpPlayerData->GetPlayers();
		for (int i = 0; i < players.size(); i++)
		{
			playerMiddlePos += (players[i]->GetStatus().Position - mstCameraPosition);
		}
		playerMiddlePos /= (int)players.size();
		VECTOR_2D checkField = GetDisplayDistance();
		if (playerMiddlePos.Abs().X >= (checkField.X * 0.2f))
		{
			mstTargetPosition.X = mstCameraPosition.X + ((playerMiddlePos.Abs().X - (checkField.X * 0.2f)) * playerMiddlePos.Sign().X);
		}
		if (playerMiddlePos.Abs().Y >= (checkField.Y * 0.2f))
		{
			mstTargetPosition.Y = mstCameraPosition.Y + ((playerMiddlePos.Abs().Y - (checkField.Y * 0.2f)) * playerMiddlePos.Sign().Y);
		}
	}
		break;

	case CAMERA_MODE::FORCED_SCROLL:
		break;
	}

	if (mstCameraSize != mstTargetSize)
	{
		VECTOR_2D diffSize = mstTargetSize - mstCameraSize;

		Calculation::DiffReduce(&diffSize.X, mfCameraSizeChangeSpeed);
		Calculation::DiffReduce(&diffSize.Y, mfCameraSizeChangeSpeed);

		mstCameraSize = mstTargetSize - diffSize;

		mstNowOneLength = mstStartSize / mstCameraSize;
	}

	if (mstCameraPosition != mstTargetPosition)
	{
		VECTOR_2D diffPos = mstTargetPosition - mstCameraPosition;

		Calculation::DiffReduce(&diffPos.X, mfCameraMoveSpeed);
		Calculation::DiffReduce(&diffPos.Y, mfCameraMoveSpeed);

		mstCameraPosition = mstTargetPosition - diffPos;
	}
}