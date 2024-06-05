
#include"enemy.h"
void ENEMY::Draw()
{
    DrawBox(static_cast<int>(Hit_Block.Upper_Left.x), static_cast<int>(Hit_Block.Upper_Left.y),
        static_cast<int> (Hit_Block.Lower_Right.x), static_cast<int>(Hit_Block.Lower_Right.y), GetColor(255, 11, 22), TRUE);
} 
void ENEMY::SetPosition(VECTOR InitPos)
{
    Position = InitPos;
    SetHitBlock();
}
ENEMY::ENEMY(VECTOR InitPos)
{
    SetPosition(InitPos);
}
HitBlock ENEMY::GetHitBlock()
{
    return Hit_Block;
}
bool ENEMY::isCollisonPlayer(PLAYER* player)
{
    HitBlock* jagBlock=new HitBlock;
    *jagBlock=player->GetHitBlock();
   
    return  isCollionHitBlock(jagBlock);
}
void ENEMY::Updata()
{
    Position=VAdd(Position, Move);
    SetHitBlock();
}

VECTOR ENEMY::GetMove()
{
    return Move;
}
VECTOR ENEMY::GetPosition()
{
    return Position;
}