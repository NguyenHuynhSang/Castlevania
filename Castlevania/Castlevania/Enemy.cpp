#include "Enemy.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnItem.h"
void Enemy::UpdateEnemy()
{
	if (this->setDestroy) {
		this->TurnOffCollision();
		HandleSpawnEffects::GetInstance()->SpawnEffect(EFD_FLAME, this->x + 10, this->y + 32 / 4);
		HandleSpawnItem::GetInstance()->SpawnRandomItem(this->x, this->y);
		isDestroyed = true;
	}
}








Enemy::~Enemy()
{
}
