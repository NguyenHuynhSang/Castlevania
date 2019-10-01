#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "InputController.h"
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include"define.h"
#define KEYBOARD_BUFFER_SIZE 1024
/*
Abstract class to define keyboard event handlers
*/


class CGame
{
	static CGame * __instance;
	HWND hWnd;									// Window handle

	LPDIRECT3D9 d3d = NULL;						// Direct3D handle
	LPDIRECT3DDEVICE9 d3ddv = NULL;				// Direct3D device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;		
	LPD3DXSPRITE spriteHandler = NULL;			// Sprite helper library to help us draw 2D image on the screen 

	LPDIRECTINPUT8       di;		// The DirectInput object         
	LPDIRECTINPUTDEVICE8 didv;		// The keyboard device 

	BYTE  keyStates[256];			// DirectInput keyboard state buffer 
	DIDEVICEOBJECTDATA keyEvents[KEYBOARD_BUFFER_SIZE];		// Buffered keyboard data

	InputController* keyHandler;

	// font 
	ID3DXFont * font;
	
	float cam_x = 0.0f;
	float cam_y = 0.0f;


public:
	void InitKeyboard(InputController* handler);
	void Init(HWND hWnd);
	void Draw(int nx,float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255);

	int IsKeyDown(int KeyCode);
	
	void ProcessKeyboard();

	static void SweptAABB(
		float ml,			// move left 
		float mt,			// move top
		float mr,			// move right 
		float mb,			// move bottom
		float dx,			// 
		float dy,			// 
		float sl,			// static left
		float st, 
		float sr, 
		float sb,
		float &t, 
		float &nx, 
		float &ny);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetCamPos(float x, float y) { cam_x = x; cam_y = y; }
	void GetCamera(float& camx, float& camy) { camx = this->cam_x; camy = this->cam_y; }
	RECT GetCamera() {
		RECT rec;
		rec = { (long)this->cam_x,(long)this->cam_y,(long)this->cam_x + SCREEN_WIDTH,(long)this->cam_y + SCREEN_HEIGHT };
		return rec;
	}
	ID3DXFont* GetFont() { 
		return this->font; 
	}

	void DrawUIText(std::string text,RECT bound);
	static CGame * GetInstance();

	~CGame();
};


