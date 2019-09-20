#include "SceneManagement.h"


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
	textures->Add(ID_TEX_ITEM_HEART, L"Data\\GameObject\\Items\\Heart.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MORNINGSTAR, L"Data\\GameObject\\Items\\MORNING_STAR.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_ITEM_MONEYBAG, L"Data\\GameObject\\Items\\Money_Bag.png", D3DCOLOR_XRGB(255, 0, 255));
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


	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add("20001", 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add("30001", 5, 14, 21, 29, texEnemy);
	sprites->Add("30002", 25, 14, 41, 29, texEnemy);
	sprites->Add("30003", 45, 21, 61, 29, texEnemy); // die sprite





	LPANIMATION ani;





	ani = new CAnimation(100);		// brick
	ani->Add("20001");
	animations->Add("601", ani);

	ani = new CAnimation(300);		// Goomba walk
	ani->Add("30001");
	ani->Add("30002");
	animations->Add("701", ani);

	ani = new CAnimation(100);		// Goomba dead
	ani->Add("30003");
	animations->Add("702", ani);



	/*for (const auto& entity : cmap->GetObjects()) {
		DebugOut(L" ===============ID =%d \n", entity.first);
		for (const auto& child : entity.second) {
			DebugOut(L" ID =%d \n", child->GetId());
		}
	}*/

	whip = Whip::GetInstance();
	whip->AddAnimation("800");
	
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
	//clean object
	for (vector<LPGAMEOBJECT>::iterator it = objects.begin(); it != objects.end(); ) {

		if ((*it)->isDestroyed) {
			it = objects.erase(it);

		}
		else ++it;
	}
	//clean effects
	for (vector<LPGAMEOBJECT>::iterator it = effects.begin(); it != effects.end(); ) {

		if ((*it)->isDestroyed) {
			it = effects.erase(it);
		}
		else ++it;
	}
	//clean item
	for (vector<LPGAMEOBJECT>::iterator it = items.begin(); it != items.end(); ) {

		if ((*it)->isDestroyed) {
			it = items.erase(it);
		}
		else ++it;
	}

	vector<LPGAMEOBJECT> coObjects;
	for (std::size_t  i = 1; i < objects.size(); i++)
	{

		coObjects.push_back(objects[i]);
	}
	for (std::size_t  i = 0; i < items.size(); i++)  //item
	{
		coObjects.push_back(items[i]);
	}

	//update object
	for (std::size_t  i = 0; i < objects.size(); i++) //object
	{
		objects[i]->Update(dt, &coObjects);
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


	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);

	cx -= SCREEN_WIDTH / 2;
	cy -= SCREEN_HEIGHT / 2;
	if (currentScene == GAME_STATE_01) {
		if (cx > 0 && cx < 47 * 32 - SCREEN_WIDTH)
			CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}
	else {
		if (cx > 0 && cx < 176 * 32 - SCREEN_WIDTH)
			CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}
	
		
}
void SceneManagement::Render()
{
	if (this->isNextScene) return;
	cmap->Render();
	for (std::size_t  i = 1; i < objects.size(); i++)
		objects[i]->Render();
	for (std::size_t  i = 0; i < this->items.size(); i++)
		this->items[i]->Render();
	for (std::size_t  i = 0; i < this->effects.size(); i++)
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
	case GAME_STATE_01:
		
		cmap->LoadMap("Data\\Map\\Courtyard_map.tmx", textures->Get(ID_TEX_TILESET_1));
		cmap->LoadObjects("Data\\Map\\Courtyard_map.tmx");
		LoadObjects(GAME_STATE_01);
		break;
	case GAME_STATE_02:
		
		cmap = CTileMap::GetInstance();
		cmap->LoadMap("Data\\Map\\Great_Hall_map.tmx", textures->Get(ID_TEX_TILESET_2));
		cmap->LoadObjects("Data\\Map\\Great_Hall_map.tmx");
		LoadObjects(GAME_STATE_02);
		break;
	case GAME_STATE_03:
		break;

	}
}

void SceneManagement::GoNextScene()
{
	this->currentScene++;
	if (this->currentScene > GAME_STATE_02) currentScene = GAME_STATE_02;
	
	this->isNextScene = true;
	
	
}

void SceneManagement::LoadObjects(int currentscene)
{
	for (UINT i = 0; i < objects.size(); i++) delete objects[i];
	for (UINT i = 0; i < items.size(); i++) delete items[i];
	for (UINT i = 0; i < effects.size(); i++) delete effects[i];
	objects.clear();
	items.clear();
	effects.clear();
	switch (this->currentScene)
	{
	case GAME_STATE_01:
	{
		simon = new CSimon();
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
				trigger->SetItemPosition(smallchild->GetX(), smallchild->GetY()- smallchild->GetHeight());
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
			torch->SetItem(child->GetPropertyName());
			objects.push_back(torch);
		}
		break;
	}

	case GAME_STATE_02:
	{
		simon = new CSimon();
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

		auto zombieObject = cmap->GetObjects().find(ID_TILE_OBJECT_ZOMBIE);
		for (const auto& child : zombieObject->second) {
			zombie = new Zombie();
			zombie->SetRespawnPosition(child->GetX(), child->GetY()-child->GetHeight()+GAME_WORLD_Y);
			zombie->SetPosition(child->GetX(), child->GetY() -child->GetHeight());
			objects.push_back(zombie);
		}

		auto pantherObject = cmap->GetObjects().find(ID_TILE_OBJECT_PANTHER);
		for (const auto& child : pantherObject->second) {
			bat = new VampieBat();
			//panther->SetRespawnPosition(child->GetX(), child->GetY() - child->GetHeight() + GAME_WORLD_Y);
			bat->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			bat->SetOy();
			objects.push_back(bat);
		}


		auto stairObject = cmap->GetObjects().find(ID_TILE_OBJECT_STAIR);
		for (const auto& child : stairObject->second) {
			stair = new StairTrigger();
			stair->SetSize(child->GetWidth(), child->GetHeight());
			stair->SetPosition(child->GetX(), child->GetY());
			objects.push_back(stair);
		
		}

		break;
	}
		
	case GAME_STATE_03:
		break;

	}


}

SceneManagement::SceneManagement()
{
	this->isNextScene = false;
	this->currentScene = GAME_STATE_02;

	cmap = CTileMap::GetInstance();
}


SceneManagement::~SceneManagement()
{
}
