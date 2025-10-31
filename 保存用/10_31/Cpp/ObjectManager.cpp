#include "../Header/ObjectBases.h"
#include "../Header/ObjectManager.h"
#include "../Header/SceneManager.h"

// コンストラクタ
ObjectManager::ObjectManager()
: mpObjectBase(nullptr)
, mpCharacterBase(nullptr)
, mpCharacterControllerPlayer(nullptr)
, mpCharacterControllerEnemy(nullptr)
, mpCollisionBase(nullptr)
, mpAttackBase(nullptr)
, mpUIBase(nullptr)
, mnObjectChangeFlags(0)
, mnSetObjectChangeFlags(0)
{
}
// デストラクタ
ObjectManager::~ObjectManager()
{
}

// 初期化
void ObjectManager::Initilize()
{
	ObjectBase::Set_SetID(0);
	mnObjectChangeFlags = 0;
	mnSetObjectChangeFlags = 0;
}

// 終了
void ObjectManager::Finalize()
{
	// 全オブジェクトを削除
	DeleteAll();
}

// 更新
void ObjectManager::Update()
{
	if (mpObjectBase == nullptr)
	{
		return;
	}
	mnObjectChangeFlags = mnSetObjectChangeFlags;
	mnSetObjectChangeFlags = 0;

	ObjectBase* workObject = mpObjectBase;
	do
	{
		workObject->Update();
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// 描画
void ObjectManager::Draw()
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		workObject->Draw();
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// リストにオブジェクトを追加する
void ObjectManager::Add(ObjectBase* object, int typeNumber)
{
	bool setFlag = true;
	mnSetObjectChangeFlags |= (0b1 << typeNumber);
	mnSetObjectChangeFlags |= 1;

	if (mpObjectBase == nullptr)
	{
		mpObjectBase = object;
		setFlag = false;
	}

	if (setFlag)
	{
		// 一番後ろの場所を探す。
		ObjectBase* currentObject = mpObjectBase;
		ObjectBase* nextObject = mpObjectBase->GetNextObject();

		while (nextObject != nullptr)
		{
			currentObject = nextObject;
			nextObject = currentObject->GetNextObject();
		}

		currentObject->SetNextObject(object);
		object->SetPrevObject(currentObject);
	}

	ObjectBase* checkObject = nullptr;
	switch ((OBJECT_TYPE)typeNumber)
	{
	case OBJECT_TYPE::BASE:
		return;

	case OBJECT_TYPE::CHARACTER_BASE:
		if (mpCharacterBase == nullptr)
		{
			mpCharacterBase = object;
			return;
		}
		checkObject = mpCharacterBase;
		break;

	case OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER:
		if (mpCharacterControllerPlayer == nullptr)
		{
			mpCharacterControllerPlayer = object;
			return;
		}
		checkObject = mpCharacterControllerPlayer;
		break;

	case OBJECT_TYPE::CHARACTER_CONTROLLER_ENEMY:
		if (mpCharacterControllerEnemy == nullptr)
		{
			mpCharacterControllerEnemy = object;
			return;
		}
		checkObject = mpCharacterControllerEnemy;
		break;

	case OBJECT_TYPE::COLLISION_BASE:
		if (mpCollisionBase == nullptr)
		{
			mpCollisionBase = object;
			return;
		}
		checkObject = mpCollisionBase;
		break;

	case OBJECT_TYPE::ATTACK_BASE:
		if (mpAttackBase == nullptr)
		{
			mpAttackBase = object;
			return;
		}
		checkObject = mpAttackBase;
		break;

	case OBJECT_TYPE::UI_BASE:
		if (mpUIBase == nullptr)
		{
			mpUIBase = object;
			return;
		}
		checkObject = mpUIBase;
		break;

	}

	{
		// 一番後ろの場所を探す。
		ObjectBase* currentObject = checkObject;
		ObjectBase* nextObject = checkObject->GetNextObject(false);

		while (nextObject != nullptr)
		{
			currentObject = nextObject;
			nextObject = currentObject->GetNextObject(false);
		}

		currentObject->SetNextObject(object, false);
		object->SetPrevObject(currentObject, false);
	}
}

/*リストからオブジェクトを除外する*/
void ObjectManager::Delete(unsigned int id, int typeNumber)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}
	mnSetObjectChangeFlags |= (0b1 << typeNumber);
	mnSetObjectChangeFlags |= 1;

	ObjectBase* checkObject = GetTypeObject(typeNumber);
	if ((OBJECT_TYPE)typeNumber == OBJECT_TYPE::BASE)
	{
		checkObject = nullptr;
	}

	// 継承クラス
	do
	{
		if (checkObject != nullptr)
		{
			// もし最初のオブジェクトだった場合は特別な処理をする。
			if (checkObject->GetID() == id)
			{
				ObjectBase* next = checkObject->GetNextObject(false);
				ObjectBase* deleteObject = checkObject;
				switch ((OBJECT_TYPE)typeNumber)
				{
				case OBJECT_TYPE::CHARACTER_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpCharacterBase = next;
					}
					else {
						mpCharacterBase = nullptr;
					}
					break;

				case OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpCharacterControllerPlayer = next;
					}
					else {
						mpCharacterControllerPlayer = nullptr;
					}
					break;

				case OBJECT_TYPE::CHARACTER_CONTROLLER_ENEMY:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpCharacterControllerEnemy = next;
					}
					else {
						mpCharacterControllerEnemy = nullptr;
					}
					break;

				case OBJECT_TYPE::COLLISION_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpCollisionBase = next;
					}
					else {
						mpCollisionBase = nullptr;
					}
					break;

				case OBJECT_TYPE::ATTACK_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpAttackBase = next;
					}
					else {
						mpAttackBase = nullptr;
					}
					break;

				case OBJECT_TYPE::UI_BASE:
					if (next != nullptr) {
						next->SetPrevObject(nullptr, false);
						mpUIBase = next;
					}
					else {
						mpUIBase = nullptr;
					}
					break;

				}
				break;
			}

			// 以下、最初のオブジェクトではなかった場合の処理

			// 削除対象のオブジェクトを探索する
			ObjectBase* target = checkObject->GetNextObject(false);
			while (target->GetID() != id)
			{
				target = target->GetNextObject(false);
				
				if (target == nullptr)
				{
					break;
				}
			}

			// 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
			ObjectBase* prev = target->GetPrevObject(false);
			ObjectBase* next = target->GetNextObject(false);

			// 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
			prev->SetNextObject(next, false);
			if (next != nullptr)
			{
				next->SetPrevObject(prev, false);
			}
		}
	} while (false);

	// オブジェクトベース
	{
		// もし最初のオブジェクトだった場合は特別な処理をする。
		if (mpObjectBase->GetID() == id)
		{
			ObjectBase* next = mpObjectBase->GetNextObject();
			ObjectBase* deleteObject = mpObjectBase;
			if (next != nullptr)
			{
				next->SetPrevObject(nullptr);
				mpObjectBase = next;
			}
			else {
				mpObjectBase = nullptr;
			}

			deleteObject->Finalize();
			delete deleteObject;
			return;
		}

		// 以下、最初のオブジェクトではなかった場合の処理

		// 削除対象のオブジェクトを探索する
		ObjectBase* target = mpObjectBase->GetNextObject();
		while (target->GetID() != id)
		{
			if (target == nullptr)
			{
				return;
			}

			target = target->GetNextObject();
		}

		// 削除対象のオブジェクトの前と後ろを繋げるために、一旦確保しておく
		ObjectBase* prev = target->GetPrevObject();
		ObjectBase* next = target->GetNextObject();

		// 削除対象のオブジェクトの前後を繋げ、削除対象を孤立させる
		prev->SetNextObject(next);
		if (next != nullptr)
		{
			next->SetPrevObject(prev);
		}

		// 削除する
		target->Finalize();
		delete target;
		target = nullptr;
	}
}

// IDからオブジェクトを取得
ObjectBase* ObjectManager::FindByID(int id, bool deleteGetFlag)
{
	if (mpObjectBase == nullptr)
	{
		return mpObjectBase;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (!workObject->IsDeleteFlag() || deleteGetFlag)
		{
			if (workObject->GetID() == id)
			{
				return workObject;
			}
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);

	return workObject;
}

// タグからオブジェクトを取得
ObjectBase* ObjectManager::FindByTag(int tag, int typeNumber, bool deleteGetFlag)
{
	// 種類別に調べる
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if ((OBJECT_TYPE)typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	if (checkObject == nullptr)
	{
		return checkObject;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if (!workObject->IsDeleteFlag() || deleteGetFlag)
		{
			if (workObject->GetTag() == tag)
			{
				return workObject;
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return workObject;
}

// タグから複数オブジェクトを取得
std::vector<ObjectBase*> ObjectManager::FindsByTag(int tag, int typeNumber, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if ((OBJECT_TYPE)typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::vector<ObjectBase*> result;
	result.clear();

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if (!workObject->IsDeleteFlag() || deleteGetFlag)
		{
			if (workObject->GetTag() == tag)
			{
				result.push_back(workObject);
			}
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}

// 指定されたタイプを全取得
std::vector<ObjectBase*> ObjectManager::FindsByType(int typeNumber, bool deleteGetFlag)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if ((OBJECT_TYPE)typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	std::vector<ObjectBase*> result;
	result.clear();

	if (checkObject == nullptr)
	{
		return result;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		if (!workObject->IsDeleteFlag() || deleteGetFlag)
		{
			result.push_back(workObject);
		}
		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return result;
}

// 指定したシーンで生成されたオブジェクトの削除フラグ有効にする
void ObjectManager::SetDeleteSceneObject(SCENE_NAME targetScene)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (workObject->GetObjectScene() == targetScene)
		{
			workObject->SetDeleteFlag(true);
		}

		workObject = workObject->GetNextObject();

	} while (workObject != nullptr);
}

// オブジェクト全削除
void ObjectManager::DeleteAll()
{
	// 最初のオブジェクトがないなら何もしない
	if (mpObjectBase == nullptr)
	{
		return;
	}

	// オブジェクトの全削除
	ObjectBase* target = mpObjectBase;
	do
	{
		ObjectBase* next = target->GetNextObject();
		Delete(target->GetID(), target->GetObjectTypeNumber());
		target = next;
	} while (target != nullptr);
}

// 必要であればオブジェクト削除を行う
void ObjectManager::DeleteAllIfNeeded()
{    // 最初のオブジェクトがないなら何もしない
	if (mpObjectBase == nullptr)
	{
		return;
	}

	// 削除フラグが立っているオブジェクトを順番に削除
	ObjectBase* target = mpObjectBase;
	do
	{
		ObjectBase* next = target->GetNextObject();
		if (target->IsDeleteFlag())
		{
			Delete(target->GetID(), target->GetObjectTypeNumber());
		}
		target = next;
	} while (target != nullptr);

}

// タグにあったオブジェクトの削除フラグを有効化
void ObjectManager::DeleteSetTag(int tag)
{
	if (mpObjectBase == nullptr)
	{
		return;
	}

	ObjectBase* workObject = mpObjectBase;
	do
	{
		if (!workObject->IsDeleteFlag())
		{
			if (workObject->GetTag() == tag)
			{
				workObject->SetDeleteFlag(true);
			}
		}
		workObject = workObject->GetNextObject();
	} while (workObject != nullptr);
}

// 当たり判定確認
CollisionData ObjectManager::CheckObjectHit(CollisionData collisionData, int typeNumber)
{
	ObjectBase* checkObject = GetTypeObject(typeNumber);
	bool allBaseFlag = false;
	if ((OBJECT_TYPE)typeNumber == OBJECT_TYPE::BASE)
	{
		allBaseFlag = true;
	}

	if (checkObject == nullptr)
	{
		return collisionData;
	}

	ObjectBase* workObject = checkObject;
	do
	{
		// 判定
		collisionData = workObject->HitCheck(collisionData);

		workObject = workObject->GetNextObject(allBaseFlag);
	} while (workObject != nullptr);

	return collisionData;
}

// リストの先頭オブジェクトを取得
ObjectBase* ObjectManager::GetTypeObject(int typeNumber)
{
	switch ((OBJECT_TYPE)typeNumber)
	{
	case OBJECT_TYPE::BASE:
		return mpObjectBase;

	case OBJECT_TYPE::CHARACTER_BASE:
		return mpCharacterBase;

	case OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER:
		return mpCharacterControllerPlayer;

	case OBJECT_TYPE::CHARACTER_CONTROLLER_ENEMY:
		return mpCharacterControllerEnemy;

	case OBJECT_TYPE::COLLISION_BASE:
		return mpCollisionBase;

	case OBJECT_TYPE::ATTACK_BASE:
		return mpAttackBase;

	case OBJECT_TYPE::UI_BASE:
		return mpUIBase;
	}

	return nullptr;
}

// リストの先頭オブジェクトを設定
void ObjectManager::SetTypeObject(int typeNumber, ObjectBase* setObject)
{
	switch ((OBJECT_TYPE)typeNumber)
	{
	case OBJECT_TYPE::BASE:
		mpObjectBase = setObject;
		break;

	case OBJECT_TYPE::CHARACTER_BASE:
		mpCharacterBase = setObject;
		break;

	case OBJECT_TYPE::CHARACTER_CONTROLLER_PLAYER:
		mpCharacterControllerPlayer = setObject;
		break;

	case OBJECT_TYPE::CHARACTER_CONTROLLER_ENEMY:
		mpCharacterControllerEnemy = setObject;
		break;

	case OBJECT_TYPE::COLLISION_BASE:
		mpCollisionBase = setObject;
		break;

	case OBJECT_TYPE::ATTACK_BASE:
		mpAttackBase = setObject;
		break;

	case OBJECT_TYPE::UI_BASE:
		mpUIBase = setObject;
		break;
	}
}