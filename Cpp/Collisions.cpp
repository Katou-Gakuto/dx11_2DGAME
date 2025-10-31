#include "../Header/Camera.h"
#include "../Header/Collisions.h"
#include "../Header/GameManager.h"
#include "../Header/Master.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【当たり判定関数】
*/
// サイドの辺の中同士が当たってるかを確認する
bool CollisionFunctions::SideCheck(float srcPos, float srcSize, float dstPos, float dstSize)
{
    if ((srcPos - (srcSize * 0.5f)) >= (dstPos + (dstSize * 0.5f)))
    {
        return false;
    }
    if ((srcPos + (srcSize * 0.5f)) <= (dstPos - (dstSize * 0.5f)))
    {
        return false;
    }

    return true;
}

//ボックス当たり判定
bool CollisionFunctions::HitBox(VECTOR_2D srcPos, VECTOR_2D srcSize, VECTOR_2D dstPos, VECTOR_2D dstSize)
{
    return (SideCheck(srcPos.X, srcSize.X, dstPos.X, dstSize.X) &&
            SideCheck(srcPos.Y, srcSize.Y, dstPos.Y, dstSize.Y));
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
* 【カメラ外抑止当たり判定】
*/

// コンストラクタ
CameraCollision::CameraCollision()
: CollisionBase(Master::mpGameManager->GetCamera()->GetCameraPos(), Master::mpGameManager->GetCamera()->GetDisplayDistance() - Master::mpGameManager->GetCamera()->GetNowOneLength())
, mpCamera(nullptr)
{
}

// デストラクタ
CameraCollision::~CameraCollision()
{
}

// 当たり判定
CollisionData CameraCollision::CollisionCheck(CollisionData collisionData)
{
	if (collisionData.ObjectType != COLLISION_TYPE::PLAYER)
	{
		return collisionData;
	}

	switch (collisionData.CollisionType)
	{
	case COLLISION_TYPE::BOX:
		if (!CollisionFunctions::HitBox(collisionData.Position + collisionData.NotHitPosMove, collisionData.Size, mstPosition, mstSize))
		{
			collisionData.HitCount += 1;

			if (!CollisionFunctions::SideCheck(collisionData.Position.X, collisionData.Size.X, mstPosition.X, mstSize.X))
			{
				collisionData.NotHitPosMove.X += (collisionData.Position.X > mstPosition.X ? ((mstPosition.X + (mstSize.X * 0.5f)) - (collisionData.Position.X - (collisionData.Size.X * 0.5f))) : ((mstPosition.X - (mstSize.X * 0.5f)) - (collisionData.Position.X + (collisionData.Size.X * 0.5f)))) * 1.000001f;
			}
			if (!CollisionFunctions::SideCheck(collisionData.Position.Y, collisionData.Size.Y, mstPosition.Y, mstSize.Y))
			{
				collisionData.NotHitPosMove.Y += (collisionData.Position.Y > mstPosition.Y ? ((mstPosition.Y + (mstSize.Y * 0.5f)) - (collisionData.Position.Y - (collisionData.Size.Y * 0.5f))) : ((mstPosition.Y - (mstSize.Y * 0.5f)) - (collisionData.Position.Y + (collisionData.Size.Y * 0.5f)))) * 1.000001f;
			}
		}
		break;
	}

	return collisionData;
}

// コリジョン初期化
void CameraCollision::CollisionInitilize()
{
	mpCamera = Master::mpGameManager->GetCamera();
}

// コリジョン終了
void CameraCollision::CollisionFinalize()
{
}

// コリジョン更新
void CameraCollision::CollisionUpdate()
{
	float setY = 1.0f / mpCamera->GetNowOneLength().Y;
	mstPosition = mpCamera->GetCameraPos() + VECTOR_2D::GetFloatVec(0.0f, -setY * 0.5f);
	mstSize = mpCamera->GetDisplayDistance() - 2.0f - VECTOR_2D::GetFloatVec(0.0f, setY);
}

// コリジョン描画
void CameraCollision::CollisionDraw()
{
}



/*
// 当たり判定
CollisionData CameraCollision::CollisionCheck(CollisionData collisionData)
{
	if (!CollisionFunctions::HitBox(collisionData.Position + collisionData.NotHitPosMove, collisionData.Size, mstPosition, mstSize - Master::mpGameManager->GetCamera()->GetNowOneLength()))
	{
		collisionData.HitCount += 1;

		if (!CollisionFunctions::SideCheck(collisionData.OldPosition.X, collisionData.Size.X, mstPosition.X, mstSize.X))
		{
			collisionData.NotHitPosMove.X += (collisionData.OldPosition.X > mstPosition.X ? ((mstPosition.X + (mstSize.X * 0.5f)) - (collisionData.Position.X - (collisionData.Size.X * 0.5f))) : ((mstPosition.X - (mstSize.X * 0.5f)) - (collisionData.Position.X + (collisionData.Size.X * 0.5f))));
		}
		if (!CollisionFunctions::SideCheck(collisionData.OldPosition.Y, collisionData.Size.Y, mstPosition.Y, mstSize.Y))
		{
			collisionData.NotHitPosMove.Y += (collisionData.OldPosition.Y > mstPosition.Y ? ((mstPosition.Y + (mstSize.Y * 0.5f)) - (collisionData.Position.Y - (collisionData.Size.Y * 0.5f))) : ((mstPosition.Y - (mstSize.Y * 0.5f)) - (collisionData.Position.Y + (collisionData.Size.Y * 0.5f))));
		}
	}

	return collisionData;
}*/