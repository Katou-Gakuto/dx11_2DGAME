#include <vector>

#include "../Header/GameManager.h"
#include "../Header/Master.h"
#include "../Header/ObjectBases.h"
#include "../Header/ObjectManager.h"
#include "../Header/TargetDatas.h"

// コンストラクタ
TargetDatas::TargetDatas()
{
	mpPlayers.clear();
	mpEnemys.clear();
}
// デストラクタ
TargetDatas::~TargetDatas()
{
}

// 標的プレイヤーを削除
void TargetDatas::SubPlayer(CharacterBase* player)
{
	for (int i = 0; i < mpPlayers.size(); i++)
	{
		if (mpPlayers[i]->GetID() == player->GetID())
		{
			mpPlayers.erase(mpPlayers.begin() + i);
			return;
		}
	}
}

// 一番近いプレイヤーまでの移動量を取得を取得
VECTOR_2D TargetDatas::GetNearPlayerVec(VECTOR_2D pos)
{
	VECTOR_2D result = VECTOR_2D::Zero();

	for (int i = 0; i < mpPlayers.size(); i++)
	{
		if (result == VECTOR_2D::Zero())
		{
			result = mpPlayers[i]->GetStatus().Position - pos;
		}
		else
		{
			if (result.Abs().GetAddXY() >(mpPlayers[i]->GetStatus().Position - pos).Abs().GetAddXY())
			{
				result = mpPlayers[i]->GetStatus().Position - pos;
			}
		}

		if (result == VECTOR_2D::Zero())
		{
			break;
		}
	}

	return result;
}

// エネミーを削除
void TargetDatas::SubEnemy(CharacterBase* enemy)
{
	for (int i = 0; i < mpEnemys.size(); i++)
	{
		if (mpEnemys[i]->GetID() == enemy->GetID())
		{
			mpEnemys.erase(mpEnemys.begin() + i);
			return;
		}
	}
}