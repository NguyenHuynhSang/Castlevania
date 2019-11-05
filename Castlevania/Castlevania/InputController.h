#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include"Simon.h"
#include"Game.h"
#include"SceneManager.h"
#include"CKeyEventHandler.h"
class InputController : public CKeyEventHandler
{
private:
	SceneManager* scene;
	CSimon* player;
	CGame* game;



public:
	InputController();
	void Init(SceneManager* scene, CSimon* player) {
		game = CGame::GetInstance();
		this->scene = scene;
		this->player = player;
	}
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

