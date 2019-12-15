#pragma once
#include"Scene.h"
#include"Sprites.h"
class StartScene:public Scene
{
	LPSPRITE intro;
	CAnimation* introCastle;
	RECT bound;
public:
	virtual void LoadResource();
	virtual void Update(DWORD dt);
	virtual void Render() ;

	virtual void OnKeyDown(int keyCode) ;
	virtual void OnKeyUp(int keyCode) ;
	virtual void KeyState(BYTE* states) ;
	StartScene() {
		this->scene = GameScene::INTRO;
		SetRect(&bound, 0, 15, SCREEN_WIDTH, 80);
	}
};

