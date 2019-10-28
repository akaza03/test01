#include "Character.h"

#include "OprtKey.h"
#include "OprtTouch.h"


Character::Character()
{
	moveFlag = false;
	Gy = 0;
}


Character::~Character()
{
}


void Character::SetInit(std::string ImagePass, DIR stdir, cocos2d::Vec2 pos, int speed, cocos2d::Scene *scene)
{
	auto sprite = Sprite::create(ImagePass);

	charaDir = stdir;
	startDir = charaDir;
	OldDir = charaDir;

	setPosition(cocos2d::Vec2(pos.x + sprite->getContentSize().width / 2, pos.y));
	this->speed = speed;

	//	プラットフォームによって操作方法を変える
	//if ((CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX))
	//{
	//	_oprtState = new OprtKey();
	//}
	//else
	{
		_oprtState = new OprtTouch();
	}

	//	操作イベントの作成
	scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_oprtState->oprtInit(this, speed, this),scene);
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


