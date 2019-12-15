#pragma once
#include<Windows.h>
#include"Game.h"
enum class GameScene
{
	INTRO,
	PLAY,
	CUTSCENE,
	END
};


class Scene
{

protected:
	GameScene scene;
	CGame* game;
public:
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
	virtual void LoadResource() = 0;

	virtual void OnKeyDown(int keyCode) = 0;
	virtual void OnKeyUp(int keyCode) = 0;
	virtual void KeyState(BYTE* states) = 0;

	void SetScene(GameScene scene)
	{
		this->scene = scene;
	}
	GameScene GetScene()
	{
		return this->scene;
	}
	Scene()
	{
		game = CGame::GetInstance();
	}
};