#include"Obj.h"
#include<math.h>  
bool OBJECT::isCollionHitBlock(const HitBlock*CheckBlock)
{
    return(Hit_Block.Upper_Left.x < CheckBlock->Lower_Right.x && CheckBlock->Upper_Left.x < Hit_Block.Lower_Right.x &&
        Hit_Block.Upper_Left.y < CheckBlock->Lower_Right.y && CheckBlock->Upper_Left.y < Hit_Block.Lower_Right.y);
}
void OBJECT::FixHitBlock(const HitBlock*CheckBlock, BlockInfo  blockinfo, BlockInfo  NearInfo)
{

    //�㉺���E�̉����߂��������v�Z
    double left =CheckBlock->Upper_Left.x - Hit_Block.Lower_Right.x;
    double right =CheckBlock->Lower_Right.x - Hit_Block.Upper_Left.x;
    double up =CheckBlock->Upper_Left.y- Hit_Block.Lower_Right.y;
    double down =CheckBlock->Lower_Right.y- Hit_Block.Upper_Left.y;
    
    //�u���b�N��񂩂�ǂ����݂��Ȃ��Ƃ��́A�킴�Ƒ傫�ȉ����߂���ݒ肵
    // �ȍ~�̍ŏ��l��I�Ԍ�₩��O�����悤�ɂ���
    ///�o�O�i�����Ă����Ȃ�����ɓ���j
    if (!(blockinfo & BLOCK_LEFT))
    {
        left = -CheckBlock->Width;
    }
    else if (!(blockinfo & BLOCK_RIGHT))
    {
        right =CheckBlock->Width;
    }
    else if (!(blockinfo & BLOCK_UP))
    {
        up = -CheckBlock->Hight;
    }
    else if (!(blockinfo & BLOCK_DOWN))
    {
        down =CheckBlock->Hight;
    }
   
    //fabsf()�J�b�R���ɕϐ��̐�Βl�����߂�֐�
    //dx��X�����̍ŒZ�����߂��ړ���
    //dy��Y�����̍ŒZ�����߂��ړ���
    float dx = (fabsf(left) < fabsf(right)) ? left : right;
    float dy = (fabsf(up) < fabsf(down)) ? up : down;
   

    //�G���[�������Ƃ��ǂ��Ȃ����͏Փ˂����Ȃ�
    if (fabsf(dx) == fabsf(dy))
    {
        return;
    }
   
    if (NearInfo != BLOCK_DOWN)
    {
        
        TouchGround();
   }
   /* else
    {*/

        //X������Y�����̍ŒZ�����߂��������r����,�ŒZ�Ŗ߂�����Ŗ߂�
        if (fabsf(dx) < fabsf(dy))
        {
            Hit_Block.Upper_Left.x += dx;
            Hit_Block.Lower_Right.x += dx;
        }

        else
        {
            Hit_Block.Upper_Left.y += dy;
            Hit_Block.Lower_Right.y += dy;
            
        }
 /*   }*/
}
void OBJECT:: FixPosition()
{
    Position.x = Hit_Block.Upper_Left.x + Hit_Block.Width/2;
    Position.y = Hit_Block.Upper_Left.y + Hit_Block.Hight/2;
    Position.z = Hit_Block.Upper_Left.z + Hit_Block.Depth/2;

}
OBJECT::OBJECT()
{

}
OBJECT::~OBJECT()
{

}
void OBJECT::SetHitBlock()
{
    Hit_Block.Depth = 32;
    Hit_Block.Hight = 32;
    Hit_Block.Width = 32;
    Hit_Block.Upper_Left.x = Position.x - Hit_Block.Width / 2;
    Hit_Block.Upper_Left.y = Position.y - Hit_Block.Hight / 2;
    Hit_Block.Upper_Left.z = Position.y - Hit_Block.Depth / 2;
    Hit_Block.Lower_Right.x = Hit_Block.Upper_Left.x + Hit_Block.Width;
    Hit_Block.Lower_Right.y = Hit_Block.Upper_Left.y + Hit_Block.Hight;
    Hit_Block.Lower_Right.z = Hit_Block.Upper_Left.z + Hit_Block.Depth;
}

void OBJECT::TouchGround()
{
    isGround = true;
    
        isJump=false;
        janpTime = 50;
  
}
void OBJECT::AwayGround()
{
   
    isGround = false;
    isJump = true;
    janpTime--;
    if (janpTime == 0)
    {
        isJump = false;
    }
    
    if (janpTime<0)
    {
        Position = VAdd(Position,VGet(0,-5.f*janpTime, 0));
    }
    
    
}