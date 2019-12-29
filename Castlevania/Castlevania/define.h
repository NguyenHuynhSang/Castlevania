#pragma once
#ifndef _DEFINE_CLASS
#define _DEFINE_CLASS
#include<string>
#include<map>

#define WINDOW_CLASS_NAME L"Castlevania"
#define MAIN_WINDOW_TITLE L"Castlevania"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(5, 5, 5)
#define CROSS_EFFECT_COLOR  D3DCOLOR_XRGB(173,173,173)

#define GAMESTATE_TIME 300

#define SCREEN_WIDTH 512
#define SCREEN_HEIGHT 480
#define GAME_WORLD_Y 80
#define MAX_FRAME_RATE 120

#define FONT_PATH L"Data\\prstart.ttf"



#define EFFECTS_LIFE_TIME 500
#define CROSS_EFFECT_TIME 500
#define SCORETEXT_STATE_100 0
#define SCORETEXT_STATE_400 100
#define SCORETEXT_STATE_700 200 
#define SCORETEXT_STATE_1000 300



#define DEFAULT_HP 16


#define ID_TEX_EFFECT 600

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
#define ID_TILE_OBJECT_BOSSBAT    17
#define ID_TILE_OBJECT_BOSSBAT_BORDER    18
#define ID_TILE_OBJECT_BOSSTRIGGER 19

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




#define SIMON_BIG_BBOX_WIDTH  32
#define SIMON_BIG_BBOX_HEIGHT 62



const enum GameState {
	GSCENE_01,
	GSCENE_01_GH,
	GSTATE_02,
	GSTATE_02_UDG,
	GSTATE_02_B, // back to 03
	GSCENE_02_N, // back to 03 other stair
	GSCENE_03,
};

const enum ITEMDEF {
	ITDRAMDOM=-1,
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
	ITDROAST,
	ITDIPOTION, //InticibilityPotion
	ITDCROSS ,
	ITDHOLYWATER,
	ITDMULTIFLYSHOT
};


const enum ENEMYDEF {
	EDZOMBIE,
	EDPANTHER,
	EDBAT,
	EDFISHMAN,
	EDFIREBALL,
	EDVAMPIREBAT
};

const enum SWEAPONDEF {
	SWDDAGGER,
	SWDHOLLYWATER,
	SWDAXE,
	SWDSTOPWATCH
};

const enum EFFECTDEF {
	EFD_FLAME=0,
	EFD_DEBRIS,
	EFD_BUBBLE,
	EFD_SPARK,
	EFD_ST100,
	EFD_ST400,
	EFD_ST700,
	EFD_ST1000,
	EFD_BOSSDEAD,
};


enum class DIRECTION {
	DEFAULT = 0,
	LEFT = -1,
	RIGHT = 1,
	TOP = 2,
    BOTTOM = -2,
};


enum class STAIRDIRECTION
{
	DEFAULT=-1,
	UPRIGHT,
	UPLEFT,
	DOWNRIGHT,
	DOWNLEFT,

};





enum class MYCOLOR
{
	RED,
	BLUE
};


#define SAFE_DELETE(ptr) \
if(ptr) \
{\
	delete (ptr); \
	ptr = nullptr; \
} \


#endif



