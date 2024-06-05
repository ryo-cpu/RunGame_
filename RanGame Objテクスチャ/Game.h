#pragma once
#include"enemy.h"
#include"map.h"
#include"3d.h"
#include<vector>
static enum Stage_Level
{
   Home,Game,End,Switch,Clear
};
class GAME
{
public:
	GAME();
	~GAME();
	void Ran();
	void Set_Stage_Level();
	void Switch_Stage_Level(int NEXT);
	void AddEnemy(std::vector<ENEMY> &EnemyS);
	int Timer = 0;
	int NowTime;
	int StatTime;
	bool IsContnue(PLAYER*player);
private:
	int Stage_Level=Home;
	int AddEnmyTIME=10;
	bool isAddENEMY = true;
};



