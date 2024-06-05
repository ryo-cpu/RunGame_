#include"Dxlib.h"
#include"player.h"
#include<math.h>

void PLAYER::SetPosition()
{
    Position.x = Player_Position_X;
    Position.y = Player_Position_Y;
    Position.z = Player_Position_Z;

}
void PLAYER::SetHitBlock()
{
    Hit_Block.Depth = Player_Size;
    Hit_Block.Hight = Player_Size;
    Hit_Block.Width = Player_Size;
    Hit_Block.Upper_Left.x = Position.x - Hit_Block.Width/2;
    Hit_Block.Upper_Left.y = Position.y - Hit_Block.Hight/2;
    Hit_Block.Upper_Left.z = Position.z - Hit_Block.Depth / 2;
    Hit_Block.Lower_Right.x = Hit_Block.Upper_Left.x + Hit_Block.Width;
    Hit_Block.Lower_Right.y= Hit_Block.Upper_Left.y + Hit_Block.Hight;
    Hit_Block.Lower_Right.z= Hit_Block.Upper_Left.z + Hit_Block.Depth;



}
void PLAYER::SetSpeed()
{
    Speed = { 0 };
}
PLAYER::PLAYER()
{
    SetPosition();
    SetHitBlock();
    SetSpeed();
}
PLAYER::~PLAYER()
{

}
void PLAYER::DrawPlayer()
{
    DrawBox(static_cast<int>(Hit_Block.Upper_Left.x), static_cast<int>(Hit_Block.Upper_Left.y),
      static_cast<int> ( Hit_Block.Lower_Right.x), static_cast<int>(Hit_Block.Lower_Right.y), GetColor(255, 11, 22), TRUE);
}
void PLAYER:: UpdataPlayer()
{
    VECTOR GraVity = VGet(0, 0.5f, 0);
    VECTOR Jump = { 0 };
    
    if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0&&(isGround))
    {
        AwayGround();
       
       
    }
     if (isJump)
    {

        
        AwayGround();
        Jump = VGet(0, -1*janpTime/10, 0);
       
    }
    

    Speed =(VScale(VAdd(Jump, GraVity),moveSpeed));
        
 
   
    if (Position.x < Player_Position_X)
    {
        Position = VAdd(Position, VGet(1, 0, 0));
    }
    Position = VAdd(Position, Speed);
    SetHitBlock();
}
VECTOR PLAYER::GetPosition()
{
    return Position;
}
VECTOR PLAYER::GetSpeed()
{
    return Speed;
}
HitBlock PLAYER::GetHitBlock()
{
    return Hit_Block;
}