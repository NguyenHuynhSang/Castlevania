#pragma once
#include"Scene.h"

class SceneManager
{

private:
	Scene* scene;
	GameScene currentScene;
	static SceneManager* __instance;
public:
	static SceneManager* GetInstance();
	void LoadResource();
	void Update(DWORD dt);
	void Render();
	SceneManager();
	Scene* GetCurrentScene() {
		return this->scene;
	}
	void SetCurrentScene(GameScene scene) {
		this->currentScene = scene;
	};
	void InitScene(GameScene currentScene);

};

