#include "PlayScene.h"
#include"Fishman.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnEnemy.h"
#include"HandleSpawnItem.h"
#include"HandleSpawnSubWeapon.h"
#include"BossZone.h"
#include"PlayScene.h"
#include"TypeConverter.h"
void PlayScene::LoadResource()
{
	int startScene = 1;
	ResourceManager::GetInstance()->LoadSceneData("Data\\Data\\Data01.xml", this->miniScenes);
	this->currentMiniScene = miniScenes.at(1);
	simon = new CSimon();
	LoadObjects();
	D3DXVECTOR2 pos = this->entryPoint.at(currentMiniScene->entryPointID);
	this->simon->SetPosition(pos.x, pos.y);
	this->sceneBox = this->sceneAreas.at(currentMiniScene->areaID);
	currentMap = maps->Get(currentMiniScene->mapID);
	grid = grids.at(currentMiniScene->mapID);

}



void PlayScene::CamUpdate(DWORD dt)
{
	if (isNextScene)
	{
		return;
	}
	float cx, cy;
	simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2 - 30;
	cy -= SCREEN_HEIGHT / 2;

	for (size_t i = 0; i < this->listDoor.size(); i++)
	{
		if (listDoor[i]->CheckIsColideWithPlayer())
		{
			this->door = (listDoor.at(i));
			door->SetIsColicePlayer(false);
		}

	}
	if (cx > sceneBox.left&& cx < sceneBox.right - SCREEN_WIDTH && !simon->CheckIsFightWithBoss())
	{
		Camera::GetInstance()->SetCamera(cx, 0.0f);
	}

	if (simon->CheckIsHitDoor()) {
		for (size_t i = 0; i < this->objects.size(); i++)
		{
			if (dynamic_cast<Enemy*>(objects[i]))
			{
				Enemy* e = dynamic_cast<Enemy*>(objects[i]);
				e->DestroyImmediate();
			}


		}

		float camx, camy;
		Camera::GetInstance()->GetCamera(camx, camy);
		if (camx < sceneBox.right - SCREEN_WIDTH / 2) // move 255 px
		{
			float camVx = 0.2f;
			camx += camVx * dt;
			Camera::GetInstance()->SetCamera(camx, camy);
		}
		else
		{
			door->SetState(DOOR_STATE_OPEN);
		}

	}

	if (door != NULL && door->GetState() == DOOR_STATE_OPEN)
	{
		if (simon->CheckAutoWalk() == false)
		{
			simon->SetLastPosition(simon->x);
		}
		if (door->CheckIsDoorOpened())
		{
			simon->SetAutoWalk(true);
		
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
		}

		if (simon->SimonAutoWalkaStep(simon->GetLastPosition() + 150))
		{
			float camx, camy;
			Camera::GetInstance()->GetCamera(camx, camy);
			if (camx < sceneBox.right - 32) // move 255 px
			{
				door->SetState(DOOR_STATE_CLOSING);
				if (door->CheckIsDoorClosed())
				{
					float camVx = 0.2f;
					camx += camVx * dt;
					Camera::GetInstance()->SetCamera(camx, camy);
				}

			}
			else
			{
				door->ResetDoor();
				float x_, y_;
				door->GetPosition(x_, y_);
				BoundMap* bound = new BoundMap();
				bound->SetSize(10, SCREEN_HEIGHT / 2);
				bound->SetPosition(x_, y_);
				AddToGrid(bound, grid);
				door = NULL;
				simon->SetAutoWalk(false);
				simon->ResetState();
				this->currentMiniScene = miniScenes.at(currentMiniScene->nextMiniScene);
				this->isNextScene = true;

			}


		}

	}



}

void PlayScene::GetListobjectFromGrid()
{
	this->objects.clear();

	while (!qItem.empty())
	{
		AddToGrid(qItem.front(), grid);
		qItem.pop();
	}

	while (!qEnemy.empty())
	{
		AddToGrid(qEnemy.front(), grid);
		qEnemy.pop();
	}
	while (!qSubWeapon.empty())
	{
		AddToGrid(qSubWeapon.front(), grid);
		qSubWeapon.pop();
	}
	while (!qEffect.empty())
	{
		AddToGrid(qEffect.front(), grid);
		qEffect.pop();
	}
	grid->GetListobject(objects);



}

void PlayScene::UpdateGrid()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		LPGAMEOBJECT obj = objects[i];
		float x_, y_;
		obj->GetPosition(x_, y_);
		grid->Update(obj);
	}


}

void PlayScene::GoToNextArea()
{
	D3DXVECTOR2 pos = this->entryPoint.at(currentMiniScene->entryPointID);
	this->simon->SetPosition(pos.x, pos.y);
	this->sceneBox = this->sceneAreas.at(currentMiniScene->areaID);
	Camera::GetInstance()->SetCamera(sceneBox.left, 0);
	currentMap = maps->Get(currentMiniScene->mapID);
	grid = grids.at(currentMiniScene->mapID);
	grid->ResetStaticObject();
	hud->setState(currentMiniScene->state);
}

void PlayScene::HandleCrossEffect()
{

	if (simon->CheckIsGetCross())
	{
		sound->Play(eSound::soundHolyCross);
		if (this->cross_start == 0)
		{
			cross_start = GetTickCount64();
		}
		simon->ResetIsGetCross();
		playCrossEffect = true;
	}

	if (this->cross_start != 0
		&& GetTickCount64() - this->cross_start > CROSS_EFFECT_TIME)
	{
		playCrossEffect = false;

		this->cross_start = 0;
	}
}


int PlayScene::CheckNumOfFishMan()
{
	int counter = 0;
	for (size_t i = 0; i < enemies.size(); i++)
	{
		if (dynamic_cast<Fishman*>(enemies.at(i)))
		{
			counter++;
		}
	}
	return counter;
}
void PlayScene::Update(DWORD dt)
{
	GameTimeCounter();


	if (this->simon->GetState() == SIMON_STATE_DIE)
	{
		if (this->reset_start == 0) reset_start = GetTickCount();
		else if (GetTickCount() - this->reset_start > 2000) {
			this->isNextScene = true;
			simon->ResetPoint();
			this->currentMiniScene = miniScenes.at(currentMiniScene->revivalSceneID);
			simon->SetState(SIMON_STATE_IDLE);
			this->reset_start = 0;
		}
	}

	if (this->simon->CheckIsFightWithBoss() && !phantomBat->CheckAwake())
	{
		if (sound->isPlaying(eSound::musicState1))
		{
			sound->Stop(eSound::musicState1);
			sound->Play(eSound::music_PhantomBat, true);
		}
		phantomBat->StartAwake();
		bossAreaWall = new BoundMap();
		RECT bossActiceBox = phantomBat->GetActiveArea();
		bossAreaWall->SetPosition(bossActiceBox.left, bossActiceBox.top);
		bossAreaWall->SetSize(15, abs(bossActiceBox.bottom - bossActiceBox.top));
		AddToGrid(bossAreaWall, grid);
	}

	if (!this->simon->CheckIsFightWithBoss())
	{
		if (sound->isPlaying(eSound::music_PhantomBat))
		{
			sound->Stop(eSound::music_PhantomBat);

		}
		sound->Play(eSound::musicState1, true);

	}

	if (this->isNextScene) {
		if (bossAreaWall!=NULL)
		{
			bossAreaWall->DestroyImmediate();
		}
		if (simon->CheckIsFightWithBoss())
		{
			phantomBat->Reset();
			simon->ResetFightBoss();
		}
		
		this->isNextScene = false;
		GoToNextArea();
		return;
	}

	if (simon->CheckIsGetCross())
	{
		KillAllEnemy();
	}
	HandleCrossEffect();
	hud->Update();
	GetListobjectFromGrid();

	vector<LPGAMEOBJECT> coObjects;
	coObjects.clear();
	GetCoObjects(simon, coObjects);
	simon->Update(dt, &coObjects);
	coObjects.clear();
	for (std::size_t i = 0; i < objects.size(); i++) //object
	{
		GetCoObjects(objects.at(i), coObjects);
		objects[i]->Update(dt, &coObjects);
		if (dynamic_cast<NextScene*> (objects[i]))
		{
			NextScene* nextscene = dynamic_cast<NextScene*>(objects[i]);
			if (nextscene->CheckIsColliceWithPlayer())
			{
				nextscene->Reset();
				int playerState = nextscene->GetPlayerAction();
				this->currentMiniScene = miniScenes.at(nextscene->GetNextSceneID());
				this->simon->ResetState();
				D3DXVECTOR2 pos = this->entryPoint.at(currentMiniScene->entryPointID);
				this->simon->SetPosition(pos.x, pos.y);
				this->simon->SetState(playerState);
				this->isNextScene = true;
			}
		}
	}

	CamUpdate(dt);
	UpdateGrid();
	CleanListObject();
}
void PlayScene::Render()
{
	if (this->isNextScene) return;

	currentMap->Render();

	for (std::size_t i = 0; i < objects.size(); i++)
	{
	
		objects[i]->Render();
	}


	hud->Render();
	simon->Render();

	//grid->Render();


}


void PlayScene::GetCoObjects(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>& coObjects)
{
	// lấy ds những object dùng xét va chạm với object truyền vào
	coObjects.clear();
	if (dynamic_cast<Item*>(obj))
	{
		for (auto object : this->objects)
		{
			if (dynamic_cast<Ground*>(object))
			{
				coObjects.push_back(object);
			}
		}
	}
	else if (dynamic_cast<Enemy*>(obj))
	{
		if (dynamic_cast<PhantomBat*>(obj))
		{
			coObjects.push_back(simon); // past simon potion to boss
		}
		else {
			for (auto object : this->objects)
			{
				if (dynamic_cast<Ground*>(object)
					|| dynamic_cast<Water*>(object))
				{
					coObjects.push_back(object);
				}
			}
		}

	}
	else if (dynamic_cast<SubWeapon*>(obj)
		|| dynamic_cast<Whip*>(obj))
	{

		for (auto object : this->objects)
		{
			if (dynamic_cast<Ground*>(object)
				|| dynamic_cast<Candle*>(object)
				|| dynamic_cast<Enemy*>(object)
				|| dynamic_cast<Torch*>(object)
				|| dynamic_cast<CBrick*>(object))
			{
				coObjects.push_back(object);
			}
		}
	}
	else if (dynamic_cast<CSimon*>(obj))
	{
		for (auto object : this->objects)
		{
			if (dynamic_cast<Ground*>(object)
				|| dynamic_cast<BoundMap*>(object)
				|| dynamic_cast<CBrick*>(object)
				|| dynamic_cast<Entry*>(object)
				|| dynamic_cast<NextScene*>(object)
				|| dynamic_cast<StairTrigger*>(object)
				|| dynamic_cast<MoneyBagTrigger*>(object)
				|| dynamic_cast<Door*>(object)
				|| dynamic_cast<Item*>(object)
				|| dynamic_cast<Candle*>(object)
				|| dynamic_cast<Torch*>(object)
				|| dynamic_cast<Enemy*>(object)
				|| dynamic_cast<Water*>(object)
				|| dynamic_cast<BossZone*>(object)
				|| dynamic_cast<CBrick*>(object))


			{
				coObjects.push_back(object);
			}
		}

	}

}

void PlayScene::AddToGrid(LPGAMEOBJECT object, Grid* grid, bool alwayUpdate)
{
	if (!alwayUpdate)
	{
		grid->Add(object);
	}
	else {
		grid->AddToAlwayUpdateObjects(object);
	}

}

void PlayScene::FreezeEnemy(bool flag)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->CheckActive())
		{
			Enemy* enemy = dynamic_cast<Enemy*> (enemies.at(i));
			enemy->SetFreeze(flag);
		}

	}
}

void PlayScene::KillAllEnemy()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i]->CheckActive()) // chỉ kill những enemy đang nằm trong cam
		{
			this->enemies[i]->SetDestroy();
		}
	}


}



void PlayScene::JumpToScene(int state)
{
	this->isNextScene = true;
	this->currentMiniScene = this->miniScenes.at(state);
}

void PlayScene::LoadObjects()
{
	DebugOut(L"Load object \n");

	objects.clear();
	enemies.clear();

	items.clear();
	effects.clear();
	subWeapon.clear();
	//simon->ResetState();
	spawnObjects.clear();


	for (auto const& map : *(maps->GetMaps()))
	{

		Grid* grid = new Grid(map.second->GetMapWidth(), map.second->GetMapHeight());
		std::string mapName = map.first;
		for (auto const& objectLayer : map.second->GetObjects())
		{
			auto name = objectLayer.first;
			auto groupObject = objectLayer.second;
			auto objectId = -1;
			if (string2EntityType.count(name) > 0)
			{
				objectId = string2EntityType.at(name);
			}



			switch (objectId)
			{
			case ObjectID::OPlayer:
				for (const auto& child : groupObject) {
					D3DXVECTOR2 entry = { (float)(child->GetX()), (float)(child->GetY() - child->GetHeight()) };
					std::string name = child->GetName();
					int id = std::stoi(name);
					entryPoint.insert(std::make_pair(id, entry));
				}
				break;
			case ObjectID::OBoss:
				for (const auto& child : groupObject) {
					phantomBat = new PhantomBat();
					phantomBat->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
					auto bossBatBorder = map.second->GetObjects().at("BossBorder");
					for (const auto& smallchild : bossBatBorder) {
						float l = 0, t = 0, r = 0, b = 0;
						l = smallchild->GetX();
						t = smallchild->GetY() + 80;
						r = l + smallchild->GetWidth();
						b = t + smallchild->GetHeight();
						RECT rect = { l,t,r,b };
						phantomBat->SetActiveArea(rect);
					}
					AddToGrid(phantomBat, grid);

				}
				break;
			case ObjectID::OBossTrigger:
				for (const auto& child : groupObject) {
					BossZone* bzone = new BossZone();
					bzone->SetSize(child->GetWidth(), child->GetHeight());
					bzone->SetPosition(child->GetX(), child->GetY());
					AddToGrid(bzone, grid);
				}
				break;
			case ObjectID::OGround:
				for (const auto& child : groupObject) {
					ground = new Ground();
					ground->SetSize(child->GetWidth(), child->GetHeight());
					ground->SetPosition(child->GetX(), child->GetY());
					AddToGrid(ground, grid, true);
				}
				break;
			case ObjectID::OWall:
				for (const auto& child : groupObject) {
					bound = new BoundMap();
					bound->SetSize(child->GetWidth(), child->GetHeight());
					bound->SetPosition(child->GetX(), child->GetY());
					AddToGrid(bound, grid, true);
				}
				break;
			case ObjectID::OWater:
				for (const auto& child : groupObject) {
					water = new Water();
					water->SetSize(child->GetWidth(), child->GetHeight());
					water->SetPosition(child->GetX(), child->GetY());
					AddToGrid(water, grid, true);
				}
				break;
			case ObjectID::ODoor:
				for (const auto& child : groupObject) {
					door = new Door();
					door->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
					AddToGrid(door, grid, true);
					this->listDoor.push_back(door);
				}
				break;
			case ObjectID::OEntrance:
				for (const auto& child : groupObject) {
					entry = new Entry();
					entry->SetSize(child->GetWidth(), child->GetHeight());
					entry->SetPosition(child->GetX(), child->GetY());
					AddToGrid(entry, grid);
				}
				break;
			case ObjectID::OTorch:
				for (const auto& child : groupObject) {
					torch = new Torch();
					torch->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
					torch->SetItem(child->GetIntProperty("item"));
					AddToGrid(torch, grid);
				}
				break;
			case ObjectID::ONextmap:
				for (const auto& child : groupObject) {
					nextScene = new NextScene(child->GetIntProperty("playerAction"), child->GetIntProperty("nextSceneID"));
					nextScene->SetSize(child->GetWidth(), child->GetHeight());
					nextScene->SetPosition(child->GetX(), child->GetY());
					AddToGrid(nextScene, grid);
				}
				break;
			case ObjectID::OMoneyBagTrigger:
				for (const auto& child : groupObject) {
					trigger = new MoneyBagTrigger();
					trigger->SetSize(child->GetWidth(), child->GetHeight());
					trigger->SetPosition(child->GetX(), child->GetY());
					auto moneyBagObject = map.second->GetObjects().find("MoneyBag");
					for (const auto& smallchild : moneyBagObject->second) {
						trigger->SetItemPosition(smallchild->GetX(), smallchild->GetY() - smallchild->GetHeight());
					}
					AddToGrid(trigger, grid);
				}
				break;
			case ObjectID::OStair:
				for (const auto& child : groupObject) {
					stair = new StairTrigger();
					stair->SetDirection(child->GetIntProperty("dir"));
					stair->SetSize(child->GetWidth(), child->GetHeight());
					stair->SetPosition(child->GetX(), child->GetY());
					AddToGrid(stair, grid);
				}
				break;
			case ObjectID::OSpawner:
				for (const auto& child : groupObject) {
					spawnZone = new SpawnZone(child->GetIntProperty("enemydef"), child->GetIntProperty("num"), child->GetIntProperty("respawntime"));
					spawnZone->SetSize(child->GetWidth(), child->GetHeight());
					spawnZone->SetPosition(child->GetX(), child->GetY());
					AddToGrid(spawnZone, grid, true);
				}
				break;
			case ObjectID::OBirck:
				for (const auto& child : groupObject) {
					brick = new CBrick();
					brick->SetState(child->GetIntProperty("brickstate"));
					brick->SetItemDef(child->GetIntProperty("itemdef"));
					brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
					AddToGrid(brick, grid);
				}
				break;
			case ObjectID::OCam:
				for (const auto& child : groupObject) {
					int l = child->GetX();
					int t = child->GetY();
					int r = child->GetX() + child->GetWidth();
					int b = child->GetY() + child->GetHeight();
					sceneBox = { l,t,r,b };
					this->sceneAreas.insert(std::make_pair(std::stoi(child->GetName()), sceneBox));
				}
				break;
			case ObjectID::OCandle:
				for (const auto& child : groupObject) {
					candle = new Candle();
					candle->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
					int itemdef = child->GetIntProperty("itemdef");
					candle->SetItem(itemdef);

					AddToGrid(candle, grid);
				}
				break;
			default:
				DebugOut(L"Ten object khong dung \n");
				break;
			}
		}

		this->grids.insert(std::make_pair(mapName, grid));
	}
}
void PlayScene::CleanListObject()
{
	for (vector<LPGAMEOBJECT>::iterator it = objects.begin(); it != objects.end(); ) {

		if ((*it)->isDestroyed) {
			it = objects.erase(it);
		}
		else ++it;
	}
	for (vector<LPGAMEOBJECT>::iterator it = enemies.begin(); it != enemies.end(); ) {

		if ((*it)->isDestroyed) {
			it = enemies.erase(it);
		}
		else ++it;
	}
	for (vector<LPGAMEOBJECT>::iterator it = items.begin(); it != items.end(); ) {

		if ((*it)->isDestroyed) {
			it = items.erase(it);
		}
		else ++it;
	}
	for (vector<LPGAMEOBJECT>::iterator it = effects.begin(); it != effects.end(); ) {

		if ((*it)->isDestroyed) {
			it = effects.erase(it);
		}
		else ++it;
	}
	for (vector<LPGAMEOBJECT>::iterator it = subWeapon.begin(); it != subWeapon.end(); ) {

		if ((*it)->isDestroyed) {
			it = subWeapon.erase(it);
		}
		else ++it;
	}
	for (vector<LPGAMEOBJECT>::iterator it = spawnObjects.begin(); it != spawnObjects.end(); ) {

		if ((*it)->isDestroyed) {
			it = spawnObjects.erase(it);
		}
		else ++it;
	}
}
void PlayScene::GameTimeCounter()
{
	if (this->timeCounter_start == 0)
	{
		timeCounter_start = GetTickCount();
	}
	else if (GetTickCount() - this->timeCounter_start >= 1000)
	{
		if (this->stateTime > 0)
		{
			this->stateTime--;
		}

		this->timeCounter_start = 0;
	}
}

void PlayScene::OnKeyDown(int keyCode)
{
	bool devSupport = false;
	switch (keyCode)
	{
		devSupport = true;
	case DIK_Q:
		JumpToScene(1);
		break;
	case DIK_W:
		JumpToScene(2);
		break;
	case DIK_E:
		JumpToScene(3);
		break;
	case DIK_R:
		JumpToScene(4);
		break;
	case DIK_T:
		JumpToScene(5);
		break;
	case DIK_Y:
		JumpToScene(6);
		break;
	case DIK_U:
		JumpToScene(7);
		break;
	case DIK_I:
		JumpToScene(8);
		break;
	}
	if (devSupport)
	{
		return;
	}
	if (simon->GetState() == SIMON_STATE_DIE || simon->GetState() == SIMON_STATE_FALL_DOWN) return;

	if (simon->CheckLockControl())
	{
		return;
	}


	float sx, sy;
	simon->GetPosition(sx, sy);
	if (simon->CheckAutoWalk()) {
		return;
	}

	if (simon->GetPowerUpTime() != 0)
	{
		return;
	}
	if (simon->GetActack_Time() != 0) // đang dùng sub weapon
	{
		return;
	}


	if (simon->GetState() == SIMON_STATE_DEFLECT) {
		return;
	}
	switch (keyCode)
	{

	case DIK_1:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDWhip, sx, sy - 64, false);
		break;
	case DIK_2:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDMULTIFLYSHOT, sx, sy - 64, false);
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
		HandleSpawnItem::GetInstance()->SpawnItem(ITDCROSS, sx, sy - 64, false);
		break;
	case DIK_TAB:
		KillAllEnemy();
		break;
	case DIK_H:
		simon->SetAutoWalk(true);
		break;
	case DIK_SPACE:
		if (!simon->CheckIsJumping()
			&& simon->GetState() != SIMON_STATE_SIT
			&& !simon->CheckAttack()
			&& !simon->CheckIsOnStair())
			simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_C: {
		if (simon->GetActack_Time() == 0
			&& simon->GetCurrentSubWeapon() != -1
			&& !simon->CheckAttack())
		{
			simon->StartUseSubWeapon();
		}
		break;

	}
	case DIK_F:
		if (game->IsKeyDown(DIK_UP))
		{
			DebugOut(L"Simon use sub weapon \n");
			if (simon->GetActack_Time() == 0
				&& simon->GetCurrentSubWeapon() != -1
				&& !simon->CheckAttack())
			{
				simon->StartUseSubWeapon();
				break;
			}

		}

		if (!simon->CheckAttack()
			&& !simon->CheckIsUseSubWeapon())
		{
			simon->StartActack();
			if (simon->CheckIsOnStair())
			{

				if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::UPLEFT
					|| simon->CheckStepOnStairDirection() == STAIRDIRECTION::UPRIGHT
					&& simon->GetState() == SIMON_STATE_UPSTAIR_IDLE)
				{
					simon->SetState(SIMON_STATE_UPSTAIR_ATTACK);
				}
				else if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNLEFT
					|| simon->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNRIGHT
					&& simon->GetState() == SIMON_STATE_DOWNSTAIR_IDLE)
				{
					simon->SetState(SIMON_STATE_DOWNSTAIR_ATTACK);

				}

			}
			else {
				if (simon->GetState() == SIMON_STATE_SIT)
				{
					simon->SetState(SIMON_STATE_SIT_ATTACK);
				}
				else {


					simon->SetState(SIMON_STATE_STAND_ATTACK);
				}

			}

		}


		break;

	}
}
void PlayScene::OnKeyUp(int keyCode)
{
}
void PlayScene::KeyState(BYTE* states)
{

	if (simon->GetState() == SIMON_STATE_DIE || simon->GetState() == SIMON_STATE_FALL_DOWN) return;
	if (simon->CheckLockControl())
	{
		return;
	}
	if (simon->CheckAutoWalk()) {
		return;
	}
	if ((simon->GetPowerUpTime() != 0) && GetTickCount() - simon->GetPowerUpTime() > SIMON_POWERUP_TIME)
	{
		simon->SetState(SIMON_STATE_IDLE);
		simon->ResetPowerUpTime();
	}

	if (simon->GetPowerUpTime() != 0)
	{
		return;
	}
	if (simon->GetState() == SIMON_STATE_DEFLECT) {
		return;
	}

	if (simon->CheckAttack()) { // dùng attack time thay cho nhiều state attack
		return;
	}

	if ((simon->GetActack_Time() != 0) && GetTickCount() - simon->GetActack_Time() > SIMON_ATTACK_TIME)
	{
		if (simon->CheckIsOnStair())
		{
			if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::UPLEFT
				|| simon->CheckStepOnStairDirection() == STAIRDIRECTION::UPRIGHT)
			{
				simon->SetLastState(SIMON_STATE_UPSTAIR_ATTACK);
				simon->SetState(SIMON_STATE_UPSTAIR_IDLE);
			}
			else if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNLEFT
				|| simon->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNRIGHT)
			{
				simon->SetLastState(SIMON_STATE_DOWNSTAIR_ATTACK);
				simon->SetState(SIMON_STATE_DOWNSTAIR_IDLE);
			}

		}
		else
			simon->SetState(SIMON_STATE_IDLE, false);

		simon->ResetActack_Time();
		simon->ResetSpriteFrame();
		simon->ResetUseSubWeapon();
		return;
	}
	if (simon->GetActack_Time() != 0) // đang dùng sub weapon
	{
		return;
	}

	if (simon->CheckIsJumping() == true) {
		return;

	}

	if (game->IsKeyDown(DIK_UP))
	{

		if (simon->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {


			if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNLEFT)
				simon->SetStepOnStairDirection(STAIRDIRECTION::UPRIGHT);
			else if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::DOWNRIGHT)
				simon->SetStepOnStairDirection(STAIRDIRECTION::UPLEFT);
			simon->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}

		else if (simon->CheckCanStepUp()) {
			if (!simon->CheckIsOnStair() && simon->CheckCollideWithStair()) {
				simon->SetStartStepOnStair();
			}
			else if (simon->GetState() == SIMON_STATE_UPSTAIR_IDLE) {

				simon->SetStartStepOnStair();
			}
			return;
		}

	}
	else if (game->IsKeyDown(DIK_DOWN))
	{

		if (simon->GetState() == SIMON_STATE_UPSTAIR_IDLE) {
			if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::UPRIGHT)
				simon->SetStepOnStairDirection(STAIRDIRECTION::DOWNLEFT);
			else if (simon->CheckStepOnStairDirection() == STAIRDIRECTION::UPLEFT) {
				simon->SetStepOnStairDirection(STAIRDIRECTION::DOWNRIGHT);
			}
			simon->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}
		if (simon->CheckCanStepDown()) {
			if (!simon->CheckIsOnStair() && simon->CheckCollideWithStair()) {
				simon->SetStartStepOnStair();
			}
			else if (simon->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {
				simon->SetStartStepOnStair();
			}
			return;
		}

	}
	if (simon->CheckIsOnStair() || simon->CheckStairOnStair()) {
		return;
	}

	if (game->IsKeyDown(DIK_DOWN)) {
		simon->SetState(SIMON_STATE_SIT);
		return;
	}
	else if (game->IsKeyDown(DIK_RIGHT))
		simon->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		simon->SetState(SIMON_STATE_WALKING_LEFT);
	else
		simon->SetState(SIMON_STATE_IDLE);
}


PlayScene::PlayScene()
{
	this->stateTime = GAMESTATE_TIME;
	this->isNextScene = false;
	this->currentScene = GSCENE_01;
	sound = Sound::GetInstance();
	maps = MapManager::GetInstance();
	hud = new Hud(this);
	DebugOut(L"Init play scene \n");
	HandleSpawnEffects::GetInstance()->Init(this);
	HandleSpawnEnemy::GetInstance()->Init(this);
	HandleSpawnItem::GetInstance()->Init(this);
	HandleSpawnSubWeapon::GetInstance()->Init(this);

}


PlayScene::~PlayScene()
{
	for (size_t i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}
