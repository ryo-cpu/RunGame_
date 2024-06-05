#pragma once
#include"Collision.h"
//ブロック壁情報
#define BLOCK_LEFT  0x01     //　0001
#define BLOCK_RIGHT 0x02    //  0010
#define BLOCK_UP    0x04    //  0100
#define BLOCK_DOWN  0x08    //  1000
#define BLOCK_FLONT 0x16
#define BLOCK_BACK 0x32

typedef unsigned char BlockInfo;
class OBJECT
{
public:
	OBJECT();
	~OBJECT();
	void SetHitBlock();
	void FixHitBlock(const HitBlock* CheckBlock, BlockInfo  blockinfo,BlockInfo  NearInfo);
	bool isCollionHitBlock(const HitBlock* CheckBlock);
	void FixPosition();
	void AwayGround();
	void TouchGround();
	
protected:
	VECTOR Position;
	HitBlock Hit_Block;
	bool isGround = false;
	bool isJump = false;
	int janpTime = 50;
	

};

