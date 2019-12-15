#include "StartScene.h"
#include"Sprites.h"
#include"SceneManager.h"

void StartScene::LoadResource()
{
	this->intro = CSprites::GetInstance()->Get("MainMenu_01");
}

void StartScene::Update(DWORD dt)
{
}

void StartScene::Render()
{
	this->intro->Draw(DIRECTION::DEFAULT, 0, 0, 255, false);
}

void StartScene::OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case DIK_RETURN: {
		SceneManager::GetInstance()->SetCurrentScene(GameScene::PLAY);
		DebugOut(L"Chuyển Scene");
		break;
	}
	default:
		break;
	}
}

void StartScene::OnKeyUp(int keyCode)
{
}

void StartScene::KeyState(BYTE* states)
{

}
