#include "SceneManager.h"

#include"StartScene.h"
#include"PlayScene.h"
#include"ResourceManager.h"


SceneManager* SceneManager::__instance = NULL;
SceneManager* SceneManager::GetInstance()
{
	if (__instance == NULL) __instance = new SceneManager();
	return __instance;
}

void SceneManager::LoadResource()
{

	ResourceManager* rs = ResourceManager::GetInstance();
	rs->LoadData("Data\\Data\\Data01.xml");
	scene->LoadResource();
}
void SceneManager::Update(DWORD dt)
{
	if (currentScene!=scene->GetScene())
	{
		InitScene(currentScene);
		this->currentScene = scene->GetScene();
		scene->LoadResource();

		return;
	}
	scene->Update(dt);
}
void SceneManager::Render()
{
	scene->Render();
}
SceneManager::SceneManager()
{
	scene = new StartScene();
	currentScene = scene->GetScene();
}
void SceneManager::InitScene(GameScene currentScene)
{
	delete scene;
	scene = NULL;
	switch (currentScene)
	{
	case GameScene::INTRO:
	
		scene = new StartScene();
		break;
	case GameScene::PLAY:
		scene = new PlayScene();
		break;
	case GameScene::CUTSCENE:
		break;
	case GameScene::END:
		break;
	default:
		break;
	}
	
}
