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
    // �t�@�C�����J��
    FILE* fp;
    errno_t err;
    //�P�f�[�^ 16bit�ő�l "65535,"(6����)�Ƃ��ĕ���������Ă����Ƃ��̂P�s�T�C�Y
    
    err = fopen_s(&fp, "./img./map/3map..csv", "rt");
    if (err)
    {
        printf("�t�@�C�����J���܂���");
        return true;
    }
   /*�t�@�C�����P�s����ǂ݂��A�P�s�̃f�[�^���𐔂� 
    */   
    
    char buff[MAX_LINE_LENGTH];
    fgets(buff, MAX_LINE_LENGTH, fp); // �ŏ��̍s��ǂݎ��

    // �J���}�̐��𐔂���
    char* token;
    char* next_token=NULL;
    token = strtok_s(buff, ",", &next_token);
    while (token != NULL)
    {
        mapXnum++;
        token = strtok_s(NULL, ",", &next_token);
    }
    //while (c != '\n' && c != EOF) {
    //    // �ǂݎ�����������J���}�Ȃ�1�J�E���g���₷
    //    c = fgetc(fp);
    //    if (c == ',') {
    //        mapXnum++;
    //    }
    //}
    mapXnum++;
    int bufferLen = mapXnum * 6 + 1;
    //�P�s���̃o�b�t�@�m��
    char* buf = new char[bufferLen];
    char* ptmp = buf;
    //�t�@�C���|�C���^��擪�ɖ߂��s����ǂ�
    fseek(fp, 0, SEEK_SET);
    bool firstRow = true;
    while (fgets(buf, bufferLen - 1, fp) != NULL)
    {
        mapYnum++;
    }
    //2�����z��𓮓I�m�ۂ��� map[row][col] �Ƃ��ē��I�m�ۂ���
    mapData = new int* [mapYnum];
    int ix, iy;
    for (iy = 0; iy < mapYnum; iy++)
    {
        mapData[iy] = new int[mapXnum];
    }
    //�t�@�C���|�C���^��擪�ɖ߂�
    fseek(fp, 0, SEEK_SET);
    // �t�@�C������f�[�^��z��Ɉڂ�
    char* readPoint;
    char* firstPoint;
    for (iy = 0; iy < mapYnum; iy++)
    {
        // 1�s��荞��
        fgets(buf, bufferLen - 1, fp);
        readPoint = firstPoint = buf;
        for (ix = 0; ix < mapXnum; ix++)
        {
            //�J���}�܂�readPoint�̈ʒu��i�߂�
            while (',' != *readPoint && '\n' != *readPoint)
            {
                readPoint++;
            }
            // �J���}��NULL�����ɒu������
            *readPoint = '\0';
            //���̎��_��firstPoint - readPoint�Ԃŕ����񂪊�������̂Ő��l�ɕϊ�
            mapData[iy][ix] = atoi(firstPoint);
            //���̃f�[�^�ǂݎ��ʒu�܂Ői�߂�
            readPoint++;
            firstPoint = readPoint;
        }
    }
    // �t�@�C�������
    fclose(fp);
    // �o�b�t�@�J��
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

    //�u���b�N��1�����󔒂��H
    if (GetBlockTypeMap(x + Back_Block, y) == 0&&x!=0)
    {
        ret |= BLOCK_LEFT;
    }
    //�u���b�N��1�E���󔒂��H
    if (GetBlockTypeMap(x + Next_Block, y) == 0)
    {
        ret |= BLOCK_RIGHT;
    }
    //�u���b�N��1�オ�󔒂��H
    if (GetBlockTypeMap(x, y + Back_Block) == 0&&y != 0)
    {
        ret |= BLOCK_UP;
    }

    //�u���b�N��1�����󔒂��H
    if (GetBlockTypeMap(x, y + Next_Block) == 0)
    {
        ret |= BLOCK_DOWN;
    }

    return ret;
    
}
unsigned char map::GetBlockTypeMap(int x, int y)///�G���[�̌�������
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
