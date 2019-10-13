#include "SceneManagement.h"
#include"Fishman.h"

SceneManagement * SceneManagement::__instance = NULL;

void SceneManagement::LoadResource()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_TILESET_1, L"Data\\Map\\Courtyard_bank.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TILESET_2, L"Data\\Map\\Great_Hall_bank.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TILESET_3, L"Data\\Map\\Underground_bank.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_UI_HP, L"Data\\UI\\HP.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SIMON, L"Data\\GameObject\\Simon\\SIMON.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_BRICK, L"Data\\GameObject\\Ground\\Brick.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_WHIP, L"Data\\GameObject\\Weapons\\Whipedip.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SPRITE_BBOX, L"textures\\bbox1.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TORCH, L"Data\\GameObject\\Ground\\Torch.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_CANDLE, L"Data\\GameObject\\Ground\\Candle.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_DOOR, L"Data\\GameObject\\Ground\\Door.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_HEART, L"Data\\GameObject\\Items\\Heart.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MORNINGSTAR, L"Data\\GameObject\\Items\\MORNING_STAR.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MONEYBAG, L"Data\\GameObject\\Items\\Money_Bag.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_DAGGER, L"Data\\GameObject\\Items\\Dagger.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_AXE, L"Data\\GameObject\\Items\\Axe.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_STOPWATCH, L"Data\\GameObject\\Items\\StopWatch.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_ROAST, L"Data\\GameObject\\Items\\ROAST.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ZOMBIE, L"Data\\GameObject\\Enemies\\ZOMBIE.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_PANTHER, L"Data\\GameObject\\Enemies\\PANTHER.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_BAT, L"Data\\GameObject\\Enemies\\BAT.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FISHMAN, L"Data\\GameObject\\Enemies\\Fishman.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_FIREBALL, L"Data\\GameObject\\Enemies\\FIREBALL.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_AXE, L"Data\\GameObject\\Sub_weapons\\Axe.png", D3DCOLOR_XRGB(255, 0, 255));

	textures->Add(ID_TEX_EFFECT_FLAME, L"Data\\GameObject\\Effect\\Flame.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_EFFECT_DEBRIS, L"Data\\GameObject\\Effect\\Debris.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_EFFECT_BUBBLE, L"Data\\GameObject\\Effect\\Bubble.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_EFFECT_SCROTE_TEXT, L"Data\\GameObject\\Effect\\ScoreText.png", D3DCOLOR_XRGB(255, 0, 255));

	resource = ResourceManagement::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	resource->LoadSprites("Data\\GameObject\\Simon\\Simon_sprite.xml", texSimon);
	resource->LoadAnimations("Data\\GameObject\\Simon\\Simon_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texHP = textures->Get(ID_TEX_UI_HP);
	resource->LoadSprites("Data\\UI\\HP_sprite.xml", texHP);
	
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	resource->LoadSprites("Data\\GameObject\\Weapons\\Whip_sprite.xml", texWhip);
	resource->LoadAnimations("Data\\GameObject\\Weapons\\Whip_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texTorch = textures->Get(ID_TEX_TORCH);
	resource->LoadSprites("Data\\GameObject\\Ground\\Torch_sprite.xml", texTorch);
	resource->LoadAnimations("Data\\GameObject\\Ground\\Torch_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texDoor = textures->Get(ID_TEX_DOOR);
	resource->LoadSprites("Data\\GameObject\\Ground\\Door_sprite.xml", texDoor);
	resource->LoadAnimations("Data\\GameObject\\Ground\\Door_ani.xml", animations);

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

	LPDIRECT3DTEXTURE9 texItemAxe = textures->Get(ID_TEX_ITEM_AXE);
	resource->LoadSprites("Data\\GameObject\\Items\\Axe_sprite.xml", texItemAxe);
	resource->LoadAnimations("Data\\GameObject\\Items\\Axe_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texItemStopWatch = textures->Get(ID_TEX_ITEM_STOPWATCH);
	resource->LoadSprites("Data\\GameObject\\Items\\StopWatch_sprite.xml", texItemStopWatch);
	resource->LoadAnimations("Data\\GameObject\\Items\\StopWatch_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texItemRoast = textures->Get(ID_TEX_ITEM_ROAST);
	resource->LoadSprites("Data\\GameObject\\Items\\Roast_sprite.xml", texItemRoast);
	resource->LoadAnimations("Data\\GameObject\\Items\\Roast_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texAxe = textures->Get(ID_TEX_AXE);
	resource->LoadSprites("Data\\GameObject\\Sub_weapons\\Axe_sprite.xml", texAxe);
	resource->LoadAnimations("Data\\GameObject\\Sub_weapons\\Axe_ani.xml", animations);


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



	LPDIRECT3DTEXTURE9 texEffectFlame = textures->Get(ID_TEX_EFFECT_FLAME);
	resource->LoadSprites("Data\\GameObject\\Effect\\Flame_sprite.xml", texEffectFlame);
	resource->LoadAnimations("Data\\GameObject\\Effect\\Flame_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texEffectDebris = textures->Get(ID_TEX_EFFECT_DEBRIS);
	resource->LoadSprites("Data\\GameObject\\Effect\\Debris_sprite.xml", texEffectDebris);
	resource->LoadAnimations("Data\\GameObject\\Effect\\Debris_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texEffectBubble = textures->Get(ID_TEX_EFFECT_BUBBLE);
	resource->LoadSprites("Data\\GameObject\\Effect\\Bubble_sprite.xml", texEffectBubble);
	resource->LoadAnimations("Data\\GameObject\\Effect\\Bubble_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texEffectScoreText = textures->Get(ID_TEX_EFFECT_SCROTE_TEXT);
	resource->LoadSprites("Data\\GameObject\\Effect\\ScoreText_sprite.xml", texEffectScoreText);
	resource->LoadAnimations("Data\\GameObject\\Effect\\ScoreText_ani.xml", animations);


	LPDIRECT3DTEXTURE9 texCandle = textures->Get(ID_TEX_CANDLE);
	resource->LoadSprites("Data\\GameObject\\Ground\\Candle_sprite.xml", texCandle);
	resource->LoadAnimations("Data\\GameObject\\Ground\\Candle_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texBrick = textures->Get(ID_TEX_BRICK);
	resource->LoadSprites("Data\\GameObject\\Ground\\Brick_sprite.xml", texBrick);
	resource->LoadAnimations("Data\\GameObject\\Ground\\Brick_ani.xml", animations);





	simon = new CSimon();

}

void SceneManagement::HandleSpawningItem()
{
	//if(itemtoSpawn.push)
}

void SceneManagement::CamUpdate(DWORD dt)
{
	if (isNextScene)
	{
		return;
	}
	float cx, cy;
	simon->GetPosition(cx, cy);
	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	if (currentScene == GSCENE_01_GH || currentScene == GSCENE_02_N)
	{
		if (cx > sceneBox.left && cx < sceneBox.right - SCREEN_WIDTH)
		{
			Camera::GetInstance()->SetCamera(cx, 0.0f);
		}
		else
		{
			if (simon->CheckIsHitDoor()) {
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
			simon->SetAutoWalk(true);
			simon->SetState(SIMON_STATE_WALKING_RIGHT);
			if (simon->SimonAutoWalkaStep(simon->GetLastPosition() + 150))
			{
				float camx, camy;
				Camera::GetInstance()->GetCamera(camx, camy);
				if (camx < sceneBox.right - 32) // move 255 px
				{
					door->SetState(DOOR_STATE_CLOSING);
					float camVx = 0.1f;
					camx += camVx * dt;
					Camera::GetInstance()->SetCamera(camx, camy);
				}
				else
				{

					this->GoNextScene();
				}
			}

		}
	}
	else if (currentScene == GSTATE_02 || currentScene == GSTATE_02_B || currentScene == GSCENE_03)
	{
		if (cx > sceneBox.left && cx < sceneBox.right - SCREEN_WIDTH)
			Camera::GetInstance()->SetCamera(cx, 0.0f);
	}
	else {
		if (cx > 0 && cx < cmap->GetMapWidth() - SCREEN_WIDTH)
			Camera::GetInstance()->SetCamera(cx, 0.0f);
	}

}

void SceneManagement::GetListUnitFromGrid()
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
	grid->GetListUnit(listUnit);
	for (size_t i = 0; i < groundObjects.size(); i++)
	{
		this->objects.push_back(groundObjects[i]);
	}
	for (size_t i = 0; i < listUnit.size(); i++)
	{
		this->objects.push_back(listUnit[i]->GetGameObject());
	}

	//DebugOut(L"listUnit=%d \n", listUnit.size());

}

void SceneManagement::UpdateGrid()
{
	for (size_t i = 0; i < listUnit.size(); i++)
	{
		LPGAMEOBJECT obj = listUnit[i]->GetGameObject();
		float x_, y_;
		obj->GetPosition(x_, y_);
		grid->Update(listUnit[i], x_, y_);
	}


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
int SceneManagement::CheckNumOfFishMan()
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
void SceneManagement::Update(DWORD dt)
{
	
	if (this->isNextScene) {
		LoadScene();
		this->isNextScene = false;
		return;
	}

	hub->Update();
	// update trước để spawn enemy và xử lý va chạm ở frame hiện tại
	for (size_t i = 0; i < spawnObjects.size(); i++)
	{
		spawnObjects[i]->Update(dt);

	}

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
	}
	//update efftects
	for (std::size_t i = 0; i < effects.size(); i++) //effect
	{
		effects[i]->Update(dt);
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
			delete (*it);
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

}
void SceneManagement::Render()
{
	if (this->isNextScene) return;
	
	cmap->Render();
	for (std::size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}

	for (std::size_t i = 0; i < this->effects.size(); i++)
		this->effects[i]->Render();

	hub->Render();
	simon->Render();



}
void SceneManagement::SceneUpdate()
{
}

void SceneManagement::GetCoObjects(LPGAMEOBJECT obj, vector<LPGAMEOBJECT>& coObjects)
{
	// lấy ds những object dùng xét va chạm với object truyền vào

	if (dynamic_cast<Item *>(obj))
	{
		for (auto object : this->objects)
		{
			if (dynamic_cast<Ground *>(object))
			{
				coObjects.push_back(object);
			}
		}
	}
	else if (dynamic_cast<Enemy *>(obj))
	{
		for (auto object : this->objects)
		{
			if (dynamic_cast<Ground *>(object)
				|| dynamic_cast<BoundMap *>(object))
			{
				coObjects.push_back(object);
			}
		}
	}
	else if (dynamic_cast<SubWeapon *>(obj)
		|| dynamic_cast<Whip *>(obj))
	{
		for (auto object : this->enemies)
		{
			coObjects.push_back(object);
		}
		for (auto object : this->objects)
		{
			if (dynamic_cast<Ground *>(object)
				|| dynamic_cast<Candle *>(object)
				|| dynamic_cast<Torch *>(object)
				|| dynamic_cast<CBrick *>(object))
			{
				coObjects.push_back(object);
			}
		}
	}
	else if (dynamic_cast<CSimon *>(obj))
	{
		for (auto object : this->objects)
		{
			if (dynamic_cast<Ground *>(object)
				|| dynamic_cast<BoundMap *>(object)
				|| dynamic_cast<CBrick *>(object)
				|| dynamic_cast<Entry *>(object)
				|| dynamic_cast<NextScene *>(object)
				|| dynamic_cast<StairTrigger *>(object)
				|| dynamic_cast<MoneyBagTrigger *>(object)
				|| dynamic_cast<Door *>(object)
				|| dynamic_cast<Item *>(object)
				|| dynamic_cast<Candle *>(object)
				|| dynamic_cast<Torch *>(object)
				|| dynamic_cast<Enemy *>(object)
				|| dynamic_cast<CBrick *>(object))


			{
				coObjects.push_back(object);
			}
		}

	}

}

void SceneManagement::FreezeEnemy(bool flag)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		Enemy * enemy = dynamic_cast<Enemy*> (enemies.at(i));
		enemy->SetFreeze(flag);
	}
}

void SceneManagement::KillAllEnemy()
{
	for (size_t i = 0; i < this->enemies.size(); i++)
	{
		if (this->enemies[i]->CheckActive())
		{
			this->enemies[i]->SetDestroy();
		}
	}


}

void SceneManagement::LoadScene()
{
	CTextures * textures = CTextures::GetInstance();
	Camera::GetInstance()->SetAllowScrollCam(false);
	cmap->GetObjects().clear();
	delete grid;
	switch (this->currentScene)
	{
	case GSCENE_01:


		cmap->LoadMap("Data\\Map\\Courtyard_map.tmx", textures->Get(ID_TEX_TILESET_1));
		cmap->LoadObjects("Data\\Map\\Courtyard_map.tmx");
		grid = new Grid(cmap->GetMapWidth(), cmap->GetMapHeight());
		LoadObjects(GSCENE_01);
		break;


	case GSCENE_01_GH:
		cmap->ClearObject();
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
		cmap->LoadObjects("Data\\Map\\Great_Hall_map.tmx");
		grid = new Grid(cmap->GetMapWidth(), cmap->GetMapHeight());
		LoadObjects(GSCENE_01_GH);
		break;
	case GSTATE_02:
	{
		cmap->ClearObject();
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
		cmap->LoadObjects("Data\\Map\\Great_Hall_map.tmx");
		grid = new Grid(cmap->GetMapWidth(), cmap->GetMapHeight());
		LoadObjects(GSTATE_02);
		break;
	}
	case GSTATE_02_UDG:
	{
		cmap->ClearObject();
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Underground_map.tmx", textures->Get(ID_TEX_TILESET_3));
		cmap->LoadObjects("Data\\Map\\Underground_map.tmx");
		LoadObjects(GSTATE_02_UDG);
		break;
	}
	case GSTATE_02_B:
	{
		cmap->ClearObject();
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
		cmap->LoadObjects("Data\\Map\\Great_Hall_map.tmx");
		LoadObjects(GSTATE_02_B);
		break;
	}
	case GSCENE_02_N: {
		cmap->ClearObject();
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
		cmap->LoadObjects("Data\\Map\\Great_Hall_map.tmx");
		LoadObjects(GSCENE_02_N);
		break;
	}
	case GSCENE_03: {
		cmap->ClearObject();
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
		cmap->LoadObjects("Data\\Map\\Great_Hall_map.tmx");
		LoadObjects(GSCENE_03);
		break;
	}
	}
}

void SceneManagement::GoNextScene()
{
	this->currentScene++;
	if (this->currentScene > GSCENE_03) currentScene = GSCENE_03;
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
	for (UINT i = 0; i < objects.size(); i++) {
		if (dynamic_cast<Enemy *>(objects.at(i))
			|| dynamic_cast<Item *>(objects.at(i))
			|| dynamic_cast<Ground *>(objects.at(i))
			|| dynamic_cast<CSimon *>(objects.at(i))
			|| dynamic_cast<SubWeapon *>(objects.at(i))
			)
		{
			continue;
		}
		else
		{
			

			delete objects[i];
		}
	}
	for (UINT i = 0; i < enemies.size(); i++) delete enemies[i];
	for (UINT i = 0; i < subWeapon.size(); i++) delete subWeapon[i];
	for (UINT i = 0; i < groundObjects.size(); i++) delete groundObjects[i];
	for (UINT i = 0; i < items.size(); i++) delete items[i];
	for (UINT i = 0; i < effects.size(); i++) delete effects[i];
	for (UINT i = 0; i < spawnObjects.size(); i++) delete spawnObjects[i];
	Unit * unit;
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
		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
		}

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			groundObjects.push_back(ground);
			//unit = new Unit(this->grid, ground, ground->x, ground->y);

		}



		auto entryObject = cmap->GetObjects().find(ID_TILE_OBJECT_ENTRY);
		for (const auto& child : entryObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			entry = new Entry();
			entry->SetSize(child->GetWidth(), child->GetHeight());
			entry->SetPosition(child->GetX(), child->GetY());
			//objects.push_back(entry);
			unit = new Unit(this->grid, entry);
			//	m_grid->AddObject(entry);
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
			unit = new Unit(this->grid, trigger);
			//	objects.push_back(trigger);
			//	m_grid->AddObject(trigger);
		}


		auto nextsceneObject = cmap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			//objects.push_back(nextScene);
			unit = new Unit(this->grid, nextScene);
			//	m_grid->AddObject(nextScene);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			//objects.push_back(bound);
			unit = new Unit(this->grid, bound);
			//	m_grid->AddObject(bound);
		}


		auto torchObject = cmap->GetObjects().find(ID_TILE_OBJECT_TORCH);
		for (const auto& child : torchObject->second) {
			torch = new Torch();
			torch->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			torch->SetItem(child->GetPropertyByKey("item"));
			//	objects.push_back(torch);
			unit = new Unit(this->grid, torch);
			//m_grid->AddObject(torch);
		}
		break;
	}

	case GSCENE_01_GH:
	{
		Camera::GetInstance()->SetCamera(0.0f, 0.0f);
		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				//	DebugOut(L"[Complete]Load Simon position in game world \n");
			}

		}


		auto camObject = cmap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
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

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			this->groundObjects.push_back(ground);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}

		auto spawnObject = cmap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				this->spawnObjects.push_back(spawnZone);
			}

		}

		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_STAIR);
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


		auto candleObject = cmap->GetObjects().find(ID_TILE_OBJECT_CANDLE);
		for (const auto& child : candleObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_01_GH)
			{
				candle = new Candle();
				candle->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				unit = new Unit(this->grid, candle);
			}

		}

		auto brickObject = cmap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
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

		auto doorObject = cmap->GetObjects().find(ID_TILE_OBJECT_GS2_DOOR);
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
		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				//	DebugOut(L"[Complete]Load Simon position in game world \n");
			}

		}


		auto camObject = cmap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
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

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			groundObjects.push_back(ground);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			unit = new Unit(this->grid, bound);
		}

		auto spawnObject = cmap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				this->spawnObjects.push_back(spawnZone);
			}

		}

		auto brickObject = cmap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
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

		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_STAIR);
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


		auto nextsceneObject = cmap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
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
	case GSTATE_02_UDG:
	{
		Camera::GetInstance()->SetCamera(0.0f, 0.0f);
		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			int x = child->GetX();
			int y = child->GetY() - child->GetHeight();
			simon->SetPosition(x, y);
		}
		simon->SetState(SIMON_STATE_DOWNSTAIR_IDLE);
		objects.push_back(simon);

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
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

		auto triggerObject = cmap->GetObjects().find(ID_TILE_OBJECT_TRIGGER);
		for (const auto& child : triggerObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			trigger = new MoneyBagTrigger();
			trigger->SetSize(child->GetWidth(), child->GetHeight());
			trigger->SetPosition(child->GetX(), child->GetY());
			auto moneyBagObject = cmap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_MONERBAG);
			for (const auto& smallchild : moneyBagObject->second) {
				trigger->SetItemPosition(smallchild->GetX(), smallchild->GetY() - smallchild->GetHeight());
			}
			objects.push_back(trigger);
		}


		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_STAIR);
		for (const auto& child : stairObject->second) {
			stair = new StairTrigger();
			stair->SetDirection(child->GetPropertyByKey("dir"));
			stair->SetSize(child->GetWidth(), child->GetHeight());
			stair->SetPosition(child->GetX(), child->GetY());
			objects.push_back(stair);
		}

		auto spawnObject = cmap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
			spawnZone->SetSize(child->GetWidth(), child->GetHeight());
			spawnZone->SetPosition(child->GetX(), child->GetY());
			objects.push_back(spawnZone);
		}


		auto waterObject = cmap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_WATER);
		for (const auto& child : waterObject->second) {
			water = new Water();
			water->SetSize(child->GetWidth(), child->GetHeight());
			water->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			objects.push_back(water);
		}

		auto brickObject = cmap->GetObjects().find(ID_TILE_OBJECT_UNDERGROUND_BRICK);
		for (const auto& child : brickObject->second) {
			brick = new CBrick();
			brick->SetState(child->GetPropertyByKey("brickstate"));
			brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			objects.push_back(brick);
		}

		auto nextsceneObject = cmap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			objects.push_back(nextScene);
		}
		break;

	}
	case GSTATE_02_B:
	{


		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02_B)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				//	DebugOut(L"[Complete]Load Simon position in game world \n");
			}

		}
		simon->SetState(SIMON_STATE_UPSTAIR_IDLE);
		objects.push_back(simon);


		auto camObject = cmap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
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

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			objects.push_back(ground);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			objects.push_back(bound);
		}

		auto spawnObject = cmap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				objects.push_back(spawnZone);
			}

		}

		auto brickObject = cmap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				objects.push_back(brick);
			}

		}

		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				objects.push_back(stair);
			}

		}


		auto nextsceneObject = cmap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			objects.push_back(nextScene);
		}
		break;
	}

	case GSCENE_02_N:
	{
		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_02_N)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				//	DebugOut(L"[Complete]Load Simon position in game world \n");
			}

		}
		simon->SetState(SIMON_STATE_UPSTAIR_IDLE);
		objects.push_back(simon);


		auto camObject = cmap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
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

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			objects.push_back(ground);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			objects.push_back(bound);
		}

		auto spawnObject = cmap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				objects.push_back(spawnZone);
			}

		}

		auto brickObject = cmap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSTATE_02)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				objects.push_back(brick);
			}

		}

		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_02_N)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				objects.push_back(stair);
			}

		}

		auto nextsceneObject = cmap->GetObjects().find(ID_TILE_OBJECT_NEXTSCENE);
		for (const auto& child : nextsceneObject->second) {
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			nextScene = new NextScene();
			nextScene->SetSceneDef(child->GetPropertyByKey("nextscene"));
			nextScene->SetSize(child->GetWidth(), child->GetHeight());
			nextScene->SetPosition(child->GetX(), child->GetY());
			objects.push_back(nextScene);
		}


		auto doorObject = cmap->GetObjects().find(ID_TILE_OBJECT_GS2_DOOR);
		for (const auto& child : doorObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_02_N)
			{
				door = new Door();
				door->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				objects.push_back(door);
			}

		}
		break;
	}

	case GSCENE_03:
	{

		auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);
		for (const auto& child : simonPos->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				simon->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				//	DebugOut(L"[Complete]Load Simon position in game world \n");
			}

		}
		objects.push_back(simon);


		auto camObject = cmap->GetObjects().find(ID_TILE_OBJECT_CAMBOUNDBOX);
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

		auto groundObject = cmap->GetObjects().find(ID_TILE_OBJECT_GROUND);
		for (const auto& child : groundObject->second) {
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			objects.push_back(ground);
		}

		auto boundObject = cmap->GetObjects().find(ID_TILE_OBJECT_BOUNDMAP);
		for (const auto& child : boundObject->second) {
			bound = new BoundMap();
			bound->SetSize(child->GetWidth(), child->GetHeight());
			bound->SetPosition(child->GetX(), child->GetY());
			objects.push_back(bound);
		}

		auto spawnObject = cmap->GetObjects().find(ID_TILE_OBJECT_SPAWNZONE);
		for (const auto& child : spawnObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				spawnZone = new SpawnZone(child->GetPropertyByKey("enemydef"), child->GetPropertyByKey("num"), child->GetPropertyByKey("respawntime"));
				spawnZone->SetSize(child->GetWidth(), child->GetHeight());
				spawnZone->SetPosition(child->GetX(), child->GetY());
				objects.push_back(spawnZone);
			}

		}



		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				stair = new StairTrigger();
				stair->SetDirection(child->GetPropertyByKey("dir"));
				stair->SetSize(child->GetWidth(), child->GetHeight());
				stair->SetPosition(child->GetX(), child->GetY());
				objects.push_back(stair);
			}

		}


		auto candleObject = cmap->GetObjects().find(ID_TILE_OBJECT_CANDLE);
		for (const auto& child : candleObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				candle = new Candle();
				candle->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				objects.push_back(candle);
			}

		}

		auto brickObject = cmap->GetObjects().find(ID_TiLE_OBJECT_BREAKING_BRICK);
		for (const auto& child : brickObject->second) {
			if (child->GetPropertyByKey("scenedef") == GSCENE_03)
			{
				brick = new CBrick();
				brick->SetState(child->GetPropertyByKey("brickstate"));
				brick->SetItemDef(child->GetPropertyByKey("itemdef"));
				brick->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
				objects.push_back(brick);
			}

		}

		break;
	}
	}
}

SceneManagement::SceneManagement()
{
	this->isNextScene = false;
	this->currentScene = GSCENE_01;

	cmap = CTileMap::GetInstance();
	hub = new Hub(this);
}


SceneManagement::~SceneManagement()
{
}
