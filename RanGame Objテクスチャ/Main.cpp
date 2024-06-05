#include<Windows.h>
#include"DxLib.h"
#include"Game.h"
#include"player.h"
#include"map.h"
#include"3d.h"
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevinstance, LPSTR IpCmdshow, int nCmdshow)
{
	///--------��{�ݒ�---------///
	///�E�B���h�E���[�h
	ChangeWindowMode(TRUE);
	///�E�B���h�E����
	SetMainWindowText("Srpg");
	///�E�B���h�E�T�C�Y�ƃJ�[���[���[�h
	SetGraphMode(ScreenSizeX, ScreenSizeY, mapChipSize);
	ChangeWindowMode(TRUE);
	///���C�u�����̏�����
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