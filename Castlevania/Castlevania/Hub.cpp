#include "Hub.h"



void Hub::Update()
{
}

void Hub::Render()
{
	game->DrawUIText(this->_UIinfor, bound);
}

Hub::Hub()
{
	SetRect(&bound, 0, 15, SCREEN_WIDTH, 80);
	game = CGame::GetInstance();
	_UIinfor = "SCORE-000000 TIME 0000 SCENE 00\n";
	_UIinfor += "PLAYER                  -00\n";
	_UIinfor += "ENEMY                   -00\n";
}


Hub::~Hub()
{
}
