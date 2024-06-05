#include<iostream>
#include <stdlib.h>
#include<string.h>
#include"DxLib.h"
#include"map.h"
#define MAX_LINE_LENGTH 1024
#define MAX_FIELDS 10


bool map::LodzMapLayer()
{


    mapData = NULL;
    mapXnum = 0;
    mapYnum = 0;
    // ファイルを開く
    FILE* fp;
    errno_t err;
    //１データ 16bit最大値 "65535,"(6文字)として文字列入ってきたときの１行サイズ
    
    err = fopen_s(&fp, "./img./map/3map..csv", "rt");
    if (err)
    {
        printf("ファイルを開けません");
        return true;
    }
   /*ファイルを１行分空読みし、１行のデータ数を数え 
    */   
    
    char buff[MAX_LINE_LENGTH];
    fgets(buff, MAX_LINE_LENGTH, fp); // 最初の行を読み取る

    // カンマの数を数える
    char* token;
    char* next_token=NULL;
    token = strtok_s(buff, ",", &next_token);
    while (token != NULL)
    {
        mapXnum++;
        token = strtok_s(NULL, ",", &next_token);
    }
    //while (c != '\n' && c != EOF) {
    //    // 読み取った文字がカンマなら1つカウント増やす
    //    c = fgetc(fp);
    //    if (c == ',') {
    //        mapXnum++;
    //    }
    //}
    mapXnum++;
    int bufferLen = mapXnum * 6 + 1;
    //１行分のバッファ確保
    char* buf = new char[bufferLen];
    char* ptmp = buf;
    //ファイルポインタを先頭に戻し行数を読む
    fseek(fp, 0, SEEK_SET);
    bool firstRow = true;
    while (fgets(buf, bufferLen - 1, fp) != NULL)
    {
        mapYnum++;
    }
    //2次元配列を動的確保する map[row][col] として動的確保する
    mapData = new int* [mapYnum];
    int ix, iy;
    for (iy = 0; iy < mapYnum; iy++)
    {
        mapData[iy] = new int[mapXnum];
    }
    //ファイルポインタを先頭に戻す
    fseek(fp, 0, SEEK_SET);
    // ファイルからデータを配列に移す
    char* readPoint;
    char* firstPoint;
    for (iy = 0; iy < mapYnum; iy++)
    {
        // 1行取り込み
        fgets(buf, bufferLen - 1, fp);
        readPoint = firstPoint = buf;
        for (ix = 0; ix < mapXnum; ix++)
        {
            //カンマまでreadPointの位置を進める
            while (',' != *readPoint && '\n' != *readPoint)
            {
                readPoint++;
            }
            // カンマをNULL文字に置き換え
            *readPoint = '\0';
            //この時点でfirstPoint - readPoint間で文字列が完成するので数値に変換
            mapData[iy][ix] = atoi(firstPoint);
            //次のデータ読み取り位置まで進める
            readPoint++;
            firstPoint = readPoint;
        }
    }
    // ファイルを閉じる
    fclose(fp);
    // バッファ開放
    delete[] buf;

    return false;
}
void map::DrawMap()
{
    int startX=static_cast<int>(ScrrenPositionX / mapChipSize);
    int offsetX = ScrrenPositionX % mapChipSize;

    for (int i = 0; i < mapScreenY; i++)
    {
        for (int j = 0; j < mapScrrenX; j++)
        {
            int mapX = j + startX;
            
            
            int imgIndex = mapData[i][mapX];
            if (imgIndex != -1)
            {
                int imgHandl = mapChip[imgIndex];
                DrawGraph(j * mapChipSize-offsetX, i * mapChipSize,  imgHandl, TRUE);

                
            }
           

        }
    }

}
void map::LodMapChip()
{
    LoadDivGraph("img/map/mapimg.png", 10, 2, 5, mapChipSize, mapChipSize, mapChip);
}
void map::ScrollMap()
{
   
        ScrrenPositionX += MoveScreenSpeed*Accel;
    
   
    
}
void map::UpdataScreenSpeed()
{
    Accel+=0.01f;
}
bool map::isHitCalc(OBJECT*obj)
{
    bool hitFlag = false;
    HitBlock *BlockRect=new HitBlock;
    int startX = static_cast<int>(ScrrenPositionX / mapChipSize);
    int offsetX = ScrrenPositionX % mapChipSize;

    for (int y = 0; y < mapScreenY; y++)
    {
       
          
        for (int x = 0; x < mapScrrenX; x++)
        {
            int mapX = x + startX;
            if (mapX >= mapXnum)
            {
                ScrrenPositionX = 0;
            }
            if (mapData[y][mapX]!= -1)
            {
                BlockRect->Upper_Left.y = y * (static_cast<float>(mapChipSize));
                BlockRect->Lower_Right.y = BlockRect->Upper_Left.y + BlockRect->Hight;
                BlockRect->Upper_Left.x = x * mapChipSize-offsetX;
                BlockRect->Lower_Right.x = BlockRect->Upper_Left.x + BlockRect->Width;
                DrawBox(static_cast<int>(BlockRect->Upper_Left.x), static_cast<int>(BlockRect->Upper_Left.y), static_cast<int>(BlockRect->Lower_Right.x), static_cast<int>(BlockRect->Lower_Right.y), GetColor(100, 500, 50), TRUE);
             
               
            }
            if (obj->isCollionHitBlock(BlockRect))
            {

                BlockInfo bi = GetBlockTypeMap(mapX, y);
                BlockInfo b = GetBlockInfo(mapX, y);


                obj->FixHitBlock(BlockRect, bi,b);
                obj->FixPosition();

                hitFlag = true;
            }
          
            }
        

    }
    return hitFlag;
}
BlockInfo  map::GetBlockInfo(int x, int y)
{
     BlockInfo ret = 0;

    //ブロックの1つ左が空白か？
    if (GetBlockTypeMap(x + Back_Block, y) == 0&&x!=0)
    {
        ret |= BLOCK_LEFT;
    }
    //ブロックの1つ右が空白か？
    if (GetBlockTypeMap(x + Next_Block, y) == 0)
    {
        ret |= BLOCK_RIGHT;
    }
    //ブロックの1つ上が空白か？
    if (GetBlockTypeMap(x, y + Back_Block) == 0&&y != 0)
    {
        ret |= BLOCK_UP;
    }

    //ブロックの1つ下が空白か？
    if (GetBlockTypeMap(x, y + Next_Block) == 0)
    {
        ret |= BLOCK_DOWN;
    }

    return ret;
    
}
unsigned char map::GetBlockTypeMap(int x, int y)///エラーの原因かも
{
    if (x < 0 || y < 0 || x >= ScreenSizeX || y >= ScreenSizeY)
    {
        return 0;
    }
    return mapData[y][x];
}
int map::GetScrenPosition()
{
    return ScrrenPositionX;
}
