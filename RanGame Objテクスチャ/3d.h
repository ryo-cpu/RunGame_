#pragma once
#include"DxLib.h"
class sreedObject
{
private:
	int ModelHandle;
	int StatTime = GetNowCount();
	int NowTime;
	VECTOR CamerPosition;
	int  Direction = 1;
	VECTOR ModelPosition;

public:
	void SetComer();
	const int GetModelHandle();
	void MoveComer();
	void SetModel();
	void DrawModel();
	void LotModel();
	void ScaleModel();
	void ResetModel();
	void UpdataModel();
	~sreedObject();
};