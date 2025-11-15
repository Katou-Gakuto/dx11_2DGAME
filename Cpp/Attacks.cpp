#include "../Header/Attacks.h"
#include "../Header/ObjectBases.h"
#include "../Header/TemplateData.h"

// コンストラクタ
CloseRangeAttack::CloseRangeAttack(const wchar_t* fileName, CharacterBase* attackCharacter, int attackTime, VECTOR_2D attackPosition, VECTOR_2D attackSize, COLLISION_TYPE objectType, int attackPower)
: AttackBase(DrawData::GetDrawData(1, fileName), attackCharacter, attackTime, attackPosition, attackSize, objectType, attackPower)
{
}

// デストラクタ
CloseRangeAttack::~CloseRangeAttack()
{
}

// アタック初期化
void CloseRangeAttack::AttackInitilize()
{
	mstCollisionData.CollisionType = COLLISION_TYPE::BOX;
	mstCollisionData.ObjectType = meObjectType;
	mstCollisionData.Position = mstAttackPosition;
	mstCollisionData.Size = mstAttackSize * 0.6f;
}

// アタック終了
void CloseRangeAttack::AttackFinalize()
{
}

// アタック更新
void CloseRangeAttack::AttackUpdate()
{
	TemplateAttackProcess();
}

// アタック描画
void CloseRangeAttack::AttackDraw()
{
	TemplateDrawProcess();
}