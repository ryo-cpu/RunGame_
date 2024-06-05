#include"Obj.h"
#include<math.h>  
bool OBJECT::isCollionHitBlock(const HitBlock*CheckBlock)
{
    return(Hit_Block.Upper_Left.x < CheckBlock->Lower_Right.x && CheckBlock->Upper_Left.x < Hit_Block.Lower_Right.x &&
        Hit_Block.Upper_Left.y < CheckBlock->Lower_Right.y && CheckBlock->Upper_Left.y < Hit_Block.Lower_Right.y);
}
void OBJECT::FixHitBlock(const HitBlock*CheckBlock, BlockInfo  blockinfo, BlockInfo  NearInfo)
{

    //上下左右の押し戻し距離を計算
    double left =CheckBlock->Upper_Left.x - Hit_Block.Lower_Right.x;
    double right =CheckBlock->Lower_Right.x - Hit_Block.Upper_Left.x;
    double up =CheckBlock->Upper_Left.y- Hit_Block.Lower_Right.y;
    double down =CheckBlock->Lower_Right.y- Hit_Block.Upper_Left.y;
    
    //ブロック情報から壁が存在しないときは、わざと大きな押し戻しを設定し
    // 以降の最小値を選ぶ候補から外されるようにする
    ///バグ（入っていけない分岐に入る）
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
   
    //fabsf()カッコ内に変数の絶対値を求める関数
    //dxはX方向の最短押し戻し移動量
    //dyはY方向の最短押し戻し移動量
    float dx = (fabsf(left) < fabsf(right)) ? left : right;
    float dy = (fabsf(up) < fabsf(down)) ? up : down;
   

    //エラー時両方とも壁がない時は衝突をしない
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

        //X方向とY方向の最短押し戻し距離を比較して,最短で戻せる方で戻す
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