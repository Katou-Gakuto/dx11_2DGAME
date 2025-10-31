#pragma once
#include "ObjectBases.h"

class CloseRangeAttack : public AttackBase
{
public:
    CloseRangeAttack(const wchar_t* fileName, CharacterBase* attackCharacter, int attackTime, VECTOR_2D attackPosition, VECTOR_2D attackSize, COLLISION_TYPE objectType, int attackPower);
    ~CloseRangeAttack();

protected:
    /*アタック初期化*/
    virtual void AttackInitilize() override;
    /*アタック終了*/
    virtual void AttackFinalize() override;
    /*アタック更新*/
    virtual void AttackUpdate() override;
    /*アタック描画*/
    virtual void AttackDraw() override;
};