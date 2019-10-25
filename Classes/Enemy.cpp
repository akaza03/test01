#include "Enemy.h"



Enemy::Enemy()
{
	Sprite::create("image/Sprites/enemies/crab-idle/crab-idle-1.png");
	setPosition(cocos2d::Vec2(100, 100));
	state = AnimState::IDLE;
	oldState = AnimState::STATE_MAX;

	charaDir = DIR::RIGHT;
	startDir = charaDir;
	OldDir = charaDir;

	this->speed = 5;

	this->scheduleUpdate();
}


Enemy::~Enemy()
{
}

void Enemy::update(float d)
{
}
