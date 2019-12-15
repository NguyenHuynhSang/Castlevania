#pragma once
#include"Scene.h"
#include"Sprites.h"
class StartScene:public Scene
{
	LPSPRITE intro;
public:
	virtual void LoadResource();
	virtual void Update(DWORD dt);
	virtual void Render() ;

	virtual void OnKeyDown(int keyCode) ;
	virtual void OnKeyUp(int keyCode) ;
	virtual void KeyState(BYTE* states) ;
	StartScene() {
		this->scene = GameScene::INTRO;
	}
};

