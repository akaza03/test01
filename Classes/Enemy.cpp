#include "Enemy.h"



Enemy::Enemy()
{
	Sprite::create("image/Sprites/enemies/crab-idle/crab-idle-1.png");
	setPosition(cocos2d::Vec2(100, 100));
	_state = AnimState::IDLE;
	_oldState = AnimState::STATE_MAX;

	_charaDir = DIR::RIGHT;
	_startDir = _charaDir;
	_oldDir = _charaDir;

	this->_speed = 5;

	this->scheduleUpdate();
}


Enemy::~Enemy()
{
}

void Enemy::update(float d)
{
}

void Enemy::AnimStateUpdate()
{

}
