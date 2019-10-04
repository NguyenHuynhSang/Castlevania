#pragma once
#include<Windows.h>
#include<d3dx9.h>
class Camera
{
private:
	float camX = 0.0f;
	float camY = 0.0f;
	bool allowScrollCam;
	static Camera * __instance;
public:
	Camera();
	void SetAllowScrollCam(bool flag) {
		this->allowScrollCam = flag;
	}
	bool CheckIsAllowScrollCam() {
		return this->allowScrollCam;
	}
	static Camera * GetInstance();
	void GetCamera(float &x, float &y) {
		x = this->camX;
		y = this->camY;
	}
	D3DXVECTOR2 GetCamera() {
		return D3DXVECTOR2(	this->camX,this->camY);
	}
	void SetCamera(float x, float y) {
		this->camX = x;
		this->camY = y;
	}
	
	~Camera();
};

