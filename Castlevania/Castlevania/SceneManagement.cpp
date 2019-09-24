﻿#include "SceneManagement.h"


SceneManagement * SceneManagement::__instance = NULL;

void SceneManagement::LoadResource()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_TILESET_1, L"Data\\Map\\Courtyard_bank.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TILESET_2, L"Data\\Map\\Great_Hall_bank.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SIMON, L"Data\\GameObject\\Simon\\SIMON.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_WHIP, L"Data\\GameObject\\Weapons\\Whipedip.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SPRITE_BBOX, L"textures\\bbox1.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TORCH, L"Data\\GameObject\\Ground\\Torch.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CANDLE, L"Data\\GameObject\\Ground\\Candle.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_HEART, L"Data\\GameObject\\Items\\Heart.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MORNINGSTAR, L"Data\\GameObject\\Items\\MORNING_STAR.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MONEYBAG, L"Data\\GameObject\\Items\\Money_Bag.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_DAGGER, L"Data\\GameObject\\Items\\Dagger.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ZOMBIE, L"Data\\GameObject\\Enemies\\ZOMBIE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_PANTHER, L"Data\\GameObject\\Enemies\\PANTHER.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BAT, L"Data\\GameObject\\Enemies\\BAT.png", D3DCOLOR_XRGB(255, 0, 255));


	textures->Add(ID_TEX_EFFECT_FLAME, L"Data\\GameObject\\Effect\\Flame.png", D3DCOLOR_XRGB(255, 0, 255));
	resource = ResourceManagement::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	resource->LoadSprites("Data\\GameObject\\Simon\\Simon_sprite.xml", texSimon);
	resource->LoadAnimations("Data\\GameObject\\Simon\\Simon_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	resource->LoadSprites("Data\\GameObject\\Weapons\\Whip_sprite.xml", texWhip);
	resource->LoadAnimations("Data\\GameObject\\Weapons\\Whip_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texTorch = textures->Get(ID_TEX_TORCH);
	resource->LoadSprites("Data\\GameObject\\Ground\\Torch_sprite.xml", texTorch);
	resource->LoadAnimations("Data\\GameObject\\Ground\\Torch_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texHeart = textures->Get(ID_TEX_ITEM_HEART);
	resource->LoadSprites("Data\\GameObject\\Items\\Heart_sprite.xml", texHeart);
	resource->LoadAnimations("Data\\GameObject\\Items\\Heart_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texMorningStar = textures->Get(ID_TEX_ITEM_MORNINGSTAR);
	resource->LoadSprites("Data\\GameObject\\Items\\MorningStar_sprite.xml", texMorningStar);
	resource->LoadAnimations("Data\\GameObject\\Items\\MorningStar_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texMoneyBag = textures->Get(ID_TEX_ITEM_MONEYBAG);
	resource->LoadSprites("Data\\GameObject\\Items\\MoneyBag_sprite.xml", texMoneyBag);
	resource->LoadAnimations("Data\\GameObject\\Items\\MoneyBag_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texDagger = textures->Get(ID_TEX_ITEM_DAGGER);
	resource->LoadSprites("Data\\GameObject\\Items\\Dagger_sprite.xml", texDagger);
	resource->LoadAnimations("Data\\GameObject\\Items\\Dagger_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texGhoul = textures->Get(ID_TEX_ZOMBIE);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Zombie_sprite.xml", texGhoul);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Zombie_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texPanther = textures->Get(ID_TEX_PANTHER);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Panther_sprite.xml", texPanther);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Panther_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texBAT = textures->Get(ID_TEX_BAT);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Bat_sprite.xml", texBAT);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Bat_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texEffectFlame = textures->Get(ID_TEX_EFFECT_FLAME);
	resource->LoadSprites("Data\\GameObject\\Effect\\Flame_sprite.xml", texEffectFlame);
	resource->LoadAnimations("Data\\GameObject\\Effect\\Flame_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE);
	resource->LoadSprites("Data\\GameObject\\Ground\\Candle_sprite.xml", texCandle);
	resource->LoadAnimations("Data\\GameObject\\Ground\\Candle_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add("20001", 408, 225, 424, 241, texMisc);



	simon = new CSimon();
	objects.push_back(simon);
}

void SceneManagement::HandleSpawningItem()
{
	//if(itemtoSpawn.push)
}

SceneManagement *SceneManagement::GetInstance()
{
	if (__instance == NULL) __instance = new SceneManagement();
	return __instance;
}
void SceneManagement::OnCreate()
{
	game = CGame::GetInstance();
	LoadResource();
	LoadScene();
}
void SceneManagement::Update(DWORD dt)
{
	// We know that Simon is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 
	if (this->isNextScene) {
		LoadScene();
		game->SetCamPos(0, 0); //reset cam
		this->isNextScene = false;
		return;
	}

	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;

	//clean object
	for (vector<LPGAMEOBJECT>::iterator it = objects.begin(); it != objects.end(); ) {

		if ((*it)->isDestroyed) {
			delete (*it);
			it = objects.erase(it);
		}
		else ++it;
	}
	//clean subweapon
	for (vector<LPGAMEOBJECT>::iterator it = subWeapon.begin(); it != subWeapon.end(); ) {
		if ((*it)->isDestroyed) {
			delete (*it);
			it = subWeapon.erase(it);
		}
		else ++it;
	}
	//clean enemy
	for (vector<LPGAMEOBJECT>::iterator it = enemies.begin(); it != enemies.end(); ) {

		if ((*it)->isDestroyed) {
			delete (*it);
			it = enemies.erase(it);
			DebugOut(L"Xoa enemy \n");
		}
		else ++it;
	}
	//clean effects
	for (vector<LPGAMEOBJECT>::iterator it = effects.begin(); it != effects.end(); ) {

		if ((*it)->isDestroyed) {
			delete (*it);
			it = effects.erase(it);
		}
		else ++it;
	}
	//clean item
	for (vector<LPGAMEOBJECT>::iterator it = items.begin(); it != items.end(); ) {

		if ((*it)->isDestroyed) {
			delete (*it);
			it = items.erase(it);
		}
		else ++it;
	}

	
		


	vector<LPGAMEOBJECT> coObjects;
	for (std::size_t i = 1; i < objects.size(); i++)
	{
		if (dynamic_cast<Ground *>(objects[i]))
		{
			coObjects.push_back(objects[i]);
			continue;
		}
		else if (objects[i]->x > cx && objects[i]->x < cx + SCREEN_WIDTH+128)
		{
			coObjects.push_back(objects[i]);
		}

	}
	for (std::size_t i = 0; i < subWeapon.size(); i++)
	{
		coObjects.push_back(subWeapon[i]);
	}
	for (std::size_t i = 0; i < enemies.size(); i++)
	{
		if (enemies[i]->x > cx && enemies[i]->x < cx + SCREEN_WIDTH)
		{
			coObjects.push_back(enemies[i]);
		}
	}	
	for (std::size_t i = 0; i < items.size(); i++)  //item
	{
		coObjects.push_back(items[i]);
	}

	//update object
	for (std::size_t i = 0; i < objects.size(); i++) //object
	{
		objects[i]->Update(dt, &coObjects);
	}
	//update subweapon
	for (std::size_t i = 0; i < subWeapon.size(); i++) //object
	{
		if (subWeapon[i]->x<0 || subWeapon[i]->x>cmap->GetMapWidth() || subWeapon[i]->y > SCREEN_HEIGHT)
		{
			subWeapon[i]->SetDestroy();
		}
		subWeapon[i]->Update(dt, &coObjects);
	}
	//update enemies
	for (std::size_t i = 0; i < enemies.size(); i++) //object
	{
		if (enemies[i]->x<0 || enemies[i]->x>cmap->GetMapWidth() || enemies[i]->y > SCREEN_HEIGHT)
		{
			enemies[i]->SetDestroy();
		}
		enemies[i]->Update(dt, &coObjects);
	}
	
	//update efftects
	for (std::size_t i = 0; i < effects.size(); i++) //effect
	{
		effects[i]->Update(dt, &coObjects);
	}
	//update items
	for (std::size_t i = 0; i < items.size(); i++)
	{
		items[i]->Update(dt, &coObjects);
	}

	


	if (cx > 0 && cx < cmap->GetMapWidth() - SCREEN_WIDTH)
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);


}
void SceneManagement::Render()
{
	float cx, cy;
	game->GetCamera(cx, cy);
	if (this->isNextScene) return;
	cmap->Render();
	for (std::size_t i = 1; i < objects.size(); i++)
	{
		if (objects[i]->x > cx&&objects[i]->x < cx + SCREEN_WIDTH)
		{
			objects[i]->Render();
		}
	}

	for (std::size_t i = 0; i < subWeapon.size(); i++)
	{
		if (subWeapon[i]->x > cx&&subWeapon[i]->x < cx + SCREEN_WIDTH)
		{
			subWeapon[i]->Render();
		}
	}

	for (std::size_t i = 0; i < enemies.size(); i++) {
		if (enemies[i]->x > cx&&enemies[i]->x < cx + SCREEN_WIDTH)
		{
			enemies[i]->Render();
		}
	}

	for (std::size_t i = 0; i < this->items.size(); i++)
		this->items[i]->Render();
	for (std::size_t i = 0; i < this->effects.size(); i++)
		this->effects[i]->Render();
	objects[0]->Render();


}
void SceneManagement::SceneUpdate()
{
}

void SceneManagement::LoadScene()
{
	CTextures * textures = CTextures::GetInstance();
	cmap->GetObjects().clear();
	switch (this->currentScene)
	{
	case GSTATE_01:

		cmap->LoadMap("Data\\Map\\Courtyard_map.tmx", textures->Get(ID_TEX_TILESET_1));
		cmap->LoadObjects("Data\\Map\\Courtyard_map.tmx");
		LoadObjects(GSTATE_01);
		break;
	case GSTATE_02:
		cmap->ClearObject();
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
		cmap->LoadObjects("Data\\Map\\Great_Hall_map.tmx");
		LoadObjects(GSTATE_02);
		break;
	case GSTATE_03:
		break;

	}
}

void SceneManagement::GoNextScene()
{
	this->currentScene++;
	if (this->currentScene > GSTATE_02) currentScene = GSTATE_02;

	this->isNextScene = true;


}

void SceneManagement::JumpToState(int state)
{
	this->currentScene = state;
	this->isNextScene = true;
}

void SceneManagement::LoadObjects(int currentscene)
{
	DebugOut(L"Load object \n");
	for (UINT i = 1; i < objects.size(); i++) delete objects[i]; // mặc định object[0] là Simon 
	for (UINT i = 0; i < enemies.size(); i++) delete enemies[i];
	for (UINT i = 0; i < subWeapon.size(); i++) delete subWeapon[i];
	for (UINT i = 0; i < items.size(); i++) delete items[i];
	for (UINT i = 0; i < effects.size(); i++) delete effects[i];
	
	objects.clear();
	enemies.clear();
	items.clear();
	effects.clear();
	subWeapon.clear();
	simon->ResetState();
	switch (this->currentScene)
	{
	case GSTATE_01:
	{

		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			//	DebugOut(L"[Complete]Load Simon position in game world \n");
		}
		objects.push_back(simon);

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			objects.push_back(ground);
		}



		auto entryObject = cmap->GetObjects().find(ID_TILE_OBJECT_ENTRY);
		for (const auto& child : entryObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			entry = new Entry();
			entry->SetSize(child->GetWidth(), child->GetHeight());
			entry->SetPosition(child->GetX(), child->GetY());
			objects.push_back(entry);
		}


		auto triggerObject = cmap->GetObjects().find(ID_TILE_OBJECT_TRIGGER);
		for (const auto& child : triggerObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			trigger = new MoneyBagTrigger();
			trigger->SetSize(child->GetWidth(), child->GetHeight());
			trigger->SetPosition(child->GetX(), child->GetY());
			auto moneyBagObject = cmap->GetObjects().find(ID_TILE_OBJECT_MONEY_BAG);
			for (const auto& smallchild : moneyBagObject->second) {
				trigger->SetItemPosition(smallchild->GetX(), smallchild->GetY() - smallchild->GetHeight());
			}
			objects.push_back(trigger);
		}


		auto nextsceneObject = cmap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			objects.push_back(nextScene);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			objects.push_back(bound);
		}


		auto torchObject = cmap->GetObjects().find(ID_TILE_OBJECT_TORCH);
		for (const auto& child : torchObject->second) {
			torch = new Torch();
			torch->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			torch->SetItem(child->GetPropertyByKey("item"));
			objects.push_back(torch);
		}
		break;
	}

	case GSTATE_02:
	{
		
		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			//	DebugOut(L"[Complete]Load Simon position in game world \n");
		}
		objects.push_back(simon);


		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"Ground state 2 x=%f y=%f \n", ground->x, ground->y);
			objects.push_back(ground);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			objects.push_back(bound);
		}

		auto spawnObject = cmap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
			spawnZone->SetSize(child->GetWidth(), child->GetHeight());
			spawnZone->SetPosition(child->GetX(), child->GetY());
			objects.push_back(spawnZone);
		}

		auto pantherObject = cmap->GetObjects().find(ID_TILE_OBJECT_PANTHER);
		for (const auto& child : pantherObject->second) {
			panther = new Panther();
			//panther->SetRespawnPosition(child->GetX(), child->GetY() - child->GetHeight() + GAME_WORLD_Y);
			panther->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			objects.push_back(panther);
		}


		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			stair = new StairTrigger();
			stair->SetDirection(child->GetPropertyByKey("dir"));
			stair->SetSize(child->GetWidth(), child->GetHeight());
			stair->SetPosition(child->GetX(), child->GetY());
			objects.push_back(stair);
		}


		auto candleObject = cmap->GetObjects().find(ID_TILE_OBJECT_CANDLE);
		for (const auto& child : candleObject->second) {
			candle = new Candle();
			candle->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			objects.push_back(candle);
		}

		break;
	}

	case GSTATE_03:
		break;

	}


}

SceneManagement::SceneManagement()
{
	this->isNextScene = false;
	this->currentScene = GSTATE_02;

	cmap = CTileMap::GetInstance();
}


SceneManagement::~SceneManagement()
{
}
