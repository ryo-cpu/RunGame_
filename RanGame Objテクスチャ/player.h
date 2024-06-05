#pragma once
#include"Obj.h"
const float Player_Position_X=100.0f;
const float Player_Position_Y=600.0f;
const float Player_Position_Z = 1.0f;
const int Player_Size = 32;

class PLAYER:public OBJECT
{
public:
	PLAYER();
	~PLAYER();
	///	セッター
	void SetPosition();
	void SetHitBlock();
	void SetSpeed();
	
    /// ゲッター
    HitBlock GetHitBlock();
	VECTOR GetPosition();
	VECTOR GetSpeed();
	void UpdataPlayer();
	void DrawPlayer();
private:
	VECTOR Speed;
	float moveSpeed =8.0f;
	
	
};