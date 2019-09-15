#include "Enemy.h"
#include"Effects.h"
#include"Flame.h"
#include"SceneManagement.h"
void Enemy::UpdateEnemy()
{
	/*if (!this->reSpawn) {
		return;
	}*/

	/*if (GetTickCount() - this->spawn_start > ENEMY_SPWAWN_TIME) {
		DebugOut(L"Zombie back to worlk \n");
		this->reSpawn = false;
		return;
	}*/

	if (this->isDestroyed) {
		return;
	}
	if (this->setDestroy) {
		this->TurnOffCollision();
		Effects* effect = new Flame();
		effect->SetPositionInWorld(this->x + 10, this->y + 32 / 4);
		SceneManagement::GetInstance()->SpawnEffect(effect);
		isDestroyed = true;
	}
	//CGame *game = CGame::GetInstance();
	//RECT camBox = game->GetCamera();
	//if (CGameObject::AABB(this->respawnX, this->respawnY, this->respawnX + this->enermyBBoxWidth, this->respawnY + this->enermyBBoxHeight, camBox.left,
	//	camBox.top, camBox.right, camBox.bottom
	//)) {
	//	this->ResetSpawnStart();
	//	//DebugOut(L"Zombie Reset spawn start \n");
	//}
	//if (((this->respawnX) - (float)camBox.left) > 0) {
	//	nx = 1;
	//}
	//else if (((this->respawnX) - (float)camBox.left) < 0) {
	//	nx = -1;
	//}

}








Enemy::~Enemy()
{
}
