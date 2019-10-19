﻿#include "InputController.h"
#include"HandleSpawnItem.h"


void InputController::OnKeyDown(int KeyCode)
{
	float sx, sy;
	player->GetPosition(sx, sy);
	if (player->CheckAutoWalk()) {
		return;
	}

	if (player->GetPowerUpTime() != 0)
	{
		return;
	}
	if (player->GetActack_Time() != 0) // đang dùng sub weapon
	{
		return;
	}


	if (player->GetState() == SIMON_STATE_DEFLECT) {
		return;
	}
	switch (KeyCode)
	{

	case DIK_1:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDWhip, sx, sy - 64, false);
		break;
	case DIK_2:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDDagger, sx, sy - 64, false);
		break;
	case DIK_3:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDAXE, sx, sy - 64, false);
		break;
	case DIK_4:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDIPOTION, sx, sy - 64, false);
		break;
	case DIK_5:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDROAST, sx, sy - 64, false);
		break;
	case DIK_6:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDMONEYBAGRED, sx, sy - 64, false);
		break;
	case DIK_Q:
		scene->JumpToState(GSCENE_01);
		break;
	case DIK_W:
		scene->JumpToState(GSCENE_01_GH);
		break;
	case DIK_E:
		scene->JumpToState(GSTATE_02);
		break;
	case DIK_R:
		scene->JumpToState(GSTATE_02_UDG);
		break;
	case DIK_T:
		scene->JumpToState(GSTATE_02_B);
		break;
	case DIK_Y:
		scene->JumpToState(GSCENE_02_N);
		break;
	case DIK_U:
		scene->JumpToState(GSCENE_03);
		break;
	case DIK_TAB:
		scene->KillAllEnemy();
		break;
	case DIK_H:
		player->SetAutoWalk(true);
		break;
	case DIK_SPACE:
		if (!player->CheckIsJumping()
			&& player->GetState() != SIMON_STATE_SIT
			&& !player->CheckAttack()
			&& !player->CheckIsOnStair())
			player->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_C: {
		if (player->GetActack_Time() == 0
			&& player->GetCurrentSubWeapon() != -1
			&& !player->CheckAttack())
		{
			player->StartUseSubWeapon();
		}
		break;

	}
	case DIK_F:
		if (!player->CheckAttack()
			&& !player->CheckIsUseSubWeapon())
		{
			player->StartActack();
			if (player->CheckIsOnStair())
			{

				if (player->CheckStepOnStairDirection() == DIR_UPLEFT
					|| player->CheckStepOnStairDirection() == DIR_UPRIGHT
					&& player->GetState() == SIMON_STATE_UPSTAIR_IDLE)
				{
					player->SetState(SIMON_STATE_UPSTAIR_ATTACK);
				}
				else if (player->CheckStepOnStairDirection() == DIR_DOWNLEFT
					|| player->CheckStepOnStairDirection() == DIR_DOWNRIGHT
					&& player->GetState() == SIMON_STATE_DOWNSTAIR_IDLE)
				{
					player->SetState(SIMON_STATE_DOWNSTAIR_ATTACK);

				}

			}
			else {
				if (player->GetState() == SIMON_STATE_SIT)
				{
					player->SetState(SIMON_STATE_SIT_ATTACK);
				}
				else {


					player->SetState(SIMON_STATE_STAND_ATTACK);
				}

			}

		}

		break;
	case DIK_A: // reset
		player->SetState(SIMON_STATE_IDLE);
		player->SetPosition(50.0f, 0.0f);
		player->SetSpeed(0, 0);
		break;
	}
}

void InputController::OnKeyUp(int KeyCode)
{
}


InputController::InputController()
{
}

void InputController::KeyState(BYTE* states)
{
	if (player->GetState() == SIMON_STATE_DIE) return;
	if (player->CheckAutoWalk()) {
		return;
	}
	if ((player->GetPowerUpTime() != 0) && GetTickCount() - player->GetPowerUpTime() > SIMON_POWERUP_TIME)
	{
		player->SetState(SIMON_STATE_IDLE);
		player->ResetPowerUpTime();
	}

	if (player->GetPowerUpTime() != 0)
	{
		return;
	}
	if (player->GetState() == SIMON_STATE_DEFLECT) {
		return;
	}

	if (player->CheckAttack()) { // dùng attack time thay cho nhiều state attack
		return;
	}

	if ((player->GetActack_Time() != 0) && GetTickCount() - player->GetActack_Time() > SIMON_ATTACK_TIME)
	{
		if (player->CheckIsOnStair())
		{
			if (player->CheckStepOnStairDirection() == DIR_UPLEFT
				|| player->CheckStepOnStairDirection() == DIR_UPRIGHT)
			{
				player->SetLastState(SIMON_STATE_UPSTAIR_ATTACK);
				player->SetState(SIMON_STATE_UPSTAIR_IDLE);
			}
			else if (player->CheckStepOnStairDirection() == DIR_DOWNLEFT
				|| player->CheckStepOnStairDirection() == DIR_DOWNRIGHT)
			{
				player->SetLastState(SIMON_STATE_DOWNSTAIR_ATTACK);
				player->SetState(SIMON_STATE_DOWNSTAIR_IDLE);
			}

		}
		else
			player->SetState(SIMON_STATE_IDLE);
		player->StartDelayAttack();
		player->ResetActack_Time();
		player->ResetSpriteFrame();
		player->ResetUseSubWeapon();
		return;
	}
	if (player->GetActack_Time() != 0) // đang dùng sub weapon
	{
		return;
	}

	if (player->CheckIsJumping() == true) {
		return;

	}
	if (game->IsKeyDown(DIK_UP))
	{

		if (player->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {
			if (player->CheckStepOnStairDirection() == DIR_DOWNLEFT)
				player->SetStepOnStairDirection(DIR_UPRIGHT);
			else if (player->CheckStepOnStairDirection() == DIR_DOWNRIGHT)
				player->SetStepOnStairDirection(DIR_UPLEFT);
			player->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}

		else if (player->CheckCanStepUp()) {
			if (!player->CheckIsOnStair() && player->CheckCollideWithStair()) {
				player->SetStartStepOnStair();
			}
			else if (player->GetState() == SIMON_STATE_UPSTAIR_IDLE) {
				player->SetStartStepOnStair();
			}
			return;
		}

	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (player->GetState() == SIMON_STATE_UPSTAIR_IDLE) {
			if (player->CheckStepOnStairDirection() == DIR_UPRIGHT)
				player->SetStepOnStairDirection(DIR_DOWNLEFT);
			else if (player->CheckStepOnStairDirection() == DIR_UPLEFT) {
				player->SetStepOnStairDirection(DIR_DOWNRIGHT);
			}
			player->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}
		if (player->CheckCanStepDown()) {
			if (!player->CheckIsOnStair() && player->CheckCollideWithStair()) {
				player->SetStartStepOnStair();
			}
			else if (player->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {
				player->SetStartStepOnStair();
			}
			return;
		}

	}
	if (player->CheckIsOnStair() || player->CheckStairOnStair()) {
		return;
	}

	if (game->IsKeyDown(DIK_DOWN)) {
		player->SetState(SIMON_STATE_SIT);
		return;
	}
	else if (game->IsKeyDown(DIK_RIGHT))
		player->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		player->SetState(SIMON_STATE_WALKING_LEFT);
	else
		player->SetState(SIMON_STATE_IDLE);
}
