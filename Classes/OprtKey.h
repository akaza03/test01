#pragma once

#include "OprtState.h"

class OprtKey
	:public OprtState
{
public:
	OprtKey();
	~OprtKey();
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed);								//	�L�����N�^�[�ł͂Ȃ��I�u�W�F�N�g�p
	cocos2d::EventListener* oprtInit(cocos2d::Sprite *sprite, int speed, Character *chara);				//	�L�����N�^�[�p
};

