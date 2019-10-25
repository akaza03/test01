#include "Character.h"



Character::Character()
{
	moveFlag = false;
	Gy = 0;
}


Character::~Character()
{
}


void Character::SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, int speed)
{
	auto sprite = Sprite::create(ImagePass);

	charaDir = stdir;
	startDir = charaDir;
	OldDir = charaDir;

	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));
	this->speed = speed;
}

AnimState Character::GetState()
{
	return state;
}

void Character::SetState(AnimState st)
{
	state = st;
}

DIR Character::GetDir()
{
	return charaDir;
}

void Character::SetDir(DIR dir)
{
	charaDir = dir;
}

void Character::SetSpeed(int sp)
{
	speed = sp;
}

int Character::GetSpeed()
{
	return speed;
}

void Character::SetMoveFlag(bool flag)
{
	moveFlag = flag;
}

void Character::SetMovePosX(float pos)
{
	movePos.x = pos;
}

void Character::SetMovePosY(float pos)
{
	movePos.y = pos;
}


