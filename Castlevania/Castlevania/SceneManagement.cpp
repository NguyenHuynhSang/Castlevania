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
	textures->Add(ID_TEX_ZOMBIE, L"Data\\GameObject\\Enemies\\ZOMBIE.png", D3DCOLOR_XRGB(255, 0, 255));
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

	LPDIRECT3DTEXTURE9 texGhoul = textures->Get(ID_TEX_ZOMBIE);
	resource->LoadSprites("Data\\GameObject\\Enemies\\Zombie_sprite.xml", texGhoul);
	resource->LoadAnimations("Data\\GameObject\\Enemies\\Zombie_ani.xml", animations);



	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add("20001", 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
	sprites->Add("30001", 5, 14, 21, 29, texEnemy);
	sprites->Add("30002", 25, 14, 41, 29, texEnemy);
	sprites->Add("30003", 45, 21, 61, 29, texEnemy); // die sprite




	sprites->Add("WHIP_LEVEL1_01", 480, 0, 720, 66, texWhip);
	sprites->Add("WHIP_LEVEL1_02", 240, 0, 480, 66, texWhip);
	sprites->Add("WHIP_LEVEL1_03", 0, 0, 240, 66, texWhip); // die sprite





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


	ani = new CAnimation(SIMON_ATTACK_TIME);		//whip
	ani->Add("WHIP_LEVEL1_01");
	ani->Add("WHIP_LEVEL1_02");
	ani->Add("WHIP_LEVEL1_03");
	animations->Add("800", ani);

	/*for (const auto& entity : cmap->GetObjects()) {
		DebugOut(L" ===============ID =%d \n", entity.first);
		for (const auto& child : entity.second) {
			DebugOut(L" ID =%d \n", child->GetId());
		}
	}*/









	whip = Whip::GetInstance();
	whip->AddAnimation("800");
	//	objects.push_back(whip);
		/*for (int i = 0; i < 180; i++)
		{
			CBrick *brick = new CBrick();
			brick->AddAnimation("601");
			brick->SetPosition(0 + i*16.0f-640/2+60, 350);
			objects.push_back(brick);
		}*/


		// and Goombas 
		/*for (int i = 0; i < 4; i++)
		{
			goomba = new CGoomba();
			goomba->AddAnimation("701");
			goomba->AddAnimation("702");
			goomba->SetPosition(200 + i*60, 334);
			goomba->SetState(GOOMBA_STATE_WALKING);
			objects.push_back(goomba);
		}*/

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
		this->isNextScene = false;
	}
	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{

		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
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

	cmap->Render();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	objects[0]->Render();//SIMON test 

}
void SceneManagement::SceneUpdate()
{
}

void SceneManagement::LoadScene()
{
	CTextures * textures = CTextures::GetInstance();
	switch (this->currentScene)
	{
	case GAME_STATE_01:
		cmap = CTileMap::GetInstance();
		LPDIRECT3DTEXTURE9 texTileSet;
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

void SceneManagement::LoadObjects(int currentscene)
{
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
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
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


		auto torchObject = cmap->GetObjects().find(ID_TILE_OBJECT_TORCH);
		Item* citem;
		for (const auto& child : torchObject->second) {
			citem = new Heart();

			//DebugOut(L"[Complete]Load Torch position in game world \n");
			torch = new Torch();
			torch->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			citem->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
			citem->SetState(HEART_STATE_BIGHEART);

			objects.push_back(citem);
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
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			ground = new Ground();
			ground->SetSize(child->GetWidth(), child->GetHeight());
			ground->SetPosition(child->GetX(), child->GetY());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
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
			//DebugOut(L"[Complete]Load Torch position in game world \n");
			zombie = new Zombie();
			zombie->SetRespawnPosition(child->GetX(), child->GetY()-child->GetHeight());
			zombie->SetPosition(child->GetX(), child->GetY() -child->GetHeight());
			//DebugOut(L"[Complete]Load Simon position in game world \n");
			objects.push_back(zombie);
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
	
}


SceneManagement::~SceneManagement()
{
}
