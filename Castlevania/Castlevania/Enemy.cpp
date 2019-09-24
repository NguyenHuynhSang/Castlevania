#include "Enemy.h"
#include"Effects.h"
#include"Flame.h"
#include"SceneManagement.h"
void Enemy::UpdateEnemy()
{
	if (this->setDestroy) {
		this->TurnOffCollision();
		Effects* effect = new Flame();
		effect->SetPositionInWorld(this->x + 10, this->y + 32 / 4);
		effect->AddItemDef(0);
		SceneManagement::GetInstance()->SpawnEffect(effect);
		isDestroyed = true;
	}
}








Enemy::~Enemy()
{
}
