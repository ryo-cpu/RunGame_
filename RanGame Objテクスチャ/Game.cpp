#include<Windows.h>
#include"DxLib.h"
#include"Game.h"
#include"player.h"
#include"map.h"
#include"enemy.h"
#include<vector>
#include"DebugDraw/DebugDraw/DebugDraw.h"
GAME::GAME()
{

}
GAME::~GAME()
{
	
}

void GAME::Ran()
{
	SetFontSize(64);

	sreedObject* SreeD = new sreedObject;
	std::vector<ENEMY>EnemyS;
	PLAYER* player = new PLAYER;
	map* MAP = new map;
	OBJECT* Pobj = player;
	bool isErr = false;
	MAP->LodMapChip();
	SreeD->SetComer();
	SreeD->SetModel();
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		
		ClearDrawScreen();
		DrawGrid(100, 100);
		if (Stage_Level == Home)
		{
			/*SreeD->MoveComer();
			SreeD->LotModel();*/
			SreeD->DrawModel();
			DrawString(500, 580, "Next SPACE KEY", GetColor(250, 500, 30));
			if (CheckHitKey(KEY_INPUT_SPACE))
			{
				Timer = 0;
				StatTime = GetNowCount();
				Stage_Level = Game;
				player = new PLAYER;
				MAP = new map;
				
				Pobj = player;
				isErr = MAP->LodzMapLayer();
				MAP->LodMapChip();
				if (isErr)
				{
					break;
				}
				SreeD->ResetModel();
			}
		}
		else if (Stage_Level == Game)
		{
			NowTime = GetNowCount();
			Timer = (NowTime - StatTime)/1000;
			/*SreeD->MoveComer();*/
			player->UpdataPlayer();
			for (int i = 0; i < EnemyS.size(); i++)
			{
				EnemyS[i].Updata();
			}
			if (Timer% AddEnmyTIME == 0&&isAddENEMY)
			{
				AddEnemy(EnemyS);
				isAddENEMY = false;
			}
			else if (Timer % AddEnmyTIME != 0)
			{
				isAddENEMY = true;
			}
			for (int i = 0; i < EnemyS.size(); i++)
			{
				VECTOR Pos;
 				Pos = EnemyS[i].GetPosition();
				if (Pos.x <= 0)
				{
					EnemyS.erase(EnemyS.begin() + i);
				}
				
			}

			
			/*SreeD->MoveComer();*/
			if (Timer % 20 == 0&&Timer!=0)
			{
				DrawFormatString(500, 0, GetColor(250, 500, 30), " Žc‚è:%d ", 90-Timer);
				MAP->UpdataScreenSpeed();

				AddEnmyTIME = AddEnmyTIME > 0 ? AddEnmyTIME-- : 1;
			}
			MAP->ScrollMap();
			if (MAP->isHitCalc(Pobj))
			{
				player->FixPosition();
			}
			/*SreeD->ScaleModel();*/
			SreeD->UpdataModel();
			SreeD->DrawModel();
			MAP->DrawMap();
			player->DrawPlayer();
			for (int i = 0; i < EnemyS.size(); i++)
			{
				EnemyS[i].Draw();
				if (EnemyS[i].isCollisonPlayer(player))
				{
					Stage_Level = End;
				}
			}
			
			
			if (Timer==90)
			{
				Stage_Level = Clear;
			}
			if (!IsContnue(player))
			{
				Stage_Level = End;
			}
			VECTOR M = MV1GetPosition(SreeD->GetModelHandle());
			DrawFormatString(0, 100, GetColor(250, 700, 30), "x:: %f ", M.x);
			DrawFormatString(0, 200, GetColor(250, 800, 30), "y:: %f ", M.y);
			DrawFormatString(0, 300, GetColor(250, 900, 30), "z:: %f ", M.z);


			DrawFormatString(0, 0, GetColor(250, 500, 30), "TIME:: %d ", Timer);
			
			


		}
		else if(Stage_Level==End)
		{
			EnemyS.clear();
			DrawString(500, 580, "GAME OVAR", GetColor(250, 500, 30));
			DrawString(500, 780, "Next SPACE A", GetColor(250, 500, 30));
			/*SreeD->MoveComer();*/
			SreeD->DrawModel();

			if (CheckHitKey(KEY_INPUT_A))
			{
				Stage_Level = Home;
				/*SreeD->ResetModel();*/

			}
		}
		else if (Stage_Level == Clear)
		{
			EnemyS.clear();
			DrawString(500, 580, "GAME CLEAR", GetColor(250, 500, 30));
			DrawString(500, 780, "Next SPACE A", GetColor(250, 500, 30));
			if (CheckHitKey(KEY_INPUT_A))
			{
				Stage_Level = Home;
				SreeD->ResetModel();

			}
		/*	SreeD->MoveComer();*/
			SreeD->DrawModel();

		}
		
		ScreenFlip();
	}
	/*sreedObject* SreeD = new sreedObject;
	std::vector<ENEMY>EnemyS;
	PLAYER* player = new PLAYER;
	map* MAP = new map;
	OBJECT* Pobj = player;*/
	delete SreeD;

	delete player;
	delete MAP;

}

bool GAME::IsContnue(PLAYER* player)
{
	VECTOR Jag;
	Jag = player->GetPosition();
	return Jag.x > 0 && Jag.x < ScreenSizeX && Jag.y < ScreenSizeY;
}
void GAME::AddEnemy(std::vector<ENEMY> &EnemyS)
{
	EnemyS.push_back(ENEMY(VGet(ScreenSizeX - 1, 800, 0)));
}
