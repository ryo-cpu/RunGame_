#pragma once
#include"player.h"
const int  mapChipSize = 32;
const int ScreenSizeY = 1080;
const int ScreenSizeX = 1920;
const int Next_Block = 1;
const int Back_Block = -1;

class map
{
private:
	int** mapData;
	int mapXnum=0;
	int mapYnum=0;
	int mapScrrenX = ScreenSizeX / mapChipSize + 1;
	int mapScreenY = ScreenSizeY / mapChipSize + 1;
	int mapChip[10];
	int ScrrenPositionX = 0;
	int MoveScreenSpeed=1;
	float Accel = 1;

public:
	void DrawMap();
	bool LodzMapLayer();
	void LodMapChip();
	void ScrollMap();
	void UpdataScreenSpeed();
	bool isHitCalc(OBJECT* obj);
	BlockInfo GetBlockInfo(int x, int y);
	unsigned char GetBlockTypeMap(int x, int y);
	int GetScrenPosition();
};