/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102

	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions:
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox

================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Simon.h"
#include "Brick.h"
#include "Ghoul.h"
#include"ResourceManagement.h"
#include "Whip.h"
#include"Ground.h"
#include"CTileMap.h"
#include"define.h"
#include"Torch.h"
#include"BoundMap.h"
CGame *game;
CSimon *simon;
Ghoul *goomba;
Whip* whip;
Torch * torch;
Ground *ground;
BoundMap *bound;
ResourceManagement * resource;
vector<LPGAMEOBJECT> objects;
CTileMap* cmap;
class CSampleKeyHander : public InputController
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;
bool isJumping = false;
void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);

	switch (KeyCode)
	{
	case DIK_SPACE:
		if (!simon->IsJumping() && simon->GetState() != SIMON_STATE_SIT && simon->GetActack_Time() == 0) // dùng atack time khỏi phải dùng state attack nhiều lần
			simon->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_F:
		if (simon->GetActack_Time() == 0) {
			simon->StartActack();
			if (simon->GetState() == SIMON_STATE_SIT)
			{
				simon->SetState(SIMON_STATE_SIT_ATTACK);
				return;
			}
			else {
				simon->SetState(SIMON_STATE_STAND_ATTACK);
			}
			//	DebugOut(L"Start counting");
		}

		break;
	case DIK_A: // reset
		simon->SetState(SIMON_STATE_IDLE);
		simon->SetLevel(SIMON_LEVEL_BIG);
		simon->SetPosition(50.0f, 0.0f);
		simon->SetSpeed(0, 0);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}



void CSampleKeyHander::KeyState(BYTE *states)
{


	// disable control key when Simon die 
	//DebugOut(L"state=%d  \n", mario->GetState());
	if (simon->GetState() == SIMON_STATE_DIE) return;

	if ((simon->GetActack_Time() != 0) && (GetTickCount() - simon->GetActack_Time() > 3 * SIMON_ATTACK_TIME))
	{
		//DebugOut(L"stop atack \n");
		simon->SetState(SIMON_STATE_IDLE);
		simon->ResetActack_Time();
		simon->ResetSpriteFrame();

	}

	if (simon->GetActack_Time() != 0) { // dùng attack time thay cho nhiều state attack
		return;

	}
	if (simon->IsJumping() == true) {
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

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();
	textures->Add(ID_TEX_TILESET_1, L"Data\\Map\\Courtyard_bank.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SIMON, L"Data\\GameObject\\Simon\\SIMON.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_WHIP, L"Data\\GameObject\\Weapons\\Whipedip.png", D3DCOLOR_XRGB(3, 26, 110));
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_SPRITE_BBOX, L"textures\\bbox1.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_TORCH, L"Data\\GameObject\\Ground\\Torch.png", D3DCOLOR_XRGB(255, 0, 255));
	resource = ResourceManagement::GetInstance();
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	cmap = CTileMap::GetInstance();
	cmap->LoadMap("Data\\Map\\Courtyard_map.tmx");
	cmap->LoadObjects("Data\\Map\\Courtyard_map.tmx");

	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
	resource->LoadSprites("Data\\GameObject\\Simon\\Simon_sprite.xml", texSimon);
	resource->LoadAnimations("Data\\GameObject\\Simon\\Simon_ani.xml", animations);
	LPDIRECT3DTEXTURE9 texWhip = textures->Get(ID_TEX_WHIP);
	resource->LoadSprites("Data\\GameObject\\Weapons\\Whip_sprite.xml", texWhip);
	resource->LoadAnimations("Data\\GameObject\\Weapons\\Whip_ani.xml", animations);

	LPDIRECT3DTEXTURE9 texTorch = textures->Get(ID_TEX_TORCH);
	resource->LoadSprites("Data\\GameObject\\Ground\\Torch_sprite.xml", texTorch);
	resource->LoadAnimations("Data\\GameObject\\Ground\\Torch_ani.xml", animations);

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

	simon = new CSimon();
	auto simonPos = cmap->GetObjects().find(ID_TILE_OBJECT_SIMON);

	for (const auto& child : simonPos->second) {
		simon->SetPosition(child->GetX(), child->GetY()- child->GetHeight());
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
	for (const auto& child : torchObject->second) {
		//DebugOut(L"[Complete]Load Torch position in game world \n");
		torch = new Torch();
		torch->SetPosition(child->GetX(), child->GetY() - child->GetHeight());
		//DebugOut(L"[Complete]Load Simon position in game world \n");
		objects.push_back(torch);
	}









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

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Simon is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

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
	if (cx > 0 && cx < 47 * 32 - SCREEN_WIDTH)
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
}

/*
	Render a frame
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		// Clear back buffer with a color
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		cmap->Render();
		for (int i = 0; i < objects.size(); i++)
			objects[i]->Render();
		objects[0]->Render();//SIMON test 
		spriteHandler->End();
		d3ddv->EndScene();
	}

	// Display back buffer content to the screen
	d3ddv->Present(NULL, NULL, NULL, NULL);
}



HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();

			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);


	LoadResources();
	D3DXVECTOR2 vector(0, 0);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}