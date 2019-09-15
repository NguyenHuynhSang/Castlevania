#pragma once
#ifndef _GAMEOBJECT_CLASS
#define _GAMEOBJECT_CLASS
#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include"define.h"
#include "Sprites.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box
#define ID_TEX_SPRITE_BBOX -101
class CGameObject; 
typedef CGameObject * LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent * LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;
	CCollisionEvent(float t, float nx, float ny, LPGAMEOBJECT obj = NULL) { this->t = t; this->nx = nx; this->ny = ny; this->obj = obj; }

	static bool compare(const LPCOLLISIONEVENT &a, LPCOLLISIONEVENT &b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x; 
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;	 

	int state;

	DWORD dt; 

	vector<LPANIMATION> animations;


	bool setDestroy=false;
	bool isDestroyed = false;
	bool isCollide = true;
public: 
	void SetDestroy() {
		this->setDestroy = true;
	}
	bool CheckDestroyed() {
		return this->isDestroyed;
	}
	void TurnOffCollision() {
		this->isCollide = false;
	}
	void SetPosition(float x, float y) { this->x = x, this->y = y+ GAME_WORLD_Y; }// cộng thêm phần board
	void SetPositionInWorld(float x, float y) { this->x = x, this->y = y; }// cộng thêm phần board
	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float &x, float &y) { x = this->x; y = this->y; }
	void GetSpeed(float &vx, float &vy) { vx = this->vx; vy = this->vy; }
	void ResetFrame(int frameID);
	int GetState() { return this->state; }

	void RenderBoundingBox(); // dùng check va chạm
	void RenderSpriteBox(); // vẽ khung lấy sprite dùng tính toán vị trí
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT> *coObjects, vector<LPCOLLISIONEVENT> &coEvents);
	void FilterCollision(
		vector<LPCOLLISIONEVENT> &coEvents, 
		vector<LPCOLLISIONEVENT> &coEventsResult, 
		float &min_tx, 
		float &min_ty, 
		float &nx, 
		float &ny);

	void AddAnimation(string aniId);
	bool IsColliding(CGameObject *a, CGameObject *b) {
		float top, left, right, button;
		a->GetBoundingBox(left, top, right, button);
		float l, t, r, bt;
		b->GetBoundingBox(l, t, r, bt);
		return AABB(l, t, r, bt, left, top, right, button);
	}
	// thuat toan xu ly va cham AABB
	bool AABB(float l, float t, float r, float b, float l1, float t1, float r1, float b1);

	CGameObject();

	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom) = 0;
	virtual void GetSpriteBox(float &width, float &height) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }


	~CGameObject();
};
#endif
