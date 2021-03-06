﻿#include <d3dx9.h>
#include <algorithm>


#include "debug.h"
#include "Textures.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include<string>
#include"StairTrigger.h"
bool CGameObject::AABB(float l, float t, float r, float b, float l1, float t1, float r1, float b1)
{
	float left = l1 - r;
	float top = b1 - t;
	float right = r1 - l;
	float bottom = t1 - b;
	//  xét ngược lại cho nhanh hơn
	return !(left > 0 || right < 0 || top < 0 || bottom > 0);
}
CGameObject::CGameObject()
{
	x = y = 0;
	vx = vy = 0;
	nx = DIRECTION::RIGHT;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	this->dt = dt;
	dx = vx*dt;
	dy = vy*dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/
LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetSpeed(svx, svy);

	float sdx = svx*dt;
	float sdy = svy*dt;

	float dx = this->dx - sdx;
	float dy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	CGame::SweptAABB(
		ml, mt, mr, mb,
		dx, dy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent * e = new CCollisionEvent(t, nx, ny, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects 
	
	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT> *coObjects, 
	vector<LPCOLLISIONEVENT> &coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		if (dynamic_cast<StairTrigger*>(coObjects->at(i)))
		{
			continue;
		}
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT> &coEvents,
	vector<LPCOLLISIONEVENT> &coEventsResult,
	float &min_tx, float &min_ty, 
	float &nx, float &ny)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i;
		}

		if (c->t < min_ty  && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i;
		}
	}

	if (min_ix>=0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy>=0) coEventsResult.push_back(coEvents[min_iy]);
}


void CGameObject::ResetFrame(int frameID)
{
	animations[frameID]->ResetAnimation();
}

void CGameObject::ResetAnimation()
{
	for (auto ani : animations)
		ani->ResetAnimation();
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l,t,r,b; 
	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;


	// Vẽ lại vị  trí bouding box có tọa độ rõ ràng k vẽ từ tọa độ object
	//==> tọa độ object sẽ khác với bouding box

	CGame::GetInstance()->Draw(true, nx,l, t, bbox, rect.left, rect.top, rect.right, rect.bottom, 64);
}

void CGameObject::RenderSpriteBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;
	LPDIRECT3DTEXTURE9 sbbox = CTextures::GetInstance()->Get(ID_TEX_SPRITE_BBOX);
	float width,height,r,b;
	GetSpriteBox(width, height);
	r = x + width;
	b = y + height;
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)x;
	rect.bottom = (int)b - (int)y;
	// Vẽ lại vị  trí bouding box có tọa độ rõ ràng k vẽ từ tọa độ object
	//==> tọa độ object sẽ khác với bouding box
	CGame::GetInstance()->Draw(true,nx, x, y, sbbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}

void CGameObject::RenderActiveBox(RECT rec,MYCOLOR color,int alpha)
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;
	LPDIRECT3DTEXTURE9 bbox;
	switch (color)
	{
	case MYCOLOR::RED:
		 bbox = CTextures::GetInstance()->Get(ID_TEX_SPRITE_BBOX);
		break;
	case MYCOLOR::BLUE:
		 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		break;
	default:
		 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);
		break;
	}


	rect.left = 0;
	rect.top = 0;
	rect.right = (int)rec.right - (int)rec.left;
	rect.bottom = (int)rec.bottom - (int)rec.top;


	CGame::GetInstance()->Draw(true, nx, rec.left, rec.top, bbox, rect.left, rect.top, rect.right, rect.bottom, alpha);
}

void CGameObject::AddAnimation(string aniId, bool isLoop)
{
	
	LPANIMATION ani = CAnimations::GetInstance()->Get(aniId);
	ani->SetAnimationLoop(isLoop);
	animations.push_back(ani);
}


CGameObject::~CGameObject()
{

}