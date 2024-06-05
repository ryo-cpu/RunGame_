#pragma once
#include"player.h"
class ENEMY:public OBJECT
{
private:
    VECTOR Move=VGet(-1,0,0);
public:
    VECTOR GetMove();
    VECTOR GetPosition();
    void SetMove();
    void AddMove();
    ENEMY(VECTOR InitPos);
    void SetPosition(VECTOR InitPos);
    void Updata();
    void Draw();
    HitBlock GetHitBlock();
    bool isCollisonPlayer(PLAYER*player);

};