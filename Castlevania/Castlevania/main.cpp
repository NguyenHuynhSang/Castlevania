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
#include"SceneManagement.h"
#include"HandleSpawnItem.h"
CGame *game;
SceneManagement *scene;
class CSampleKeyHander : public InputController
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler;
void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	float sx, sy;
	scene->GetSimon()->GetPosition(sx, sy);
	//DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	if (scene->GetSimon()->CheckAutoWalk()) {
		return;
	}
	//if ((scene->GetSimon()->GetPowerUpTime() != 0) && GetTickCount() - scene->GetSimon()->GetPowerUpTime() > SIMON_POWERUP_TIME)
	//{
	//	scene->GetSimon()->SetState(SIMON_STATE_IDLE);
	//	scene->GetSimon()->ResetPowerUpTime();
	//}
	if (scene->GetSimon()->GetPowerUpTime() != 0)
	{
		return;
	}
	if (scene->GetSimon()->GetActack_Time() != 0) // đang dùng sub weapon
	{
		return;
	}


	if (scene->GetSimon()->GetState() == SIMON_STATE_DEFLECT) {
		return;
	}
	switch (KeyCode)
	{

	case DIK_1: 
		HandleSpawnItem::GetInstance()->SpawnItem(ITDWhip, sx, sy - 64,false);
		break;
	case DIK_2:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDDagger, sx, sy - 64,false);
		break;
	case DIK_3:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDAXE, sx, sy - 64, false);
		break;
	case DIK_4:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDMONEYBAGBLUE, sx, sy - 64, false);
		break;
	case DIK_5:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDMONEYBAGWHITE, sx, sy - 64, false);
		break;
	case DIK_6:
		HandleSpawnItem::GetInstance()->SpawnItem(ITDMONEYBAGRED, sx, sy - 64, false);
		break;
	case DIK_Q:
		scene->JumpToState(GSTATE_01);
		break;
	case DIK_W:
		scene->JumpToState(GSTATE_02);
		break;
	case DIK_E:
		scene->JumpToState(GSTATE_03);
		break;
	case DIK_H:
		scene->GetSimon()->SetAutoWalk(true);
		break;
	case DIK_SPACE:
		if (!scene->GetSimon()->CheckIsJumping() && scene->GetSimon()->GetState() != SIMON_STATE_SIT && !scene->GetSimon()->CheckAttack()) // dùng atack time khỏi phải dùng state attack nhiều lần
			scene->GetSimon()->SetState(SIMON_STATE_JUMP);
		break;
	case DIK_C: {
		if (scene->GetSimon()->GetActack_Time() == 0 && scene->GetSimon()->GetCurrentSubWeapon() != -1)
		{
			scene->GetSimon()->SimonUseSubWeapon();
			scene->GetSimon()->StartUseSubWeapon();
		}
		break;

	}
	case DIK_F:
		DebugOut(L"Press F \n");
		DebugOut(L"state=%d \n", scene->GetSimon()->GetState());
		if (!scene->GetSimon()->CheckAttack()) {
			DebugOut(L"Check attact \n");
			scene->GetSimon()->StartActack();
			if (scene->GetSimon()->CheckIsOnStair())
			{
				DebugOut(L"CheckIsOnStair \n");
				if (scene->GetSimon()->CheckStepOnStairDirection() == DIR_UPLEFT
					|| scene->GetSimon()->CheckStepOnStairDirection() == DIR_UPRIGHT
					&& scene->GetSimon()->GetState() == SIMON_STATE_UPSTAIR_IDLE)
				{
					scene->GetSimon()->SetState(SIMON_STATE_UPSTAIR_ATTACK);
				}
				else if (scene->GetSimon()->CheckStepOnStairDirection() == DIR_DOWNLEFT
					|| scene->GetSimon()->CheckStepOnStairDirection() == DIR_DOWNRIGHT
					&& scene->GetSimon()->GetState() == SIMON_STATE_DOWNSTAIR_IDLE)
				{
					scene->GetSimon()->SetState(SIMON_STATE_DOWNSTAIR_ATTACK);

				}

			}
			else {
				if (scene->GetSimon()->GetState() == SIMON_STATE_SIT)
				{
					scene->GetSimon()->SetState(SIMON_STATE_SIT_ATTACK);
				}
				else {
					scene->GetSimon()->SetState(SIMON_STATE_STAND_ATTACK);
				}

			}

		}

		break;
	case DIK_A: // reset
		scene->GetSimon()->SetState(SIMON_STATE_IDLE);
		scene->GetSimon()->SetLevel(SIMON_LEVEL_BIG);
		scene->GetSimon()->SetPosition(50.0f, 0.0f);
		scene->GetSimon()->SetSpeed(0, 0);
		break;
	}
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	//	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}



void CSampleKeyHander::KeyState(BYTE *states)
{
	if (scene->GetSimon()->GetState() == SIMON_STATE_DIE) return;
	if (scene->GetSimon()->CheckAutoWalk()) {
		return;
	}
	if ((scene->GetSimon()->GetPowerUpTime() != 0) && GetTickCount() - scene->GetSimon()->GetPowerUpTime() > SIMON_POWERUP_TIME)
	{
		scene->GetSimon()->SetState(SIMON_STATE_IDLE);
		scene->GetSimon()->ResetPowerUpTime();
	}

	if (scene->GetSimon()->GetPowerUpTime() != 0)
	{
		return;
	}
	if (scene->GetSimon()->GetState() == SIMON_STATE_DEFLECT) {
		return;
	}

	if (scene->GetSimon()->CheckAttack()) { // dùng attack time thay cho nhiều state attack
		return;
	}

	if ((scene->GetSimon()->GetActack_Time() != 0) && GetTickCount() - scene->GetSimon()->GetActack_Time() > SIMON_ATTACK_TIME)
	{
		scene->GetSimon()->SetState(SIMON_STATE_IDLE);
		scene->GetSimon()->StartDelayAttack();
		scene->GetSimon()->ResetActack_Time();
		scene->GetSimon()->ResetSpriteFrame();
		scene->GetSimon()->ResetUseSubWeapon();
		return;
	}
	if (scene->GetSimon()->GetActack_Time() != 0) // đang dùng sub weapon
	{
		return;
	}

	if (scene->GetSimon()->CheckIsJumping() == true) {
		return;

	}
	if (game->IsKeyDown(DIK_UP))
	{

		if (scene->GetSimon()->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {
			if (scene->GetSimon()->CheckStepOnStairDirection() == DIR_DOWNLEFT)
				scene->GetSimon()->SetStepOnStairDirection(DIR_UPRIGHT);
			else if (scene->GetSimon()->CheckStepOnStairDirection() == DIR_DOWNRIGHT)
				scene->GetSimon()->SetStepOnStairDirection(DIR_UPLEFT);
			scene->GetSimon()->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}

		else if (scene->GetSimon()->CheckCanStepUp()) {
			if (!scene->GetSimon()->CheckIsOnStair() && scene->GetSimon()->CheckCollideWithStair()) {
				scene->GetSimon()->SetStartStepOnStair();
			}
			else if (scene->GetSimon()->GetState() == SIMON_STATE_UPSTAIR_IDLE) {
				scene->GetSimon()->SetStartStepOnStair();
			}
			return;
		}

	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (scene->GetSimon()->GetState() == SIMON_STATE_UPSTAIR_IDLE) {
			if (scene->GetSimon()->CheckStepOnStairDirection() == DIR_UPRIGHT)
				scene->GetSimon()->SetStepOnStairDirection(DIR_DOWNLEFT);
			else if (scene->GetSimon()->CheckStepOnStairDirection() == DIR_UPLEFT) {
				scene->GetSimon()->SetStepOnStairDirection(DIR_DOWNRIGHT);
			}
			scene->GetSimon()->SetStartStepOnStair();
			DebugOut(L"Simon up to down \n");
			return;
		}
		if (scene->GetSimon()->CheckCanStepDown()) {
			if (!scene->GetSimon()->CheckIsOnStair() && scene->GetSimon()->CheckCollideWithStair()) {
				scene->GetSimon()->SetStartStepOnStair();
			}
			else if (scene->GetSimon()->GetState() == SIMON_STATE_DOWNSTAIR_IDLE) {
				scene->GetSimon()->SetStartStepOnStair();
			}
			return;
		}

	}
	if (scene->GetSimon()->CheckIsOnStair() || scene->GetSimon()->CheckStairOnStair()) {
		return;
	}

	if (game->IsKeyDown(DIK_DOWN)) {
		scene->GetSimon()->SetState(SIMON_STATE_SIT);
		return;
	}
	else if (game->IsKeyDown(DIK_RIGHT))
		scene->GetSimon()->SetState(SIMON_STATE_WALKING_RIGHT);
	else if (game->IsKeyDown(DIK_LEFT))
		scene->GetSimon()->SetState(SIMON_STATE_WALKING_LEFT);
	else
		scene->GetSimon()->SetState(SIMON_STATE_IDLE);
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


/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{

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
		//d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);
		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		scene->Render();
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

			scene->Update(dt);
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

	scene = SceneManagement::GetInstance();
	scene->OnCreate();
	D3DXVECTOR2 vector(0, 0);

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}