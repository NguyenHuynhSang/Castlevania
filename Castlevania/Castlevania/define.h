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
#define GAME_WORLD_Y 80
#define MAX_FRAME_RATE 120

#define FONT_PATH L"Data\\prstart.ttf"

#define EFFECTS_LIFE_TIME 500
#define SCORETEXT_STATE_100 0
#define SCORETEXT_STATE_400 100
#define SCORETEXT_STATE_700 200 
#define SCORETEXT_STATE_1000 300

#define ID_TEX_SIMON 0
#define ID_TEX_ENEMY 10
#define ID_TEX_BRICK 20
#define ID_TEX_WHIP 30
#define ID_TEX_TORCH 40
#define ID_TEX_ZOMBIE 50
#define ID_TEX_PANTHER 60
#define ID_TEX_BAT 70
#define ID_TEX_CANDLE 80
#define ID_TEX_FISHMAN 100
#define ID_TEX_FIREBALL 110
#define ID_TEX_DOOR      120
#define ID_TEX_AXE      130

#define ID_TEX_ITEM_HEART 500
#define ID_TEX_ITEM_MORNINGSTAR 501
#define ID_TEX_ITEM_MONEYBAG 502
#define ID_TEX_ITEM_DAGGER 503
#define ID_TEX_ITEM_AXE      504
#define ID_TEX_ITEM_STOPWATCH 505
#define ID_TEX_ITEM_ROAST   506

#define ID_TEX_EFFECT_FLAME 600
#define ID_TEX_EFFECT_DEBRIS 601
#define ID_TEX_EFFECT_BUBBLE 602
#define ID_TEX_EFFECT_SCROTE_TEXT 603

#define ID_TEX_TILESET_1 1000
#define ID_TEX_TILESET_2 1001
#define ID_TEX_TILESET_3 1002

#define ID_TILE_BACKGROUND 1
#define ID_TILE_OBJECT_BOUNDMAP 2
#define ID_TILE_OBJECT_GROUND 3
#define ID_TILE_OBJECT_TRIGGER 4
#define ID_TILE_OBJECT_SIMON 5
#define ID_TILE_OBJECT_TORCH 6 //
#define ID_TILE_OBJECT_ENTRY 8 
#define ID_TILE_OBJECT_MONEY_BAG 9

#define ID_TILE_OBJECT_NEXTSCENE 7
#define ID_TILE_OBJECT_SPAWNZONE 6 
#define ID_TILE_OBJECT_PANTHER 8 
#define ID_TILE_OBJECT_STAIR 9
#define ID_TILE_OBJECT_CANDLE 11

/// object upderground
#define ID_TILE_OBJECT_UNDERGROUND_MONERBAG 6
#define ID_TILE_OBJECT_UNDERGROUND_WATER 8
#define ID_TILE_OBJECT_UNDERGROUND_STAIR 10
#define ID_TILE_OBJECT_UNDERGROUND_SPAWNZONE 11
#define ID_TILE_OBJECT_UNDERGROUND_BRICK 12

//object castle
#define ID_TILE_OBJECT_NEXTSCENE_CASTLE 7
#define ID_TiLE_OBJECT_BREAKING_BRICK 14
#define ID_TILE_OBJECT_GS2_DOOR     15
#define ID_TILE_OBJECT_CAMBOUNDBOX   16
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
#define ITEM_GRAVITY			0.0002f


#define GAME_STATE_01 1
#define GAME_STATE_02 2
#define GAME_STATE_03 3


const enum GameState {
	GSCENE_01,
	GSCENE_01_GH,
	GSTATE_02,
	GSTATE_02_UDG,
	GSTATE_02_B, // back to 03
	GSCENE_02_N, // back to 03 other stair
	GSCENE_03,
};

const enum ItemID {
	ITDHeart = 0,
	ITDLargeHeart = 1,
	ITDWhip = 2,
	ITDDagger = 3,
	ITDMONEYBAGFULLCOLOR,
	ITDMONEYBAGBLUE,
	ITDMONEYBAGWHITE,
	ITDMONEYBAGRED,
	ITDAXE,
	ITDSTOPWATCH,
	ITDROAST
};

const enum StairDir {
	DIR_UPRIGHT,
	DIR_UPLEFT,
	DIR_DOWNRIGHT,
	DIR_DOWNLEFT
};

const enum EnemyDef {
	EDZOMBIE,
	EDPANTHER,
	EDBAT,
	EDFISHMAN,
	EDFIREBALL,
};

const enum SubWeaponDef {
	SWDDAGGER,
	SWDHOLLYWATER,
	SWDAXE,
	SWDSTOPWATCH
};

const enum EffectDef {
	EFD_FLAME,
	EFD_DEBRIS,
	EFD_BUBBLE,
	EFD_ST100,
	EFD_ST400,
	EFD_ST700,
	EFD_ST1000,
};

const enum class DIRECTION {
	LEFT = -1,
	RIGHT = 1,
	UP,
	DOWN,
};
#endif