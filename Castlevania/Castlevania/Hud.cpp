#include "Hud.h"
#include"SceneManager.h"

void Hud::Update()
{
	this->playerEnery = scene->GetSimon()->GetEnery();
	string enery_ = playerEnery < 10 ? "0" + std::to_string(playerEnery) : std::to_string(playerEnery);
	this->playerHP = scene->GetSimon()->GetHP();

	if (this->bossHP != 0)
	{

		this->bossHP = scene->GetBossHP();
	}


	unsigned int score_ = CSimon::GetScore();
	string score;
	if (score_ < 10)
	{
		score = "00000" + std::to_string(score_);
	}
	else if (score_ < 100)
	{
		score = "0000" + std::to_string(score_);
	}
	else if (score_ < 1000) {
		score = "000" + std::to_string(score_);
	}
	else if (score_ < 10000)
	{
		score = "00" + std::to_string(score_);
	}
	else if (score_ < 100000)
	{
		score = "0" + std::to_string(score_);
	}
	else {
		score = std::to_string(score_);
	}


	_UIinfor = "SCORE-" + score + " TIME 0" + std::to_string(scene->GetTime()) + " STAGE 00\n";
	_UIinfor = _UIinfor + "PLAYER                  -" + enery_ + "\n";
	_UIinfor += "ENEMY                   -00\n";
}

void Hud::Render()
{
	CSprites::GetInstance()->Get("BLACKBOARD_UI_SPRITE")->Draw(DIRECTION::DEFAULT, 290, 32, 255, false);
	switch (scene->GetSimon()->GetCurrentSubWeapon())
	{
	case SWDAXE: {

		CSprites::GetInstance()->Get("AXE_UI_SPRITE")->Draw(DIRECTION::DEFAULT, 300, 40, 255, false);
		break;
	}
	case SWDDAGGER: {
		CSprites::GetInstance()->Get("KNIFE_UI_SPRITE")->Draw(DIRECTION::DEFAULT, 300, 40, 255, false);
		break;
	}
	case SWDHOLLYWATER: {
		CSprites::GetInstance()->Get("HOLY_WATER_UI_SPRITE")->Draw(DIRECTION::DEFAULT, 305, 35, 255, false);
		break;
	}

	case SWDSTOPWATCH: {
		CSprites::GetInstance()->Get("STOP_WATCH_UI_SPRITE")->Draw(DIRECTION::DEFAULT, 300, 35, 255, false);
		break;
	}
	}
	game->DrawUIText(this->_UIinfor, bound);
	for (size_t i = 0; i < this->playerHP; i++)
	{
		CSprites::GetInstance()->Get("PLAYER_HP_SPRITE")->Draw(DIRECTION::DEFAULT, 105 + i * 9, 32, 255, false);

	}
	for (size_t i = 0; i < bossHP; i++)
	{
		CSprites::GetInstance()->Get("BOSS_HP_SPRITE")->Draw(DIRECTION::DEFAULT, 105 + i * 9, 50, 255, false);
	}
	for (size_t i = this->playerHP; i < 16; i++)
	{
		CSprites::GetInstance()->Get("NOHP_UI_SPRITE")->Draw(DIRECTION::DEFAULT, 105 + i * 9, 32, 255, false);
	}
	for (size_t i = this->bossHP; i < 16; i++)
	{
		CSprites::GetInstance()->Get("NOHP_UI_SPRITE")->Draw(DIRECTION::DEFAULT, 105 + i * 9, 50, 255, false);
	}
}

Hud::Hud(SceneManager* scene)
{
	this->scene = scene;
	SetRect(&bound, 0, 15, SCREEN_WIDTH, 80);
	this->bossHP = 16;
	game = CGame::GetInstance();
	_UIinfor = "SCORE-000000 TIME 0000 STAGE 00\n";
	_UIinfor += "PLAYER                  -00\n";
	_UIinfor += "ENEMY                   -00\n";
}


Hud::~Hud()
{

}
