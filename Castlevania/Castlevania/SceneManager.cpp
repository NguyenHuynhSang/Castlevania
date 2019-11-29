#include "SceneManager.h"
#include"Fishman.h"
#include"HandleSpawnEffects.h"
#include"HandleSpawnEnemy.h"
#include"HandleSpawnItem.h"
#include"HandleSpawnSubWeapon.h"
#include"BossZone.h"
void SceneManager::LoadResource()
{
	CTextures* textures = CTextures::GetInstance();
	textures->Add(ID_TEX_TILESET_1, L"Data\\Map\\Courtyard_bank.png", BACKGROUND_COLOR);
	textures->Add(ID_TEX_TILESET_2, L"Data\\Map\\Great_Hall_bank.png", BACKGROUND_COLOR);
	textures->Add(ID_TEX_TILESET_3, L"Data\\Map\\Underground_bank.png", BACKGROUND_COLOR);
	textures->Add(ID_TEX_UI, L"Data\\UI\\UIpack.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_SIMON, L"Data\\GameObject\\Simon\\SIMON.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_GROUNDOBJECT, L"Data\\GameObject\\Ground\\groundObject.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_WHIP, L"Data\\GameObject\\Weapons\\Whipedip.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SPRITE_BBOX, L"textures\\bbox1.png", D3DCOLOR_XRGB(255, 255, 255));



	textures->Add(ID_TEX_ITEM_PACK, L"Data\\GameObject\\Items\\ITEM_PACK.png", D3DCOLOR_XRGB(255, 0, 255));


	textures->Add(ID_TEX_ZOMBIE, L"Data\\GameObject\\Enemies\\ZOMBIE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_PANTHER, L"Data\\GameObject\\Enemies\\PANTHER.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BAT, L"Data\\GameObject\\Enemies\\BAT.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FISHMAN, L"Data\\GameObject\\Enemies\\Fishman.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FIREBALL, L"Data\\GameObject\\Enemies\\FIREBALL.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_AXE, L"Data\\GameObject\\Sub_weapons\\Axe.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_HOLYWATER, L"Data\\GameObject\\Sub_weapons\\HOLY_WATER.png", D3DCOLOR_XRGB(255, 0, 255));

	textures->Add(ID_TEX_VAMPRITEBAT, L"Data\\GameObject\\\Bosses\\VAMPIRE_BAT.png", D3DCOLOR_XRGB(255, 0, 255));



	textures->Add(ID_TEX_EFFECT, L"Data\\GameObject\\Effect\\EFFECT_PACK.png", D3DCOLOR_XRGB(255, 0, 255));




	resource = ResourceManagement::GetInstance();
	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	resource->LoadSprites("Data\\GameObject\\Simon\\Simon_sprite.xml", texSimon);
	resource->LoadAnimations("Data\\GameObject\\Simon\\Simon_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texUI = textures->Get(ID_TEX_UI);
	resource->LoadSprites("Data\\UI\\UI_sprite.xml", texUI);

	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	resource->LoadSprites("Data\\GameObject\\Weapons\\Whip_sprite.xml", texWhip);
	resource->LoadAnimations("Data\\GameObject\\Weapons\\Whip_ani.xml", animations);




	LPDIRECT3DTEXTURE9 texItem = textures->Get(ID_TEX_ITEM_PACK);
	resource->LoadSprites("Data\\GameObject\\Items\\Item_sprite.xml", texItem);
	resource->LoadAnimations("Data\\GameObject\\Items\\Item_ani.xml", animations);








	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_AXE);
	resource->LoadSprites("Data\\GameObject\\Sub_weapons\\Axe_sprite.xml", texAxe);
	resource->LoadAnimations("Data\\GameObject\\Sub_weapons\\Axe_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texSWHolyWater = textures->Get(ID_TEX_HOLYWATER);
	resource->LoadSprites("Data\\GameObject\\Sub_weapons\\HolyWater_sprite.xml", texSWHolyWater);
	resource->LoadAnimations("Data\\GameObject\\Sub_weapons\\HolyWater_ani.xml", animations);





	LPDIRECT3DTEXTURE9 texGhoul = textures->Get(ID_TEX_ZOMBIE);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Zombie_sprite.xml", texGhoul);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Zombie_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texPanther = textures->Get(ID_TEX_PANTHER);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Panther_sprite.xml", texPanther);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Panther_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texBAT = textures->Get(ID_TEX_BAT);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Bat_sprite.xml", texBAT);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Bat_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texFishman = textures->Get(ID_TEX_FISHMAN);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Fishman_sprite.xml", texFishman);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Fishman_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texFireball = textures->Get(ID_TEX_FIREBALL);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Fireball_sprite.xml", texFireball);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Fireball_ani.xml", animations);



	LPDIRECT3DTEXTURE9 texVampireBat = textures->Get(ID_TEX_VAMPRITEBAT);
	resource->LoadSprites("Data\\GameObject\\Bosses\\VampireBat_sprite.xml", texVampireBat);
	resource->LoadAnimations("Data\\GameObject\\Bosses\\VampireBat_ani.xml", animations);



	LPDIRECT3DTEXTURE9 texEffectFlame = textures->Get(ID_TEX_EFFECT);
	resource->LoadSprites("Data\\GameObject\\Effect\\Effect_sprite.xml", texEffectFlame);
	resource->LoadAnimations("Data\\GameObject\\Effect\\Effect_ani.xml", animations);





	LPDIRECT3DTEXTURE9 texBrick = textures->Get(ID_TEX_GROUNDOBJECT);
	resource->LoadSprites("Data\\GameObject\\Ground\\groundObject_sprite.xml", texBrick);
	resource->LoadAnimations("Data\\GameObject\\Ground\\groundObject_ani.xml", animations);

	maps->AddMap("map1", "Data\\Map\\Courtyard_map.tmx", textures->Get(ID_TEX_TILESET_1));
	maps->AddMap("map2", "Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
	maps->AddMap("map3", "Data\\Map\\Underground_map.tmx", textures->Get(ID_TEX_TILESET_3));
	simon = new CSimon();

}



void SceneManager::CamUpdate(DWORD dt)
{
	if (isNextScene)
	{
		return;
	}
	float cx, cy;
	simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2 - SIMON_BIG_BBOX_WIDTH;
	cy -= SCREEN_HEIGHT / 2;
	if (currentScene == GSCENE_01_GH || currentScene == GSCENE_02_N)
	{
		if (cx > sceneBox.left&& cx < sceneBox.right - SCREEN_WIDTH)
		{
			Camera::GetInstance()->SetCamera(cx, 0.0f);
		}
		else
		{
			if (simon->CheckIsHitDoor()) {
				for (size_t i = 0; i < this->spawnObjects.size(); i++)
				{
					SpawnZone* spawner = dynamic_cast<SpawnZone*>(spawnObjects[i]);
					spawner->DestroyImmediate();
				}
				for (size_t i = 0; i < this->objects.size(); i++)
				{
					if (dynamic_cast<Enemy*>(objects[i]))
					{
						Enemy* e = dynamic_cast<Enemy*>(objects[i]);
						e->DestroyImmediate();
					}


				}
				spawnObjects.clear();
				float camx, camy;
				Camera::GetInstance()->GetCamera(camx, camy);
				if (camx < sceneBox.right - 32 - SCREEN_WIDTH / 2) // move 255 px
				{
					float camVx = 0.1f;
					camx += camVx * dt;
					Camera::GetInstance()->SetCamera(camx, camy);
				}
				else
				{
					door->SetState(DOOR_STATE_OPEN);
				}

			}
		}

		if (door->GetState() == DOOR_STATE_OPEN)
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
						float camVx = 0.1f;
						camx += camVx * dt;
						Camera::GetInstance()->SetCamera(camx, camy);
					}

				}
				else
				{
					door->ResetDoor();
					this->GoNextScene();
				}
			}

		}
	}
	else if (currentScene == GSTATE_02 || currentScene == GSTATE_02_B || currentScene == GSCENE_03)
	{
		if (cx > sceneBox.left&& cx < sceneBox.right - SCREEN_WIDTH
			&& !simon->CheckIsFightWithBoss())
			Camera::GetInstance()->SetCamera(cx, 0.0f);
	}
	else {
		if (cx > 0 && cx < currentMap->GetMapWidth() - SCREEN_WIDTH)
			Camera::GetInstance()->SetCamera(cx, 0.0f);
	}

}

void SceneManager::GetListUnitFromGrid()
{
	listUnit.clear();
	this->objects.clear();

	while (!qItem.empty())
	{
		Unit* unit = new Unit(this->grid, qItem.front());
		qItem.pop();
	}

	while (!qEnemy.empty())
	{
		Unit* unit = new Unit(this->grid, qEnemy.front());
		qEnemy.pop();
	}
	while (!qSubWeapon.empty())
	{
		Unit* unit = new Unit(this->grid, qSubWeapon.front());
		qSubWeapon.pop();
	}
	while (!qEffect.empty())
	{
		Unit* unit = new Unit(this->grid, qEffect.front());
		qEffect.pop();
	}
	grid->GetListUnit(listUnit);
	for (size_t i = 0; i < groundObjects.size(); i++)
	{
		this->objects.push_back(groundObjects[i]);
	}
	for (size_t i = 0; i < spawnObjects.size(); i++)
	{
		this->objects.push_back(spawnObjects[i]);
	}
	for (size_t i = 0; i < listUnit.size(); i++)
	{
		this->objects.push_back(listUnit[i]->GetGameObject());
	}


}

void SceneManager::UpdateGrid()
{
	for (size_t i = 0; i < listUnit.size(); i++)
	{
		LPGAMEOBJECT obj = listUnit[i]->GetGameObject();
		float x_, y_;
		obj->GetPosition(x_, y_);
		grid->Update(listUnit[i], x_, y_);
	}


}

void SceneManager::HandleCrossEffect()
{

	if (simon->CheckIsGetCross())
	{
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

void SceneManager::OnCreate()
{
	game = CGame::GetInstance();
	this->stateTime = GAMESTATE_TIME;
	LoadResource();
	LoadScene();
	HandleSpawnItem::GetInstance()->Init(this);
	HandleSpawnEnemy::GetInstance()->Init(this);
	HandleSpawnEffects::GetInstance()->Init(this);
	HandleSpawnSubWeapon::GetInstance()->Init(this);
}
int SceneManager::CheckNumOfFishMan()
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
void SceneManager::Update(DWORD dt)
{

	if (this->simon->GetState() == SIMON_STATE_DIE)
	{
		if (this->reset_start == 0) reset_start = GetTickCount();
		else if (GetTickCount() - this->reset_start > 2000) {
			this->isNextScene = true;
			simon->ResetPoint();
			simon->SetState(SIMON_STATE_IDLE);
			this->reset_start = 0;
		}
	}

	if (this->simon->CheckIsFightWithBoss() && !phantomBat->CheckAwake())
	{
		phantomBat->StartAwake();
		bound = new BoundMap();
		RECT bossActiceBox = phantomBat->GetActiveArea();
		bound->SetPosition(bossActiceBox.left, bossActiceBox.top);
		bound->SetSize(15, abs(bossActiceBox.bottom - bossActiceBox.top));
		Unit* unit = new Unit(this->grid, bound);
	}
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

	if (this->isNextScene) {
		LoadScene();
		this->isNextScene = false;
		return;
	}


	if (simon->CheckIsGetCross())
	{
		KillAllEnemy();
	}
	HandleCrossEffect();


	hud->Update();


	GetListUnitFromGrid();
	// Update camera to follow simon

	vector<LPGAMEOBJECT> coObjects;
	coObjects.clear();


	GetCoObjects(simon, coObjects);
	simon->Update(dt, &coObjects);
	//update object
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
				int nextSceneID = nextscene->CheckSceneDef();
				this->JumpToScene(nextSceneID);
				nextscene->DestroyImmediate();
			}
		}
	}

	CamUpdate(dt);
	/// cap nhat lai vi tri cac unit trong grid
	UpdateGrid();

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
void SceneManager::Render()
{
	if (this->isNextScene) return;

	currentMap->Render();

	for (std::size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}


	hud->Render();
	simon->Render();



}
void SceneManager::SceneUpdate()
{
}

void SceneManager::GetCoObjects(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>& coObjects)
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

void SceneManager::FreezeEnemy(bool flag)
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

void SceneManager::KillAllEnemy()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i]->CheckActive()) // chỉ kill những enemy đang nằm trong cam
		{
			this->enemies[i]->SetDestroy();
		}
	}


}

void SceneManager::LoadScene()
{
	CTextures* textures = CTextures::GetInstance();
	Camera::GetInstance()->SetAllowScrollCam(false);

	delete grid;
	switch (this->currentScene)
	{
	case GSCENE_01:

		currentMap = maps->Get("map1");
		grid = new Grid(currentMap->GetMapWidth(), currentMap->GetMapHeight());
		LoadObjects(GSCENE_01);
		break;
	case GSCENE_01_GH:
		currentMap = maps->Get("map2");
		grid = new Grid(currentMap->GetMapWidth(), currentMap->GetMapHeight());
		LoadObjects(GSCENE_01_GH);
		break;
	case GSTATE_02:
	{
		currentMap = maps->Get("map2");
		grid = new Grid(currentMap->GetMapWidth(), currentMap->GetMapHeight());
		LoadObjects(GSTATE_02);
		break;
	}
	case GSTATE_02_UDG:
	{
		currentMap = maps->Get("map3");
		grid = new Grid(currentMap->GetMapWidth(), currentMap->GetMapHeight());
		LoadObjects(GSTATE_02_UDG);
		break;
	}
	case GSTATE_02_B:
	{

		currentMap = maps->Get("map2");
		grid = new Grid(currentMap->GetMapWidth(), currentMap->GetMapHeight());
		LoadObjects(GSTATE_02_B);
		break;
	}
	case GSCENE_02_N: {
		currentMap = maps->Get("map2");
		grid = new Grid(currentMap->GetMapWidth(), currentMap->GetMapHeight());
		LoadObjects(GSCENE_02_N);
		break;
	}
	case GSCENE_03: {
		currentMap = maps->Get("map2");
		grid = new Grid(currentMap->GetMapWidth(), currentMap->GetMapHeight());
		LoadObjects(GSCENE_03);
		break;
	}
	}
}

void SceneManager::GoNextScene()
{
	this->currentScene++;
	if (this->currentScene > GSCENE_03) currentScene = GSCENE_03;
	this->isNextScene = true;


}

void SceneManager::JumpToScene(int state)
{
	this->currentScene = state;
	this->isNextScene = true;
}

void SceneManager::LoadObjects(int currentscene)
{
	DebugOut(L"Load object \n");
	//for (UINT i = 0; i < objects.size(); i++) {
	//	if (dynamic_cast<Enemy *>(objects[i])
	//		|| dynamic_cast<Item *>(objects[i])
	//		|| dynamic_cast<Ground *>(objects[i])
	//		|| dynamic_cast<Effects*>(objects[i])
	//		|| dynamic_cast<CSimon*>(objects[i])
	//		|| dynamic_cast<SpawnZone*>(objects[i])
	//		|| dynamic_cast<SubWeapon*>(objects[i])
	//		)
	//	{
	//		continue; // tránh trường hợp con trỏ bị delete 2 lần
	//	}
	//	else
	//	{
	//		delete objects[i];
	//	}
	//}
	for (UINT i = 0; i < enemies.size(); i++) delete enemies[i];
	for (UINT i = 0; i < subWeapon.size(); i++) delete subWeapon[i];
	for (UINT i = 0; i < groundObjects.size(); i++) delete groundObjects[i];
	for (UINT i = 0; i < items.size(); i++) delete items[i];
	for (UINT i = 0; i < effects.size(); i++) delete effects[i];
	for (UINT i = 0; i < spawnObjects.size(); i++) delete spawnObjects[i];
	Unit* unit;
	objects.clear();
	enemies.clear();
	groundObjects.clear();
	items.clear();
	effects.clear();
	subWeapon.clear();
	simon->ResetState();
	spawnObjects.clear();

	switch (this->currentScene)
	{
	case GSCENE_01:
	{
	
		Camera::GetInstance()->SetCamera(0.0f, 0.0f);
		auto simonPos = currentMap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
		}

		auto groundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			groundObjects.push_back(ground);
		}



		auto entryObject = currentMap->GetObjects().find(ID_TILE_OBJECT_ENTRY);
		for (const auto& child : entryObject->second) {
			entry = new Entry();
			entry->SetSize(child->GetWidth(), child->GetHeight());
			entry->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, entry);
		}


		auto triggerObject = currentMap->GetObjects().find(ID_TILE_OBJECT_TRIGGER);
		for (const auto& child : triggerObject->second) {
			trigger = new MoneyBagTrigger();
			trigger->SetSize(child->GetWidth(), child->GetHeight());
			trigger->SetPosition(child->GetX(), child->GetY());
			auto moneyBagObject = currentMap->GetObjects().find(ID_TILE_OBJECT_MONEY_BAG);
			for (const auto& smallchild : moneyBagObject->second) {
				trigger->SetItemPosition(smallchild->GetX(), smallchild->GetY() - smallchild->GetHeight());
			}
			unit = new Unit(this->grid, trigger);
		}


		auto nextsceneObject = currentMap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, nextScene);
		}

		auto boundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}


		auto torchObject = currentMap->GetObjects().find(ID_TILE_OBJECT_TORCH);
		for (const auto& child : torchObject->second) {
			torch = new Torch();
			torch->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			torch->SetItem(child->GetPropertyByKey("item"));
			unit = new Unit(this->grid, torch);
		}
		break;
	}

	case GSCENE_01_GH:
	{
	
		Camera::GetInstance()->SetCamera(0.0f, 0.0f);
		auto simonPos = currentMap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			}

		}


		auto camObject = currentMap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
		for (const auto& child : camObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				int l = child->GetX();
				int t = child->GetY();
				int r = child->GetX() + child->GetWidth();
				int b = child->GetY() + child->GetHeight();
				sceneBox = { l,t,r,b };
			}
		}

		auto groundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			this->groundObjects.push_back(ground);
		}

		auto boundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}

		auto spawnObject = currentMap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				this->spawnObjects.push_back(spawnZone);
			}

		}

		auto stairObject = currentMap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				unit = new Unit(this->grid, stair);
			}

		}


		auto candleObject = currentMap->GetObjects().find(ID_TILE_OBJECT_CANDLE);
		for (const auto& child : candleObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				candle = new Candle();
				candle->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, candle);
			}

		}

		auto brickObject = currentMap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, brick);
			}

		}

		auto doorObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GS2_DOOR);
		for (const auto& child : doorObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				door = new Door();
				door->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, door);
			}

		}
		break;
	}
	case GSTATE_02:
	{
	
		auto simonPos = currentMap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			}

		}


		auto camObject = currentMap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
		for (const auto& child : camObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				int l = child->GetX();
				int t = child->GetY();
				int r = child->GetX() + child->GetWidth();
				int b = child->GetY() + child->GetHeight();
				sceneBox = { l,t,r,b };
				Camera::GetInstance()->SetCamera(l, 0);
			}
		}

		auto groundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			groundObjects.push_back(ground);
		}

		auto boundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}

		auto spawnObject = currentMap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				this->spawnObjects.push_back(spawnZone);
			}

		}

		auto brickObject = currentMap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, brick);
			}

		}

		auto stairObject = currentMap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				unit = new Unit(this->grid, stair);
			}

		}


		auto nextsceneObject = currentMap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, nextScene);
		}
		break;
	}
	case GSTATE_02_UDG:
	{
	
		Camera::GetInstance()->SetCamera(0.0f, 0.0f);
		auto simonPos = currentMap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			int x = child->GetX();
			int y = child->GetY() - child->GetHeight();
			simon->SetPosition(x, y);
		}
		simon->SetState(SIMON_STATE_DOWNSTAIR_IDLE);

		auto groundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			this->groundObjects.push_back(ground);
		}

		auto boundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			unit = new Unit(this->grid, bound);
		}

		auto triggerObject = currentMap->GetObjects().find(ID_TILE_OBJECT_TRIGGER);
		for (const auto& child : triggerObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			trigger = new MoneyBagTrigger();
			trigger->SetSize(child->GetWidth(), child->GetHeight());
			trigger->SetPosition(child->GetX(), child->GetY());
			auto moneyBagObject = currentMap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_MONERBAG);
			for (const auto& smallchild : moneyBagObject->second) {
				trigger->SetItemPosition(smallchild->GetX(), smallchild->GetY() - smallchild->GetHeight());
			}
			unit = new Unit(this->grid, trigger);
		}


		auto stairObject = currentMap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_STAIR);
		for (const auto& child : stairObject->second) {
			stair = new StairTrigger();
			stair->SetDirection(child->GetPropertyByKey("dir"));
			stair->SetSize(child->GetWidth(), child->GetHeight());
			stair->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, stair);
		}

		auto spawnObject = currentMap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
			spawnZone->SetSize(child->GetWidth(), child->GetHeight());
			spawnZone->SetPosition(child->GetX(), child->GetY());
			this->spawnObjects.push_back(spawnZone);
		}


		auto waterObject = currentMap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_WATER);
		for (const auto& child : waterObject->second) {
			water = new Water();
			water->SetSize(child->GetWidth(), child->GetHeight());
			water->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			unit = new Unit(this->grid, water);
		}

		auto brickObject = currentMap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_BRICK);
		for (const auto& child : brickObject->second) {
			brick = new CBrick();
			brick->SetState(child->GetPropertyByKey("brickstate"));
			brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			unit = new Unit(this->grid, brick);
		}

		auto nextsceneObject = currentMap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, nextScene);
		}
		break;

	}
	case GSTATE_02_B:
	{
	

		auto simonPos = currentMap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02_B)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				//	DebugOut(L"[Complete]Load Simon position in game world \n");
			}

		}
		simon->SetState(SIMON_STATE_UPSTAIR_IDLE);



		auto camObject = currentMap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
		for (const auto& child : camObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				int l = child->GetX();
				int t = child->GetY();
				int r = child->GetX() + child->GetWidth();
				int b = child->GetY() + child->GetHeight();
				sceneBox = { l,t,r,b };
				Camera::GetInstance()->SetCamera(l, 0);
			}
		}

		auto groundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			groundObjects.push_back(ground);
		}

		auto boundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}

		auto spawnObject = currentMap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				this->spawnObjects.push_back(spawnZone);
			}

		}

		auto brickObject = currentMap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, brick);
			}

		}

		auto stairObject = currentMap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				unit = new Unit(this->grid, stair);
			}

		}


		auto nextsceneObject = currentMap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, nextScene);
		}
		break;
	}

	case GSCENE_02_N:
	{
	
		auto simonPos = currentMap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_02_N)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				//	DebugOut(L"[Complete]Load Simon position in game world \n");
			}

		}
		simon->SetState(SIMON_STATE_UPSTAIR_IDLE);



		auto camObject = currentMap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
		for (const auto& child : camObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				int l = child->GetX();
				int t = child->GetY();
				int r = child->GetX() + child->GetWidth();
				int b = child->GetY() + child->GetHeight();
				sceneBox = { l,t,r,b };
				Camera::GetInstance()->SetCamera(l, 0);
			}
		}

		auto groundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			this->groundObjects.push_back(ground);
		}

		auto boundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}

		auto spawnObject = currentMap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				this->spawnObjects.push_back(spawnZone);
			}

		}

		auto brickObject = currentMap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, brick);
			}

		}

		auto stairObject = currentMap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_02_N)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				unit = new Unit(this->grid, stair);
			}

		}

		auto nextsceneObject = currentMap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, nextScene);
		}


		auto doorObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GS2_DOOR);
		for (const auto& child : doorObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_02_N)
			{
				door = new Door();
				door->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, door);
			}

		}
		break;
	}

	case GSCENE_03:
	{
	
		auto simonPos = currentMap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			}

		}



		auto camObject = currentMap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
		for (const auto& child : camObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				int l = child->GetX();
				int t = child->GetY();
				int r = child->GetX() + child->GetWidth();
				int b = child->GetY() + child->GetHeight();
				sceneBox = { l,t,r,b };
				Camera::GetInstance()->SetCamera(l, 0.0f);
			}
		}

		auto groundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			this->groundObjects.push_back(ground);
		}

		auto boundObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}

		auto spawnObject = currentMap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				this->spawnObjects.push_back(spawnZone);
			}

		}

		auto stairObject = currentMap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				unit = new Unit(this->grid, stair);
			}

		}


		auto candleObject = currentMap->GetObjects().find(ID_TILE_OBJECT_CANDLE);
		for (const auto& child : candleObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				candle = new Candle();
				candle->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, candle);
			}

		}

		auto brickObject = currentMap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, brick);
			}

		}

		auto bossBatObject = currentMap->GetObjects().find(ID_TILE_OBJECT_BOSSBAT);
		for (const auto& child : bossBatObject->second) {
			phantomBat = new PhantomBat();
			phantomBat->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			unit = new Unit(this->grid, phantomBat);
		}

		auto bossBatBorder = currentMap->GetObjects().find(ID_TILE_OBJECT_BOSSBAT_BORDER);
		for (const auto& child : bossBatBorder->second) {
			float l = 0, t = 0, r = 0, b = 0;
			l = child->GetX();
			t = child->GetY() + 80;
			r = l + child->GetWidth();
			b = t + child->GetHeight();
			RECT rect = { l,t,r,b };
			phantomBat->SetActiveArea(rect);
		}

		auto bossZone = currentMap->GetObjects().find(ID_TILE_OBJECT_BOSSTRIGGER);
		for (const auto& child : bossZone->second) {
			BossZone* bzone = new BossZone();
			bzone->SetSize(child->GetWidth(), child->GetHeight());
			bzone->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bzone);
		}




		break;
	}
	}
}

SceneManager::SceneManager()
{
	this->isNextScene = false;
	this->currentScene = GSCENE_01;
	maps = MapManager::GetInstance();
	hud = new Hud(this);
}


SceneManager::~SceneManager()
{
}
