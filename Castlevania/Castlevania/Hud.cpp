#include "Hud.h"
#include"SceneManagement.h"

void Hud::Update()
{
	this->playerEnery = scene->GetSimon()->GetEnery();
	string enery_ = playerEnery < 10 ? "0" + std::to_string(playerEnery) : std::to_string(playerEnery);
	this->playerHP= scene->GetSimon()->GetHP();
	_UIinfor = "SCORE-000000 TIME 0000 SCENE 00\n";
	_UIinfor = _UIinfor+ "PLAYER                  -"+ enery_+"\n";
	_UIinfor += "ENEMY                   -00\n";
}

void Hud::Render()
{
	game->DrawUIText(this->_UIinfor, bound);
	for (size_t i = 0; i < this->playerHP; i++)
	{
		CSprites::GetInstance()->Get("PLAYER_HP_SPRITE")->Draw(0,105 + i * 9, 32,255,false);
		CSprites::GetInstance()->Get("BOSS_HP_SPRITE")->Draw(0, 105 + i * 9, 50, 255, false);
	}

}

Hud::Hud(SceneManagement* scene)
{
	this->scene = scene;
	SetRect(&bound, 0, 15, SCREEN_WIDTH, 80);
	game = CGame::GetInstance();
	_UIinfor = "SCORE-000000 TIME 0000 SCENE 00\n";
	_UIinfor += "PLAYER                  -00\n";
	_UIinfor += "ENEMY                   -00\n";
}


Hud::~Hud()
{
	
}
