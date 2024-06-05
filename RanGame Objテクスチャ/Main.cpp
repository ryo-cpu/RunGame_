#include<Windows.h>
#include"DxLib.h"
#include"Game.h"
#include"player.h"
#include"map.h"
#include"3d.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR IpCmdshow, int nCmdshow)
{
	///--------基本設定---------///
	///ウィンドウモード
	ChangeWindowMode(TRUE);
	///ウィンドウ命名
	SetMainWindowText("Srpg");
	///ウィンドウサイズとカーラーモード
	SetGraphMode(ScreenSizeX, ScreenSizeY, mapChipSize);
	ChangeWindowMode(TRUE);
	///ライブラリの初期化
	if (DxLib_Init() == -1)
	{
		return -1;
	}
	
	GAME* game;
	game = new GAME;
	game->Ran();
	delete game;
	DxLib_End();
	return 0;
}