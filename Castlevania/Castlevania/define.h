#pragma once
#ifndef _DEFINE_CLASS
#define _DEFINE_CLASS
#include<string>
#include<map>

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(0, 0, 0)
#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
#define GAME_WORLD_Y 64

#define MAX_FRAME_RATE 120

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_WHIP 31
#define ID_TEX_TORCH 40
#define ID_TEX_ZOMBIE 50
#define ID_TEX_PANTHER 60
#define ID_TEX_BAT 70
#define ID_TEX_ITEM_HEART 500
#define ID_TEX_ITEM_MORNINGSTAR 501
#define ID_TEX_ITEM_MONEYBAG 502
#define ID_TEX_EFFECT_FLAME 600
#define ID_TEX_TILESET_1 1000
#define ID_TEX_TILESET_2 1001

#define ID_TILE_BACKGROUND 1
#define ID_TILE_OBJECT_BOUNDMAP 2
#define ID_TILE_OBJECT_GROUND 3
#define ID_TILE_OBJECT_TRIGGER 4
#define ID_TILE_OBJECT_SIMON 5
#define ID_TILE_OBJECT_TORCH 6 //
#define ID_TILE_OBJECT_ENTRY 8 
#define ID_TILE_OBJECT_MONEY_BAG 9

#define ID_TILE_OBJECT_NEXTSCENE 7
#define ID_TILE_OBJECT_ZOMBIE 6 
#define ID_TILE_OBJECT_PANTHER 8 
#define ID_TILE_OBJECT_STAIR 9
///
///ITEM
///
#define ITEM_STATE_HIDING 100
#define HEART_STATE_BIGHEART 200
#define HEART_STATE_SMALLHEART 300
#define HEART_BIG 1
#define HEART_SMALL 0;
#define HEART_ANI_SMAIL 0
#define HEART_ANI_BIG 1
#define HEART_BBOX_HEIGHT 30
#define HEART_BBOX_WIDTH 31
#define HEART_GRAVITY			0.0002f


#define GAME_STATE_01 1
#define GAME_STATE_02 2
#define GAME_STATE_03 3


const enum GameState {
	STATE_01,
	STATE_02,
	STATE_03
};

const enum ItemID {
	IDHeart,
	IDLargeHeart,
	IDWhip
};

const enum StairDir {
	DIR_UPRIGHT,
	DIR_UPLEFT,
	DIR_DOWNRIGHT,
	DIR_DOWNLEFT
};
#endif